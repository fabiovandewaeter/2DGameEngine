#include "Core.hpp"

Core::Core(Texture *texture, unsigned int HP)
{
    init(texture, 1, HP, true);
}
Core::Core(Texture *texture, SDL_Rect hitBox, unsigned int HP)
{
    init(texture, hitBox, 1, HP, true);
}