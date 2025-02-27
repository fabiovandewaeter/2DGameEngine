#ifdef PROFILER
#include "tracy_profiler/tracy/Tracy.hpp"
#endif

#ifndef astar_path_finding_hpp
#define astar_path_finding_hpp

#define TILE_SIZE 16

#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <SDL2/SDL_rect.h>
#include <algorithm>
#include <iostream>

// Pour utiliser std::pair<int,int> dans un unordered_map
struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const
    {
        // Mélange simple des deux hash
        return std::hash<T1>()(p.first) ^ (std::hash<T2>()(p.second) << 1);
    }
};

// Déclaration anticipée des classes Map et Chunk
class Map;
class Chunk;

// Structure représentant un nœud dans l'algorithme A*
struct Node
{
    int x, y;     // Coordonnées de la case (en indice de grille)
    float g;      // Coût parcouru depuis le départ
    float h;      // Heuristique (coût estimé jusqu'à l'arrivée)
    float f;      // f = g + h (coût total estimé)
    Node *parent; // Pointeur vers le nœud parent (pour reconstruire le chemin)
};

// Pour la priority_queue : on veut extraire le nœud de coût total le plus faible
struct CompareNode
{
    bool operator()(const Node *a, const Node *b) const
    {
        return a->f > b->f;
    }
};

// Fonction principale de l'algorithme A*
// Retourne un vecteur de SDL_Point représentant les cases à parcourir
// Si aucun chemin n'est trouvé, retourne un vecteur vide.
class AstarPathFinding
{
public:
    static void findPath(Map *map, int startX, int startY, int goalX, int goalY, std::vector<SDL_Point> *result);

private:
    static float heuristic(int x1, int y1, int x2, int y2);
    static void reconstructPath(Node *node, std::vector<SDL_Point> *result);
};

#endif
