#ifndef entity_hpp
#define entity_hpp

#define VELOCITY_MULTIPLIER 1

#include <SDL2/SDL_render.h>
#include <stack>

class Texture;
class State;
class Camera;
class Faction;
class Map;
class Behavior;
class Action;

class Entity
{
public:
    Entity(Texture *texture, SDL_Rect hitBox, int HP, Map *map, Behavior *behavior) : texture(texture), hitBox(hitBox), speed(VELOCITY_MULTIPLIER), HP(HP), map(map), velX(0), velY(0), behavior(behavior), faction(nullptr) {};
    ~Entity() = default;

    virtual void update();
    // void move();
    virtual void render(Camera *camera);
    virtual void onCollision(Entity *);
    virtual void hit(int damage);
    virtual void onLeftClick();
    virtual void onRightClick();
    virtual bool canMove();
    virtual bool isMoving();
    void moveBy(float dx, float dy);
    void kill();

    void setPosition(int x, int y);
    void setVelocity(int velX, int velY);
    void setVelocityX(int velocityX);
    void setVelocityY(int velocityY);
    void setFaction(Faction *faction);

    int getPositionX();
    int getPositionY();
    int getSpeed();
    int getCenterX();
    int getCenterY();
    SDL_Rect getHitBox();
    int getHP();
    Map *getMap();

protected:
    Texture *texture;
    int velX, velY;
    int speed;
    SDL_Rect hitBox;
    int HP;
    Map *map;
    Faction *faction;
    Behavior *behavior;
    std::stack<Action *> actionStack;
};

#endif
