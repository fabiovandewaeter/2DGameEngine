#ifndef entity_hpp
#define entity_hpp

#include <SDL_render.h>
#include "../Texture.hpp"

class Entity
{
public:
    Entity();
    ~Entity();

    void init(Texture *texture, int positionX, int positionY);
    bool update();
    bool move();
    void render(SDL_Renderer *renderer, int cameraCenterX, int cameraCenterY, int cameraCoordinateX, int cameraCoordinateY, double scale);

    void setVelocity(int velX, int velY);
    void setVelocityX(int velocityX);
    void setVelocityY(int velocityY);

    int getPositionX();
    int getPositionY();
    Texture* getTexture();

protected:
    Texture *texture;
    int velX, velY;
    int positionX, positionY;
    int VELOCITY;
};

#endif