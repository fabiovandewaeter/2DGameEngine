#ifndef player_hpp
#define player_hpp

#define SPRINT_MULTIPLIER 5

#include <SDL2/SDL.h>

#include "Entity.hpp"
#include "systems/core/GUIManager.hpp"
#include "systems/core/MouseManager.hpp"
#include "systems/core/Camera.hpp"
#include "map/Map.hpp"

class Map;
class Camera;

class Player : public Entity
{
public:
    Player(std::string textureName, float positionX, float positionY, float width, float height, int HP, Map *map, Camera *camera) : Entity(textureName, positionX, positionY, width, height, HP, map), camera(camera), mouseManager(new MouseManager()), guiManager(new GUIManager(camera->getWindow(), camera->getRenderer(), camera->getTextureManager(), map->getTickManager(), map->getStructureFactory(), mouseManager)) {}
    ~Player();

    void handleEvents(SDL_Event *event);
    void update() override;
    void render();
    void move();

    Camera *getCamera();

private:
    Camera *camera;
    MouseManager *mouseManager;
    GUIManager *guiManager;
};

#endif
