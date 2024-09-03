#ifndef player_hpp
#define player_hpp

#include <SDL_render.h>
#include "../LTexture.hpp"

class Player
{
    public:
        Player();
        ~Player();

        bool update();
        void init(LTexture texture, SDL_Rect position);
        bool move();
        void render(SDL_Renderer *renderer);
        
        void setVelocity(int velX, int velY);

    private:
        LTexture texture;
        int velX, velY;
        SDL_Rect position;
};

#endif