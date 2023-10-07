#include "Chunk.h"

bool Chunk::debug = false;

BlockLayer::BlockLayer() {
    layer = new Block * [CHUNK_LENGTH];
    for (int i = 0; i < CHUNK_LENGTH; ++i) {
        layer[i] = new Block[CHUNK_LENGTH];
    }
}

BlockLayer::BlockLayer(Block blocks[CHUNK_LENGTH][CHUNK_LENGTH]) {
    layer = new Block * [CHUNK_LENGTH];
    for (int i = 0; i < CHUNK_LENGTH; ++i) {
        layer[i] = new Block[CHUNK_LENGTH];
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
    block_layers = std::vector<BlockLayer>(MAX_HEIGHT);
    int steepness = MAX_STEEPNESS * (1 - (base_height / MAX_HEIGHT) * (base_height / MAX_HEIGHT));
    for (int i = 0; i < CHUNK_LENGTH; ++i) {
        for (int j = 0; j < CHUNK_LENGTH; ++j) {
            height_map[i][j] = base_height + rand() % (steepness * 2) - 1 - steepness;
        }
    }

    for (int i = 0; i < CHUNK_LENGTH; ++i) {
        for (int j = 0; j < CHUNK_LENGTH; ++j) {
            for (int z = 0; z < MAX_HEIGHT - 1; ++z) {
                if (z < height_map[i][j]) {
                    block_layers[z].layer[i][j] = DirtBlock({ (float)(position.x * 16 + i), (float)(position.y * 16 + j), (float)z });
                }
                else if (z == height_map[i][j]) {
                    block_layers[height_map[i][j]].layer[i][j] = GrassBlock({ (float)(position.x * 16 + i), (float)(position.y * 16 + j), (float)height_map[i][j] });
                }
                else {
                    block_layers[z].layer[i][j] = Air({ (float)(position.x * 16 + i), (float)(position.y * 16 + j), (float)z });
                }
                //std::cout << "Block at x: " << i << " y: " << j << " z: " << z << " is air: " << block_layers[z].layer[i][j].is_air << '\n'; 
            }

        }
    }

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

                //if(i>2 || j>2)continue;

                unsigned int bottom_id;
                unsigned int top_id;
                unsigned int back_id;
                unsigned int front_id;
                unsigned int left_id;
                unsigned int right_id;



                if (render_bottom) VoxelRender::registerFace(bottom_id, { (float)i, (float)z, (float)j }, position, BOTTOM, block_layers[z].layer[i][j].bottom.texture.index);
                if (render_top) VoxelRender::registerFace(top_id, { (float)i, (float)z, (float)j }, position, TOP, block_layers[z].layer[i][j].top.texture.index);
                if (render_back) VoxelRender::registerFace(back_id, { (float)i, (float)z, (float)j }, position, BACK, block_layers[z].layer[i][j].back.texture.index);
                if (render_front) VoxelRender::registerFace(front_id, { (float)i, (float)z, (float)j }, position, FRONT, block_layers[z].layer[i][j].front.texture.index);
                if (render_left) VoxelRender::registerFace(left_id, { (float)i, (float)z, (float)j }, position, LEFT, block_layers[z].layer[i][j].left.texture.index);
                if (render_right)  VoxelRender::registerFace(right_id, { (float)i, (float)z, (float)j }, position, RIGHT, block_layers[z].layer[i][j].right.texture.index);
            }
        }
    }
}
