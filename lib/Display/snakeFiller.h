#pragma once

#include <TFT_eSPI.h>

class SnakeFiller {
public:
    SnakeFiller(int x1, int y1, int x2, int y2, TFT_eSPI &tft);
    void randomPixel();
    void reset();

private:
    int x_min, y_min, x_max, y_max;
    int current_x, current_y, lastMove;
    TFT_eSPI &tft;
    bool isInitialized = false;
    int color;
};