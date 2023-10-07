#ifndef BLOCK
#define BLOCK

#include "../../Utils/math_utils.h"
#include "../../Engine/Engine.h"
#include "game_textures.h"

#define BLOCK_TEXTURE_RESOLUTION 512

class BlockFace {
public:
    BlockFace();
    BlockFace(GameTexture texture);
    GameTexture texture;
};

class Block {
public:
    Block();
    Block(Vec3 position, bool is_visible);
    Vec3 position;
    bool is_air;
    BlockFace top;
    BlockFace bottom;
    BlockFace left;
    BlockFace right;
    BlockFace front;
    BlockFace back;
private:
};

class GrassBlock : public Block {
public:
    GrassBlock(Vec3 position);
};

class DirtBlock : public Block {
public:
    DirtBlock(Vec3 position);
};

class Air : public Block {
public:
    Air(Vec3 position);
};

#endif
