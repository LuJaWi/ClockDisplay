#include <TFT_eSPI.h>
#include "../lib/Display/screen_styles.h"

void repeatText(TFT_eSPI &tft)
{

  String repeatedText = "on and ";

  int16_t cursor_y;
  for (int i = 0; i < repeatedText.length(); i++)
  {
    int r = random(0, 256);
    int g = random(0, 256);
    int b = random(0, 256);
    uint16_t rgb565 = tft.color565(r, g, b);
    tft.setTextColor(rgb565);
    char c = repeatedText[i];
    tft.print(c);
    if (c != ' ')
    {
      delay(20);
    }
    // cursor_x = tft.getCursorX();
    cursor_y = tft.getCursorY();
    if (cursor_y >= TFT_WIDTH)
    {
      tft.setCursor(0, 0);
      tft.fillScreen(BG_COLOR);
    }
  }
}