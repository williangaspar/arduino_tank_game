#ifndef TANK_CLASS
#define TANK_CLASS

#include "Bullet.h"
#include "Game.h"

namespace Tanks {
class Tank : public Game::Entity {
 public:
  Bullets::Bullet bullet;

  void shoot();
  void destroy();
};

enum TankAction {
  MOVE_UP,
  MOVE_DOWN,
  MOVE_LEFT,
  MOVE_RIGHT,
  SHOOT
};

}  // namespace Tanks

#endif