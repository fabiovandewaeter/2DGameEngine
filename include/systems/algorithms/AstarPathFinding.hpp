#ifndef astar_path_finding_hpp
#define astar_path_finding_hpp

#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <SDL2/SDL_rect.h>
#include <algorithm>

// Pour utiliser std::pair<int,int> dans un unordered_map
struct pair_hash {
    template<class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        // Mélange simple des deux hash
        return std::hash<T1>()(p.first) ^ (std::hash<T2>()(p.second) << 1);
    }
};

// Déclaration anticipée des classes Map et Chunk
class Map;
class Chunk;

// Structure représentant un nœud dans l'algorithme A*
struct Node {
    int x, y;          // Coordonnées de la case (en indice de grille)
    float g;           // Coût parcouru depuis le départ
    float h;           // Heuristique (coût estimé jusqu'à l'arrivée)
    float f;           // f = g + h (coût total estimé)
    Node* parent;      // Pointeur vers le nœud parent (pour reconstruire le chemin)
};

// Pour la priority_queue : on veut extraire le nœud de coût total le plus faible
struct CompareNode {
    bool operator()(const Node* a, const Node* b) const {
        return a->f > b->f;
    }
};

// Heuristique : ici, on utilise la distance octile adaptée aux déplacements en diagonale
inline float heuristic(int x1, int y1, int x2, int y2) {
    int dx = std::abs(x1 - x2);
    int dy = std::abs(y1 - y2);
    float D  = 1.0f;
    float D2 = 1.414f; // approximatif de sqrt(2)
    return D * (dx + dy) + (D2 - 2 * D) * std::min(dx, dy);
}

// Fonction de reconstruction du chemin en partant du nœud d'arrivée
inline std::vector<SDL_Point> reconstructPath(Node* node) {
    std::vector<SDL_Point> path;
    while (node != nullptr) {
        SDL_Point p;
        p.x = node->x;
        p.y = node->y;
        path.push_back(p);
        node = node->parent;
    }
    // On inverse le chemin (du départ à l'arrivée)
    std::reverse(path.begin(), path.end());
    return path;
}

// Fonction principale de l'algorithme A*
// Retourne un vecteur de SDL_Point représentant les cases à parcourir
// Si aucun chemin n'est trouvé, retourne un vecteur vide.
std::vector<SDL_Point> findPath(Map* map, int startX, int startY, int goalX, int goalY);

#endif // ASTAR_HPP
