#include "stdint.h"
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"
#include "TouchScreen.h"
#include "bitmaps.h"

// Pins for display
#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8
#define PRESSURE_THRESHOLD 1200

// Pins for touch screen
#define YP A2
#define XM A3
#define YM 13
#define XP 12

// Touch screen boundaries
#define TS_LEFT 150
#define TS_RT 840
#define TS_TOP 120
#define TS_BOT 900

enum ButtonState
{
  Unpressed,
  Pressed
};

int xpos, ypos = {0};

typedef struct View
{
  int16_t height;
  int16_t width;
  int anchor[2];
  ButtonState state;
} view;

typedef struct NumPad
{
  View buttons[12];
  int buttonCount;
} numpad;

NumPad numbers = {0};

// Button state (0 = No Button Pressed, 1 = Button One Pressed, 2 = Button Two Pressed...)
static int state = 0;

void mapTouchWithRotation(TSPoint point);
void checkButtonState(int state);

void buttonDepress(int button);