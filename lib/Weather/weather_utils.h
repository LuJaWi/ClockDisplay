# pragma once

#if defined(ESP8266) 
  #include <ESP8266HTTPClient.h>
  #include <ESP8266WiFi.h>
#else 
  #include <HTTPClient.h>
  #include <WiFiClient.h>
#endif

#include <Arduino.h>

String fetchTemperature();
unsigned char* fetchWeatherWidget();
