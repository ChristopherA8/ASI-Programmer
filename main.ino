#include "main.h"

// Initialize touchscreen and display objects
Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// Runs once on reset
void setup()
{
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  delay(1000);
  digitalWrite(3, LOW);

  // Serial.begin(9600);
  // Serial.setTimeout(50);

  tft.begin();
  tft.setRotation(2);

  tft.fillScreen(HX8357_WHITE);

  int16_t height = tft.height();
  int16_t width = tft.width();

  numbers.buttonCount = 10; // it will be 12 when I add "a" and "b"

  // Input box
  View inputBox = {0};
  inputBox.height = 100;
  inputBox.width = width;
  inputBox.anchor[0] = 0;  // top left x-value
  inputBox.anchor[1] = 50; // top left y-value

  // Draw inputBox
  tft.drawLine(inputBox.anchor[0], inputBox.anchor[1], inputBox.anchor[0] + inputBox.width, inputBox.anchor[1], HX8357_BLACK);
  tft.drawLine(inputBox.anchor[0], inputBox.anchor[1], inputBox.anchor[0], inputBox.anchor[1] + inputBox.height, HX8357_BLACK);
  tft.drawLine(inputBox.anchor[0], inputBox.anchor[1] + inputBox.height, inputBox.anchor[0] + inputBox.width, inputBox.anchor[1] + inputBox.height, HX8357_BLACK);
  tft.drawLine(inputBox.anchor[0] + inputBox.width, inputBox.anchor[1] + inputBox.height, inputBox.anchor[0] + inputBox.width, inputBox.anchor[1], HX8357_BLACK);

  // Number One
  View numOne = {0};
  numOne.height = 50;
  numOne.width = width / 3;
  numOne.anchor[0] = 0;   // top left x-value
  numOne.anchor[1] = 200; // top left y-value

  // Add it to the numpad
  numbers.buttons[0] = numOne;

  // Draw numOne
  tft.drawLine(numOne.anchor[0], numOne.anchor[1], numOne.anchor[0] + numOne.width, numOne.anchor[1], HX8357_BLACK);
  tft.drawLine(numOne.anchor[0], numOne.anchor[1], numOne.anchor[0], numOne.anchor[1] + numOne.height, HX8357_BLACK);
  tft.drawLine(numOne.anchor[0], numOne.anchor[1] + numOne.height, numOne.anchor[0] + numOne.width, numOne.anchor[1] + numOne.height, HX8357_BLACK);
  tft.drawLine(numOne.anchor[0] + numOne.width, numOne.anchor[1] + numOne.height, numOne.anchor[0] + numOne.width, numOne.anchor[1], HX8357_BLACK);
  tft.setCursor(numOne.anchor[0] + (numOne.width / 2), numOne.anchor[1] + (numOne.height / 2));
  tft.setTextColor(HX8357_BLACK);
  tft.setTextSize(3);
  tft.println("1");

  // Number Two
  View numTwo = {0};
  numTwo.height = 50;
  numTwo.width = width / 3;
  numTwo.anchor[0] = width / 3; // top left x-value
  numTwo.anchor[1] = 200;       // top left y-value

  numbers.buttons[1] = numTwo;

  // Draw numTwo
  tft.drawLine(numTwo.anchor[0], numTwo.anchor[1], numTwo.anchor[0] + numTwo.width, numTwo.anchor[1], HX8357_BLACK);
  tft.drawLine(numTwo.anchor[0], numTwo.anchor[1], numTwo.anchor[0], numTwo.anchor[1] + numTwo.height, HX8357_BLACK);
  tft.drawLine(numTwo.anchor[0], numTwo.anchor[1] + numTwo.height, numTwo.anchor[0] + numTwo.width, numTwo.anchor[1] + numTwo.height, HX8357_BLACK);
  tft.drawLine(numTwo.anchor[0] + numTwo.width, numTwo.anchor[1] + numTwo.height, numTwo.anchor[0] + numTwo.width, numTwo.anchor[1], HX8357_BLACK);
  tft.setCursor(numTwo.anchor[0] + (numTwo.width / 2), numTwo.anchor[1] + (numTwo.height / 2));
  tft.setTextColor(HX8357_BLACK);
  tft.setTextSize(3);
  tft.println("2");

  // Number Three
  View numThree = {0};
  numThree.height = 50;
  numThree.width = width / 3;
  numThree.anchor[0] = (width / 3) * 2; // top left x-value
  numThree.anchor[1] = 200;             // top left y-value

  numbers.buttons[2] = numThree;

  // Draw numThree
  tft.drawLine(numThree.anchor[0], numThree.anchor[1], numThree.anchor[0] + numThree.width, numThree.anchor[1], HX8357_BLACK);
  tft.drawLine(numThree.anchor[0], numThree.anchor[1], numThree.anchor[0], numThree.anchor[1] + numThree.height, HX8357_BLACK);
  tft.drawLine(numThree.anchor[0], numThree.anchor[1] + numThree.height, numThree.anchor[0] + numThree.width, numThree.anchor[1] + numThree.height, HX8357_BLACK);
  tft.drawLine(numThree.anchor[0] + numThree.width, numThree.anchor[1] + numThree.height, numThree.anchor[0] + numThree.width, numThree.anchor[1], HX8357_BLACK);
  tft.setCursor(numThree.anchor[0] + (numThree.width / 2), numThree.anchor[1] + (numThree.height / 2));
  tft.setTextColor(HX8357_BLACK);
  tft.setTextSize(3);
  tft.println("3");

  // Number Four
  View numFour = {0};
  numFour.height = 50;
  numFour.width = width / 3;
  numFour.anchor[0] = 0;   // top left x-value
  numFour.anchor[1] = 280; // top left y-value

  numbers.buttons[3] = numFour;

  // Draw numFour
  tft.drawLine(numFour.anchor[0], numFour.anchor[1], numFour.anchor[0] + numFour.width, numFour.anchor[1], HX8357_BLACK);
  tft.drawLine(numFour.anchor[0], numFour.anchor[1], numFour.anchor[0], numFour.anchor[1] + numFour.height, HX8357_BLACK);
  tft.drawLine(numFour.anchor[0], numFour.anchor[1] + numFour.height, numFour.anchor[0] + numFour.width, numFour.anchor[1] + numFour.height, HX8357_BLACK);
  tft.drawLine(numFour.anchor[0] + numFour.width, numFour.anchor[1] + numFour.height, numFour.anchor[0] + numFour.width, numFour.anchor[1], HX8357_BLACK);
  tft.setCursor(numFour.anchor[0] + (numFour.width / 2), numFour.anchor[1] + (numFour.height / 2));
  tft.setTextColor(HX8357_BLACK);
  tft.setTextSize(3);
  tft.println("4");

  // Number Five
  View numFive = {0};
  numFive.height = 50;
  numFive.width = width / 3;
  numFive.anchor[0] = width / 3; // top left x-value
  numFive.anchor[1] = 280;       // top left y-value

  numbers.buttons[4] = numFive;

  // Draw numFive
  tft.drawLine(numFive.anchor[0], numFive.anchor[1], numFive.anchor[0] + numFive.width, numFive.anchor[1], HX8357_BLACK);
  tft.drawLine(numFive.anchor[0], numFive.anchor[1], numFive.anchor[0], numFive.anchor[1] + numFive.height, HX8357_BLACK);
  tft.drawLine(numFive.anchor[0], numFive.anchor[1] + numFive.height, numFive.anchor[0] + numFive.width, numFive.anchor[1] + numFive.height, HX8357_BLACK);
  tft.drawLine(numFive.anchor[0] + numFive.width, numFive.anchor[1] + numFive.height, numFive.anchor[0] + numFive.width, numFive.anchor[1], HX8357_BLACK);
  tft.setCursor(numFive.anchor[0] + (numFive.width / 2), numFive.anchor[1] + (numFive.height / 2));
  tft.setTextColor(HX8357_BLACK);
  tft.setTextSize(3);
  tft.println("5");

  // Number Six
  View numSix = {0};
  numSix.height = 50;
  numSix.width = width / 3;
  numSix.anchor[0] = (width / 3) * 2; // top left x-value
  numSix.anchor[1] = 280;             // top left y-value

  numbers.buttons[5] = numSix;

  // Draw numSix
  tft.drawLine(numSix.anchor[0], numSix.anchor[1], numSix.anchor[0] + numSix.width, numSix.anchor[1], HX8357_BLACK);
  tft.drawLine(numSix.anchor[0], numSix.anchor[1], numSix.anchor[0], numSix.anchor[1] + numSix.height, HX8357_BLACK);
  tft.drawLine(numSix.anchor[0], numSix.anchor[1] + numSix.height, numSix.anchor[0] + numSix.width, numSix.anchor[1] + numSix.height, HX8357_BLACK);
  tft.drawLine(numSix.anchor[0] + numSix.width, numSix.anchor[1] + numSix.height, numSix.anchor[0] + numSix.width, numSix.anchor[1], HX8357_BLACK);
  tft.setCursor(numSix.anchor[0] + (numSix.width / 2), numSix.anchor[1] + (numSix.height / 2));
  tft.setTextColor(HX8357_BLACK);
  tft.setTextSize(3);
  tft.println("6");

  // Number Seven
  View numSeven = {0};
  numSeven.height = 50;
  numSeven.width = width / 3;
  numSeven.anchor[0] = 0;   // top left x-value
  numSeven.anchor[1] = 360; // top left y-value

  numbers.buttons[6] = numSeven;

  // Draw numSeven
  tft.drawLine(numSeven.anchor[0], numSeven.anchor[1], numSeven.anchor[0] + numSeven.width, numSeven.anchor[1], HX8357_BLACK);
  tft.drawLine(numSeven.anchor[0], numSeven.anchor[1], numSeven.anchor[0], numSeven.anchor[1] + numSeven.height, HX8357_BLACK);
  tft.drawLine(numSeven.anchor[0], numSeven.anchor[1] + numSeven.height, numSeven.anchor[0] + numSeven.width, numSeven.anchor[1] + numSeven.height, HX8357_BLACK);
  tft.drawLine(numSeven.anchor[0] + numSeven.width, numSeven.anchor[1] + numSeven.height, numSeven.anchor[0] + numSeven.width, numSeven.anchor[1], HX8357_BLACK);
  tft.setCursor(numSeven.anchor[0] + (numSeven.width / 2), numSeven.anchor[1] + (numSeven.height / 2));
  tft.setTextColor(HX8357_BLACK);
  tft.setTextSize(3);
  tft.println("7");

  // Number Eight
  View numEight = {0};
  numEight.height = 50;
  numEight.width = width / 3;
  numEight.anchor[0] = width / 3; // top left x-value
  numEight.anchor[1] = 360;       // top left y-value

  numbers.buttons[7] = numEight;

  // Draw numEight
  tft.drawLine(numEight.anchor[0], numEight.anchor[1], numEight.anchor[0] + numEight.width, numEight.anchor[1], HX8357_BLACK);
  tft.drawLine(numEight.anchor[0], numEight.anchor[1], numEight.anchor[0], numEight.anchor[1] + numEight.height, HX8357_BLACK);
  tft.drawLine(numEight.anchor[0], numEight.anchor[1] + numEight.height, numEight.anchor[0] + numEight.width, numEight.anchor[1] + numEight.height, HX8357_BLACK);
  tft.drawLine(numEight.anchor[0] + numEight.width, numEight.anchor[1] + numEight.height, numEight.anchor[0] + numEight.width, numEight.anchor[1], HX8357_BLACK);
  tft.setCursor(numEight.anchor[0] + (numEight.width / 2), numEight.anchor[1] + (numEight.height / 2));
  tft.setTextColor(HX8357_BLACK);
  tft.setTextSize(3);
  tft.println("8");

  // Number Nine
  View numNine = {0};
  numNine.height = 50;
  numNine.width = width / 3;
  numNine.anchor[0] = (width / 3) * 2; // top left x-value
  numNine.anchor[1] = 360;             // top left y-value

  numbers.buttons[8] = numNine;

  // Draw numNine
  tft.drawLine(numNine.anchor[0], numNine.anchor[1], numNine.anchor[0] + numNine.width, numNine.anchor[1], HX8357_BLACK);
  tft.drawLine(numNine.anchor[0], numNine.anchor[1], numNine.anchor[0], numNine.anchor[1] + numNine.height, HX8357_BLACK);
  tft.drawLine(numNine.anchor[0], numNine.anchor[1] + numNine.height, numNine.anchor[0] + numNine.width, numNine.anchor[1] + numNine.height, HX8357_BLACK);
  tft.drawLine(numNine.anchor[0] + numNine.width, numNine.anchor[1] + numNine.height, numNine.anchor[0] + numNine.width, numNine.anchor[1], HX8357_BLACK);
  tft.setCursor(numNine.anchor[0] + (numNine.width / 2), numNine.anchor[1] + (numNine.height / 2));
  tft.setTextColor(HX8357_BLACK);
  tft.setTextSize(3);
  tft.println("9");

  // Number Zero
  View numZero = {0};
  numZero.height = 50;
  numZero.width = width / 3;
  numZero.anchor[0] = width / 3; // top left x-value
  numZero.anchor[1] = 440;       // top left y-value

  numbers.buttons[9] = numZero;

  // Draw numZero
  tft.drawLine(numZero.anchor[0], numZero.anchor[1], numZero.anchor[0] + numZero.width, numZero.anchor[1], HX8357_BLACK);
  tft.drawLine(numZero.anchor[0], numZero.anchor[1], numZero.anchor[0], numZero.anchor[1] + numZero.height, HX8357_BLACK);
  tft.drawLine(numZero.anchor[0], numZero.anchor[1] + numZero.height, numZero.anchor[0] + numZero.width, numZero.anchor[1] + numZero.height, HX8357_BLACK);
  tft.drawLine(numZero.anchor[0] + numZero.width, numZero.anchor[1] + numZero.height, numZero.anchor[0] + numZero.width, numZero.anchor[1], HX8357_BLACK);
  tft.setCursor(numZero.anchor[0] + (numZero.width / 2), numZero.anchor[1] + (numZero.height / 2));
  tft.setTextColor(HX8357_BLACK);
  tft.setTextSize(3);
  tft.println("0");
}

void loop()
{

  TSPoint p = ts.getPoint();
  switch (tft.getRotation())
  {
  case 0:
    xpos = map(p.x, TS_LEFT, TS_RT, 0, tft.width());
    ypos = map(p.y, TS_TOP, TS_BOT, 0, tft.height());
    break;
  case 1:
    xpos = map(p.y, TS_TOP, TS_BOT, 0, tft.width());
    ypos = map(p.x, TS_RT, TS_LEFT, 0, tft.height());
    break;
  case 2:
    xpos = map(p.x, TS_RT, TS_LEFT, 0, tft.width());
    ypos = map(p.y, TS_BOT, TS_TOP, 0, tft.height());
    break;
  case 3:
    xpos = map(p.y, TS_BOT, TS_TOP, 0, tft.width());
    ypos = map(p.x, TS_LEFT, TS_RT, 0, tft.height());
    break;
  }

  checkButtonState(state);

  // Reset button state
  state = 0;

  if (p.z > ts.pressureThreshhold)
  {
    // Serial.println(p.z);

    // tft.drawPixel(xpos, ypos, HX8357_BLACK);

    for (int i = 0; i < numbers.buttonCount; i++)
    {
      int width = numbers.buttons[i].width;
      int height = numbers.buttons[i].height;
      int leftSide = numbers.buttons[i].anchor[0];
      int topSide = numbers.buttons[i].anchor[1];
      int rightSide = leftSide + width;
      int bottomSide = topSide + height;

      // If touch is within button bounds
      if (xpos >= leftSide && xpos <= rightSide && ypos >= topSide && ypos <= bottomSide)
      {
        state = i + 1;
      }
    }
  }
}

void checkButtonState(int state)
{
  switch (state)
  {
  case 0:
    digitalWrite(3, LOW);
    for (int i = 0; i < numbers.buttonCount; i++)
    {
      // On button release
      if (numbers.buttons[i].state == Pressed)
      {
        // Button released
        digitalWrite(3, HIGH);
        delay(300);
        digitalWrite(3, LOW);
      }

      // Reset button states
      numbers.buttons[i].state = Unpressed;
    }
    break;
  case 1:
    if (numbers.buttons[0].state == Unpressed)
    {
      digitalWrite(3, HIGH);
      numbers.buttons[0].state = Pressed;
      int width = numbers.buttons[0].width;
      int height = numbers.buttons[0].height;
      int leftSide = numbers.buttons[0].anchor[0];
      int topSide = numbers.buttons[0].anchor[1];
      tft.drawRect(leftSide + 1, topSide - 1, width - 1, height - 1, HX8357_BLACK);
    }
    break;
  case 2:
    if (numbers.buttons[1].state == Unpressed)
    {

      numbers.buttons[1].state = Pressed;
    }
    break;
  case 3:
    if (numbers.buttons[2].state == Unpressed)
    {

      numbers.buttons[2].state = Pressed;
    }
    break;
  case 4:
    if (numbers.buttons[3].state == Unpressed)
    {

      numbers.buttons[3].state = Pressed;
    }
    break;
  case 5:
    if (numbers.buttons[4].state == Unpressed)
    {

      numbers.buttons[4].state = Pressed;
    }
    break;
  case 6:
    if (numbers.buttons[5].state == Unpressed)
    {

      numbers.buttons[5].state = Pressed;
    }
    break;
  case 7:
    if (numbers.buttons[6].state == Unpressed)
    {

      numbers.buttons[6].state = Pressed;
    }
    break;
  case 8:
    if (numbers.buttons[7].state == Unpressed)
    {

      numbers.buttons[7].state = Pressed;
    }
    break;
  case 9:
    if (numbers.buttons[8].state == Unpressed)
    {

      numbers.buttons[8].state = Pressed;
    }
    break;
  case 10:
    if (numbers.buttons[9].state == Unpressed)
    {

      numbers.buttons[9].state = Pressed;
    }
    break;
  default:
    break;
  }
}