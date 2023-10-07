#ifndef CHUNK
#define CHUNK

#include "../../Utils/math_utils.h"
#include "../../Engine/Engine.h"
#include "Block.h"
#include <string>
#include <iostream>

#define CHUNK_LENGTH 16
#define MAX_STEEPNESS 4
#define MAX_HEIGHT 150

class BlockLayer {
public:
    BlockLayer();
    BlockLayer(Block blocks[CHUNK_LENGTH][CHUNK_LENGTH]);
    ~BlockLayer();
    Block** layer;
};

class Chunk {
public:
    Chunk();
    Chunk(int base_height, int climate, Vec2 position);
    Chunk(std::string chunk_file);
    void save(std::string name);
    static bool debug;
    int height_map[CHUNK_LENGTH][CHUNK_LENGTH];
private:
    int base_height = 0;
    std::vector<BlockLayer> block_layers;
    std::vector<BlockFace> visible_block_faces;
};

#endif
