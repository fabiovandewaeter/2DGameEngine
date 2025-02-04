#include "systems/core/MouseManager.hpp"

#include "map/Map.hpp"
#include "map/Chunk.hpp"
#include "systems/core/Camera.hpp"
#include "systems/game_objects/EntityManager.hpp"
#include "structures/Structure.hpp"
#include "entities/Entity.hpp"
#include "entities/Player.hpp"

MouseManager::MouseManager() {}
MouseManager::~MouseManager() {}

// source : https://lazyfoo.net/tutorials/SDL/17_mouse_events/index.php

bool MouseManager::handleClickOnEntity(SDL_Event *event, Player *player, int x, int y)
{
	int i = x;
	int j = y;
	player->getCamera()->convertCameraToInGameCoordinates(i, j);

	int size = 5;
	SDL_Rect area = {i - size, i - size, size * 2, size * 2};
	std::vector<Entity *> potentialEntities = player->getMap()->getEntityManager()->getEntities();
	bool isEntityClicked = false;
	Entity *clickedEntity = nullptr;
	size = potentialEntities.size();
	int k = 0;
	while (k < size && !isEntityClicked)
	{
		if (player->getMap()->isPointInCollisionWithRectangle(i, j, potentialEntities[k]->getHitBox()))
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

bool MouseManager::handleClickOnMap(SDL_Event *event, Player *player, int x, int y)
{
	Chunk *chunk;
	int i = x;
	int j = y;
	player->getCamera()->convertCameraToInGameCoordinates(i, j);

	chunk = player->getMap()->getChunk(i, j);
	bool isStructureClicked = chunk->isStructure(i, j);
	if (event->button.button == SDL_BUTTON_LEFT)
	{
		if (isStructureClicked)
		{
			chunk->getStructure(i, j)->onLeftClick();
		}
		else
		{
			if (this->clickOnEmptyTileStrategy != nullptr)
			{
				Structure *newStructure = this->clickOnEmptyTileStrategy(i, j);
				chunk->addStructure(newStructure);
			}
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

void MouseManager::handleEvents(SDL_Event *event, Player *player)
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
			if (handleClickOnEntity(event, player, x, y))
			{ // skip handleClickOnMap() if the click is on an Entity
				break;
			}
			handleClickOnMap(event, player, x, y);
			break;

		case SDL_MOUSEBUTTONUP:
			break;
		}
	}
}

void MouseManager::setClickOnEmptyTileStrategy(std::function<Structure *(int, int)> strategy) { this->clickOnEmptyTileStrategy = strategy; }
