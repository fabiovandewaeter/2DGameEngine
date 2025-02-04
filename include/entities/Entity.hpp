#ifndef entity_hpp
#define entity_hpp

#define VELOCITY_MULTIPLIER 1

#include <SDL2/SDL_render.h>

class Texture;
class State;
class Camera;
class Faction;
class Map;

class Entity
{
public:
    Entity(Texture *texture, SDL_Rect hitBox, int HP) : texture(texture), hitBox(hitBox), HP(HP), velX(0), velY(0), state(nullptr) {};
    ~Entity() = default;

    void update(Map *map);
    void move(Map *map);
    void render(Camera *camera);
    void kill();
    void onCollision(Entity *);
    void hit(int damage);
    void onLeftClick();
    void onRightClick();
    bool canMove();
    bool isMoving();

    void setVelocity(int velX, int velY);
    void setVelocityX(int velocityX);
    void setVelocityY(int velocityY);
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
