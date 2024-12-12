#ifndef mouse_manager_hpp
#define mouse_manager_hpp

#include <SDL2/SDL.h>

class Camera;
class Map;
class EntityManager;
class CollisionManager;

class MouseManager
{
public:
	MouseManager();
	~MouseManager();

	void init(Camera *camera, Map *map, EntityManager *entityManager, CollisionManager *collisionManager);
	void handleEvents(SDL_Event *event);
	bool handleClickOnEntity(SDL_Event *event, const int &x, const int &y);
	bool handleClickOnMap(SDL_Event *event, const int &x, const int &y);

private:
	Camera *camera;
	Map *map;
	EntityManager *entityManager;
	CollisionManager *collisionManager;
};

#endif
