#ifndef TANK_FUNCTIONS
#define TANK_FUNCTIONS

#include <stdint.h>

namespace NTank {
enum Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

enum TankAction {
  MOVE_UP,
  MOVE_DOWN,
  MOVE_LEFT,
  MOVE_RIGHT,
  SHOOT
};


struct Bullet {
  int8_t x;
  int8_t y;
  bool isAlive;
  Direction direction;
};
struct Tank {
  int8_t x;
  int8_t y;
  Direction direction;
  Bullet bullet;
  bool isAlive;
};

void moveTank(Tank &tank, Direction direction);
void tankCollisionCheck(Tank &tank, Tank &otherTank);
void shootBullet(Tank &tank);
void moveBullet(Bullet &bullet);
void destroyBullet(Tank &tank);

}  // namespace NTank

#endif