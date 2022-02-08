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
  numbers.buttonCount = 10; // it will be 12 when I add "a" and "b"

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
  writeButton.width = 60;
  writeButton.anchor[0] = width - 60; // top left x-value
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

  // Read Button
  View readButton = {0};
  readButton.height = 50;
  readButton.width = width / 3;
  readButton.anchor[0] = (width / 3) * 2; // top left x-value
  readButton.anchor[1] = 420;             // top left y-value

  // Read button
  tft.drawLine(readButton.anchor[0], readButton.anchor[1], readButton.anchor[0] + readButton.width, readButton.anchor[1], HX8357_BLACK);
  tft.drawLine(readButton.anchor[0], readButton.anchor[1], readButton.anchor[0], readButton.anchor[1] + readButton.height, HX8357_BLACK);
  tft.drawLine(readButton.anchor[0], readButton.anchor[1] + readButton.height, readButton.anchor[0] + readButton.width, readButton.anchor[1] + readButton.height, HX8357_BLACK);
  tft.drawLine(readButton.anchor[0] + readButton.width - 1, readButton.anchor[1] + readButton.height, readButton.anchor[0] + readButton.width - 1, readButton.anchor[1], HX8357_BLACK);
  tft.setCursor(readButton.anchor[0] + (readButton.width / 2) + (-30), readButton.anchor[1] + (readButton.height / 2) + NUMPAD_PADDING_HEIGHT);
  tft.setTextColor(HX8357_BLACK);
  tft.setTextSize(NUMPAD_TEXT_SIZE);
  tft.println("Read");

  // Number One
  View numOne = {0};
  numOne.height = 50;
  numOne.width = width / 3;
  numOne.anchor[0] = 0;   // top left x-value
  numOne.anchor[1] = 180; // top left y-value

  // Add it to the numpad
  numbers.buttons[0] = numOne;

  // Draw numOne
  tft.drawLine(numOne.anchor[0], numOne.anchor[1], numOne.anchor[0] + numOne.width, numOne.anchor[1], HX8357_BLACK);
  tft.drawLine(numOne.anchor[0], numOne.anchor[1], numOne.anchor[0], numOne.anchor[1] + numOne.height, HX8357_BLACK);
  tft.drawLine(numOne.anchor[0], numOne.anchor[1] + numOne.height, numOne.anchor[0] + numOne.width, numOne.anchor[1] + numOne.height, HX8357_BLACK);
  tft.drawLine(numOne.anchor[0] + numOne.width, numOne.anchor[1] + numOne.height, numOne.anchor[0] + numOne.width, numOne.anchor[1], HX8357_BLACK);
  tft.setCursor(numOne.anchor[0] + (numOne.width / 2) + NUMPAD_PADDING_WIDTH, numOne.anchor[1] + (numOne.height / 2) + NUMPAD_PADDING_HEIGHT);
  tft.setTextColor(HX8357_BLACK);
  tft.setTextSize(NUMPAD_TEXT_SIZE);
  tft.println("1");

  // Number Two
  View numTwo = {0};
  numTwo.height = 50;
  numTwo.width = width / 3;
  numTwo.anchor[0] = width / 3; // top left x-value
  numTwo.anchor[1] = 180;       // top left y-value

  numbers.buttons[1] = numTwo;

  // Draw numTwo
  tft.drawLine(numTwo.anchor[0], numTwo.anchor[1], numTwo.anchor[0] + numTwo.width, numTwo.anchor[1], HX8357_BLACK);
  tft.drawLine(numTwo.anchor[0], numTwo.anchor[1], numTwo.anchor[0], numTwo.anchor[1] + numTwo.height, HX8357_BLACK);
  tft.drawLine(numTwo.anchor[0], numTwo.anchor[1] + numTwo.height, numTwo.anchor[0] + numTwo.width, numTwo.anchor[1] + numTwo.height, HX8357_BLACK);
  tft.drawLine(numTwo.anchor[0] + numTwo.width, numTwo.anchor[1] + numTwo.height, numTwo.anchor[0] + numTwo.width, numTwo.anchor[1], HX8357_BLACK);
  tft.setCursor(numTwo.anchor[0] + (numTwo.width / 2) + NUMPAD_PADDING_WIDTH, numTwo.anchor[1] + (numTwo.height / 2) + NUMPAD_PADDING_HEIGHT);
  tft.setTextColor(HX8357_BLACK);
  tft.setTextSize(NUMPAD_TEXT_SIZE);
  tft.println("2");

  // Number Three
  View numThree = {0};
  numThree.height = 50;
  numThree.width = width / 3;
  numThree.anchor[0] = (width / 3) * 2; // top left x-value
  numThree.anchor[1] = 180;             // top left y-value

  numbers.buttons[2] = numThree;

  // Draw numThree
  tft.drawLine(numThree.anchor[0], numThree.anchor[1], numThree.anchor[0] + numThree.width, numThree.anchor[1], HX8357_BLACK);
  tft.drawLine(numThree.anchor[0], numThree.anchor[1], numThree.anchor[0], numThree.anchor[1] + numThree.height, HX8357_BLACK);
  tft.drawLine(numThree.anchor[0], numThree.anchor[1] + numThree.height, numThree.anchor[0] + numThree.width, numThree.anchor[1] + numThree.height, HX8357_BLACK);
  tft.drawLine(numThree.anchor[0] + numThree.width, numThree.anchor[1] + numThree.height, numThree.anchor[0] + numThree.width, numThree.anchor[1], HX8357_BLACK);
  tft.setCursor(numThree.anchor[0] + (numThree.width / 2) NUMPAD_PADDING_WIDTH, numThree.anchor[1] + (numThree.height / 2) + NUMPAD_PADDING_HEIGHT);
  tft.setTextColor(HX8357_BLACK);
  tft.setTextSize(NUMPAD_TEXT_SIZE);
  tft.println("3");

  // Number Four
  View numFour = {0};
  numFour.height = 50;
  numFour.width = width / 3;
  numFour.anchor[0] = 0;   // top left x-value
  numFour.anchor[1] = 260; // top left y-value

  numbers.buttons[3] = numFour;

  // Draw numFour
  tft.drawLine(numFour.anchor[0], numFour.anchor[1], numFour.anchor[0] + numFour.width, numFour.anchor[1], HX8357_BLACK);
  tft.drawLine(numFour.anchor[0], numFour.anchor[1], numFour.anchor[0], numFour.anchor[1] + numFour.height, HX8357_BLACK);
  tft.drawLine(numFour.anchor[0], numFour.anchor[1] + numFour.height, numFour.anchor[0] + numFour.width, numFour.anchor[1] + numFour.height, HX8357_BLACK);
  tft.drawLine(numFour.anchor[0] + numFour.width, numFour.anchor[1] + numFour.height, numFour.anchor[0] + numFour.width, numFour.anchor[1], HX8357_BLACK);
  tft.setCursor(numFour.anchor[0] + (numFour.width / 2) + NUMPAD_PADDING_WIDTH, numFour.anchor[1] + (numFour.height / 2) + NUMPAD_PADDING_HEIGHT);
  tft.setTextColor(HX8357_BLACK);
  tft.setTextSize(NUMPAD_TEXT_SIZE);
  tft.println("4");

  // Number Five
  View numFive = {0};
  numFive.height = 50;
  numFive.width = width / 3;
  numFive.anchor[0] = width / 3; // top left x-value
  numFive.anchor[1] = 260;       // top left y-value

  numbers.buttons[4] = numFive;

  // Draw numFive
  tft.drawLine(numFive.anchor[0], numFive.anchor[1], numFive.anchor[0] + numFive.width, numFive.anchor[1], HX8357_BLACK);
  tft.drawLine(numFive.anchor[0], numFive.anchor[1], numFive.anchor[0], numFive.anchor[1] + numFive.height, HX8357_BLACK);
  tft.drawLine(numFive.anchor[0], numFive.anchor[1] + numFive.height, numFive.anchor[0] + numFive.width, numFive.anchor[1] + numFive.height, HX8357_BLACK);
  tft.drawLine(numFive.anchor[0] + numFive.width, numFive.anchor[1] + numFive.height, numFive.anchor[0] + numFive.width, numFive.anchor[1], HX8357_BLACK);
  tft.setCursor(numFive.anchor[0] + (numFive.width / 2) + NUMPAD_PADDING_WIDTH, numFive.anchor[1] + (numFive.height / 2) + NUMPAD_PADDING_HEIGHT);
  tft.setTextColor(HX8357_BLACK);
  tft.setTextSize(NUMPAD_TEXT_SIZE);
  tft.println("5");

  // Number Six
  View numSix = {0};
  numSix.height = 50;
  numSix.width = width / 3;
  numSix.anchor[0] = (width / 3) * 2; // top left x-value
  numSix.anchor[1] = 260;             // top left y-value

  numbers.buttons[5] = numSix;

  // Draw numSix
  tft.drawLine(numSix.anchor[0], numSix.anchor[1], numSix.anchor[0] + numSix.width, numSix.anchor[1], HX8357_BLACK);
  tft.drawLine(numSix.anchor[0], numSix.anchor[1], numSix.anchor[0], numSix.anchor[1] + numSix.height, HX8357_BLACK);
  tft.drawLine(numSix.anchor[0], numSix.anchor[1] + numSix.height, numSix.anchor[0] + numSix.width, numSix.anchor[1] + numSix.height, HX8357_BLACK);
  tft.drawLine(numSix.anchor[0] + numSix.width, numSix.anchor[1] + numSix.height, numSix.anchor[0] + numSix.width, numSix.anchor[1], HX8357_BLACK);
  tft.setCursor(numSix.anchor[0] + (numSix.width / 2) + NUMPAD_PADDING_WIDTH, numSix.anchor[1] + (numSix.height / 2) + NUMPAD_PADDING_HEIGHT);
  tft.setTextColor(HX8357_BLACK);
  tft.setTextSize(NUMPAD_TEXT_SIZE);
  tft.println("6");

  // Number Seven
  View numSeven = {0};
  numSeven.height = 50;
  numSeven.width = width / 3;
  numSeven.anchor[0] = 0;   // top left x-value
  numSeven.anchor[1] = 340; // top left y-value

  numbers.buttons[6] = numSeven;

  // Draw numSeven
  tft.drawLine(numSeven.anchor[0], numSeven.anchor[1], numSeven.anchor[0] + numSeven.width, numSeven.anchor[1], HX8357_BLACK);
  tft.drawLine(numSeven.anchor[0], numSeven.anchor[1], numSeven.anchor[0], numSeven.anchor[1] + numSeven.height, HX8357_BLACK);
  tft.drawLine(numSeven.anchor[0], numSeven.anchor[1] + numSeven.height, numSeven.anchor[0] + numSeven.width, numSeven.anchor[1] + numSeven.height, HX8357_BLACK);
  tft.drawLine(numSeven.anchor[0] + numSeven.width, numSeven.anchor[1] + numSeven.height, numSeven.anchor[0] + numSeven.width, numSeven.anchor[1], HX8357_BLACK);
  tft.setCursor(numSeven.anchor[0] + (numSeven.width / 2) + NUMPAD_PADDING_WIDTH, numSeven.anchor[1] + (numSeven.height / 2) + NUMPAD_PADDING_HEIGHT);
  tft.setTextColor(HX8357_BLACK);
  tft.setTextSize(NUMPAD_TEXT_SIZE);
  tft.println("7");

  // Number Eight
  View numEight = {0};
  numEight.height = 50;
  numEight.width = width / 3;
  numEight.anchor[0] = width / 3; // top left x-value
  numEight.anchor[1] = 340;       // top left y-value

  numbers.buttons[7] = numEight;

  // Draw numEight
  tft.drawLine(numEight.anchor[0], numEight.anchor[1], numEight.anchor[0] + numEight.width, numEight.anchor[1], HX8357_BLACK);
  tft.drawLine(numEight.anchor[0], numEight.anchor[1], numEight.anchor[0], numEight.anchor[1] + numEight.height, HX8357_BLACK);
  tft.drawLine(numEight.anchor[0], numEight.anchor[1] + numEight.height, numEight.anchor[0] + numEight.width, numEight.anchor[1] + numEight.height, HX8357_BLACK);
  tft.drawLine(numEight.anchor[0] + numEight.width, numEight.anchor[1] + numEight.height, numEight.anchor[0] + numEight.width, numEight.anchor[1], HX8357_BLACK);
  tft.setCursor(numEight.anchor[0] + (numEight.width / 2) + NUMPAD_PADDING_WIDTH, numEight.anchor[1] + (numEight.height / 2) + NUMPAD_PADDING_HEIGHT);
  tft.setTextColor(HX8357_BLACK);
  tft.setTextSize(NUMPAD_TEXT_SIZE);
  tft.println("8");

  // Number Nine
  View numNine = {0};
  numNine.height = 50;
  numNine.width = width / 3;
  numNine.anchor[0] = (width / 3) * 2; // top left x-value
  numNine.anchor[1] = 340;             // top left y-value

  numbers.buttons[8] = numNine;

  // Draw numNine
  tft.drawLine(numNine.anchor[0], numNine.anchor[1], numNine.anchor[0] + numNine.width, numNine.anchor[1], HX8357_BLACK);
  tft.drawLine(numNine.anchor[0], numNine.anchor[1], numNine.anchor[0], numNine.anchor[1] + numNine.height, HX8357_BLACK);
  tft.drawLine(numNine.anchor[0], numNine.anchor[1] + numNine.height, numNine.anchor[0] + numNine.width, numNine.anchor[1] + numNine.height, HX8357_BLACK);
  tft.drawLine(numNine.anchor[0] + numNine.width, numNine.anchor[1] + numNine.height, numNine.anchor[0] + numNine.width, numNine.anchor[1], HX8357_BLACK);
  tft.setCursor(numNine.anchor[0] + (numNine.width / 2) + NUMPAD_PADDING_WIDTH, numNine.anchor[1] + (numNine.height / 2) + NUMPAD_PADDING_HEIGHT);
  tft.setTextColor(HX8357_BLACK);
  tft.setTextSize(NUMPAD_TEXT_SIZE);
  tft.println("9");

  // Number Zero
  View numZero = {0};
  numZero.height = 50;
  numZero.width = width / 3;
  numZero.anchor[0] = width / 3; // top left x-value
  numZero.anchor[1] = 420;       // top left y-value

  numbers.buttons[9] = numZero;

  // Draw numZero
  tft.drawLine(numZero.anchor[0], numZero.anchor[1], numZero.anchor[0] + numZero.width, numZero.anchor[1], HX8357_BLACK);
  tft.drawLine(numZero.anchor[0], numZero.anchor[1], numZero.anchor[0], numZero.anchor[1] + numZero.height, HX8357_BLACK);
  tft.drawLine(numZero.anchor[0], numZero.anchor[1] + numZero.height, numZero.anchor[0] + numZero.width, numZero.anchor[1] + numZero.height, HX8357_BLACK);
  tft.drawLine(numZero.anchor[0] + numZero.width, numZero.anchor[1] + numZero.height, numZero.anchor[0] + numZero.width, numZero.anchor[1], HX8357_BLACK);
  tft.setCursor(numZero.anchor[0] + (numZero.width / 2) + NUMPAD_PADDING_WIDTH, numZero.anchor[1] + (numZero.height / 2) + NUMPAD_PADDING_HEIGHT);
  tft.setTextColor(HX8357_BLACK);
  tft.setTextSize(NUMPAD_TEXT_SIZE);
  tft.println("0");

  // Mode button
  View modeButton = {0};
  modeButton.height = 50;
  modeButton.width = width / 3;
  modeButton.anchor[0] = 0;   // top left x-value
  modeButton.anchor[1] = 420; // top left y-value

  numbers.buttons[10] = modeButton;

  // Draw modeButton
  tft.drawLine(modeButton.anchor[0], modeButton.anchor[1], modeButton.anchor[0] + modeButton.width, modeButton.anchor[1], HX8357_BLACK);
  tft.drawLine(modeButton.anchor[0], modeButton.anchor[1], modeButton.anchor[0], modeButton.anchor[1] + modeButton.height, HX8357_BLACK);
  tft.drawLine(modeButton.anchor[0], modeButton.anchor[1] + modeButton.height, modeButton.anchor[0] + modeButton.width, modeButton.anchor[1] + modeButton.height, HX8357_BLACK);
  tft.drawLine(modeButton.anchor[0] + modeButton.width, modeButton.anchor[1] + modeButton.height, modeButton.anchor[0] + modeButton.width, modeButton.anchor[1], HX8357_BLACK);
  tft.setCursor(modeButton.anchor[0] + (modeButton.width / 4) + NUMPAD_PADDING_WIDTH, modeButton.anchor[1] + (modeButton.height / 2) + NUMPAD_PADDING_HEIGHT);
  tft.setTextColor(HX8357_BLACK);
  tft.setTextSize(NUMPAD_TEXT_SIZE);
  tft.println("a/b/O");
  changeMode("O");

  tft.setTextSize(INPUT_BOX_TEXT_SIZE);
  tft.setCursor(25, 120);
  tft.print("0");
}

void loop()
{

  TSPoint p = ts.getPoint();
  mapTouchWithRotation(p);

  if (p.z > MIN_PRESSURE && p.z < MAX_PRESSURE)
  {
    // Number buttons
    for (int i = 0; i < numbers.buttonCount; i++)
    {
      int width = numbers.buttons[i].width;
      int height = numbers.buttons[i].height;
      int topLeftX = numbers.buttons[i].anchor[0];
      int topLeftY = numbers.buttons[i].anchor[1];
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
    int width = numbers.buttons[10].width;
    int height = numbers.buttons[10].height;
    int topLeftX = numbers.buttons[10].anchor[0];
    int topLeftY = numbers.buttons[10].anchor[1];
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
    for (int i = 0; i < numbers.buttonCount + 1; i++)
    {
      // On button release
      if (numbers.buttons[i].state == Pressed)
      {
        // Button released
        int width = numbers.buttons[i].width;
        int height = numbers.buttons[i].height;
        int topLeftX = numbers.buttons[i].anchor[0];
        int topLeftY = numbers.buttons[i].anchor[1];
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
      numbers.buttons[i].state = Unpressed;
    }
    break;
  case 1:
    if (numbers.buttons[0].state == Unpressed)
    {
      pressButton(0);
      numbers.buttons[0].state = Pressed;
    }
    break;
  case 2:
    if (numbers.buttons[1].state == Unpressed)
    {
      pressButton(1);
      numbers.buttons[1].state = Pressed;
    }
    break;
  case 3:
    if (numbers.buttons[2].state == Unpressed)
    {
      pressButton(2);
      numbers.buttons[2].state = Pressed;
    }
    break;
  case 4:
    if (numbers.buttons[3].state == Unpressed)
    {
      pressButton(3);
      numbers.buttons[3].state = Pressed;
    }
    break;
  case 5:
    if (numbers.buttons[4].state == Unpressed)
    {
      pressButton(4);
      numbers.buttons[4].state = Pressed;
    }
    break;
  case 6:
    if (numbers.buttons[5].state == Unpressed)
    {
      pressButton(5);
      numbers.buttons[5].state = Pressed;
    }
    break;
  case 7:
    if (numbers.buttons[6].state == Unpressed)
    {
      pressButton(6);
      numbers.buttons[6].state = Pressed;
    }
    break;
  case 8:
    if (numbers.buttons[7].state == Unpressed)
    {
      pressButton(7);
      numbers.buttons[7].state = Pressed;
    }
    break;
  case 9:
    if (numbers.buttons[8].state == Unpressed)
    {
      pressButton(8);
      numbers.buttons[8].state = Pressed;
    }
    break;
  case 10:
    if (numbers.buttons[9].state == Unpressed)
    {
      pressButton(9);
      numbers.buttons[9].state = Pressed;
    }
  case 11: // a/b/O button
    if (numbers.buttons[10].state == Unpressed)
    {
      // pressButton(10);
      changeMode(numbers.mode);
      numbers.buttons[10].state = Pressed;
    }
    break;
  default:
    break;
  }
}

void pressButton(int button)
{
  int width = numbers.buttons[button].width;
  int height = numbers.buttons[button].height;
  int topLeftX = numbers.buttons[button].anchor[0];
  int topLeftY = numbers.buttons[button].anchor[1];
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
  tft.print(numbers.number);

  char str[128];
  snprintf(str, 128, "Button %d Pressed", buttonName);
  Serial.println(str);
}

void changeMode(const char *mode)
{
  if (mode == "a")
  {
    numbers.mode = "b";
  }
  else if (mode == "b")
  {
    numbers.mode = "O";
  }
  else if (mode == "O")
  {
    numbers.mode = "a";
  }
  else
  {
    numbers.mode = mode;
  }

  tft.setTextSize(INPUT_BOX_TEXT_SIZE);
  clearInputMode();
  tft.setCursor(81, 120);
  tft.print(numbers.mode);
}

unsigned changeNumber(unsigned number)
{
  if (getNumberLength(numbers.number) >= 2 || numbers.number == 0)
  {
    if (number <= 3)
    {
      numbers.number = number;
      return numbers.number;
    }
    else
    {
      numbers.number = 0;
      return numbers.number;
    }
  }
  else
  {
    if (numbers.number == 3 && number != 0)
    {
      numbers.number = 0;
      return numbers.number;
    }

    numbers.number = concatenate(numbers.number, number);
    return numbers.number;
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