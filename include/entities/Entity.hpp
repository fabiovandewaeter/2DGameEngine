#ifndef entity_hpp
#define entity_hpp

#define VELOCITY_MULTIPLIER 1

#include <SDL2/SDL_render.h>

class Texture;
class State;
class CollisionManager;
class Camera;
class Faction;

class Entity
{
public:
    Entity(Texture *texture, SDL_Rect hitBox, const int& HP);
    ~Entity();

    void update(CollisionManager *collisionManager);
    bool canMove();
    bool isMoving();
    void move(CollisionManager *collisionManager);
    void render(Camera *camera);
    void kill();
    void onCollision(Entity *);
    void hit(const int& damage);
    virtual void onLeftClick();
    virtual void onRightClick();

    void setVelocity(const int& velX, const int& velY);
    void setVelocityX(const int& velocityX);
    void setVelocityY(const int& velocityY);
    void setFaction(Faction *faction);

    int getPositionX();
    int getPositionY();
    int getCenterX();
    int getCenterY();
    SDL_Rect getHitBox();
    int getHP();

protected:
    Texture *texture;
    int velX, velY;
    SDL_Rect hitBox;
    State *state;
    int HP;
    Faction *faction;
};

#endif