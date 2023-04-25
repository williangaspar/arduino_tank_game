#include <LiquidCrystal.h>

#include "EnemyTank.h"
#include "Sprites.h"
#include "Tank.h"

using namespace NTank;
using namespace NSprites;
using namespace NEnemyTank;

#define LCD_COLUMNS 16
#define LCD_LINES 2
#define BTN_LEFT A0
#define BTN_UP A1
#define BTN_DOWN A2
#define BTN_RIGHT A3
#define BUZZER A4
#define BTN_SHOOT A5

#define TONE_SHOOT 600
#define TONE_HIT 300
#define TONE_BEGIN 1400

#define RS 12
#define EN 11
#define D4 5
#define D5 4
#define D6 3
#define D7 2

#define SPRITE_BULLET 5

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

Tank player;
TankAction playerAction;
Tank enemyList[] = {Tank(), Tank(), Tank()};

int32_t score = 0;

bool isButtonPressed = false;

void setup() {
  lcd.begin(LCD_COLUMNS, LCD_LINES);
  resetGame();

  // Register buttons
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);
  pinMode(BTN_SHOOT, INPUT_PULLUP);

  // Register buzzer
  pinMode(BUZZER, OUTPUT);

  // Register custom chars
  lcd.createChar(UP, spriteTankUp);
  lcd.createChar(DOWN, spriteTankDown);
  lcd.createChar(LEFT, spriteTankLeft);
  lcd.createChar(RIGHT, spriteTankRight);
  lcd.createChar(SPRITE_BULLET, spriteBullet);
}

void resetGame() {
  score = 0;

  // Initiate player
  player.x = 0;
  player.y = 0;
  player.direction = RIGHT;
  player.bullet.isAlive = false;
  player.isAlive = true;

  // Initiate enemys
  for (auto &e : enemyList) {
    e.isAlive = false;
    e.bullet.isAlive = false;
  }

  // Start message
  lcd.clear();
  tone(BUZZER, TONE_BEGIN, 200);
  lcd.setCursor(LCD_COLUMNS / 2 - 7, LCD_LINES / 2 - 1);
  lcd.print("TANK GAME 3000");
  delay(3000);
}

void gameOver() {
  tone(BUZZER, TONE_BEGIN, 200);
  lcd.setCursor(LCD_COLUMNS / 2 - 5, LCD_LINES / 2 - 1);
  lcd.print("GAME OVER");
  lcd.setCursor(LCD_COLUMNS / 2 - 7, LCD_LINES - 1);
  lcd.print("HIGH SCORE:");
  lcd.print(score);
  delay(2000);
}

void readUserInput() {
  if (isButtonPressed) {
    isButtonPressed = false;
    return;
  }

  if (digitalRead(BTN_UP) == LOW) {
    playerAction = MOVE_UP;
    isButtonPressed = true;
  };

  if (digitalRead(BTN_DOWN) == LOW) {
    playerAction = MOVE_DOWN;
    isButtonPressed = true;
  };

  if (digitalRead(BTN_LEFT) == LOW) {
    playerAction = MOVE_LEFT;
    isButtonPressed = true;
  }

  if (digitalRead(BTN_RIGHT) == LOW) {
    playerAction = MOVE_RIGHT;
    isButtonPressed = true;
  }

  if (digitalRead(BTN_SHOOT) == LOW) {
    playerAction = SHOOT;
    isButtonPressed = true;
  }
}

void gameLogic() {
  executePlayerAction();
  playerCollisionCheck();

  for (auto &e : enemyList) {
    executeEnemyAction(e);
    bulletWallCheck(e);
    tankWallCheck(e);
  }
  bulletCollisionCheck();
}

void playerCollisionCheck() {
  for (auto &e : enemyList) {
    tankCollisionCheck(player, e);
  };
  tankWallCheck(player);
  bulletWallCheck(player);
}

void executePlayerAction() {
  if (isButtonPressed) {
    switch (playerAction) {
      case MOVE_UP:
        moveTank(player, UP);
        break;
      case MOVE_DOWN:
        moveTank(player, DOWN);
        break;
      case MOVE_LEFT:
        moveTank(player, LEFT);
        break;
      case MOVE_RIGHT:
        moveTank(player, RIGHT);
        break;
      case SHOOT:
        if (!player.bullet.isAlive) {
          tone(BUZZER, TONE_SHOOT, 100);
          shootBullet(player);
        }
        break;
      default:
        break;
    }
  }
}
void executeEnemyAction(Tank &enemy) {
  if (enemy.isAlive) {
    tickEnemyTank(enemy);
    tankCollisionCheck(enemy, player);
  } else {
    spawnEnemyTank(enemy, LCD_COLUMNS, LCD_LINES, player);
  }
}

void bulletWallCheck(Tank &tank) {
  moveBullet(tank.bullet);

  if (tank.bullet.x < 0 || tank.bullet.x >= LCD_COLUMNS ||
      tank.bullet.y < 0 || tank.bullet.y >= LCD_LINES) {
    destroyBullet(tank);
  }
}

void tankWallCheck(Tank &tank) {
  if (tank.x < 0) {
    tank.x = 0;
  } else if (tank.x >= LCD_COLUMNS) {
    tank.x = LCD_COLUMNS - 1;
  }

  if (tank.y < 0) {
    tank.y = 0;
  } else if (tank.y >= LCD_LINES) {
    tank.y = LCD_LINES - 1;
  }
}

void bulletCollisionCheck() {
  // Check if bullet hits enemy
  if (player.bullet.isAlive) {
    for (auto &e : enemyList) {
      if (e.isAlive) {
        if (player.bullet.x == e.x &&
            player.bullet.y == e.y) {
          score++;
          destroyBullet(player);
          destroyEnemyTank(e);
          tone(BUZZER, TONE_HIT, 100);
        }
      }
    }
  }

  // Check if bullet hits player
  for (auto &e : enemyList) {
    if (e.isAlive) {
      if (e.bullet.isAlive) {
        if (e.bullet.x == player.x &&
            e.bullet.y == player.y) {
          destroyBullet(e);
          player.isAlive = false;
          gameOver();
          return;
        }
      }
    }
  }
}

void drawFrame() {
  lcd.clear();
  lcd.setCursor(player.x, player.y);
  lcd.write(player.direction);

  for (auto &e : enemyList) {
    if (e.isAlive) {
      lcd.setCursor(e.x, e.y);
      lcd.write(e.direction);

      if (e.bullet.isAlive) {
        lcd.setCursor(e.bullet.x, e.bullet.y);
        lcd.write(SPRITE_BULLET);
      }
    }
  }

  if (player.bullet.isAlive) {
    lcd.setCursor(player.bullet.x, player.bullet.y);
    lcd.write(SPRITE_BULLET);
  }
}

void loop() {
  if (player.isAlive) {
    readUserInput();
    drawFrame();
    gameLogic();
  } else {
    if (digitalRead(BTN_SHOOT) == LOW) {
      resetGame();
    }
  };
  delay(100);
}
