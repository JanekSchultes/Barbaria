#ifndef WORLD
#define WORLD

#include "../../Utils/math_utils.h"
#include "Chunk.h"
#include "../../Engine/Engine.h"

#define CLIMATE_AMPLITUDE 100
/* Those are base numbers, they are changed by a random displacement */
#define CLIMATE_SN_CHANGE_RATE 0.05
#define CLIMATE_EW_CHANGE_RATE 0.01

#define HEIGHT_MAX_BASE 120
#define HEIGHT_SN_CHANGE_RATE 0.1
#define HEIGHT_EW_CHANGE_RATE 0.02

#define MIN_BASE_HEIGHT 64

#define VIEW_DISTANCE 10

#define _USE_MATH_DEFINES

#include <memory.h>
#include <math.h>
#include <mutex>

class World {
public:
    World();
    void updatePlayerPos(Vec3 pos, bool regen);
    void loadInitialChunks(Vec2 spawn_pos);
    void doTick();
    float getAmbientStrength();
    ~World();
private:
    float getClimate(Vec2 chunk_pos);
    float getBaseLevel(Vec2 chunk_pos);
    Vec3 player_pos = { 0.0f, 0.0f, 0.0f };
    Chunk** chunks;
    int day_time = 0;
    int day_count = 0;
    float ambient_strength = 0.0f;
};

#endif
