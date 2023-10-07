#include "Block.h"

BlockFace::BlockFace() {

}

BlockFace::BlockFace(GameTexture texture) : texture(texture) {
}

Block::Block() {

}

Block::Block(Vec3 position, bool is_visible) : position(position) {

}

GrassBlock::GrassBlock(Vec3 position) {
    this->position = position;
    this->is_air = false;
    this->top = BlockFace(GrassTexture());
    this->bottom = BlockFace(DirtTexture());
    this->left = BlockFace(GrassSideTexture());
    this->right = BlockFace(GrassSideTexture());
    this->front = BlockFace(GrassSideTexture());
    this->back = BlockFace(GrassSideTexture());
}

DirtBlock::DirtBlock(Vec3 position) {
    this->position = position;
    this->is_air = false;
    this->top = BlockFace(DirtTexture());
    this->bottom = BlockFace(DirtTexture());
    this->left = BlockFace(DirtTexture());
    this->right = BlockFace(DirtTexture());
    this->front = BlockFace(DirtTexture());
    this->back = BlockFace(DirtTexture());
}

Air::Air(Vec3 position) {
    this->position = position;
    this->is_air = true;
}
