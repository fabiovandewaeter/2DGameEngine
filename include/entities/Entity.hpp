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
    Entity(Texture *texture, SDL_Rect hitBox, int HP, Map *map, Behavior *behavior) : texture(texture), hitBox(hitBox), speed(VELOCITY_MULTIPLIER), HP(HP), map(map), velX(0), velY(0), state(nullptr), behavior(behavior) {};
    ~Entity() = default;

    void update(Map *map);
    // void move();
    void render(Camera *camera);
    void kill();
    void onCollision(Entity *);
    void hit(int damage);
    void onLeftClick();
    void onRightClick();
    bool canMove();
    bool isMoving();
    void moveBy(float dx, float dy);

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
    State *state;
    int HP;
    Map *map;
    Faction *faction;
    Behavior *behavior;
    std::stack<Action *> actionStack;
};

#endif
