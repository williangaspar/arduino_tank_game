#include "EnemyTank.h"

#include <stdlib.h>

#include "Tank.h"

using namespace NEnemyTank;
using namespace NTank;

void NEnemyTank::spawnEnemyTank(NTank::Tank &enemy, int8_t maxX, int8_t maxY, Tank &player) {
  if (rand() % 1000 > 950) {
    enemy.x = rand() % maxX;
    enemy.y = rand() % maxY;
    enemy.direction = rand() % 4;
    enemy.isAlive = true;

    if (enemy.x == player.x && enemy.y == player.y) {
      if (enemy.x >= maxX) {
        enemy.x--;
      } else {
        enemy.x++;
      }
    }
  }
}

void NEnemyTank::tickEnemyTank(NTank::Tank &enemy) {
  if (enemy.isAlive) {
    int8_t action = rand() % 60;
    switch (action) {
      case NTank::MOVE_UP:
        moveTank(enemy, NTank::UP);
        break;
      case NTank::MOVE_DOWN:
        moveTank(enemy, NTank::DOWN);
        break;
      case NTank::MOVE_LEFT:
        moveTank(enemy, NTank::LEFT);
        break;
      case NTank::MOVE_RIGHT:
        moveTank(enemy, NTank::RIGHT);
        break;
      case NTank::SHOOT:
        shootBullet(enemy);
        break;
      default:
        break;
    }
  }
}

void NEnemyTank::destroyEnemyTank(NTank::Tank &enemy) {
  enemy.isAlive = false;
  enemy.x = 0;
  enemy.y = 0;
  enemy.direction = UP;
  enemy.bullet.x = 0;
  enemy.bullet.y = 0;
  enemy.bullet.direction = UP;
  enemy.bullet.isAlive = false;
}
