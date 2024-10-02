#ifndef structure_hpp
#define structure_hpp

#include <SDL.h>
#include <string>

class Texture;
class Camera;
class Entity;
class CollisionManager;

struct description
{
    std::string name;
    std::string details;
};

class Structure
{
public:
    Structure();
    /*Structure(Texture *texture, unsigned int HP, bool solid);
    Structure(Texture *texture, SDL_Rect hitBox, unsigned int HP, bool solid);*/
    ~Structure();

    void init(Texture *texture, CollisionManager *collisionManager, unsigned int range, unsigned int HP, bool solid);
    void init(Texture *texture, CollisionManager *collisionManager, SDL_Rect hitBox, unsigned int range, unsigned int HP, bool solid);

    void update();
    void destroy();
    void render(Camera *camera);
    void onCollision(Entity *entity);
    virtual void onClick();

    SDL_Rect getHitBox();
    bool isSolid();
    bool isActive();
    void setHitBox(SDL_Rect hitBox);
    description getDescription();

protected:
    SDL_Rect hitBox;
    CollisionManager *collisionManager;
    bool active;

private:
    Texture *texture;
    unsigned int range;
    bool solid;
    unsigned int HP;
    description description;
};

#endif