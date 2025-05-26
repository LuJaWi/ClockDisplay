#include <Arduino.h>
#include <TFT_eSPI.h>

#include "screen_styles.h"

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "../config/env.h"
#include "../config/test.h"

void dummyConnect(TFT_eSPI &tft) {
  Serial.println("Running in test mode, no connection to internet!");
  tft.println("This would be the wifi connection");
  tft.println("starting if test mode wasn't active.");
  for (int i = 0; i < 5; i++) {
    tft.print(".");
    delay(100);
  }
  tft.println("");  tft.println("");
  tft.println("You're not connected,");
  tft.println("but that's what you wanted, right?");
}

/**
 * @brief Connects to a Wi-Fi network and provides feedback on a TFT display.
 *
 * This function attempts to connect to a Wi-Fi network using the provided
 * SSID and password. It displays the connection status on a TFT_eSPI display
 * and prints debug information to the Serial monitor. If the connection
 * fails after a specified number of attempts, the function returns false.
 *
 * @param tft Reference to a TFT_eSPI object used for displaying connection status.
 * @return true if the connection is successful, false if the connection fails.
 *
 * @note The Wi-Fi credentials (WIFI_SSID and WIFI_PASSWORD) must be defined
 *       as global constants or macros elsewhere in the program.
 * @note The function waits for up to 30 seconds (60 attempts with 500ms delay)
 *       before determining that the connection has failed.
 */
bool connectToWifi(TFT_eSPI &tft)
{
  if (!TEST_MODE) {
    tft.setCursor(0, 0);
    tft.fillScreen(BG_COLOR);
    String loadingPrompt = WIFI_SSID;
    loadingPrompt = "Connecting to " + loadingPrompt;
    tft.print(loadingPrompt);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    int connectionCheckCount = 0;
    Serial.print("Connecting..");
    while (WiFi.status() != WL_CONNECTED)
    {
      Serial.print(".");
      tft.print(".");
      delay(500);
      connectionCheckCount++;
      if (connectionCheckCount > 60)
      {
        tft.println("");
        tft.println("Failed to connect!");
        return false;
      }
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.print(WIFI_SSID);
    Serial.print(" in ");
    Serial.print(connectionCheckCount / 2);
    Serial.println(" seconds.");
    return true;
  } else {
    dummyConnect(tft);
    return true;
  }
}