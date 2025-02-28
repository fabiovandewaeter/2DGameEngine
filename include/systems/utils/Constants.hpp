#ifndef constants_hpp
#define constants_hpp

#define TILE_PIXELS_SIZE 16
#define CHUNK_TILE_SIZE 16

#define TEXTURE_DEFAULT_SIZE 32

// hash for std::pair<int, int> as coordinates
struct hash_pair
{
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const
    {
        return std::hash<T1>{}(p.first) ^ (std::hash<T2>{}(p.second) << 1);
    }
};

#endif
