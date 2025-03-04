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
    Player(std::string textureName, float x, float y, float width, float height, int HP, Map *map, Camera *camera) : Entity(textureName, x, y, width, height, HP, map), camera(camera), guiManager(camera truc)
    {
        GUIManager *guiManager = new GUIManager(this->window, this->renderer, &this->textureManager, &this->tickManager, &this->structureFactory, this->mouseManager);
    };
    ~Player();

    void handleEvents(SDL_Event *event, MouseManager *mouseManager);
    void update() override;
    void render();
    void move();

    Camera *getCamera();

private:
    Camera *camera;
    GUIManager *guiManager;
};

#endif
