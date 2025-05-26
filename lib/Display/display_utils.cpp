#include <Arduino.h>
#include <TFT_eSPI.h>
#include <ArduinoJson.h>
#include "screen_styles.h"
#include "time_utils.h"
#include "weather_utils.h"
#include "snakeFiller.h"

/**
 * @namespace DisplayState
 * @brief A namespace that encapsulates various display-related state variables.
 *
 * This namespace contains string representations of date, time, and temperature,
 * as well as a pointer to a widget for display purposes.
 *
 * Variables:
 * - DATE: The full date as a string.
 * - DAY: The day of the week as a string.
 * - MONTH: The month as a string.
 * - YEAR: The year as a string.
 * - TIME: The full time as a string.
 * - HH: The hour component of the time as a string.
 * - MM: The minute component of the time as a string.
 * - SS: The second component of the time as a string.
 * - TEMP: The temperature as a string.
 * - WIDGET: A pointer to an unsigned char representing a widget for display.
 */
namespace DisplayState
{
  String DATE;
  String DAY;
  String MONTH;
  String YEAR;

  String TIME;
  String HH;
  String MM;
  String SS;

  String TEMP;
  unsigned char *WIDGET;
}

// Updates the date fields on the display
/**
 * @brief Updates the date display on the TFT screen.
 *
 * This function updates the date display widget on the TFT screen by comparing
 * the current date with the previously displayed date. If the date has changed,
 * it updates the display with the new date. If no valid date data is detected,
 * it clears the widget area.
 *
 * @param tft Reference to the TFT_eSPI object used for drawing on the screen.
 *
 * The function performs the following steps:
 * - Checks if the `DisplayState::DATE` string contains valid date data.
 * - If invalid, clears the widget area and exits.
 * - Extracts the day, month, and year components from `DisplayState::DATE`.
 * - Fetches the current date using `fetchDate()` and extracts its components.
 * - Updates the display for each component (day, month, year) only if it has changed.
 * - Updates the `DisplayState` variables to reflect the new date.
 */
void updateDateDisplay(TFT_eSPI &tft)
{

  String dateNow = fetchDate();
  uint16_t x_pos = TFT_HEIGHT;
  uint16_t y_pos = 0;

  String dayNow = dateNow.substring(0, 2);
  String monthNow = dateNow.substring(2, 5);
  String yearNow = dateNow.substring(5, 9);

  if (DisplayState::DATE == dateNow) {
    return;
  }
  tft.setTextFont(DATE_FONT);
  if (DisplayState::DAY != dayNow) {
    tft.setCursor(TFT_HEIGHT - tft.textWidth(DisplayState::DAY), y_pos);
    tft.setTextColor(BG_COLOR);
    tft.print(DisplayState::DAY);
    tft.setCursor(TFT_HEIGHT - tft.textWidth(dayNow), y_pos);
    tft.setTextColor(DATE_COLOR);
    tft.print(dayNow);
  }
  if (DisplayState::MONTH != monthNow) {
    tft.setCursor(TFT_HEIGHT - tft.textWidth(DisplayState::MONTH) - tft.textWidth(DisplayState::DAY) - tft.textWidth(" "), y_pos);
    tft.setTextColor(BG_COLOR);
    tft.print(DisplayState::MONTH);
    tft.setCursor(TFT_HEIGHT - tft.textWidth(monthNow) - tft.textWidth(dayNow) - tft.textWidth(" "), y_pos);
    tft.setTextColor(DATE_COLOR);
    tft.print(monthNow);
  }
  if (DisplayState::YEAR != yearNow) {
    tft.setCursor(x_pos - tft.textWidth(DisplayState::YEAR), y_pos + tft.fontHeight(DATE_FONT));
    tft.setTextColor(BG_COLOR);
    tft.print(DisplayState::YEAR);
    tft.setCursor(x_pos - tft.textWidth(yearNow), y_pos + tft.fontHeight(DATE_FONT));
    tft.setTextColor(DATE_COLOR);
    tft.print(yearNow);
  }

  DisplayState::DATE = dateNow;
  DisplayState::DAY = dayNow;
  DisplayState::MONTH = monthNow;
  DisplayState::YEAR = yearNow;
}

/**
 * @brief Updates the time display on the TFT screen.
 *
 * This function fetches the current time, extracts the hours, minutes,
 * and seconds, and updates the display accordingly. It also updates
 * the internal state of the display to reflect the current time.
 *
 * @param tft Reference to the TFT_eSPI object used for drawing on the screen.
 *
 * The function performs the following steps:
 * - Fetches the current time as a string in the format "HH:MM:SS".
 * - Extracts the hours, minutes, and seconds from the time string.
 * - Updates the display for hours and minutes, drawing a colon (:) between them.
 * - Updates the internal DisplayState with the new time values.
 */
void updateTimeDisplay(TFT_eSPI &tft)
{
  uint16_t x_pos = 5;
  uint16_t y_pos = 0;
  String timeNow = fetchTime();

  String hhNow = timeNow.substring(0, 2);
  String mmNow = timeNow.substring(3, 5);
  String ssNow = timeNow.substring(6, 8);

  if (hhNow != DisplayState::HH || mmNow != DisplayState::MM) {
    tft.setTextFont(TIME_FONT);
  }
  if (hhNow != DisplayState::HH){
    tft.setTextColor(BG_COLOR);
    tft.setCursor(x_pos, y_pos);
    tft.print(DisplayState::HH);
    tft.setTextColor(TIME_COLOR);
    tft.setCursor(x_pos, y_pos);
    tft.print(hhNow);
    tft.print(":");
  }
  if (mmNow != DisplayState::MM){
    x_pos += tft.textWidth(hhNow + ":");
    tft.setTextColor(BG_COLOR);
    tft.setCursor(x_pos, y_pos);
    if (DisplayState::MM.substring(0,1) != mmNow.substring(0,1)) {
      tft.drawString(DisplayState::MM.substring(0,1), x_pos, y_pos, TIME_FONT);
      tft.setTextColor(TIME_COLOR);
      tft.drawString(mmNow.substring(0,1), x_pos, y_pos, TIME_FONT);
    }
    x_pos += tft.textWidth(mmNow.substring(0,1));
    if (DisplayState::MM.substring(1,2) != mmNow.substring(1,2)) {
      tft.setTextColor(BG_COLOR);
      tft.drawString(DisplayState::MM.substring(1,2), x_pos, y_pos, TIME_FONT);
      tft.setTextColor(TIME_COLOR);
      tft.drawString(mmNow.substring(1,2), x_pos, y_pos, TIME_FONT);
    }
  }

  DisplayState::HH = hhNow;
  DisplayState::MM = mmNow;
  DisplayState::SS = ssNow;
}

/**
 * @brief Updates the temperature display on the TFT screen.
 *
 * This function fetches the current temperature, formats it, and updates
 * the display with the new temperature value. It also updates the
 * DisplayState::TEMP variable to reflect the current temperature.
 *
 * @param tft Reference to the TFT_eSPI object used for rendering on the display.
 */
void updateTempDisplay(TFT_eSPI &tft)
{
  uint16_t y_pos = TFT_WIDTH - tft.fontHeight(TEMP_FONT) - 45;
  uint16_t x_pos = 10;
  String tempNow = fetchTemperature() + "`";
  if (DisplayState::TEMP != tempNow){
    tft.setTextFont(TEMP_FONT);
    tft.setTextColor(BG_COLOR);
    tft.setCursor(x_pos, y_pos);
    tft.print(DisplayState::TEMP);
    tft.setCursor(x_pos, y_pos);
    tft.setTextColor(TEXT_COLOR);
    tft.print(tempNow);
    DisplayState::TEMP = tempNow;
  }
}

/**
 * @brief Updates the weather widget display on the TFT screen.
 *
 * This function fetches the current weather widget bitmap and compares it
 * with the previously displayed widget. If the widget has changed, it clears
 * the old widget from the screen and draws the new one at the specified position.
 *
 * @param tft Reference to the TFT_eSPI object used for drawing on the screen.
 *
 * The function performs the following steps:
 * - Fetches the current weather widget bitmap using `fetchWeatherWidget()`.
 * - Compares the fetched widget with the currently displayed widget.
 * - If the widgets are the same, the function returns without making changes.
 * - If the widgets are different:
 *   - Clears the old widget from the screen by drawing it with the background color.
 *   - Draws the new widget on the screen with the text color.
 *   - Updates the `DisplayState::WIDGET` to the new widget.
 */
void updateWeatherWidgetDisplay(TFT_eSPI &tft)
{
  uint16_t x_pos = 5;
  uint16_t y_pos = TFT_WIDTH - 48;
  if (DisplayState::WIDGET == nullptr) { // On first check, set the widget and exit
    DisplayState::WIDGET = fetchWeatherWidget();  
    const unsigned char *c_currentWidget = DisplayState::WIDGET;
    tft.drawXBitmap(
      x_pos,
      y_pos,
      c_currentWidget,
      48, 48, TEXT_COLOR);
    return;
  }

  unsigned char *widgetNow = fetchWeatherWidget();
  const unsigned char *c_widgetNow = widgetNow; // create const to use for drawXBitmap function
  const unsigned char *c_currentWidget = DisplayState::WIDGET;
  if (c_widgetNow == c_currentWidget) {return;}

  tft.drawXBitmap(
      x_pos,
      y_pos,
      c_currentWidget,
      48, 48, BG_COLOR);

  tft.drawXBitmap(
      x_pos,
      y_pos,
      c_widgetNow,
      48, 48, TEXT_COLOR);
  DisplayState::WIDGET = widgetNow;
}

void updateTextBox(TFT_eSPI &tft)
{
  uint16_t x_pos = 60;
  uint16_t y_pos = tft.fontHeight(TIME_FONT) + 10;
  tft.setTextFont(2);
  tft.drawString("maeve is a sweet lil cutie", x_pos, y_pos);
  tft.drawString(" pie & i luv her sm  <<333", x_pos, y_pos + tft.fontHeight(2));
}

void fillRandom(TFT_eSPI &tft)
{
  if (random(0, 2))
  {
    uint16_t x_pos = 60;
    uint16_t y_pos = tft.fontHeight(TIME_FONT) + 10;
    int r;

    int x = random(x_pos, TFT_HEIGHT);
    int y = random(y_pos, TFT_WIDTH);
    uint16_t c = random(0x0000, 0xFFFF);
    int w = random(1, 25);
    int h = w;

    if (random(0, 5))
    {
      r = random(1, 5);
    }
    else
    {
      r = random(5, w); // get weird on occasion
    }
    tft.fillRoundRect(x, y, w, h, r, c);
    int rand_border = random(0, 3);
    if (rand_border == 1)
    {
      tft.drawRoundRect(x, y, w, h, r, 0xFFFF);
    }
    else if (rand_border == 2)
    {
      tft.drawRoundRect(x, y, w, h, r, 0x0000);
    }
    else
    {
      tft.drawRoundRect(x, y, w, h, r, c);
    }
  }
}

void growSnake(SnakeFiller& snakeFiller) {
  snakeFiller.randomPixel();
}

/**
 * @brief Sets up the display regions by drawing horizontal and vertical lines
 *        to divide the screen into sections.
 *
 * @param tft Reference to a TFT_eSPI object used to interact with the display.
 */
void setupRegions(TFT_eSPI &tft)
{
  tft.drawLine(0, tft.fontHeight(TIME_FONT) + 5, TFT_HEIGHT, tft.fontHeight(TIME_FONT) + 5, BORDER_COLOR);
  tft.drawLine(0, tft.fontHeight(TIME_FONT) + 6, TFT_HEIGHT, tft.fontHeight(TIME_FONT) + 6, BORDER_COLOR);
  tft.drawLine(0, tft.fontHeight(TIME_FONT) + 7, TFT_HEIGHT, tft.fontHeight(TIME_FONT) + 7, BORDER_COLOR);

  int line_x = 55;
  tft.drawLine(line_x - 1, tft.fontHeight(TIME_FONT) + 5, line_x - 1, TFT_WIDTH, BORDER_COLOR);
  tft.drawLine(line_x + 0, tft.fontHeight(TIME_FONT) + 5, line_x + 0, TFT_WIDTH, BORDER_COLOR);
  tft.drawLine(line_x + 1, tft.fontHeight(TIME_FONT) + 5, line_x + 1, TFT_WIDTH, BORDER_COLOR);
}
