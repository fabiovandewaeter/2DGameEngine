#include "systems/MouseManager.hpp"

#include "map/Map.hpp"
#include "map/Chunk.hpp"
#include "systems/Camera.hpp"
#include "systems/EntityManager.hpp"
#include "systems/CollisionManager.hpp"
#include "structures/Structure.hpp"
#include "entities/Entity.hpp"

MouseManager::MouseManager() {}
MouseManager::~MouseManager() {}

void MouseManager::init(Camera *camera, Map *map, EntityManager *entityManager, CollisionManager *collisionManager)
{
	this->camera = camera;
	this->map = map;
	this->entityManager = entityManager;
	this->collisionManager = collisionManager;
}

// source : https://lazyfoo.net/tutorials/SDL/17_mouse_events/index.php

bool MouseManager::handleClickOnEntity(SDL_Event *event, int x, int y)
{
	int i = x;
	int j = y;
	this->camera->convertCameraToInGameCoordinates(i, j);

	int size = 5;
	SDL_Rect area = {i - size, i - size, size * 2, size * 2};
	std::vector<Entity *> potentialEntities = this->entityManager->getEntities();
	bool isEntityClicked = false;
	Entity *clickedEntity = nullptr;
	size = potentialEntities.size();
	int k = 0;
	while (k < size && !isEntityClicked)
	{
		if (this->collisionManager->checkCollisionFromCoordinates(i, j, potentialEntities[k]->getHitBox()))
		{
			clickedEntity = potentialEntities[k];
			isEntityClicked = true;
		}
		k++;
	}
	if (event->button.button == SDL_BUTTON_LEFT)
	{
		if (isEntityClicked)
		{
			clickedEntity->onLeftClick();
			std::cout << "ENTITY KILLED" << std::endl;
		}
	}
	else if (event->button.button == SDL_BUTTON_RIGHT)
	{
		if (isEntityClicked)
		{
			clickedEntity->onRightClick();
		}
	}
}

bool MouseManager::handleClickOnMap(SDL_Event *event, int x, int y)
{
	Chunk *chunk;
	int i = x;
	int j = y;
	this->camera->convertCameraToInGameCoordinates(i, j);

	chunk = this->map->getChunk(i, j);
	bool isStructure = chunk->isStructure(i, j);
	if (event->button.button == SDL_BUTTON_LEFT)
	{
		if (isStructure)
		{
			chunk->getStructure(i, j)->onLeftClick();
		}
		else
		{
			chunk->addWall(i, j);
		}
	}
	else if (event->button.button == SDL_BUTTON_RIGHT)
	{
		if (isStructure)
		{
			chunk->getStructure(i, j)->onRightClick();
		}
	}
}

void MouseManager::handleEvents(SDL_Event *event)
{
	if (event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		int i, j;
		SDL_GetMouseState(&x, &y);
		switch (event->type)
		{
		case SDL_MOUSEMOTION:
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (handleClickOnEntity(event, x, y))
			{ // skip handleClickOnMap() if the click is on an Entity
				break;
			}
			handleClickOnMap(event, x, y);
			break;

		case SDL_MOUSEBUTTONUP:
			break;
		}
	}
}
