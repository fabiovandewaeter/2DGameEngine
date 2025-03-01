#ifndef entity_hpp
#define entity_hpp

#define VELOCITY_MULTIPLIER (4.0 / 16)

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
    Entity(Texture *texture, float x, float y, float width, float height, int HP, Map *map) : texture(texture), x(x), y(y), width(width), height(height), speed(VELOCITY_MULTIPLIER), HP(HP), map(map), velX(0), velY(0), behavior(nullptr), faction(nullptr) {};
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
    void setBehavior(Behavior *behavior);
    void pushAction(Action *action);

    float getPositionX();
    float getPositionY();
    Texture *getTexture() const;
    SDL_FRect getHitBox() const;
    int getHP();
    Map *getMap() const;
    float getSpeed();

protected:
    Texture *texture;
    float x, y;
    float width, height;
    float velX, velY;
    float speed;
    int HP;
    Map *map;
    Faction *faction;
    Behavior *behavior;
    std::stack<Action *> actionStack;
};

#endif
