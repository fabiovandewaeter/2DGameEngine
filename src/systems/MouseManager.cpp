#include "MouseManager.hpp"

#include "../map/Map.hpp"
#include "../map/Chunk.hpp"
#include "Camera.hpp"
#include "../structures/Structure.hpp"

MouseManager::MouseManager() {}
MouseManager::~MouseManager() {}

void MouseManager::init(Camera *camera, Map *map)
{
	this->camera = camera;
	this->map = map;
}

// source : https://lazyfoo.net/tutorials/SDL/17_mouse_events/index.php
void MouseManager::handleEvents(SDL_Event *event)
{
	if (event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		int i, j;
		Chunk *chunk;
		SDL_GetMouseState(&x, &y);
		switch (event->type)
		{
		case SDL_MOUSEMOTION:
			break;

		case SDL_MOUSEBUTTONDOWN:
			this->camera->convertCameraToInGameCoordinates(x, y);
			i = x;
			j = y;
			chunk = this->map->getChunk(x, y);
			if (event->button.button == SDL_BUTTON_LEFT)
			{
				if (chunk->isActiveStructure(i, j)){
					chunk->getActiveStructure(i, j)->onClick();
				}
				else {
					chunk->addWall(i, j);
				}
			}
			else if (event->button.button == SDL_BUTTON_RIGHT)
			{
				chunk->destroyPassiveStructure(i, j);
			}
			break;

		case SDL_MOUSEBUTTONUP:
			break;
		}
	}
}
