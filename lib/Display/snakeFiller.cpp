#include "snakeFiller.h"
#include <Arduino.h>

SnakeFiller::SnakeFiller(int x1, int y1, int x2, int y2, TFT_eSPI &tft)
    : x_min(x1), y_min(y1), x_max(x2), y_max(y2),
  current_x(random(x_min, x_max + 1)),
  current_y(random(y_min, y_max + 1)), 
  lastMove(0),
  tft(tft),
  color(TFT_WHITE)
{
  
}

void SnakeFiller::randomPixel()
{
  snakeFill(tft);
}

void SnakeFiller::snakeFill(TFT_eSPI &tft)
{
  uint16_t r = (color >> 11) & 0x1F;
  uint16_t g = (color >> 5) & 0x3F;
  uint16_t b = color & 0x1F;

  int channel = random(0, 3);
  if (channel == 0) {
    // Red
    if (random(0, 2) == 0 && r < 31) r++;
    else if (r > 0) r--;
  } else if (channel == 1) {
    // Green
    if (random(0, 2) == 0 && g < 63) g++;
    else if (g > 0) g--;
  } else {
    // Blue
    if (random(0, 2) == 0 && b < 31) b++;
    else if (b > 0) b--;
  }
  color = (r << 11) | (g << 5) | b;
  if (!isInitialized)
  {
    Serial.print("Starting at pixel "); Serial.print(current_x); Serial.print(", "); Serial.println(current_y);
    tft.drawPixel(current_x, current_y, color);
    lastMove = 0;
    Serial.println("Snake Filler Initialized");
    isInitialized = true;
    lastMove = 0;
    return;
  }
  while (1)
  {
    int move_direction = random(0, 4);
    // Serial.print("Move direction: "); Serial.println(move_direction);
      if (move_direction == 0)
      {
        if (!(current_x - 1 < x_min))
        {
          current_x--;
          tft.drawPixel(current_x, current_y, color);
          lastMove = move_direction;
          return;
        }
      }
      if (move_direction == 1)
      { // Up
        if (!(current_y + 1 > y_max))
        {
          current_y++;
          tft.drawPixel(current_x, current_y, color);
          lastMove = move_direction;
          return;
        }
      }
      if (move_direction == 2)
      { // Right
        if (!(current_x + 1 > x_max))
        {
          current_x++;
          tft.drawPixel(current_x, current_y, color);
          lastMove = move_direction;
          return;
        }
      }
      if (move_direction == 3)
      { // Down
        if (!(current_y - 1 < y_min))
        {
          current_y--;
          tft.drawPixel(current_x, current_y, color);
          lastMove = move_direction;
          return;
        }
      }
    }
  }