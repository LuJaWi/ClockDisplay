#pragma once

#include <Arduino.h>
#include <TFT_eSPI.h>
#if defined(ESP8266) 
  #include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#else 
  #include <HTTPClient.h>
  #include <WiFiClient.h>
#endif

bool connectToWifi(TFT_eSPI& tft);
