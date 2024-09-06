#include "CollisionManager.hpp"

CollisionManager::CollisionManager() {}
CollisionManager::~CollisionManager() {}

void CollisionManager::init(std::vector<Entity*> entities){
    this->allEntities.insert(this->allEntities.end(), entities.begin(), entities.end());
    /*for (size_t i = 0; i < entities.size(); i++){
        for (size_t j = 0; j < entities.size(); i++)
        {
            if (i != j)
            {
                this->potentialCollisions[entities[i]].push_back(entities[j]);
            }
        }
    }*/
}

bool CollisionManager::checkCollision(SDL_Rect rectA, SDL_Rect rectB)
{
    return !(rectA.x + rectA.w <= rectB.x ||
             rectA.x >= rectB.x + rectB.w ||
             rectA.y + rectA.h <= rectB.y ||
             rectA.y >= rectB.y + rectB.h);
}

SDL_Rect CollisionManager::handleCollisionsFor(Entity *entity, int newPosX, int newPosY){
    SDL_Rect hitBox = entity->getHitBox();
    SDL_Rect res = hitBox;
    for (size_t i = 0; i < this->allEntities.size(); i++)
    {
        SDL_Rect otherEntityBox = this->allEntities[i]->getHitBox();
        if (checkCollision(hitBox, otherEntityBox)){
            res = resolveCollision(hitBox, otherEntityBox, newPosX, newPosY);
        }
    }

    return hitBox;
}

SDL_Rect CollisionManager::resolveCollision(SDL_Rect &rectA, const SDL_Rect &rectB, int &dx, int &dy)
{
    // Si rectA touche rectB après avoir essayé de bouger
    SDL_Rect rectA_afterMove = rectA;
    rectA_afterMove.x += dx;
    rectA_afterMove.y += dy;

    if (checkCollision(rectA_afterMove, rectB))
    {
        // Si une collision a lieu, on ajuste dx et dy pour permettre un déplacement partiel
        // Traitement pour l'axe X
        if (dx > 0)
        { // déplacement vers la droite
            rectA.x = rectB.x - rectA.w;
            dx = 0; // arrêt complet sur l'axe X
        }
        else if (dx < 0)
        { // déplacement vers la gauche
            rectA.x = rectB.x + rectB.w;
            dx = 0;
        }

        // Traitement pour l'axe Y
        if (dy > 0)
        { // déplacement vers le bas
            rectA.y = rectB.y - rectA.h;
            dy = 0; // arrêt complet sur l'axe Y
        }
        else if (dy < 0)
        { // déplacement vers le haut
            rectA.y = rectB.y + rectB.h;
            dy = 0;
        }
    }
    else
    {
        // Si aucune collision, applique le déplacement complet
        rectA.x += dx;
        rectA.y += dy;
    }
}

void CollisionManager::addEntity(Entity *entity){

}