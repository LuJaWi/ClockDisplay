#include <Arduino.h>
#include <TFT_eSPI.h>
#include <ArduinoJson.h>

#include "../include/headerfile.h"

TFT_eSPI tft = TFT_eSPI();


void setup()
{
  Serial.begin(115200);
  Serial.println(""); // Start the output on a fresh line
  delay(2000);        // Give time for serial monitoring to start
  screenSetup(tft);
  bool isConnected = connectToWifi(tft);
  // bool isConnected = true;
  if (isConnected)
  {
    initializeTime();
    delay(1000); // Give time initialization a second to complete
    tft.setCursor(0, 0);
    tft.fillScreen(BG_COLOR);
    tft.setTextFont(MAIN_FONT);
    setupRegions(tft);
    // updateTextBox(tft);
    // tft.print("It goes ");
  }
  else
  {
    tft.print("Failed to connect to the internet. What the fuck.");
    delay(1000);
    exit(1);
  }
}


SnakeFiller snakeFiller = SnakeFiller(60, tft.fontHeight(TIME_FONT) + 10, TFT_HEIGHT, TFT_WIDTH, tft);

int loopCount = 0;

void loop()
{
  snakeFiller.randomPixel();
  updateTempDisplay(tft);
  updateWeatherWidgetDisplay(tft);
  updateTimeDisplay(tft);
  updateDateDisplay(tft);
  loopCount++;
}