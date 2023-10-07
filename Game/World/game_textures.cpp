#include "game_textures.h"

GameTexture::GameTexture() {}
GameTexture::GameTexture(Vec2 uv_position, Vec2 uv_size, Vec2 index) : uv_position(uv_position), uv_size(uv_size), index(index) {}

GrassSideTexture::GrassSideTexture() : GameTexture({ UV_BLOCK_SIZE, 0.0f }, { UV_BLOCK_SIZE, UV_BLOCK_SIZE }, { 1.0f,0.0f }) {}
DirtTexture::DirtTexture() : GameTexture({ 2 * UV_BLOCK_SIZE, 0.0f }, { UV_BLOCK_SIZE, UV_BLOCK_SIZE }, { 0.0f,0.0f }) {}
GrassTexture::GrassTexture() : GameTexture({ 0.0f, 0.0f }, { UV_BLOCK_SIZE, UV_BLOCK_SIZE }, { 2.0f,0.0f }) {}
