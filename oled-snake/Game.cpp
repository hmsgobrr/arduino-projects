#include "Game.h"

Vec2 Game::snakeHead;
Direction Game::dir;

void Game::init() {
  snakeHead = {0, 0};
  dir = RIGHT;
}

void Game::tick(Adafruit_SSD1306& scr) {
  short int joyX = analogRead(A0);
  short int joyY = analogRead(A1);

  if (joyY < 1) dir = UP;
  else if (joyY > 1000) dir = DOWN;
  else if (joyX < 1) dir = LEFT;
  else if (joyX > 1000) dir = RIGHT;

  switch (dir) {
  case UP:
    Serial.println("UP");
    snakeHead.y--;
    break;
  case DOWN:
    Serial.println("DOWN");
    snakeHead.y++;
    break;
  case LEFT:
    Serial.println("LEFT");
    snakeHead.x--;
    break;
  case RIGHT:
    Serial.println("RIGHT");
    snakeHead.x++;
    break;
  }

  if (snakeHead.x < 0) snakeHead.x = WWIDTH;
  if (snakeHead.x > WWIDTH) snakeHead.x = 0;
  if (snakeHead.y < 0) snakeHead.y = WHEIGHT;
  if (snakeHead.y > WHEIGHT) snakeHead.y = 0;

  scr.fillRect(snakeHead.x*TILE_SCALE, snakeHead.y*TILE_SCALE, TILE_SCALE, TILE_SCALE, 1);
}
