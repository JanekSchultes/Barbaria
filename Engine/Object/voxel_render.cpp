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

ChunkRender::ChunkRender() {
    gl_mutex = new std::mutex;

    vao = 0;
    vbo = 0;
    indices = std::vector<unsigned int>(0);
    free_vao_locations = std::vector<unsigned int>(0);

    indices.reserve(CHUNK_INITAL_FACE_STORAGE * 6);
    free_vao_locations.reserve(CHUNK_INITAL_FACE_STORAGE);

    for(int i = 0; i < CHUNK_INITAL_FACE_STORAGE; ++i) {
        free_vao_locations.push_back(i);
    }
    
    for (int i = 0; i < CHUNK_INITAL_FACE_STORAGE; ++i) {
        indices.push_back(0 + i * 4);
        indices.push_back(1 + i * 4);
        indices.push_back(2 + i * 4);
        indices.push_back(2 + i * 4);
        indices.push_back(3 + i * 4);
        indices.push_back(0 + i * 4);
    }


    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &index_buffer);

    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.capacity() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
     glBufferData(GL_ARRAY_BUFFER, indices.capacity() / 6 * DATA_PER_VERTEX *  sizeof(unsigned int), (void*)0, GL_STATIC_DRAW);
    
    glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, DATA_PER_VERTEX * sizeof(unsigned int), (void*)0);
    glVertexAttribIPointer(1, 1, GL_UNSIGNED_INT, DATA_PER_VERTEX * sizeof(unsigned int), (void*)(sizeof(unsigned int)));
    glVertexAttribIPointer(2, 1, GL_UNSIGNED_INT, DATA_PER_VERTEX * sizeof(unsigned int), (void*)(2 * sizeof(unsigned int)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
}

void ChunkRender::register_face(unsigned int& id, Vec3 pos, Vec2 chunk_pos, BlockFacing facing, Vec2 block_index) {
    bool needs_buffer_regen = false;
    if(!free_vao_locations.empty()){
        id = free_vao_locations.back();
        free_vao_locations.pop_back();
    } else {
        needs_buffer_regen = true;
        ++buffer_multiplied_size;
        unsigned int face_count = CHUNK_INITAL_FACE_STORAGE * buffer_multiplied_size;
        unsigned int old_face_count = CHUNK_INITAL_FACE_STORAGE * (buffer_multiplied_size - 1);

        indices.reserve(6 * face_count);
        free_vao_locations.reserve(face_count);

        for(int i = old_face_count - 1; i < face_count; ++i) {
            free_vao_locations.push_back(i);
        }

        for (int i = old_face_count - 1; i < face_count; ++i) {
            indices.push_back(0 + i * 4);
            indices.push_back(1 + i * 4);
            indices.push_back(2 + i * 4);
            indices.push_back(2 + i * 4);
            indices.push_back(3 + i * 4);
            indices.push_back(0 + i * 4);
        }
        id = free_vao_locations.back();
        free_vao_locations.pop_back();
    }

    BlockFaceInfo info{ (int)pos.x, (int)pos.y, (int)pos.z, (int)chunk_pos.x, (int)chunk_pos.y, true, (int)block_index.x, (int)block_index.y, facing };
    int byte_position = (CHUNK_INITAL_FACE_STORAGE * buffer_multiplied_size - id - 1) * VERTICES_PER_QUAD * DATA_PER_VERTEX * sizeof(unsigned int);
    int byte_size = VERTICES_PER_QUAD * DATA_PER_VERTEX * sizeof(unsigned int);

    //std::cout << "Registering face... Pos: " << pos.x << " " << pos.y << " " << pos.z << " Facing:" << facing << "\n";

    gl_mutex->lock();
    if(needs_buffer_regen){
        glBindBuffer(GL_COPY_READ_BUFFER, vbo);
        unsigned int tmp;
        glGenBuffers(1, &tmp);
        glBindBuffer(GL_COPY_WRITE_BUFFER, tmp);

        glBufferData(GL_COPY_WRITE_BUFFER, buffer_multiplied_size * CHUNK_INITAL_FACE_STORAGE * VERTICES_PER_QUAD *  DATA_PER_VERTEX *  sizeof(unsigned int), (void*)0, GL_STATIC_DRAW);
        unsigned int old_buffer_size = (buffer_multiplied_size - 1) * CHUNK_INITAL_FACE_STORAGE * VERTICES_PER_QUAD * DATA_PER_VERTEX * sizeof(unsigned int);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, old_buffer_size - 1, old_buffer_size);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
       
        glDeleteBuffers(1, &vbo);
        vbo = tmp;
        unsigned int tmp_vao;
        glGenVertexArrays(1, &tmp_vao);
        glDeleteVertexArrays(1, &vao);
        vao = tmp_vao;
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        
        glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, DATA_PER_VERTEX * sizeof(unsigned int), (void*)0);
        glVertexAttribIPointer(1, 1, GL_UNSIGNED_INT, DATA_PER_VERTEX * sizeof(unsigned int), (void*)(sizeof(unsigned int)));
        glVertexAttribIPointer(2, 1, GL_UNSIGNED_INT, DATA_PER_VERTEX * sizeof(unsigned int), (void*)(2 * sizeof(unsigned int)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

    }
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, byte_position, byte_size, &info.data[0]);
    gl_mutex->unlock();
}


void ChunkRender::freeFace(unsigned int id) {
    free_vao_locations.push_back(id);
    int byte_position = id * DATA_PER_VERTEX * sizeof(unsigned int);
    int byte_size = VERTICES_PER_QUAD * DATA_PER_VERTEX * sizeof(unsigned int);

    unsigned int zero_array[VERTICES_PER_QUAD * DATA_PER_VERTEX] = { 0 };

    gl_mutex->lock();
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, byte_position, byte_size, &zero_array[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    gl_mutex->unlock();
}

void ChunkRender::render() {
    gl_mutex->lock();
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glDrawElements(GL_TRIANGLES, indices.size() - free_vao_locations.size() * 6, GL_UNSIGNED_INT, 0);
    gl_mutex->unlock();
}

ChunkRender::~ChunkRender() {
    gl_mutex->lock();
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &index_buffer);
    glDeleteBuffers(1, &vbo);
    gl_mutex->unlock();
}