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
	std::pair<float, float> convertedCoordinates = player->getCamera()->convertCameraToInGameCoordinates(x, y);

	int size = 5;
	SDL_FRect area = {convertedCoordinates.first - size, convertedCoordinates.second - size, size * 2, size * 2};
	std::vector<Entity *> potentialEntities = player->getMap()->getEntityManager()->getEntities();
	bool isEntityClicked = false;
	Entity *clickedEntity = nullptr;
	size = potentialEntities.size();
	int k = 0;
	while (k < size && !isEntityClicked)
	{
		if (player->getMap()->isPointInCollisionWithRectangle(convertedCoordinates.first, convertedCoordinates.second, potentialEntities[k]->getHitBox()))
		{
			clickedEntity = potentialEntities[k];
	std::cout << "test" << std::endl;
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
	std::pair<float, float> newCoordinates = player->getCamera()->convertCameraToInGameCoordinates(x, y);

	chunk = player->getMap()->getChunk(newCoordinates.first, newCoordinates.second);
	bool isStructureClicked = chunk->isStructure(newCoordinates.first, newCoordinates.second);
	if (event->button.button == SDL_BUTTON_LEFT)
	{
		if (isStructureClicked)
		{
			chunk->getStructure(newCoordinates.first, newCoordinates.second)->onLeftClick();
		}
		else
		{
			if (this->clickOnEmptyTileStrategy != nullptr)
			{
				Structure *newStructure = this->clickOnEmptyTileStrategy(newCoordinates.first, newCoordinates.second);
				chunk->addStructure(newStructure);
			}
		}
	}
	else if (event->button.button == SDL_BUTTON_RIGHT)
	{
		if (isStructureClicked)
		{
			chunk->getStructure(newCoordinates.first, newCoordinates.second)->onRightClick();
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
