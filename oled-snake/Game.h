#ifndef GAME_H
#define GAME_H

#include <Adafruit_SSD1306.h>
#include "GameUtils.h"

struct Game {
  static Vec2 snakeHead = {0, 0};
  static Direction dir;

  static void init();
  static void tick(Adafruit_SSD1306& scr);
};

#endif
