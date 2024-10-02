#ifndef core_hpp
#define core_hpp

#include "../Structure.hpp"

class EntityManager;
class TextureManager;

class Core : public Structure
{
public:
    Core(Texture *texture, CollisionManager *collisionManager, EntityManager *entityManager, std::vector<Texture *> *entityTextures, unsigned int HP);
    Core(Texture *texture, CollisionManager *collisionManager, EntityManager *entityManager, std::vector<Texture *> *entityTextures, SDL_Rect hitBox, unsigned int HP);

    void update();
    void spawnEntities();
    void onClick();

private:
    EntityManager *entityManager;
    std::vector<Texture *> *entityTextures;
};

#endif