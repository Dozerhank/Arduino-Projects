#include <Adafruit_NeoPixel.h>
#include "millisDelay.h"

//Setup and creation of NeoPixel object
#define ledCount 750
#define ledPin 12
int ledBrightness = 100;
Adafruit_NeoPixel strip(ledCount, ledPin, NEO_GRB + NEO_KHZ800);

//Mode values 
#define totalMode 7             //Total number of LED modes available
int ledMode = 1;                //Current Mode for LED, 1-totalMode
long int rainbowHue = 0;        //Keeps track of the PixelHue for Rainbow Mode

//Setting up physical buttons, dials, and sensors
#define brightnessPin 0         //Analog 0, pot
#define manualBrightnessPin 1   //Analog 1, dial
#define modePin 2               //Analog 2, dial

#define buttonPin 3             //Digital 2, Button
#define indicatorPin 2          //Digital 3, LED

//Delay and timing values
int resetCheck = 0;
millisDelay brightnessDelay;

//Segment Display setup
#define A 7
#define B 6
#define C 5
#define D 10
#define E 11
#define F 8
#define G 9
#define DP 4

//Extra
bool brightnessAutoAdjust = true;

void setup() {
  //Initiate strip
  strip.begin();
  strip.fill(strip.Color(0, 0, 255), 0, ledCount);
  strip.setBrightness(ledBrightness);
  strip.show();

  //Initiate physical buttons
  pinMode(modePin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(indicatorPin, OUTPUT);
}

void loop() {
  ledBrightnessUpdate();
  checkInput();
  
  if (ledMode >= 8) {
    updateMode();
  }
}

void ledBrightnessUpdate()  {
  //Before adjusting brightness, check to see if timer has ended
  if (brightnessDelay.justFinished()) {
    brightnessAutoAdjust = true;
  }

  //If statements that adjust brightness with either manual control or light sensing control
  if (brightnessAutoAdjust == true) {
    ledBrightness = analogRead(brightnessPin) / 2 - 180;
  } else if (brightnessAutoAdjust == false) {
    if ((ledBrightness - analogRead(manualBrightnessPin)) > 10 or (analogRead(manualBrightnessPin) - ledBrightness) > 10) {
      brightnessDelay.restart();
    }
    ledBrightness = analogRead(manualBrightnessPin);
  }

  //Fine tuning ledBrightness value before final update of brightness
  if (ledBrightness > 255)  {
      ledBrightness = 255;
    } else if (ledBrightness < 10)  {
      ledBrightness = 10;
    }

  //Update brightness of strip
  strip.setBrightness(ledBrightness);
  strip.show();
}

void checkInput()  {
  //Check for reset Button 
  while(digitalRead(buttonPin) == true)  {
    resetCheck++;
    delay(1000);
    if (resetCheck == 5)  {
      brightnessAutoAdjust = true;
      resetCheck = 0;
      break;
    }
  }

  //Check for mode change
  if (ledMode != ((analogRead(modePin) / 100) - (analogRead(modePin) % 100))) {
    while (buttonPin != true) {
      digitalWrite(indicatorPin, HIGH);
      ledMode = ((analogRead(modePin) / 100) - (analogRead(modePin) % 100));
      updateSegmentDisplay();
      digitalWrite(indicatorPin, LOW);
    }
    updateMode();
  }
  
}

void updateSegmentDisplay()  {
  switch(ledMode) {
    case 1:
      display1();
      break;
    case 2:
      display2();
      break;
    case 3:
      display3();
      break;
    case 4:
      display4();
      break;
    case 5:
      display5();
      break;
    case 6:
      display6();
      break;
    case 7:
      display7();
      break;
    case 8:
      display8();
      break;
    case 9:
      display9();
      break;
  }
}

void updateMode() {
  int delayTime = 20;
  switch(ledMode) {
    case 1:
      for (int i = 0; i < ledCount; i++) {
        strip.setPixelColor(i, strip.Color(255, 0, 255));
        strip.show();
        delay(delayTime);
      }
      break;
    case 2:
      for (int i = 0; i < ledCount; i++) {
        strip.setPixelColor(i, strip.Color(255, 0, 0));
        strip.show();
        delay(delayTime);
      }
      break;
    case 3:
      for (int i = 0; i < ledCount; i++) {
        strip.setPixelColor(i, strip.Color(255, 255, 0));
        strip.show();
        delay(delayTime);
      }
      break;
    case 4:
      for (int i = 0; i < ledCount; i++) {
        strip.setPixelColor(i, strip.Color(0, 255, 0));
        strip.show();
        delay(delayTime);
      }
      break;
    case 5:
      for (int i = 0; i < ledCount; i++) {
        strip.setPixelColor(i, strip.Color(0, 255, 255));
        strip.show();
        delay(delayTime);
      }
      break;
    case 6:
      for (int i = 0; i < ledCount; i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 255));
        strip.show();
        delay(delayTime);
      }
      break;
    case 7:
      for (int i = 0; i < ledCount; i++) {
        strip.setPixelColor(i, strip.Color(255, 255, 255));
        strip.show();
        delay(delayTime);
      }
      break;
    //Rainbow Mode
    case 8:
      if (rainbowHue == 0) {
        delay(150);
      }
      for(int i=0; i<strip.numPixels(); i++) { 
        int pixelHue = rainbowHue + (i * 65536L / strip.numPixels());
        strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
        rainbowHue += 32;
        if (rainbowHue > 5 * 65536)  {
        rainbowHue = 0;
        }
      }
      strip.show();
      delay(75);
      break;
      }  
}

//Segment Display 1
void display1() {
  unsigned char i;
  digitalWrite(C, HIGH);
  digitalWrite(B, HIGH);
  for (i = 7; i <= 11; i++)  {
    digitalWrite(i, LOW);
  }
  digitalWrite(DP, LOW);
}

//Segment Display 2
void display2() {
  unsigned char i;
  digitalWrite(B, HIGH);
  digitalWrite(A, HIGH);
  for (i = 9; i <= 11; i++)  {
    digitalWrite(i, HIGH);
  }
  digitalWrite(DP, LOW);
  digitalWrite(C, LOW);
  digitalWrite(F, LOW);
}

//Segment Display 3
void display3() {
  digitalWrite(G, HIGH);
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(DP, LOW);
  digitalWrite(F, LOW);
  digitalWrite(E, LOW);
}

//Segment Display 4
void display4() {
  digitalWrite(C, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(DP, LOW);
  digitalWrite(A, LOW);
  digitalWrite(E, LOW);
  digitalWrite(D, LOW);
}

//Segment Display 5
void display5() {
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(DP, LOW);
}

//Segment Display 6
void display6() {
  unsigned char i;
  for (i = 7; i <= 11; i++)  {
    digitalWrite(i, HIGH);
  }
  digitalWrite(C, HIGH);
  digitalWrite(DP, LOW);
  digitalWrite(B, LOW);
}

//Segment Display 7
void display7() {
  unsigned char i;
  for (i = 5; i <= 7; i++) {
    digitalWrite(i, HIGH);
  }
  digitalWrite(DP, LOW);
  for(i = 8; i <= 11; i++)  {
    digitalWrite(i, LOW);
  }
}

//Segment Display 8
void display8() {
  unsigned char i;
  for (i = 5; i <= 11; i++) {
    digitalWrite(i, HIGH);
  }
  digitalWrite(DP, LOW);
}

//Segment Display 9
void display9() {
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(DP, LOW);
}
