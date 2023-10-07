#ifndef VOXEL_RENDER
#define VOXEL_RENDER

#include "Texture.h"
#include "../../Utils/math_utils.h"
#include <GL/glew.h>
#include <iostream>

#define VERTEX_BUFFER_INITIAL_SIZE 512 * 1024 * 1024
#define INDEX_BUFFER_INITIAL_SIZE 256 * 1024 * 1024
#define DATA_PER_VERTEX 3
#define VERTICES_PER_QUAD 4

#include <vector>
#include <memory.h>
#include <math.h>

enum BlockFacing {
    FRONT = 0,
    BACK = 1,
    LEFT = 2,
    RIGHT = 3,
    TOP = 4,
    BOTTOM = 5
};


struct BlockFaceInfo {
    BlockFaceInfo(int pos_x, int pos_y, int pos_z, int chunk_pos_x, int chunk_pos_y, bool is_visible, int block_index_x, int block_index_y, BlockFacing facing);
    /* BlockData, BlockFaceData, BlockVertexData => 3 for each side => 4 */
    unsigned int data[4 * 3] = { 0 };
};

namespace VoxelRender {
    void setupVoxelRender();

    void registerFace(unsigned int& id, Vec3 pos, Vec2 chunk_pos, BlockFacing facing, Vec2 block_index);
    void freeFace(unsigned int id);

    void render();
}

#endif
