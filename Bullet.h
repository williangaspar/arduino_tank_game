#ifndef BULLET_CLASS
#define BULLET_CLASS

#include "Entity.h"

namespace Bullets {
class Bullet : public Game::Entity {
 public:
  void wallCollisionAvoidance(int8_t xMax, int8_t yMax);
};
};  // namespace Bullets

#endif