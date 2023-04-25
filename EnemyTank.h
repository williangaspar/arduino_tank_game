#ifndef ENEMY_TANK_FUNCTIONS
#define ENEMY_TANK_FUNCTIONS

#include <stdint.h>

#include "Tank.h"

using namespace NTank;

namespace NEnemyTank {

void spawnEnemyTank(Tank &enemy, int8_t maxX, int8_t maxY, Tank &player);
void tickEnemyTank(Tank &enemy);
void destroyEnemyTank(Tank &enemy);
}  // namespace NEnemyTank

#endif