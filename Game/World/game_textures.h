#ifndef GAME_TEXTURE
#define GAME_TEXTURE

#include "../../Utils/math_utils.h"

#define BLOCK_ATLAS_SIZE 2048.0f
#define BLOCK_TEXTURE_SIZE 512.0f
#define UV_BLOCK_SIZE BLOCK_TEXTURE_SIZE / BLOCK_ATLAS_SIZE

class GameTexture {
public:
    GameTexture();
    GameTexture(Vec2 uv_position, Vec2 uv_size, Vec2 index);
    Vec2 uv_position;
    Vec2 uv_size;
    Vec2 index;
};

class GrassSideTexture : public GameTexture {
public:
    GrassSideTexture();
};

class DirtTexture : public GameTexture {
public:
    DirtTexture();
};

class GrassTexture : public GameTexture {
public:
    GrassTexture();
};



#endif
