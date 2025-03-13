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
    Entity(std::string textureName, float positionX, float positionY, float width, float height, int HP, Map *map) : textureName(textureName), positionX(positionX), positionY(positionY), width(width), height(height), speed(VELOCITY_MULTIPLIER), HP(HP), range(0.5f), map(map), velocityX(0), velocityY(0), behavior(nullptr), faction(nullptr) {};
    ~Entity() = default;

    virtual void update();
    // void move();
    virtual void render(Camera *camera);
    virtual void onCollision(Entity *);
    // take damages
    virtual void onHit(int damage);
    virtual void onLeftClick();
    virtual void onRightClick();
    // attack
    virtual void attack(Entity *target);
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
    int getHP();
    bool isDead();
    float getRange();
    Map *getMap() const;
    Faction *getFaction() const;

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
    float positionX, positionY;
    float width, height;
    float velocityX, velocityY;
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
