#ifndef entity_hpp
#define entity_hpp

#include <SDL_render.h>
#include "../Texture.hpp"
#include "../systems/CollisionManager.hpp"
#include "../systems/Camera.hpp"

class CollisionManager;

class Entity
{
public:
    Entity();
    ~Entity();

    void init(Texture *texture, SDL_Rect hitbox, bool solid);
    void update(CollisionManager *collisionManager);
    bool canMove();
    bool isMoving();
    void move(CollisionManager *collisionManager);
    void render(SDL_Renderer *renderer, int viewCenterX, int viewCenterY, int cameraCoordinateX, int cameraCoordinateY, double scale, Camera *camera);

    void setVelocity(int velX, int velY);
    void setVelocityX(int velocityX);
    void setVelocityY(int velocityY);

    int getPositionX();
    int getPositionY();
    int getCenterX();
    int getCenterY();
    Texture *getTexture();
    SDL_Rect getHitBox();
    bool isSolid();

protected:
    Texture *texture;
    int velX, velY;
    int velocity;
    SDL_Rect hitBox;
    bool solid;
};

#endif