#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <stdint.h>

namespace Game {
enum Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

class Entity {
 public:
  int8_t x;
  int8_t y;
  Direction direction;
  bool isAlive;

  Entity() {
    x = 0;
    y = 0;
    isAlive = false;
  }

  void move(Direction direction);
  void entityCollisionAvoidance(Entity *otherEntity);
  void wallCollisionAvoidance(int8_t xMax, int8_t yMax);
  void destroy();
};

}  // namespace Game

#endif