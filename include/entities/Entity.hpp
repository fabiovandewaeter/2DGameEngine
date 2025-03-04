#ifndef entity_hpp
#define entity_hpp

#define VELOCITY_MULTIPLIER (4.0 / 16)

#include <SDL2/SDL_render.h>
#include <stack>
#include <vector>
#include <string>

class Texture;
class State;
class Camera;
class Faction;
class Map;
class Behavior;
class Action;
class Structure;

class Entity
{
public:
    Entity(std::string textureName, float x, float y, float width, float height, int HP, Map *map) : textureName(textureName), x(x), y(y), width(width), height(height), speed(VELOCITY_MULTIPLIER), HP(HP), range(0.5f), map(map), velX(0), velY(0), behavior(nullptr), faction(nullptr) {};
    ~Entity() = default;

    virtual void update();
    // void move();
    virtual void render(Camera *camera);
    virtual void onCollision(Entity *);
    virtual void hit(int damage);
    virtual void onLeftClick();
    virtual void onRightClick();
    virtual bool canMove();
    bool isMoving();
    void moveBy(float dx, float dy);
    void kill();
    void teleportToHome();

    // getter
    float getPositionX() const;
    float getPositionY() const;
    std::string getTextureName() const;
    SDL_FRect getHitBox() const;
    float getSpeed();
    float getRange();
    int getHP();
    Map *getMap() const;

    // setter
    void setPosition(float x, float y);
    void setVelocity(float velocityX, float velocityY);
    void setVelocityX(float velocityX);
    void setVelocityY(float velocityY);
    void setFaction(Faction *faction);
    void setBehavior(Behavior *behavior);
    void pushAction(Action *action);
    // add the structure to the inventory
    void giveStructure(Structure *structure);

protected:
    std::string textureName;
    float x, y;
    float width, height;
    float velX, velY;
    float speed;
    int HP;
    // range to break Structure
    float range;
    Map *map;
    Faction *faction;
    Behavior *behavior;
    std::stack<Action *> actionStack;
    std::vector<Structure *> inventory;

    void addToInventory(Structure *structure);
};

#endif
