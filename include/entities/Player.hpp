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
    Player(Texture *texture, SDL_Rect hitBox, int HP, Map *map, Camera *camera) : Entity(texture, hitBox, HP), map(map), camera(camera), guiManager(new GUIManager()), mouseManager(new MouseManager()) {};
    ~Player();

    void handleEvents(SDL_Event *event);
    void update();
    void update(Map *map);
    void render();
    void render(Camera *camera);

    void setPosition(int x, int y);
    Map *getMap();
    Camera *getCamera();

private:
    Map *map;
    Camera *camera;
    GUIManager *guiManager;
    MouseManager *mouseManager;
};

#endif
