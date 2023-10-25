#include "Block.h"

GrassBlock grass = GrassBlock();
DirtBlock dirt = DirtBlock();

BlockFace GrassBlock::dirtFace = BlockFace(DirtTexture());
BlockFace GrassBlock::grassFace = BlockFace(GrassTexture());
BlockFace GrassBlock::grassSideFace = BlockFace(GrassSideTexture());
BlockFace DirtBlock::dirtFace = BlockFace(DirtTexture());

BlockFace::BlockFace() {

}

BlockFace::BlockFace(GameTexture texture) : texture(texture) {
}

BlockInstance::BlockInstance() {

}

BlockInstance::BlockInstance(Vec3 position, bool is_visible)/* : position(position)*/ {

}

GrassBlockInstance::GrassBlockInstance(Vec3 position) {
    //this->position = position;
    this->is_air = false;
    this->block = &grass;
}

DirtBlockInstance::DirtBlockInstance(Vec3 position) {
    //this->position = position;
    this->is_air = false;
    this->block = &dirt;
}

AirInstance::AirInstance(Vec3 position) {
    //this->position = position;
    this->is_air = true;
}
