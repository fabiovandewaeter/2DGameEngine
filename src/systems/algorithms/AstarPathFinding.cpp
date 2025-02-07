#include "systems/algorithms/AstarPathFinding.hpp"
#include "map/Map.hpp"
#include "map/Chunk.hpp"

std::vector<SDL_Point> AstarPathFinding::findPath(Map *map, int startX, int startY, int goalX, int goalY)
{
    // Conversion des positions pixels -> indices de cases
    int tileStartX = startX / TILE_SIZE;
    int tileStartY = startY / TILE_SIZE;
    int tileGoalX = goalX / TILE_SIZE;
    int tileGoalY = goalY / TILE_SIZE;

    // File de priorité (open set) pour les nœuds
    std::priority_queue<Node *, std::vector<Node *>, CompareNode> openSet;
    // Un unordered_map pour retrouver rapidement un nœud par ses coordonnées (en grille)
    std::unordered_map<std::pair<int, int>, Node *, pair_hash> allNodes;

    // Création du nœud de départ
    Node *startNode = new Node;
    startNode->x = tileStartX;
    startNode->y = tileStartY;
    startNode->g = 0;
    startNode->h = heuristic(tileStartX, tileStartY, tileGoalX, tileGoalY);
    startNode->f = startNode->g + startNode->h;
    startNode->parent = nullptr;

    openSet.push(startNode);
    allNodes[{tileStartX, tileStartY}] = startNode;

    // Définition des 8 directions possibles (4 cardinales et 4 diagonales)
    const int dx[8] = {1, -1, 0, 0, 1, 1, -1, -1};
    const int dy[8] = {0, 0, 1, -1, 1, -1, 1, -1};

    while (!openSet.empty())
    {
        Node *current = openSet.top();
        openSet.pop();

        // Si on a atteint la destination
        if (current->x == tileGoalX && current->y == tileGoalY)
        {
            std::vector<SDL_Point> path = reconstructPath(current);
            // Libération de la mémoire des nœuds
            for (auto &pair : allNodes)
                delete pair.second;
            return path;
        }

        // Pour chaque voisin (8 directions)
        for (int i = 0; i < 8; i++)
        {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            // Vérification : on récupère le chunk correspondant à la case (les coordonnées sont en indices)
            Chunk *chunk = map->getChunk(nx, ny);
            if (!chunk)
                continue; // Hors limites de la carte
            if (chunk->isStructure(nx, ny))
                continue; // Obstacle présent

            // Pour un déplacement diagonal, éviter de "couper un coin"
            if (dx[i] != 0 && dy[i] != 0)
            {
                Chunk *chunkH = map->getChunk(current->x + dx[i], current->y);
                Chunk *chunkV = map->getChunk(current->x, current->y + dy[i]);
                if ((chunkH && chunkH->isStructure(current->x + dx[i], current->y)) ||
                    (chunkV && chunkV->isStructure(current->x, current->y + dy[i])))
                {
                    continue;
                }
            }

            // Coût du déplacement : 1 pour cardinal, 1.414 pour diagonal
            float tentative_g = current->g + ((dx[i] == 0 || dy[i] == 0) ? 1.0f : 1.414f);

            std::pair<int, int> neighborKey = {nx, ny};
            Node *neighbor = nullptr;
            if (allNodes.find(neighborKey) == allNodes.end())
            {
                // Création du nœud voisin s'il n'existe pas
                neighbor = new Node;
                neighbor->x = nx;
                neighbor->y = ny;
                neighbor->g = tentative_g;
                neighbor->h = heuristic(nx, ny, tileGoalX, tileGoalY);
                neighbor->f = neighbor->g + neighbor->h;
                neighbor->parent = current;
                allNodes[neighborKey] = neighbor;
                openSet.push(neighbor);
            }
            else
            {
                neighbor = allNodes[neighborKey];
                if (tentative_g < neighbor->g)
                {
                    neighbor->g = tentative_g;
                    neighbor->f = neighbor->g + neighbor->h;
                    neighbor->parent = current;
                    // On réinsère le nœud dans la file
                    openSet.push(neighbor);
                }
            }
        }
    }

    // Aucun chemin trouvé : on libère la mémoire et on renvoie un chemin vide.
    for (auto &pair : allNodes)
        delete pair.second;
    return std::vector<SDL_Point>();
}
void AstarPathFinding::findPath(Map *map, int startX, int startY, int goalX, int goalY, std::vector<SDL_Point> *result)
{
    // Conversion des positions pixels -> indices de cases
    int tileStartX = startX / TILE_SIZE;
    int tileStartY = startY / TILE_SIZE;
    int tileGoalX = goalX / TILE_SIZE;
    int tileGoalY = goalY / TILE_SIZE;

    // File de priorité (open set) pour les nœuds
    std::priority_queue<Node *, std::vector<Node *>, CompareNode> openSet;
    // Un unordered_map pour retrouver rapidement un nœud par ses coordonnées (en grille)
    std::unordered_map<std::pair<int, int>, Node *, pair_hash> allNodes;

    // Création du nœud de départ
    Node *startNode = new Node;
    startNode->x = tileStartX;
    startNode->y = tileStartY;
    startNode->g = 0;
    startNode->h = heuristic(tileStartX, tileStartY, tileGoalX, tileGoalY);
    startNode->f = startNode->g + startNode->h;
    startNode->parent = nullptr;

    openSet.push(startNode);
    allNodes[{tileStartX, tileStartY}] = startNode;

    // Définition des 8 directions possibles (4 cardinales et 4 diagonales)
    const int dx[8] = {1, -1, 0, 0, 1, 1, -1, -1};
    const int dy[8] = {0, 0, 1, -1, 1, -1, 1, -1};

    while (!openSet.empty())
    {
        Node *current = openSet.top();
        openSet.pop();

        // Si on a atteint la destination
        if (current->x == tileGoalX && current->y == tileGoalY)
        {
            reconstructPath(current, result);
            // Libération de la mémoire des nœuds
            for (auto &pair : allNodes)
                delete pair.second;
            return;
        }

        // Pour chaque voisin (8 directions)
        for (int i = 0; i < 8; i++)
        {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            // Vérification : on récupère le chunk correspondant à la case (les coordonnées sont en indices)
            Chunk *chunk = map->getChunk(nx, ny);
            if (!chunk)
                continue; // Hors limites de la carte
            if (chunk->isStructure(nx, ny))
                continue; // Obstacle présent

            // Pour un déplacement diagonal, éviter de "couper un coin"
            if (dx[i] != 0 && dy[i] != 0)
            {
                Chunk *chunkH = map->getChunk(current->x + dx[i], current->y);
                Chunk *chunkV = map->getChunk(current->x, current->y + dy[i]);
                if ((chunkH && chunkH->isStructure(current->x + dx[i], current->y)) ||
                    (chunkV && chunkV->isStructure(current->x, current->y + dy[i])))
                {
                    continue;
                }
            }

            // Coût du déplacement : 1 pour cardinal, 1.414 pour diagonal
            float tentative_g = current->g + ((dx[i] == 0 || dy[i] == 0) ? 1.0f : 1.414f);

            std::pair<int, int> neighborKey = {nx, ny};
            Node *neighbor = nullptr;
            if (allNodes.find(neighborKey) == allNodes.end())
            {
                // Création du nœud voisin s'il n'existe pas
                neighbor = new Node;
                neighbor->x = nx;
                neighbor->y = ny;
                neighbor->g = tentative_g;
                neighbor->h = heuristic(nx, ny, tileGoalX, tileGoalY);
                neighbor->f = neighbor->g + neighbor->h;
                neighbor->parent = current;
                allNodes[neighborKey] = neighbor;
                openSet.push(neighbor);
            }
            else
            {
                neighbor = allNodes[neighborKey];
                if (tentative_g < neighbor->g)
                {
                    neighbor->g = tentative_g;
                    neighbor->f = neighbor->g + neighbor->h;
                    neighbor->parent = current;
                    // On réinsère le nœud dans la file
                    openSet.push(neighbor);
                }
            }
        }
    }

    // Aucun chemin trouvé : on libère la mémoire et on renvoie un chemin vide.
    for (auto &pair : allNodes)
        delete pair.second;
    return;
}
// La fonction findPath implémente A* dans un environnement grille.
// Pour chaque case, nous vérifions d'abord que le chunk existe et qu'il n'y a pas de structure (obstacle) sur cette case.
/*std::vector<SDL_Point> AstarPathFinding::findPath(Map *map, int startX, int startY, int goalX, int goalY)
{
    // La file de priorité qui contient les nœuds ouverts (open set)
    std::priority_queue<Node *, std::vector<Node *>, CompareNode> openSet;
    // Pour retrouver rapidement un nœud à partir de ses coordonnées (clé = {x, y})
    std::unordered_map<std::pair<int, int>, Node *, pair_hash> allNodes;

    // Création du nœud de départ
    Node *startNode = new Node;
    startNode->x = startX;
    startNode->y = startY;
    startNode->g = 0;
    startNode->h = heuristic(startX, startY, goalX, goalY);
    startNode->f = startNode->g + startNode->h;
    startNode->parent = nullptr;

    openSet.push(startNode);
    allNodes[{startX, startY}] = startNode;

    // Définition des 8 directions possibles (4 cardinales et 4 diagonales)
    const int dx[8] = {1, -1, 0, 0, 1, 1, -1, -1};
    const int dy[8] = {0, 0, 1, -1, 1, -1, 1, -1};

    while (!openSet.empty())
    {
        // Extraction du nœud ayant le coût total (f) le plus faible
        Node *current = openSet.top();
        openSet.pop();

        // Si nous avons atteint la destination, reconstruisons et retournons le chemin.
        if (current->x == goalX && current->y == goalY)
        {
            std::vector<SDL_Point> path = reconstructPath(current);
            // Libération de la mémoire allouée
            for (auto &pair : allNodes)
                delete pair.second;
            return path;
        }

        // Pour chaque voisin (8 directions)
        for (int i = 0; i < 8; i++)
        {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            // Vérification : le chunk existant et la case est-elle praticable ?
            Chunk *chunk = map->getChunk(nx, ny);
            if (!chunk)
                continue; // En dehors de la carte
            if (chunk->isStructure(nx, ny))
                continue; // Case bloquée par une structure

            // Pour un déplacement diagonal, il faut éviter de "couper un coin" :
            if (dx[i] != 0 && dy[i] != 0)
            {
                // Vérifier que les cases horizontale et verticale adjacentes sont praticables
                Chunk *chunkH = map->getChunk(current->x + dx[i], current->y);
                Chunk *chunkV = map->getChunk(current->x, current->y + dy[i]);
                if ((chunkH && chunkH->isStructure(current->x + dx[i], current->y)) ||
                    (chunkV && chunkV->isStructure(current->x, current->y + dy[i])))
                {
                    continue;
                }
            }

            // Coût du déplacement : 1 pour une case horizontale/verticale, 1.414 pour une case diagonale.
            float tentative_g = current->g + ((dx[i] == 0 || dy[i] == 0) ? 1.0f : 1.414f);

            std::pair<int, int> neighborKey = {nx, ny};
            Node *neighbor = nullptr;
            if (allNodes.find(neighborKey) == allNodes.end())
            {
                // Le nœud n'existe pas encore, on le crée.
                neighbor = new Node;
                neighbor->x = nx;
                neighbor->y = ny;
                neighbor->g = tentative_g;
                neighbor->h = heuristic(nx, ny, goalX, goalY);
                neighbor->f = neighbor->g + neighbor->h;
                neighbor->parent = current;
                allNodes[neighborKey] = neighbor;
                openSet.push(neighbor);
            }
            else
            {
                // Le nœud existe déjà, on vérifie si ce chemin est meilleur.
                neighbor = allNodes[neighborKey];
                if (tentative_g < neighbor->g)
                {
                    neighbor->g = tentative_g;
                    neighbor->f = neighbor->g + neighbor->h;
                    neighbor->parent = current;
                    // Remarque : il n'est pas possible de mettre à jour directement la priorité
                    // dans std::priority_queue ; on ajoute donc le nœud à nouveau.
                    openSet.push(neighbor);
                }
            }
        }
    }

    // Aucun chemin trouvé : libération de la mémoire et retour d'un vecteur vide.
    for (auto &pair : allNodes)
        delete pair.second;
    return std::vector<SDL_Point>();
}

void AstarPathFinding::findPath(Map *map, int startX, int startY, int goalX, int goalY, std::vector<SDL_Point> *result)
{
    // La file de priorité qui contient les nœuds ouverts (open set)
    std::priority_queue<Node *, std::vector<Node *>, CompareNode> openSet;
    // Pour retrouver rapidement un nœud à partir de ses coordonnées (clé = {x, y})
    std::unordered_map<std::pair<int, int>, Node *, pair_hash> allNodes;

    // Création du nœud de départ
    Node *startNode = new Node;
    startNode->x = startX;
    startNode->y = startY;
    startNode->g = 0;
    startNode->h = heuristic(startX, startY, goalX, goalY);
    startNode->f = startNode->g + startNode->h;
    startNode->parent = nullptr;

    openSet.push(startNode);
    allNodes[{startX, startY}] = startNode;

    // Définition des 8 directions possibles (4 cardinales et 4 diagonales)
    const int dx[8] = {1, -1, 0, 0, 1, 1, -1, -1};
    const int dy[8] = {0, 0, 1, -1, 1, -1, 1, -1};

    while (!openSet.empty())
    {
        // Extraction du nœud ayant le coût total (f) le plus faible
        Node *current = openSet.top();
        openSet.pop();

        // Si nous avons atteint la destination, reconstruisons et retournons le chemin.
        if (current->x == goalX && current->y == goalY)
        {
            reconstructPath(current, result);
            // Libération de la mémoire allouée
            for (auto &pair : allNodes)
                delete pair.second;
            return;
        }

        // Pour chaque voisin (8 directions)
        for (int i = 0; i < 8; i++)
        {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            // Vérification : le chunk existant et la case est-elle praticable ?
            Chunk *chunk = map->getChunk(nx, ny);
            if (!chunk)
                continue; // En dehors de la carte
            if (chunk->isStructure(nx, ny))
                continue; // Case bloquée par une structure

            // Pour un déplacement diagonal, il faut éviter de "couper un coin" :
            if (dx[i] != 0 && dy[i] != 0)
            {
                // Vérifier que les cases horizontale et verticale adjacentes sont praticables
                Chunk *chunkH = map->getChunk(current->x + dx[i], current->y);
                Chunk *chunkV = map->getChunk(current->x, current->y + dy[i]);
                if ((chunkH && chunkH->isStructure(current->x + dx[i], current->y)) ||
                    (chunkV && chunkV->isStructure(current->x, current->y + dy[i])))
                {
                    continue;
                }
            }

            // Coût du déplacement : 1 pour une case horizontale/verticale, 1.414 pour une case diagonale.
            float tentative_g = current->g + ((dx[i] == 0 || dy[i] == 0) ? 1.0f : 1.414f);

            std::pair<int, int> neighborKey = {nx, ny};
            Node *neighbor = nullptr;
            if (allNodes.find(neighborKey) == allNodes.end())
            {
                // Le nœud n'existe pas encore, on le crée.
                neighbor = new Node;
                neighbor->x = nx;
                neighbor->y = ny;
                neighbor->g = tentative_g;
                neighbor->h = heuristic(nx, ny, goalX, goalY);
                neighbor->f = neighbor->g + neighbor->h;
                neighbor->parent = current;
                allNodes[neighborKey] = neighbor;
                openSet.push(neighbor);
            }
            else
            {
                // Le nœud existe déjà, on vérifie si ce chemin est meilleur.
                neighbor = allNodes[neighborKey];
                if (tentative_g < neighbor->g)
                {
                    neighbor->g = tentative_g;
                    neighbor->f = neighbor->g + neighbor->h;
                    neighbor->parent = current;
                    // Remarque : il n'est pas possible de mettre à jour directement la priorité
                    // dans std::priority_queue ; on ajoute donc le nœud à nouveau.
                    openSet.push(neighbor);
                }
            }
        }
    }

    // Aucun chemin trouvé : libération de la mémoire et retour d'un vecteur vide.
    for (auto &pair : allNodes)
        delete pair.second;
    return;
}*/
