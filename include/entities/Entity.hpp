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
    Entity(Texture *texture, float x, float y, int width, int height, int HP, Map *map, Behavior *behavior) : texture(texture), x(x), y(y), width(width), height(height), speed(VELOCITY_MULTIPLIER), HP(HP), map(map), velX(0), velY(0), behavior(behavior), faction(nullptr) {};
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

    void setPosition(float x, float y);
    void setVelocity(float velocityX, float velocityY);
    void setVelocityX(float velocityX);
    void setVelocityY(float velocityY);
    void setFaction(Faction *faction);
    void pushAction(Action *action);

    float getPositionX();
    float getPositionY();
    Texture *getTexture() const;
    int getSpeed();
    SDL_FRect getHitBox() const;
    int getHP();
    Map *getMap() const;

protected:
    Texture *texture;
    float x, y;
    int width, height;
    float velX, velY;
    int speed;
    int HP;
    Map *map;
    Faction *faction;
    Behavior *behavior;
    std::stack<Action *> actionStack;
};

#endif
