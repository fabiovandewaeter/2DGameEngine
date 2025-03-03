#ifdef PROFILER
#include "tracy_profiler/tracy/Tracy.hpp"
#endif

#ifndef astar_path_finding_hpp
#define astar_path_finding_hpp

#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <SDL2/SDL_rect.h>
#include <algorithm>
#include <iostream>

#include "systems/utils/Constants.hpp"

// Déclaration anticipée des classes Map et Chunk
class Map;
class Chunk;

// Structure représentant un nœud dans l'algorithme A*
struct Node
{
    float x, y;     // Coordonnées de la case (en indice de grille)
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
    static std::vector<SDL_Point> findPath(Map *map, float startX, float startY, float goalX, float goalY);

private:
    static float heuristic(float x1, float y1, float x2, float y2);
    static void reconstructPath(Node *node, std::vector<SDL_Point> *result);
};

#endif
