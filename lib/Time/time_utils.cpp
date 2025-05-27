#include <NTPClient.h>
#include <WiFiClient.h>
#include "time.h"

#include "../config/env.h"
#include "../config/test.h"

bool TIME_INITIALIZED = false; // Tracks whether the time client has been initialized

const char *ntpServer = NTP_SERVER;

/**
 * @brief Initializes the system time using NTP and sets the timezone.
 *
 * This function configures the system to synchronize time with an NTP server
 *
 * Steps performed:
 * 1. Synchronizes time with the specified NTP server using `configTime`.
 * 2. Sets the timezone environment variable to Pacific Time with daylight saving
 *    adjustments using `setenv`.
 * 3. Applies the timezone settings using `tzset`.
 * 4. Marks the time initialization as complete by setting `TIME_INITIALIZED` to true.
 *
 * Note:
 * - Ensure that the `ntpServer` variable is properly defined and points to a valid
 *   NTP server before calling this function.
 */
void initializeTime()
{
  configTime(0, 0, ntpServer); // From the ESP8266 or ESP32 core libraries for Arduino
  setenv("TZ", TIME_ZONE, 1);  // Standard C library (time.h)
  tzset();                     // Standard C library (time.h)
  TIME_INITIALIZED = true;
}

/**
 * @brief Fetches the current local time as a formatted string.
 *
 * This function retrieves the current local time, formats it into a
 * 12-hour clock format (HH:MM:SS), and returns it as a String. If the
 * time has not been initialized, it initializes the time first.
 *
 * @note The function assumes that the macro `TIME_INITIALIZED` is defined
 *       and indicates whether the time has been initialized. If not,
 *       `initializeTime()` is called to set up the time.
 *
 * @return String The current local time in the format "HH:MM:SS".
 */
String fetchTime()
{
  if (!TEST_MODE){
    if (!TIME_INITIALIZED)
    {
      initializeTime();
    }
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 80, "%I:%M:%S", timeinfo);
    String time = buffer;
    // Serial.print("Time: "); Serial.println(date);
    return time;
  } else {
    return "23:45";
  }

}

/**
 * @brief Fetches the current date as a formatted string.
 *
 * This function retrieves the current date in the format "DDMonYYYY" (e.g., "15Oct2023").
 * If the time system is not initialized, it initializes the time before fetching the date.
 *
 * @return String The current date as a formatted string.
 */
String fetchDate()
{
  if (!TEST_MODE) {
    if (!TIME_INITIALIZED)
    {
      initializeTime();
    }
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 80, "%d%b%Y", timeinfo);
    String time = buffer;
    return time;
  } else {
    return "16Sep1993";
  }
}
