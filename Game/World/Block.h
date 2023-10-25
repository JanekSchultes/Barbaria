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
    virtual BlockFace getTopFace() = 0;
    virtual BlockFace getBottomFace() = 0;
    virtual BlockFace getBackFace() = 0;
    virtual BlockFace getFrontFace() = 0;
    virtual BlockFace getLeftFace() = 0;
    virtual BlockFace getRightFace() = 0;
};

class GrassBlock : public Block {
public:
    BlockFace getTopFace() override { return grassFace; }
    BlockFace getBottomFace() override { return dirtFace; }
    BlockFace getLeftFace() override { return grassSideFace; }
    BlockFace getRightFace() override { return grassSideFace; }
    BlockFace getFrontFace() override { return grassSideFace; }
    BlockFace getBackFace() override { return grassSideFace; }
private:
    static BlockFace grassFace;
    static BlockFace grassSideFace;
    static BlockFace dirtFace;
};

class DirtBlock : public Block {
public:
    BlockFace getTopFace() override { return dirtFace; }
    BlockFace getBottomFace() override { return dirtFace; }
    BlockFace getLeftFace() override { return dirtFace; }
    BlockFace getRightFace() override { return dirtFace; }
    BlockFace getFrontFace() override { return dirtFace; }
    BlockFace getBackFace() override { return dirtFace; }

private:
    static BlockFace dirtFace;
};

class BlockInstance {
public:
    BlockInstance();
    BlockInstance(Vec3 position, bool is_visible);
    //Vec3 position;
    bool is_air;
    bool remove_border = false;
    Block* block;
private:
};

class GrassBlockInstance : public BlockInstance {
public:
    GrassBlockInstance(Vec3 position);
};

class DirtBlockInstance : public BlockInstance {
public:
    DirtBlockInstance(Vec3 position);
};

class AirInstance : public BlockInstance {
public:
    AirInstance(Vec3 position);
};

#endif
