#ifndef mouse_manager_hpp
#define mouse_manager_hpp

#include "Camera.hpp"
#include "../map/Map.hpp"

class MouseManager
{
public:
	MouseManager();
	~MouseManager();

	void init(Camera *camera, Map *map);
	void handleEvents(SDL_Event *event);

private:
	Camera *camera;
	Map *map;
};

#endif
