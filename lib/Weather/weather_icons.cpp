#include "weather_icons.h"
#include "weather_bitmaps.h"

static WeatherXbms::XbmEntry errorXbm = {error_bits, 48, 48};

WeatherXbms::XbmEntry *WeatherXbms::getXbm(int id, bool isDay)
{
    auto &map = isDay ? xbmDayMap : xbmNightMap;
    auto it = map.find(id);
    return (it != map.end()) ? &it->second : &errorXbm;
}


static WeatherXbms::XbmEntry dayClear = {dayClear_bits, 48, 48};
static WeatherXbms::XbmEntry dayPartlyCloudy = {dayPartlyCloudy_bits, 48, 48};
static WeatherXbms::XbmEntry dayRainy = {dayRainy_bits, 48, 48};
static WeatherXbms::XbmEntry dayFoggy = {dayFoggy_bits, 48, 48};

static WeatherXbms::XbmEntry nightClear = {nightClear_bits, 48, 48};
static WeatherXbms::XbmEntry nightPartlyCloudy = {nightPartlyCloudy_bits, 48, 48};
static WeatherXbms::XbmEntry nightRainy = {nightRainy_bits, 48, 48};
static WeatherXbms::XbmEntry nightFoggy = {nightFoggy_bits, 48, 48};

static WeatherXbms::XbmEntry rainy = {rainy_bits, 48, 48};
static WeatherXbms::XbmEntry cloudy = {cloudy_bits, 48, 48};
static WeatherXbms::XbmEntry heavyFog = {heavyFog_bits, 48, 48};

std::unordered_map<int, WeatherXbms::XbmEntry> WeatherXbms::xbmDayMap = {
  {0, dayClear},            // Clear Sky
  {1, dayClear},            // Mainly clear
  {2, dayPartlyCloudy},     // Partly cloudy
  {3, cloudy},              // Overcast
  {45, dayFoggy},           // Fog
  {48, heavyFog},           // Depositing Rime Fog
  {51, dayRainy},           // Drizzle: Light
  {53, dayRainy},           // Drizzle: Moderate
  {55, dayRainy},           // Drizzle: Dense
  {56, dayRainy},           // Freezing Drizzle: Light
  {57, dayRainy},           // Freezing Drizzle: Dense
  {61, dayRainy},           // Rain: Slight
  {62, dayRainy},           // Rain: Moderate
  {63, dayRainy},           // Rain: Moderate
  {65, dayRainy},           // Rain: Heavy
  {66, dayRainy},           // Freezing Rain: Light
  {67, dayRainy},           // Freezing Rain: Heavy
  {71, dayRainy},           // Snow Fall: Slight
  {73, dayRainy},           // Snow Fall: Moderate
  {75, dayRainy},           // Snow Fall: Heavy
  {77, dayRainy},           // Snow Grains
  {80, dayRainy},           // Rain Showers: Slight
  {81, dayRainy},           // Rain Showers: Moderate
  {82, dayRainy},           // Rain Showers: Violent
  {85, dayRainy},           // Snow showers: Slight
  {86, dayRainy},           // Snow showers: Heavy
  {95, rainy},              // Thunderstorm
  {96, rainy},              // Thunderstorm with slight hail
  {99, rainy}               // Thunderstorm with heavy hail
};


std::unordered_map<int, WeatherXbms::XbmEntry> WeatherXbms::xbmNightMap = {
  {0, nightClear},          // Clear Sky
  {1, nightClear},          // Mainly clear
  {2, nightPartlyCloudy},   // Partly cloudy
  {3, cloudy},              // Overcast
  {45, nightFoggy},         // Fog
  {48, heavyFog},           // Depositing Rime Fog
  {51, nightRainy},         // Drizzle: Light
  {53, nightRainy},         // Drizzle: Moderate
  {55, nightRainy},         // Drizzle: Dense
  {56, nightRainy},         // Freezing Drizzle: Light
  {57, nightRainy},         // Freezing Drizzle: Dense
  {61, nightRainy},         // Rain: Slight
  {62, nightRainy},         // Rain: Moderate
  {63, nightRainy},         // Rain: Moderate
  {65, nightRainy},         // Rain: Heavy
  {66, nightRainy},         // Freezing Rain: Light
  {67, nightRainy},         // Freezing Rain: Heavy
  {71, nightRainy},         // Snow Fall: Slight
  {73, nightRainy},         // Snow Fall: Moderate
  {75, nightRainy},         // Snow Fall: Heavy
  {77, nightRainy},         // Snow Grains
  {80, nightRainy},         // Rain Showers: Slight
  {81, nightRainy},         // Rain Showers: Moderate
  {82, nightRainy},         // Rain Showers: Violent
  {85, nightRainy},         // Snow showers: Slight
  {86, nightRainy},         // Snow showers: Heavy
  {95, rainy},              // Thunderstorm
  {96, rainy},              // Thunderstorm with slight hail
  {99, rainy}               // Thunderstorm with heavy hail
};
