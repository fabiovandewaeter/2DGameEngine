#ifndef mouse_manager_hpp
#define mouse_manager_hpp

#include "SDL2/SDL_events.h"
#include <functional>

class Player;
class Camera;
class Map;
class EntityManager;
class CollisionManager;
class Structure;

class MouseManager
{
public:
	MouseManager();
	~MouseManager();

	void handleEvents(SDL_Event *event, Player *player);
	void setClickOnEmptyTileStrategy(std::function<Structure *(int, int)>);

private:
	std::function<Structure *(int, int)> clickOnEmptyTileStrategy;

	// check and handle the click on an Entity
	bool handleClickOnEntity(SDL_Event *event, Player *player, int x, int y);
	bool handleClickOnMap(SDL_Event *event, Player *player, int x, int y);
};

#endif
