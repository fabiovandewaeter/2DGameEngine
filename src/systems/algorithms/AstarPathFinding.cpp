#include "systems/algorithms/AstarPathFinding.hpp"
#include "map/Map.hpp"
#include "map/Chunk.hpp"

// Heuristique : ici, on utilise la distance octile adaptée aux déplacements en diagonale
float AstarPathFinding::heuristic(float x1, float y1, float x2, float y2)
{
    float dx = std::fabs(x1 - x2);
    float dy = std::fabs(y1 - y2);
    float D = 1.0f;
    float D2 = 1.414f; // approximatif de sqrt(2)
    return D * (dx + dy) + (D2 - 2 * D) * std::min(dx, dy);
}

void AstarPathFinding::reconstructPath(Node *node, std::vector<SDL_FPoint> *result)
{
    while (node != nullptr)
    {
        SDL_FPoint p{node->x, node->y};
        // p.x = node->x + 1 / 2;
        // p.y = node->y + 1 / 2;
        result->push_back(p);
        node = node->parent;
    }
    // On inverse le chemin (du départ à l'arrivée)
    std::reverse(result->begin(), result->end());
}

std::vector<SDL_FPoint> AstarPathFinding::findPath(Map *map, float startX, float startY, float goalX, float goalY)
{
    std::vector<SDL_FPoint> res;
    // Conversion des positions pixels -> indices de cases
    int tileStartX = static_cast<int>(std::floor(startX));
    int tileStartY = static_cast<int>(std::floor(startY));
    int tileGoalX = static_cast<int>(std::floor(goalX));
    int tileGoalY = static_cast<int>(std::floor(goalY));

    // File de priorité (open set) pour les nœuds
    std::priority_queue<Node *, std::vector<Node *>, CompareNode> openSet;
    // Un unordered_map pour retrouver rapidement un nœud par ses coordonnées (en grille)
    std::unordered_map<std::pair<float, float>, Node *, hash_pair> allNodes;

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

        if (current->x < -100 || current->x > 100)
        {
            std::cout << startX << " " << startY << " " << goalX << " " << goalY << std::endl;
            exit(1);
        }
        // Si on a atteint la destination
        if (current->x == tileGoalX && current->y == tileGoalY)
        {
            reconstructPath(current, &res);
            // Libération de la mémoire des nœuds
            for (auto &pair : allNodes)
                delete pair.second;
            return res;
        }

        // Pour chaque voisin (8 directions)
        for (int i = 0; i < 8; i++)
        {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            // Vérification : on récupère le chunk correspondant à la case (les coordonnées sont en indices)
            Chunk *chunk = map->getChunk(nx, ny);
            if (!chunk)
            {
                continue; // Hors limites de la carte
            }

            // Vérifier si le voisin est un obstacle, sauf si c'est la destination
            if (chunk->isStructure(nx, ny) && !(nx == tileGoalX && ny == tileGoalY))
            {
                continue; // Obstacle présent (mais pas la destination)
            }

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
                std::cout << tentative_g << " " << neighbor->g << std::endl;
                if (tentative_g < neighbor->g)
                {
                    std::cout << "oui" << std::endl;
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
    return res;
}
