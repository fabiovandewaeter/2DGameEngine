#include "MouseManager.hpp"

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
		SDL_GetMouseState(&x, &y);
		switch (event->type)
		{
		case SDL_MOUSEMOTION:
			break;

		case SDL_MOUSEBUTTONDOWN:
			break;

		case SDL_MOUSEBUTTONUP:
			break;
		}
		this->camera->convertCameraToInGameCoordinates(x, y);
		int i = x, j = y;
		Chunk *chunk = this->map->getChunk(x, y);
		chunk->convertToTileCoordinates(i, j);
		std::cout << "pixels : " << x << " " << y << " tile: " << i << " " << j << std::endl;
	}
}
