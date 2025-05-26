#pragma once
#include <unordered_map>

class WeatherXbms {
public:
  struct XbmEntry {
    unsigned char* bitmapData;
    int width;
    int height;
  };

  static XbmEntry* getXbm(int id, bool isDay);

private:
  static std::unordered_map<int, XbmEntry> xbmDayMap;
  static std::unordered_map<int, XbmEntry> xbmNightMap;
};

