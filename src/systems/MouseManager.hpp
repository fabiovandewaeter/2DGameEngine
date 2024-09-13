#ifndef mouse_manager_hpp
#define mouse_manager_hpp

#include "Camera.hpp"

class MouseManager
{
public:
	MouseManager();
	~MouseManager();

	void init(Camera *camera);
	void handleEvents(SDL_Event &event);

private:
	Camera *camera;
};

#endif
