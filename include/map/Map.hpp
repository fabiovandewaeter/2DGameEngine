#ifndef map_hpp
#define map_hpp

#define CHUNK_SIZE 16

#include <vector>
#include <unordered_map>
#include <cmath>
#include <string>

class Camera;
class TextureManager;
class Texture;
class PerlinNoise;
class CollisionManager;
class Chunk;

class Map
{
public:
    Map();
    ~Map();

    void init(Camera *camera, int tileSize, TextureManager *textureManager, PerlinNoise *perlinNoise, CollisionManager *collisionManager);
    void loadChunks();
    void generateChunk(int positionX, int positionY);
    void loadSquareMap(int size);
    void render();
    void update();
    void free();

    bool isChunkGenerated(int x, int y);
    Chunk *getChunk(int x, int y);
    int getTileSize();
    int getChunkSize();

private:
    Camera *camera;
    int tileSize;
    TextureManager *textureManager;
    PerlinNoise *perlinNoise;
    CollisionManager *collisionManager;
    std::unordered_map<std::string, Chunk *> allChunks;
    std::vector<Chunk *> nearbyChunks;

    void convertToChunkCoordinates(int &x, int &y);
};

#endif
