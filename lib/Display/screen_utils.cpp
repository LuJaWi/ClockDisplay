#include <TFT_eSPI.h>
#include "screen_styles.h"

/**
 * @brief Initializes the TFT screen with predefined settings.
 * 
 * This function sets up the TFT screen by initializing it, setting its rotation,
 * positioning the cursor, filling the screen with a background color, and setting
 * the text color.
 * 
 * @param tft Reference to a TFT_eSPI object representing the screen to be initialized.
 */
void screenSetup(TFT_eSPI &tft)
{
  tft.init();
  tft.setRotation(3);
  tft.setCursor(0, 0);
  tft.fillScreen(BG_COLOR);
  tft.setTextColor(TEXT_COLOR);
}
