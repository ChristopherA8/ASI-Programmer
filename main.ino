#include "main.h"

// Initialize touchscreen and display objects
Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// Runs once on reset
void setup()
{
  state = 0;

  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  delay(1000);
  digitalWrite(3, LOW);

  Serial.begin(9600);

  tft.begin();
  tft.setRotation(2);

  tft.fillScreen(HX8357_WHITE);
  tft.setFont(&FreeSans12pt7b);

  int16_t height = tft.height();
  int16_t width = tft.width();

  // Button count is just for numbers (for now)
  numpad.buttonCount = 10; // it will be 12 when I add "a" and "b"

  // Input box
  inputBox.height = 100;
  inputBox.width = width;
  inputBox.anchor[0] = 0;  // top left x-value
  inputBox.anchor[1] = 50; // top left y-value

  // Draw inputBox
  tft.drawLine(inputBox.anchor[0], inputBox.anchor[1], inputBox.anchor[0] + inputBox.width, inputBox.anchor[1], HX8357_BLACK);
  tft.drawLine(inputBox.anchor[0], inputBox.anchor[1], inputBox.anchor[0], inputBox.anchor[1] + inputBox.height, HX8357_BLACK);
  tft.drawLine(inputBox.anchor[0], inputBox.anchor[1] + inputBox.height, inputBox.anchor[0] + inputBox.width, inputBox.anchor[1] + inputBox.height, HX8357_BLACK);
  tft.drawLine(inputBox.anchor[0] + inputBox.width - 1, inputBox.anchor[1] + inputBox.height, inputBox.anchor[0] + inputBox.width - 1, inputBox.anchor[1], HX8357_BLACK);

  // Write Button
  View writeButton = {0};
  writeButton.height = 100;
  writeButton.width = 90;
  writeButton.anchor[0] = width - 90; // top left x-value
  writeButton.anchor[1] = 50;         // top left y-value

  // Write button
  tft.drawLine(writeButton.anchor[0], writeButton.anchor[1], writeButton.anchor[0] + writeButton.width, writeButton.anchor[1], HX8357_BLACK);
  tft.drawLine(writeButton.anchor[0], writeButton.anchor[1], writeButton.anchor[0], writeButton.anchor[1] + writeButton.height, HX8357_BLACK);
  tft.drawLine(writeButton.anchor[0], writeButton.anchor[1] + writeButton.height, writeButton.anchor[0] + writeButton.width, writeButton.anchor[1] + writeButton.height, HX8357_BLACK);
  tft.drawLine(writeButton.anchor[0] + writeButton.width - 1, writeButton.anchor[1] + writeButton.height, writeButton.anchor[0] + writeButton.width - 1, writeButton.anchor[1], HX8357_BLACK);
  tft.setCursor(writeButton.anchor[0] + (writeButton.width / 2) + NUMPAD_PADDING_WIDTH, writeButton.anchor[1] + (writeButton.height / 2) + NUMPAD_PADDING_HEIGHT);
  tft.setTextColor(HX8357_BLACK);
  tft.setTextSize(NUMPAD_TEXT_SIZE);
  tft.println("Write");

  // Number One
  numpad.buttons[0] = Button();
  numpad.buttons[0].initButtonULwR(&tft, 0, 180, width / 3, 50, 8, HX8357_BLACK, HX8357_WHITE, HX8357_BLACK, "1", 1);
  numpad.buttons[0].drawButton();

  // Number Two
  numpad.buttons[1] = Button();
  numpad.buttons[1].initButtonULwR(&tft, width / 3, 180, width / 3, 50, 8, HX8357_BLACK, HX8357_WHITE, HX8357_BLACK, "2", 1);
  numpad.buttons[1].drawButton();

  // Number Three
  numpad.buttons[2] = Button();
  numpad.buttons[2].initButtonULwR(&tft, (width / 3) * 2, 180, width / 3, 50, 8, HX8357_BLACK, HX8357_WHITE, HX8357_BLACK, "3", 1);
  numpad.buttons[2].drawButton();

  // Number Four
  numpad.buttons[3] = Button();
  numpad.buttons[3].initButtonULwR(&tft, 0, 260, width / 3, 50, 8, HX8357_BLACK, HX8357_WHITE, HX8357_BLACK, "4", 1);
  numpad.buttons[3].drawButton();

  // Number Five
  numpad.buttons[4] = Button();
  numpad.buttons[4].initButtonULwR(&tft, width / 3, 260, width / 3, 50, 8, HX8357_BLACK, HX8357_WHITE, HX8357_BLACK, "5", 1);
  numpad.buttons[4].drawButton();

  // Number Six
  numpad.buttons[5] = Button();
  numpad.buttons[5].initButtonULwR(&tft, (width / 3) * 2, 260, width / 3, 50, 8, HX8357_BLACK, HX8357_WHITE, HX8357_BLACK, "6", 1);
  numpad.buttons[5].drawButton();

  // Number Seven
  numpad.buttons[6] = Button();
  numpad.buttons[6].initButtonULwR(&tft, 0, 340, width / 3, 50, 8, HX8357_BLACK, HX8357_WHITE, HX8357_BLACK, "7", 1);
  numpad.buttons[6].drawButton();

  // Number Eight
  numpad.buttons[7] = Button();
  numpad.buttons[7].initButtonULwR(&tft, width / 3, 340, width / 3, 50, 8, HX8357_BLACK, HX8357_WHITE, HX8357_BLACK, "8", 1);
  numpad.buttons[7].drawButton();

  // Number Nine
  numpad.buttons[8] = Button();
  numpad.buttons[8].initButtonULwR(&tft, (width / 3) * 2, 340, width / 3, 50, 8, HX8357_BLACK, HX8357_WHITE, HX8357_BLACK, "9", 1);
  numpad.buttons[8].drawButton();

  // Number Zero
  numpad.buttons[9] = Button();
  numpad.buttons[9].initButtonULwR(&tft, width / 3, 420, width / 3, 50, 8, HX8357_BLACK, HX8357_WHITE, HX8357_BLACK, "0", 1);
  numpad.buttons[9].drawButton();

  // Mode Button
  numpad.buttons[10] = Button();
  numpad.buttons[10].initButtonULwR(&tft, 0, 420, width / 3, 50, 8, HX8357_BLACK, HX8357_WHITE, HX8357_BLACK, "a/b/o", 1);
  numpad.buttons[10].drawButton();
  // changeMode("O");

  // Read Button
  numpad.buttons[11] = Button();
  numpad.buttons[11].initButtonULwR(&tft, (width / 3) * 2, 420, width / 3, 50, 8, HX8357_BLACK, HX8357_WHITE, HX8357_BLACK, "Read", 1);
  numpad.buttons[11].drawButton();

  tft.setTextSize(INPUT_BOX_TEXT_SIZE);
  tft.setCursor(25, 120);
  tft.print("0");
}

void loop()
{
}

/*
void loop()
{

  TSPoint p = ts.getPoint();
  mapTouchWithRotation(p);

  if (p.z > MIN_PRESSURE && p.z < MAX_PRESSURE)
  {
    // Number buttons
    for (int i = 0; i < numpad.buttonCount; i++)
    {
      int width = numpad.buttons[i].width;
      int height = numpad.buttons[i].height;
      int topLeftX = numpad.buttons[i].anchor[0];
      int topLeftY = numpad.buttons[i].anchor[1];
      int rightSide = topLeftX + width;
      int bottomSide = topLeftY + height;

      // If touch is within button bounds
      if (xpos >= topLeftX && xpos <= rightSide && ypos >= topLeftY && ypos <= bottomSide)
      {
        state = i + 1;
        aButtonIsPressed = true;
      }
    }

    // Other Buttons
    int width = numpad.buttons[10].width;
    int height = numpad.buttons[10].height;
    int topLeftX = numpad.buttons[10].anchor[0];
    int topLeftY = numpad.buttons[10].anchor[1];
    int rightSide = topLeftX + width;
    int bottomSide = topLeftY + height;

    // If touch is within button bounds
    if (xpos >= topLeftX && xpos <= rightSide && ypos >= topLeftY && ypos <= bottomSide)
    {
      state = 11;
      aButtonIsPressed = true;
    }

    if (!aButtonIsPressed)
    {
      state = 0;
    }
    else
    {
      aButtonIsPressed = false;
    }
  }
  else
  {
    state = 0;
  }

  // Button State Machine
  checkButtonState(state);
}

void mapTouchWithRotation(TSPoint p)
{
  switch (tft.getRotation())
  {
  case 0:
    xpos = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    ypos = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
    break;
  case 1:
    xpos = map(p.y, TS_MINY, TS_MAXY, 0, tft.width());
    ypos = map(p.x, TS_MAXX, TS_MINX, 0, tft.height());
    break;
  case 2:
    xpos = map(p.x, TS_MAXX, TS_MINX, 0, tft.width());
    ypos = map(p.y, TS_MAXY, TS_MINY, 0, tft.height());
    break;
  case 3:
    xpos = map(p.y, TS_MAXY, TS_MINY, 0, tft.width());
    ypos = map(p.x, TS_MINX, TS_MAXX, 0, tft.height());
    break;
  }
}

void checkButtonState(int state)
{
  switch (state)
  {
  case 0:
    for (int i = 0; i < numpad.buttonCount + 1; i++)
    {
      // On button release
      if (numpad.buttons[i].state == Pressed)
      {
        // Button released
        int width = numpad.buttons[i].width;
        int height = numpad.buttons[i].height;
        int topLeftX = numpad.buttons[i].anchor[0];
        int topLeftY = numpad.buttons[i].anchor[1];
        int topRightX = topLeftX + width;
        int topRightY = topLeftY;
        int bottomLeftX = topLeftX;
        int bottomLeftY = topLeftY + height;
        tft.drawLine(topLeftX + 1, topLeftY + 1, topRightX - 1, topRightY + 1, HX8357_WHITE);                          // topLeft -> topRight
        tft.drawLine(topLeftX + 1, topLeftY + 1, bottomLeftX + 1, bottomLeftY - 1, HX8357_WHITE);                      // topLeft -> bottomLeft
        tft.drawLine(bottomLeftX + 1, bottomLeftY - 1, (bottomLeftX + width) - 1, bottomLeftY - 1, HX8357_WHITE);      // bottomLeft -> bottomRight
        tft.drawLine(topRightX - 1, topRightY + 1, (bottomLeftX + width) - 1, (topRightY + height) - 1, HX8357_WHITE); // topRight -> bottomRight
      }

      // Reset button states
      numpad.buttons[i].state = Unpressed;
    }
    break;
  case 1:
    if (numpad.buttons[0].state == Unpressed)
    {
      pressButton(0);
      numpad.buttons[0].state = Pressed;
    }
    break;
  case 2:
    if (numpad.buttons[1].state == Unpressed)
    {
      pressButton(1);
      numpad.buttons[1].state = Pressed;
    }
    break;
  case 3:
    if (numpad.buttons[2].state == Unpressed)
    {
      pressButton(2);
      numpad.buttons[2].state = Pressed;
    }
    break;
  case 4:
    if (numpad.buttons[3].state == Unpressed)
    {
      pressButton(3);
      numpad.buttons[3].state = Pressed;
    }
    break;
  case 5:
    if (numpad.buttons[4].state == Unpressed)
    {
      pressButton(4);
      numpad.buttons[4].state = Pressed;
    }
    break;
  case 6:
    if (numpad.buttons[5].state == Unpressed)
    {
      pressButton(5);
      numpad.buttons[5].state = Pressed;
    }
    break;
  case 7:
    if (numpad.buttons[6].state == Unpressed)
    {
      pressButton(6);
      numpad.buttons[6].state = Pressed;
    }
    break;
  case 8:
    if (numpad.buttons[7].state == Unpressed)
    {
      pressButton(7);
      numpad.buttons[7].state = Pressed;
    }
    break;
  case 9:
    if (numpad.buttons[8].state == Unpressed)
    {
      pressButton(8);
      numpad.buttons[8].state = Pressed;
    }
    break;
  case 10:
    if (numpad.buttons[9].state == Unpressed)
    {
      pressButton(9);
      numpad.buttons[9].state = Pressed;
    }
  case 11: // a/b/O button
    if (numpad.buttons[10].state == Unpressed)
    {
      // pressButton(10);
      changeMode(numpad.mode);
      numpad.buttons[10].state = Pressed;
    }
    break;
  default:
    break;
  }
}

void pressButton(int button)
{
  int width = numpad.buttons[button].width;
  int height = numpad.buttons[button].height;
  int topLeftX = numpad.buttons[button].anchor[0];
  int topLeftY = numpad.buttons[button].anchor[1];
  int topRightX = topLeftX + width;
  int topRightY = topLeftY;
  int bottomLeftX = topLeftX;
  int bottomLeftY = topLeftY + height;
  tft.drawLine(topLeftX + 1, topLeftY + 1, topRightX - 1, topRightY + 1, HX8357_RED);                          // topLeft -> topRight
  tft.drawLine(topLeftX + 1, topLeftY + 1, bottomLeftX + 1, bottomLeftY - 1, HX8357_RED);                      // topLeft -> bottomLeft
  tft.drawLine(bottomLeftX + 1, bottomLeftY - 1, (bottomLeftX + width) - 1, bottomLeftY - 1, HX8357_RED);      // bottomLeft -> bottomRight
  tft.drawLine(topRightX - 1, topRightY + 1, (bottomLeftX + width) - 1, (topRightY + height) - 1, HX8357_RED); // topRight -> bottomRight

  int buttonName = button + 1;
  if (buttonName == 10)
    buttonName = 0;

  clearInputNumbers();
  tft.setCursor(25, 120);
  changeNumber(buttonName);
  tft.print(numpad.number);

  char str[128];
  snprintf(str, 128, "Button %d Pressed", buttonName);
  Serial.println(str);
}

void changeMode(const char *mode)
{
  if (mode == "a")
  {
    numpad.mode = "b";
  }
  else if (mode == "b")
  {
    numpad.mode = "O";
  }
  else if (mode == "O")
  {
    numpad.mode = "a";
  }
  else
  {
    numpad.mode = mode;
  }

  tft.setTextSize(INPUT_BOX_TEXT_SIZE);
  clearInputMode();
  tft.setCursor(81, 120);
  tft.print(numpad.mode);
}

unsigned changeNumber(unsigned number)
{
  if (getNumberLength(numpad.number) >= 2 || numpad.number == 0)
  {
    if (number <= 3)
    {
      numpad.number = number;
      return numpad.number;
    }
    else
    {
      numpad.number = 0;
      return numpad.number;
    }
  }
  else
  {
    if (numpad.number == 3 && number != 0)
    {
      numpad.number = 0;
      return numpad.number;
    }

    numpad.number = concatenate(numpad.number, number);
    return numpad.number;
  }
}

int getNumberLength(int x)
{
  return floor(log10(abs(x))) + 1;
}

unsigned concatenate(unsigned x, unsigned y)
{
  unsigned pow = 10;
  while (y >= pow)
    pow *= 10;
  return x * pow + y;
}

void clearInputbox()
{
  tft.fillRect(inputBox.anchor[0] + 1, inputBox.anchor[1] + 1, inputBox.width - 2, inputBox.height - 2, HX8357_WHITE);
}

// white sqaure x values
// 0 - 80
void clearInputNumbers()
{
  tft.fillRect(inputBox.anchor[0] + 1, inputBox.anchor[1] + 1, 80 - 1, inputBox.height - 2, HX8357_WHITE);
}

// 76 - inputBox.width
void clearInputMode()
{
  tft.fillRect(61, inputBox.anchor[1] + 1, (inputBox.width - 1) - 81, inputBox.height - 1, HX8357_WHITE);
}
*/