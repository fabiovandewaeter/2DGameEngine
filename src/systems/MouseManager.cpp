#include "MouseManager.hpp"

MouseManager::MouseManager(){}
MouseManager::~MouseManager() {}

void MouseManager::init(Camera *camera){
	this->camera = camera;
}
void MouseManager::convertCameraToInGameCoordinates(int &x, int &y){
	double scale = this->camera->getScale();
}
