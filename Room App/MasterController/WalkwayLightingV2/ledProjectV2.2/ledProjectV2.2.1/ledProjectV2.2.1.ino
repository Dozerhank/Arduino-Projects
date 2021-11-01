/*
Version 2.2.1 
  3 completed and working modes will be added (Solid, Rainbow, and ColorWipe).
  Motion Sensor timer will be updated to show minutes before seconds

Ideas for Version 2.2.2
  Add multicolor mode with up to x different colors
  optimize motionsensor and timer functions for Wipe function
*/

//Library Setup
#include <BlynkSimpleShieldEsp8266.h>
#include <Adafruit_NeoPixel.h>

//Blynk Related Definitions, Variables, and Setups
char auth[] = "BwcgSJY_PNZSFHjnddyvZLX2zIoCkpoS";
char ssid[] = "Wireless 2.4Ghz";
char pass[] = "dozerhank";
#define BLYNK_PRINT Serial
#define EspSerial Serial1
ESP8266 wifi(&EspSerial);
#define ESP8266_BAUD 9600
BlynkTimer timer;

//LED Related Definitions, Variables, and Setups
#define ledCount 417
#define ledCount2 264
#define ledPin 5
#define ledPin2 6
int Duration = 120;
int Brightness = 50;
int ledTimer = 10;
Adafruit_NeoPixel strip(ledCount, ledPin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(ledCount2, ledPin2, NEO_GRB + NEO_KHZ800);
int Red = 255;
int Green = 0;
int Blue = 0;
int Red2 = 0;
int Green2 = 0;
int Blue2 = 0;
int Red3 = 0;
int Green3 = 0;
int Blue3 = 0;
int Red4 = 255;
int Green4 = 0;
int Blue4 = 0;
int Red5 = 255;
int Green5 = 0;
int Blue5 = 0;
int Red6 = 255;
int Green6 = 0;
int Blue6 = 0;
int Mode = 1;
int ledStatus = 1;
long PixelHue = 0;
int WipeCycle = 0;
int ledSelect = 0;
int TimerMinute = 0;
int TimerSecond = 0;
int MulticolorValue = 1;
int ledTotal = 0;
int MulticolorCurrent = 0;

//IR Motion Sensor Setup
#define sensorPin 7
#define indicator 13
int MotionSensor = 0; 


void setup() {
  Serial.begin(9600);
  EspSerial.begin(ESP8266_BAUD);
  Blynk.begin(auth, wifi, ssid, pass);
  timer.setInterval(1000L, timerFunction);
  strip.begin();
  strip2.begin();
  strip.fill(strip.Color(Red, Green, Blue), 0, ledCount);
  strip2.fill(strip.Color(Red, Green, Blue), 0, ledCount);
  strip.setBrightness(Brightness);
  strip2.setBrightness(Brightness);
  strip.show();
  strip2.show();
  pinMode(sensorPin, INPUT);
  pinMode(indicator, OUTPUT);
  Serial.println("Program Ready!");
}

void loop() {
  Blynk.run();
  timer.run();
  if (Mode == 2 & ledStatus == 1)  {
    Rainbow();  
  } else if (Mode == 3 & ledStatus == 1)  {
    ColorWipe();
  } else if (Mode == 4 | Mode == 5 & ledStatus == 1)  {
    Multicolor();
  }
}

void timerFunction()  {
  Blynk.run();
  if (MotionSensor == 1)  {
    MotionDetect();
  } else if (MotionSensor == 0) {
    ledTimer = Duration;
  }
  TimerMinute = ledTimer / 60;
  TimerSecond = ledTimer - (TimerMinute * 60);
  Blynk.virtualWrite(V7, TimerMinute);
  Blynk.virtualWrite(V19, TimerSecond);
}

//Adjusting the Mode
BLYNK_WRITE(V0) { 
  switch(param[0].asInt())  {
    case 1:
      Mode = 1;
      strip.fill(strip.Color(Red, Green, Blue), 0, ledCount);
      strip2.fill(strip.Color(Red, Green, Blue), 0, ledCount);
      strip.show();
      strip2.show();
      PixelHue = 0;
      WipeCycle = 0;
      ledSelect = 0;
      break;
    case 2:
      Mode = 2;
      WipeCycle = 0;
      ledSelect = 0;
      Rainbow();
      break;
    case 3:
      Mode = 3;
      ColorWipe();
      PixelHue = 0;
      break;
    case 4:
      Mode = 4;
      ledTotal = 3;
      Multicolor();
    case 5:
      Mode = 5;
      ledTotal = 6;
      Multicolor();
  }
}

//Adjusting Color Values
BLYNK_WRITE(V1) {
  if (Mode != 4 | Mode != 5)  {
    Red = param[0].asInt();  
  }
  if (Mode == 1)  {
    strip.fill(strip.Color(Red, Green, Blue), 0, ledCount);
    strip2.fill(strip.Color(Red, Green, Blue), 0, ledCount);
    strip.show();
    strip2.show();
  } else if (Mode == 4 | Mode == 5) {
    switch(MulticolorValue) {
      case 1:
        Red = param[0].asInt();
        break;
      case 2:
        Red2 = param[0].asInt();
        break;
      case 3:
        Red3 = param[0].asInt();
        break;
      case 4:
        Red4 = param[0].asInt();
        break;
      case 5:
        Red5 = param[0].asInt();
        break;
      case 6:
        Red6 = param[0].asInt();
        break;
    }
    Multicolor();
  }
}
BLYNK_WRITE(V2) {
  if (Mode != 4 | Mode != 5)  {
    Green = param[0].asInt();
  }
  if (Mode == 1)  {
    strip.fill(strip.Color(Red, Green, Blue), 0, ledCount);
    strip2.fill(strip.Color(Red, Green, Blue), 0, ledCount);
    strip.show();
    strip2.show();
  } else if (Mode == 4 | Mode == 5) {
    switch(MulticolorValue) {
      case 1:
        Green = param[0].asInt();
        break;
      case 2:
        Green2 = param[0].asInt();
        break;
      case 3:
        Green3 = param[0].asInt();
        break;
      case 4:
        Green4 = param[0].asInt();
        break;
      case 5:
        Green5 = param[0].asInt();
        break;
      case 6:
        Green6 = param[0].asInt();
        break;
    }
    Multicolor();
  }
}
BLYNK_WRITE(V3) {
  if (Mode != 4 | Mode != 5)  {
    Blue = param[0].asInt();
  }
  if (Mode == 1)  {
    strip.fill(strip.Color(Red, Green, Blue), 0, ledCount);
    strip2.fill(strip.Color(Red, Green, Blue), 0, ledCount);
    strip.show();
    strip2.show();
  } else if (Mode == 4 | Mode == 5) {
    switch(MulticolorValue) {
      case 1:
        Blue = param[0].asInt();
        break;
      case 2:
        Blue2 = param[0].asInt();
        break;
      case 3:
        Blue3 = param[0].asInt();
        break;
      case 4:
        Blue4 = param[0].asInt();
        break;
      case 5:
        Blue5 = param[0].asInt();
        break;
      case 6:
        Blue6 = param[0].asInt();
        break;
    }
    Multicolor();
  } 
}

//Adjusting Brightness Value
BLYNK_WRITE(V4) {
  Brightness = param[0].asInt();
  strip.setBrightness(Brightness);
  strip2.setBrightness(Brightness);
  strip.show();
  strip2.show();
}

//Adjusting MotionSensor Value
BLYNK_WRITE(V6) {
  MotionSensor = param[0].asInt();
  if (MotionSensor == 0 & ledStatus == 0) {
    ModeMaster();
    ledTimer = Duration;
  }
}

//Adjust current LED RGB
BLYNK_WRITE(V5) {
  MulticolorValue = param.asInt();  
}

void MotionDetect() {
  if (digitalRead(sensorPin) > 0) {
    Serial.println("Somebody is in the room!");
    if (ledStatus == 0)  {
      ledTimer = Duration;
      FillRoom();
      ledStatus = 1;
    }
    ledTimer = Duration;
  } else {
    if (Mode == 3)  {
      ledTimer -= 2;
    } else  {
      ledTimer--;
    }
    if (ledTimer == -1) {
      ledTimer = 0;
      Blynk.virtualWrite(V19, 0);
    }
    if (ledTimer == 0 & ledStatus == 1)  {
      ledClear();
    }
  }
 }

void Rainbow()  {
  for(int i = 0; i < strip.numPixels(); i++)  {
    int pixelHue = PixelHue + (i * 65536L / strip.numPixels());
    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    strip2.setPixelColor(i, strip2.gamma32(strip2.ColorHSV(pixelHue)));
  }
  PixelHue += 256;
  if (PixelHue > 1310720) {
    PixelHue = 0;
  }
  strip.show();
  strip2.show();
  Blynk.virtualWrite(V18, PixelHue);
}

void ColorWipe() {
  switch(WipeCycle) {
    case 0: 
      strip.setPixelColor(ledSelect, strip.Color(255, 0, 0));
      strip2.setPixelColor(ledSelect, strip.Color(255, 0, 0));
      break;
    case 1:
      strip.setPixelColor(ledSelect, strip.Color(128, 128, 0));
      strip2.setPixelColor(ledSelect, strip.Color(128, 128, 0));
      break;
    case 2:
      strip.setPixelColor(ledSelect, strip.Color(0, 255, 0));
      strip2.setPixelColor(ledSelect, strip.Color(0, 255, 0));
      break;
    case 3:
      strip.setPixelColor(ledSelect, strip.Color(0, 128, 128));
      strip2.setPixelColor(ledSelect, strip.Color(0, 128, 128));
      break;
    case 4:
      strip.setPixelColor(ledSelect, strip.Color(0, 0, 255));
      strip2.setPixelColor(ledSelect, strip.Color(0, 0, 255));
      break;
    case 5:
      strip.setPixelColor(ledSelect, strip.Color(128, 0, 128));
      strip2.setPixelColor(ledSelect, strip.Color(128, 0, 128));
      break;
  }
  strip.show();
  strip2.show();
  ledSelect++;
  if (ledSelect > ledCount) {
    ledSelect = 0;
    WipeCycle++;
    if (WipeCycle > 5)  {
      WipeCycle = 0;  
    }
  }
}

void Multicolor() {
  Serial.println("Multicolor Ran");
  strip.setPixelColor(MulticolorCurrent, strip.Color(Red, Green, Blue));  
  strip2.setPixelColor(MulticolorCurrent, strip.Color(Red, Green, Blue));  
  strip.setPixelColor(MulticolorCurrent + 1, strip.Color(Red2, Green2, Blue2));  
  strip2.setPixelColor(MulticolorCurrent + 1, strip.Color(Red2, Green2, Blue2));
  strip.setPixelColor(MulticolorCurrent + 2, strip.Color(Red3, Green3, Blue3));
  strip2.setPixelColor(MulticolorCurrent + 2, strip.Color(Red3, Green3, Blue3));
  if (ledTotal == 6)  {
    strip.setPixelColor(MulticolorCurrent + 3, strip.Color(Red4, Green4, Blue4));
    strip2.setPixelColor(MulticolorCurrent + 3, strip.Color(Red4, Green4, Blue4));
    strip.setPixelColor(MulticolorCurrent + 4, strip.Color(Red5, Green5, Blue5));
    strip2.setPixelColor(MulticolorCurrent + 4, strip.Color(Red5, Green5, Blue5));
    strip.setPixelColor(MulticolorCurrent + 5, strip.Color(Red6, Green6, Blue6));
    strip2.setPixelColor(MulticolorCurrent + 5, strip.Color(Red6, Green6, Blue6));
    }
  MulticolorCurrent += ledTotal;
  if (MulticolorCurrent > ledCount) {
    MulticolorCurrent = 0;
    strip.show();
    strip2.show();
  }
}

void ModeMaster() {
  switch(Mode)  {
    case 1:
      strip.fill(strip.Color(Red, Green, Blue), 0, ledCount);
      strip2.fill(strip.Color(Red, Green, Blue), 0, ledCount);
      strip.show();
      strip2.show();
      PixelHue = 0;
      WipeCycle = 0;
      ledSelect = 0;
      break;
    case 2:
      Rainbow();
      WipeCycle = 0;
      ledSelect = 0;
      break;
    case 3:
      ColorWipe();
      PixelHue = 0;
      break; 
    case 4:
      ledTotal = 3;
      Multicolor();
      PixelHue = 0;
      WipeCycle = 0;
      ledSelect = 0;
    case 5:
      ledTotal = 6;
      Multicolor(); 
      PixelHue = 0;
      WipeCycle = 0;
      ledSelect = 0;
  }
  ledStatus = 1;
}

void FillRoom() {
  Blynk.run();
  PixelHue = 0;
  for (int i = 0; i < ledCount; i++)  {
    strip.setPixelColor(i, strip.Color(Red, Green, Blue));
    strip2.setPixelColor(i, strip.Color(Red, Green, Blue));
    strip.show();
    strip2.show();
  }
  ledStatus = 1;
}

void ledClear() {
  for (int i = ledCount; i > -1; i--) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip2.setPixelColor(i, strip.Color(0, 0, 0));
    strip.show();
    strip2.show();
  }
  ledStatus = 0;
}
