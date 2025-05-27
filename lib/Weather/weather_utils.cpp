
#include <HTTPClient.h>
#include <WiFiClient.h>

#include <ArduinoJson.h>
#include "../config/env.h"
#include "../config/test.h"

#include "weather_icons.h"

/**
 * @namespace WeatherData
 * @brief A namespace containing utilities and data structures for handling weather data.
 *
 * This namespace provides functionality for fetching, storing, and processing weather data
 * from an external API. It includes variables for API configuration, weather data storage,
 * and utility functions for managing update intervals.
 *
 * Variables:
 * - WEATHER_API_URL: A static string containing the URL for the weather API with query parameters.
 * - weatherData: A JsonDocument object for storing parsed weather data.
 * - weatherCode: An integer representing the current weather condition code.
 * - widgetBitmap: A pointer to an unsigned char array for storing bitmap data for weather widgets.
 * - weatherWidget: A pointer to a WeatherXbms::XbmEntry object for managing weather widget graphics.
 * - temp_s: A string representation of the current temperature.
 * - temp_i: A 16-bit integer representation of the current temperature.
 * - isDay: A boolean indicating whether it is currently daytime.
 * - delayInterval: A static unsigned long representing the delay interval for weather updates (in milliseconds).
 * - currentMillis: A static unsigned long storing the current time in milliseconds.
 * - intervalMillis: A static unsigned long storing the last update time in milliseconds.
 *
 * Functions:
 * - isIntervalElapsed(): A static function that checks if the delay interval has elapsed since the last update.
 *   @return true if the interval has elapsed or if this is the first check; false otherwise.
 */
namespace WeatherData
{
  static String WEATHER_API_URL = "http://api.open-meteo.com/v1/forecast?latitude=" + String(LAT) + "&longitude=" + String(LON) + "&hourly=temperature_2m,relative_humidity_2m,precipitation_probability,precipitation,rain,showers,weather_code,uv_index&temperature_unit=fahrenheit&wind_speed_unit=mph&current=temperature_2m,relative_humidity_2m,is_day,precipitation,rain,weather_code&precipitation_unit=inch&timeformat=unixtime&timezone=America%2FLos_Angeles";

  JsonDocument weatherData;

  int weatherCode;
  unsigned char *widgetBitmap;
  WeatherXbms::XbmEntry *weatherWidget;

  String temp_s;
  int16_t temp_i;

  bool isDay;

  // Weather check delay
  static unsigned long delayInterval = 300000;
  static unsigned long currentMillis;
  static unsigned long intervalMillis = 0;

  static bool isIntervalElapsed()
  {
    currentMillis = millis();
    if (currentMillis - intervalMillis >= delayInterval || intervalMillis == 0)
    {
      intervalMillis = currentMillis;
      return true;
    }
    return false;
  }

  void createDummyWeatherData(){
    Serial.println("Creating Dummy Weather Data...");
    temp_i = random(-20, 111);
    temp_s = String(temp_i);
    weatherCode = random(0,4);
    isDay = random(0,2);
  }

  void printWeatherData() {
    Serial.print("Weather Code: "); Serial.print(weatherCode);
    Serial.print(" || Temperature: "); Serial.print(temp_i);
    Serial.print(" || isDay: "); Serial.print(isDay);
    Serial.println();
  }
}



/**
 * @brief Sends an HTTP GET request to the specified server and retrieves the response.
 *
 * This function establishes a connection to the given server using WiFiClient and HTTPClient,
 * sends an HTTP GET request, and returns the server's response as a string. It also logs the
 * HTTP response code or error code to the Serial monitor for debugging purposes.
 *
 * @param serverName The URL or IP address of the server to send the GET request to.
 * @return String The response payload from the server. Returns an empty JSON object ("{}")
 *                if the request fails.
 */
String httpGETRequest(String serverName)
{

  WiFiClient client;
  HTTPClient https;

  https.useHTTP10(true);
  https.begin(client, serverName);

  int httpResponseCode = https.GET();

  String payload = "{}";

  if (httpResponseCode > 0)
  {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = https.getString();
  }
  else
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  https.end();
  // Serial.print("HTTP Response: "); Serial.println(payload);
  return payload;
}

/**
 * @brief Refreshes the weather data by making an HTTP GET request to the weather API.
 *
 * This function checks if the WiFi is connected and if the interval for refreshing
 * weather data has elapsed. If both conditions are met, it sends an HTTP GET request
 * to the weather API URL, retrieves the JSON response, and deserializes it into the
 * WeatherData::weatherData object.
 *
 * @return JsonDocument The updated weather data stored in a JsonDocument object.
 */
JsonDocument refreshWeatherData()
{
  String jsonBuffer;
  if (WiFi.status() == WL_CONNECTED && WeatherData::isIntervalElapsed())
  {
    Serial.println("Weather API Called");
    jsonBuffer = httpGETRequest(WeatherData::WEATHER_API_URL);
    deserializeJson(WeatherData::weatherData, jsonBuffer);

    JsonObject currentWeatherData = WeatherData::weatherData["current"]; // Hourly temp data
    float f_currentTemp = currentWeatherData["temperature_2m"];          // The most recently grabbed temperature, used to compare against the temperature on the display
    int16_t currentTemp = round(f_currentTemp);
    WeatherData::temp_i = currentTemp;
    WeatherData::temp_s = String(currentTemp);
    WeatherData::weatherCode = currentWeatherData["weather_code"];
    WeatherData::isDay = bool(currentWeatherData["is_day"]);

    WeatherData::printWeatherData();
    } else if (TEST_MODE && WeatherData::isIntervalElapsed()) {
      WeatherData::createDummyWeatherData();
    }
  return WeatherData::weatherData;
}


/**
 * @brief Fetches the current temperature as a string.
 *
 * This function updates the weather data namespace to ensure the latest
 * weather information is available, and then retrieves the temperature
 * value stored in the WeatherData namespace.
 *
 * @return String The current temperature as a string.
 */
String fetchTemperature()
{
  refreshWeatherData();
  return WeatherData::temp_s;
}

/**
 * @brief Fetches the weather widget bitmap data based on the current weather conditions.
 *
 * This function updates the weather data namespace, retrieves the appropriate weather
 * widget XBM (X BitMap) representation based on the weather code and time of day, and
 * extracts the bitmap data from the widget.
 *
 * @return A pointer to the bitmap data of the weather widget.
 */
unsigned char *fetchWeatherWidget()
{
  refreshWeatherData();
  WeatherData::weatherWidget = WeatherXbms::getXbm(WeatherData::weatherCode, WeatherData::isDay);
  WeatherData::widgetBitmap = WeatherData::weatherWidget->bitmapData;
  return WeatherData::widgetBitmap;
}


