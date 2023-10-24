#include "Chunk.h"

bool Chunk::debug = false;

BlockLayer::BlockLayer() {
    layer = new BlockInstance * [CHUNK_LENGTH];
    for (int i = 0; i < CHUNK_LENGTH; ++i) {
        layer[i] = new BlockInstance[CHUNK_LENGTH];
        for (int j = 0; j < CHUNK_LENGTH; ++j) {
            layer[i][j] = AirInstance({ 0.0f, 0.0f, 0.0f });
        }
    }
}

BlockLayer::BlockLayer(BlockInstance blocks[CHUNK_LENGTH][CHUNK_LENGTH]) {
    layer = new BlockInstance * [CHUNK_LENGTH];
    for (int i = 0; i < CHUNK_LENGTH; ++i) {
        layer[i] = new BlockInstance[CHUNK_LENGTH];
    }
    for (int i = 0; i < CHUNK_LENGTH; ++i) {
        for (int j = 0; j < CHUNK_LENGTH; ++j) {
            layer[i][j] = blocks[i][j];
        }
    }
}

BlockLayer::~BlockLayer() {
    for (int i = 0; i < CHUNK_LENGTH; ++i) {
        delete(layer[i]);
    }
    delete(layer);
}

Chunk::Chunk() {

}

Chunk::Chunk(int base_height, int climate, Vec2 position) {
    pos = position;
    /* Generate random height map*/
    block_layers = new BlockLayer[MAX_HEIGHT];
    int steepness = MAX_STEEPNESS * (1 - (base_height / MAX_HEIGHT) * (base_height / MAX_HEIGHT));
    for (int i = 0; i < CHUNK_LENGTH; ++i) {
        for (int j = 0; j < CHUNK_LENGTH; ++j) {
            height_map[i][j] = base_height + rand() % (steepness * 2) - 1 - steepness;
        }
    }

    /* Fill with blocks */
    for (int i = 0; i < CHUNK_LENGTH; ++i) {
        for (int j = 0; j < CHUNK_LENGTH; ++j) {
            for (int z = 0; z < MAX_HEIGHT - 1; ++z) {
                //block_layers[z] = BlockLayer();
                if (z < height_map[i][j]) {
                    block_layers[z].layer[i][j] = DirtBlockInstance({ (float)(position.x * 16 + i), (float)(position.y * 16 + j), (float)z });
                }
                else if (z == height_map[i][j]) {
                    block_layers[height_map[i][j]].layer[i][j] = GrassBlockInstance({ (float)(position.x * 16 + i), (float)(position.y * 16 + j), (float)height_map[i][j] });
                }
                else {
                    block_layers[z].layer[i][j] = AirInstance({ (float)(position.x * 16 + i), (float)(position.y * 16 + j), (float)z });
                }
                //std::cout << "Block at x: " << i << " y: " << j << " z: " << z << " is air: " << block_layers[z].layer[i][j].is_air << '\n'; 
            }

        }
    }
}

void Chunk::registerToRenderer() {
    /* Determine faces not to be rendered*/
    int face_count = 0;

    for (int i = 0; i < CHUNK_LENGTH; ++i) {
        for (int j = 0; j < CHUNK_LENGTH; ++j) {
            for (int z = 0; z <= height_map[i][j]; ++z) {
                bool render_bottom = false;
                bool render_top = false;
                bool render_front = false;
                bool render_back = false;
                bool render_left = false;
                bool render_right = false;
                if (block_layers[z].layer[i][j].is_air) continue;

                if (z == 0) render_bottom = true;
                else if (block_layers[z - 1].layer[i][j].is_air) render_bottom = true;
                if (z == height_map[i][j]) render_top = true;
                else if (block_layers[z + 1].layer[i][j].is_air) render_top = true;

                if (i == 0) render_left = true;
                else if (block_layers[z].layer[i - 1][j].is_air) render_left = true;
                if (i == CHUNK_LENGTH - 1) render_right = true;
                else if (block_layers[z].layer[i + 1][j].is_air) render_right = true;

                if (j == 0) render_back = true;
                else if (block_layers[z].layer[i][j - 1].is_air) render_back = true;
                if (j == CHUNK_LENGTH - 1) render_front = true;
                else if (block_layers[z].layer[i][j + 1].is_air) render_front = true;

                if (i == 0 && block_layers[z].layer[i][j].remove_border) render_left = false;
                if (j == 0 && block_layers[z].layer[i][j].remove_border) render_front = false;

                //if(i>2 || j>2)continue;

                unsigned int bottom_id;
                unsigned int top_id;
                unsigned int back_id;
                unsigned int front_id;
                unsigned int left_id;
                unsigned int right_id;



                if (render_bottom) VoxelRender::registerFace(bottom_id, { (float)i, (float)z, (float)j }, pos, BOTTOM, block_layers[z].layer[i][j].block->getBottomFace().texture.index);
                if (render_top) VoxelRender::registerFace(top_id, { (float)i, (float)z, (float)j }, pos, TOP, block_layers[z].layer[i][j].block->getTopFace().texture.index);
                if (render_back) VoxelRender::registerFace(back_id, { (float)i, (float)z, (float)j }, pos, BACK, block_layers[z].layer[i][j].block->getBackFace().texture.index);
                if (render_front) VoxelRender::registerFace(front_id, { (float)i, (float)z, (float)j }, pos, FRONT, block_layers[z].layer[i][j].block->getFrontFace().texture.index);
                if (render_left) VoxelRender::registerFace(left_id, { (float)i, (float)z, (float)j }, pos, LEFT, block_layers[z].layer[i][j].block->getLeftFace().texture.index);
                if (render_right)  VoxelRender::registerFace(right_id, { (float)i, (float)z, (float)j }, pos, RIGHT, block_layers[z].layer[i][j].block->getRightFace().texture.index);
            }
        }
    }
}

void Chunk::removeChunkBorder(int x, int y, int z) {
    block_layers[z].layer[x][y].remove_border = true;
}