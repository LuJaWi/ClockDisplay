#ifndef DISPLAY_UTILS_H
#define DISPLAY_UTILS_H

#include <TFT_eSPI.h>
#include <ArduinoJson.h>
#include "snakeFiller.h"

void updateDateDisplay(TFT_eSPI &tft);
void updateTimeDisplay(TFT_eSPI &tft);
void updateTempDisplay(TFT_eSPI &tft);
void updateWeatherWidgetDisplay(TFT_eSPI &tft);
void setupRegions(TFT_eSPI &tft);
void updateTextBox(TFT_eSPI &tft);
// void fillRandom(TFT_eSPI &tft);
void growSnake(SnakeFiller& snakeFiller);


#endif