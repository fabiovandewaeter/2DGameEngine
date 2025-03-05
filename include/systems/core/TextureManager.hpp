#ifndef texture_manager_hpp
#define texture_manager_hpp

#include <SDL2/SDL.h>
#include <unordered_map>
#include <vector>
#include <string>

class Texture;
class Camera;

class TextureManager
{
public:
    TextureManager(Camera *camera) : camera(camera) { loadConfiguration(); }
    ~TextureManager();

    Texture *getTexture(std::string name);

private:
    Camera *camera;
    std::unordered_map<std::string, Texture *> textures;

    void loadConfiguration();
};

#endif
