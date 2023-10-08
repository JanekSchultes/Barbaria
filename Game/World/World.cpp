#include "World.h"

#define DAY_DURATION 2
float day_b = (2 * M_PI) / (DAY_DURATION * 60 * 3);

World::World() {
    chunks = new Chunk * [VIEW_DISTANCE * 2 + 1];
    for (int i = 0; i < VIEW_DISTANCE * 2 + 1; ++i) {
        chunks[i] = new Chunk[VIEW_DISTANCE * 2 + 1];
    }
}

void World::loadInitialChunks(Vec2 spawn_pos) {
    int chunk_pos_x = (int)(spawn_pos.x / 16.0f);
    int chunk_pos_y = (int)(spawn_pos.y / 16.0f);
    for (int x = -VIEW_DISTANCE; x <= VIEW_DISTANCE; ++x) {
        for (int y = -VIEW_DISTANCE; y <= VIEW_DISTANCE; ++y) {
            Vec2 chunk_pos = { chunk_pos_x + x, chunk_pos_y + y };
            chunks[x + VIEW_DISTANCE][y + VIEW_DISTANCE] = Chunk(getBaseLevel(chunk_pos), getClimate(chunk_pos), chunk_pos);
            if (x > -VIEW_DISTANCE) {
                Chunk bordering_chunk = chunks[x + VIEW_DISTANCE - 1][y + VIEW_DISTANCE];
                for (int cy = 0; cy < 16; ++cy) {
                    for (int cz = 0; cz < bordering_chunk.height_map[15][cy]; ++cz) {
                        if (!bordering_chunk.block_layers[cz].layer[15][cy].is_air) {
                            chunks[x + VIEW_DISTANCE][y + VIEW_DISTANCE].removeChunkBorder(0, cy, cz);
                        }
                    }
                }
            }
            if (y > -VIEW_DISTANCE) {
                Chunk bordering_chunk = chunks[x + VIEW_DISTANCE][y + VIEW_DISTANCE - 1];
                for (int cx = 0; cx < 16; ++cx) {
                    for (int cz = 0; cz < bordering_chunk.height_map[cx][15] - 1; ++cz) {
                        if (!bordering_chunk.block_layers[cz].layer[cx][15].is_air) {
                            chunks[x + VIEW_DISTANCE][y + VIEW_DISTANCE].removeChunkBorder(cx, 0, cz);
                        }
                    }
                }
            }
            chunks[x + VIEW_DISTANCE][y + VIEW_DISTANCE].registerToRenderer();
        }
    }
    int height = chunks[0][0].height_map[(int)(spawn_pos.x / 16.0f)][(int)(spawn_pos.y / 16.0f)] + 2;
    Engine::getActiveCamera().setPosition({ spawn_pos.x + 0.5, height, spawn_pos.y + 0.5 });
}

void World::updatePlayerPos(Vec3 pos, bool regenChunks) {

}

void World::doTick() {
    day_time++;
    if (day_time >= (DAY_DURATION * 60 * 3)) {
        day_time = 0;
        day_count++;
    }
    ambient_strength = 0.4 - 0.2 * cos(day_b * (float)day_time);
}

float World::getClimate(Vec2 chunk_pos) {
    float sn_influence = CLIMATE_AMPLITUDE * sin(2 * M_PI / CLIMATE_SN_CHANGE_RATE * chunk_pos.y);
    float ew_influence = CLIMATE_AMPLITUDE * sin(2 * M_PI / CLIMATE_EW_CHANGE_RATE * chunk_pos.x);
    return sn_influence + ew_influence;
}

float World::getBaseLevel(Vec2 chunk_pos) {
    float sn_influence = HEIGHT_MAX_BASE * sin(2 * M_PI / HEIGHT_SN_CHANGE_RATE * chunk_pos.y);
    float ew_influence = HEIGHT_MAX_BASE * sin(2 * M_PI / HEIGHT_EW_CHANGE_RATE * chunk_pos.x);
    return sn_influence + ew_influence + MIN_BASE_HEIGHT;
}

World::~World() {
    for (int i = 0; i < VIEW_DISTANCE * 2 + 1; ++i) {
        free(chunks[i]);
    }
    free(chunks);
}
