#ifndef player_hpp
#define player_hpp

#define SPRINT_MULTIPLIER 5

#include <SDL2/SDL.h>

#include "Entity.hpp"
#include "systems/core/GUIManager.hpp"
#include "systems/core/MouseManager.hpp"

class Map;
class Camera;

class Player : public Entity
{
public:
    Player(Texture *texture, SDL_Rect hitBox, int HP, Map *map, Camera *camera) : Entity(texture, hitBox, HP), map(map), camera(camera) {};
    ~Player();

    void handleEvents(SDL_Event *event, GUIManager *guiManager, MouseManager *mouseManager);
    void update();
    // render the map and the player
    void render();

    void setPosition(int x, int y);
    Map *getMap();
    Camera *getCamera();

private:
    // the map the Player is currently on
    Map *map;
    Camera *camera;
};

#endif
