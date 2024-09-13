#include "MouseManager.hpp"

MouseManager::MouseManager(){}
MouseManager::~MouseManager() {}

void MouseManager::init(Camera *camera){
	this->camera = camera;
}
