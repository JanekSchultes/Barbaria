#include "voxel_render.h"

BlockFaceInfo::BlockFaceInfo(int pos_x, int pos_y, int pos_z, int chunk_pos_x, int chunk_pos_y, bool is_visible, int block_index_x, int block_index_y, BlockFacing facing) {
    unsigned int block_info = 0;
    block_info |= pos_x; /* Requires 4 bits -> 15 is 0b1111 */
    block_info |= (pos_y << 4); /* Requires 8bits -> 255 as max height */
    block_info |= (pos_z << 12); /* Requires 4 bits -> 15 is 0b1111 */
    unsigned int sign = 0x1;
    if (chunk_pos_x < 0) block_info |= (sign << 31); /* Sign of chunk_pos_x */
    if (chunk_pos_y < 1) block_info |= (sign << 30); /* Sign of chunk_pos_y */
    block_info |= (abs(chunk_pos_x) << 16); /* 128 chunks max in x direction -> vd of 64 */
    block_info |= (abs(chunk_pos_y) << 23); /* 128 chunks max in y direction -> vd of 64 */
    data[0] = block_info;
    data[3] = block_info;
    data[6] = block_info;
    data[9] = block_info;

    unsigned int block_face_info = 0;
    block_face_info |= block_index_x;
    block_face_info |= (block_index_y << 8);
    data[1] = block_face_info;
    data[4] = block_face_info;
    data[7] = block_face_info;
    data[10] = block_face_info;

    if (facing == TOP) {
        data[2] |= 0x2;     /* Tx 0, Ty 0, Px 0, Py 1, Pz 0 */
        data[5] |= 0x16;    /* Tx 1, Ty 0, Px 1, Py 1, Pz 0 */
        data[8] |= 0x1F;    /* Tx 1, Ty 1, Px 1, Py 1, Pz 1 */
        data[11] |= 0xB;    /* Tx 0, Ty 1, Px 0, Py 1, Pz 1 */
    }
    else if (facing == BOTTOM) {
        data[2] |= 0x0;     /* Tx 0, Ty 0, Px 0, Py 0, Pz 0 */
        data[5] |= 0x9;     /* Tx 0, Ty 1, Px 0, Py 0, Pz 1 */
        data[8] |= 0x1D;    /* Tx 1, Ty 1, Px 1, Py 0, Pz 1 */
        data[11] |= 0x14;   /* Tx 1, Ty 0, Px 1, Py 0, Pz 0 */
    }
    else if (facing == LEFT) {
        data[2] |= 0x0;     /* Tx 0, Ty 0, Px 0, Py 0, Pz 0 */
        data[5] |= 0xA;     /* Tx 0, Ty 1, Px 0, Py 1, Pz 0 */
        data[8] |= 0x1B;    /* Tx 1, Ty 1, Px 0, Py 1, Pz 1 */
        data[11] |= 0x11;   /* Tx 1, Ty 0, Px 0, Py 0, Pz 1 */
    }
    else if (facing == RIGHT) {
        data[2] |= 0x4;     /* Tx 0, Ty 0, Px 1, Py 0, Pz 0 */
        data[5] |= 0x15;    /* Tx 1, Ty 0, Px 1, Py 0, Pz 1 */
        data[8] |= 0x1F;    /* Tx 1, Ty 1, Px 1, Py 1, Pz 1 */
        data[11] |= 0xE;    /* Tx 0, Ty 1, Px 1, Py 1, Pz 0 */
    }
    else if (facing == FRONT) {
        data[2] |= 0x0;     /* Tx 0, Ty 0, Px 0, Py 0, Pz 0 */
        data[5] |= 0x14;    /* Tx 1, Ty 0, Px 1, Py 0, Pz 0 */
        data[8] |= 0x1E;    /* Tx 1, Ty 1, Px 1, Py 1, Pz 0 */
        data[11] |= 0xA;    /* Tx 0, Ty 1, Px 0, Py 1, Pz 0 */
    }
    else if (facing == BACK) {
        data[2] |= 0x1;     /* Tx 0, Ty 0, Px 0, Py 0, Pz 1 */
        data[5] |= 0xB;     /* Tx 0, Ty 1, Px 0, Py 1, Pz 1 */
        data[8] |= 0x1F;    /* Tx 1, Ty 1, Px 1, Py 1, Pz 1 */
        data[11] |= 0x15;   /* Tx 1, Ty 0, Px 1, Py 0, Pz 1 */
    }
}

namespace VoxelRender {
    GLuint index_buffer = 0;
    unsigned int index_buffer_byte_size = INDEX_BUFFER_INITIAL_SIZE;
    unsigned int face_count = 0;
    unsigned int* indices = nullptr;

    GLuint vao = 0;
    GLuint vbo = 0;
    std::vector<unsigned int> free_ids(0);

    GLint* base_vertices = nullptr;
    GLsizei* counts = nullptr;
    GLvoid** indicess = nullptr;
}

void VoxelRender::setupVoxelRender() {
    int max_face_count = (int)(INDEX_BUFFER_INITIAL_SIZE / sizeof(unsigned int) / 6);
    indices = new unsigned int[INDEX_BUFFER_INITIAL_SIZE / sizeof(unsigned int)];
    for (int i = 0; i < max_face_count; ++i) {
        indices[0 + i * 6] = 0 + i * 4;
        indices[1 + i * 6] = 1 + i * 4;
        indices[2 + i * 6] = 2 + i * 4;
        indices[3 + i * 6] = 2 + i * 4;
        indices[4 + i * 6] = 3 + i * 4;
        indices[5 + i * 6] = 0 + i * 4;
    }

    /*indicess = new GLvoid[face_count];
    for (int i = 0; i < face_count; ++i) {
        indicess[i] = 0;
    }

    base_vertices = new GLint[face_count];
    for (int i = 0; i < face_count; ++i) {
        base_vertices[i] = i * 4;
    }

    counts = new GLsizei[face_count];
    for (int i = 0; i < face_count; ++i) {
        counts[i] = 6;
    }

    indices = new unsigned int[6];
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 2;
    indices[4] = 3;
    indices[5] = 0;*/


    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &index_buffer);
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, max_face_count * 6 * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, VERTEX_BUFFER_INITIAL_SIZE, (void*)0, GL_STATIC_DRAW);
    glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, DATA_PER_VERTEX * sizeof(unsigned int), (void*)0);
    glVertexAttribIPointer(1, 1, GL_UNSIGNED_INT, DATA_PER_VERTEX * sizeof(unsigned int), (void*)(sizeof(unsigned int)));
    glVertexAttribIPointer(2, 1, GL_UNSIGNED_INT, DATA_PER_VERTEX * sizeof(unsigned int), (void*)(2 * sizeof(unsigned int)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
}

void VoxelRender::registerFace(unsigned int& id, Vec3 pos, Vec2 chunk_pos, BlockFacing facing, Vec2 block_index) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    if (!free_ids.empty()) {
        id = free_ids.back();
        free_ids.pop_back();
    }
    else {
        id = face_count;
        ++face_count;
    }

    BlockFaceInfo info{ (int)pos.x, (int)pos.y, (int)pos.z, (int)chunk_pos.x, (int)chunk_pos.y, true, (int)block_index.x, (int)block_index.y, facing };
    int byte_position = id * VERTICES_PER_QUAD * DATA_PER_VERTEX * sizeof(unsigned int);
    int byte_size = VERTICES_PER_QUAD * DATA_PER_VERTEX * sizeof(unsigned int);

    //std::cout << "Registering face... Pos: " << pos.x << " " << pos.y << " " << pos.z << " Facing:" << facing << "\n";

    glBufferSubData(GL_ARRAY_BUFFER, byte_position, byte_size, &info.data[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VoxelRender::freeFace(unsigned int id) {
    free_ids.push_back(id);
    int byte_position = id * DATA_PER_VERTEX * sizeof(unsigned int);
    int byte_size = VERTICES_PER_QUAD * DATA_PER_VERTEX * sizeof(unsigned int);

    unsigned int zero_array[VERTICES_PER_QUAD * DATA_PER_VERTEX] = { 0 };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, byte_position, byte_size, &zero_array[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VoxelRender::render() {
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glDrawElements(GL_TRIANGLES, face_count * 6, GL_UNSIGNED_INT, 0);
    //glMultiDrawElementsBaseVertex(GL_TRIANGLES, counts, GL_UNSIGNED_INT, (void**)indicess, face_count, base_vertices);
}
