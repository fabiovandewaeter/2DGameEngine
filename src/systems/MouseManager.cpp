#include "MouseManager.hpp"

MouseManager::MouseManager(){}
MouseManager::~MouseManager() {}

void MouseManager::init(Camera *camera){
	this->camera = camera;
}

// source : https://lazyfoo.net/tutorials/SDL/17_mouse_events/index.php
void MouseManager::handleEvents(SDL_Event &event){
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );        //Check if mouse is in button
						    //Set mouse over sprite
		switch( e->type )
		{
			case SDL_MOUSEMOTION:
				break;

			case SDL_MOUSEBUTTONDOWN:
				break;

			case SDL_MOUSEBUTTONUP:
				break;
		}
	}
}
