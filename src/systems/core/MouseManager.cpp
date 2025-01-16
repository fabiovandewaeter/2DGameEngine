#include "systems/core/MouseManager.hpp"

#include "map/Map.hpp"
#include "map/Chunk.hpp"
#include "systems/core/Camera.hpp"
#include "systems/game_objects/EntityManager.hpp"
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
		}
	}
	else if (event->button.button == SDL_BUTTON_RIGHT)
	{
		if (isEntityClicked)
		{
			clickedEntity->onRightClick();
		}
	}
	return isEntityClicked;
}

bool MouseManager::handleClickOnMap(SDL_Event *event, int x, int y)
{
	Chunk *chunk;
	int i = x;
	int j = y;
	this->camera->convertCameraToInGameCoordinates(i, j);

	chunk = this->map->getChunk(i, j);
	bool isStructureClicked = chunk->isStructure(i, j);
	if (event->button.button == SDL_BUTTON_LEFT)
	{
		if (isStructureClicked)
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
		if (isStructureClicked)
		{
			chunk->getStructure(i, j)->onRightClick();
		}
	}
	return isStructureClicked;
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
