#include "Tank.h";

#include <stdlib.h>

using namespace NTank;

void NTank::moveTank(Tank &tank, Direction direction) {
  switch (direction) {
    case UP:
      if (tank.direction == UP) {
        tank.y--;
      } else {
        tank.direction = UP;
      };
      break;
    case DOWN:
      if (tank.direction == DOWN) {
        tank.y++;
      } else {
        tank.direction = DOWN;
      }
      break;
    case LEFT:
      if (tank.direction == LEFT) {
        tank.x--;
      } else {
        tank.direction = LEFT;
      }
      break;
    case RIGHT:
      if (tank.direction == RIGHT) {
        tank.x++;
      } else {
        tank.direction = RIGHT;
      }
      break;
    default:
      break;
  }
}

void NTank::tankCollisionCheck(Tank &tank, Tank &otherTank) {
    if (otherTank.isAlive) {
      if (tank.x == otherTank.x && tank.y == otherTank.y) {
        switch (tank.direction) {
          case UP:
            tank.y++;
            break;
          case DOWN:
            tank.y--;
            break;
          case LEFT:
            tank.x++;
            break;
          case RIGHT:
            tank.x--;
            break;
          default:
            break;
        }
      }
    }
}

void NTank::shootBullet(Tank &tank) {
  if (tank.bullet.isAlive == false) {
    tank.bullet.x = tank.x;
    tank.bullet.y = tank.y;
    tank.bullet.direction = tank.direction;
    tank.bullet.isAlive = true;
  }
}

void NTank::moveBullet(Bullet &bullet) {
  switch (bullet.direction) {
    case UP:
      bullet.y--;
      break;
    case DOWN:
      bullet.y++;
      break;
    case LEFT:
      bullet.x--;
      break;
    case RIGHT:
      bullet.x++;
      break;
    default:
      break;
  }
}

void NTank::destroyBullet(Tank &tank) {
  tank.bullet.isAlive = false;
}
