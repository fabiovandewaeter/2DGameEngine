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
    Player(Texture *texture, float x, float y, float width, float height, int HP, Map *map, Camera *camera) : Entity(texture, x, y, width, height, HP, map, nullptr), camera(camera) {};
    ~Player();

    void handleEvents(SDL_Event *event, GUIManager *guiManager, MouseManager *mouseManager);
    void update() override;
    void render();
    void move();

    Camera *getCamera();

private:
    // the map the Player is currently on
    Camera *camera;
};

#endif
