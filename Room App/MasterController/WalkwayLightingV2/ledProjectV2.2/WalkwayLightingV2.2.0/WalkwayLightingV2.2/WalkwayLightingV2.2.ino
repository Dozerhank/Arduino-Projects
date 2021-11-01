/*
Version 2.2.1 
  3 completed and working modes will be added (Solid, Rainbow, and Fade).
  Motion Sensor timer will be updated to show minutes before seconds
  Motion sensor mode will begin relying on server for a detection to become compatible with wireless motion sensors.
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
int Duration = 10;
int Brightness = 50;
int ledTimer = 10;
Adafruit_NeoPixel strip(ledCount, ledPin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(ledCount2, ledPin2, NEO_GRB + NEO_KHZ800);
int Red = 255;
int Green = 0;
int Blue = 0;
int Mode = 1;
int ledStatus = 1;
long PixelHue = 0;
int WipeCycle = 0;

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
  }
}

void timerFunction()  {
  Blynk.run();
  if (MotionSensor == 1)  {
    MotionDetect();
  }
  Blynk.virtualWrite(V7, ledTimer);
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
      break;
    case 2:
      Mode = 2;
      Rainbow();
      break;
    case 3:
      Mode = 3;
      ColorWipe();
      PixelHue = 0;
      break;
  }
  Serial.println("Mode Checked");
}

//Adjusting Color Values
BLYNK_WRITE(V1) {
  Red = param[0].asInt();
  if (Mode == 1)  {
    strip.fill(strip.Color(Red, Green, Blue), 0, ledCount);
    strip2.fill(strip.Color(Red, Green, Blue), 0, ledCount);
    strip.show();
    strip2.show();
  }
}
BLYNK_WRITE(V2) {
  Green = param[0].asInt();
  if (Mode == 1)  {
    strip.fill(strip.Color(Red, Green, Blue), 0, ledCount);
    strip2.fill(strip.Color(Red, Green, Blue), 0, ledCount);
    strip.show();
    strip2.show();
  }
}
BLYNK_WRITE(V3) {
  Blue = param[0].asInt();
  if (Mode == 1)  {
    strip.fill(strip.Color(Red, Green, Blue), 0, ledCount);
    strip2.fill(strip.Color(Red, Green, Blue), 0, ledCount);
    strip.show();
    strip2.show();
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
    ledTimer--;
    Serial.println(ledTimer);
    if (ledTimer == -1) {
      ledTimer = 0;
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
      for (int i = 0; i < ledCount; i++)  {
        strip.setPixelColor(i, strip.Color(255, 0, 0));
        strip2.setPixelColor(i, strip.Color(255, 0, 0));
        strip.show();
        strip2.show();
      }
    case 1:
      for (int i = 0; i < ledCount; i++)  {
        strip.setPixelColor(i, strip.Color(128, 128, 0));
        strip2.setPixelColor(i, strip.Color(128, 128, 0));
        strip.show();
        strip2.show();
      }
    case 2:
      for (int i = 0; i < ledCount; i++)  {
        strip.setPixelColor(i, strip.Color(0, 255, 0));
        strip2.setPixelColor(i, strip.Color(0, 255, 0));
        strip.show();
        strip2.show();
      }
    case 3:
      for (int i = 0; i < ledCount; i++)  {
        strip.setPixelColor(i, strip.Color(0, 128, 128));
        strip2.setPixelColor(i, strip.Color(0, 128, 128));
        strip.show();
        strip2.show();
      }
    case 4:
      for (int i = 0; i < ledCount; i++)  {
        strip.setPixelColor(i, strip.Color(0, 0, 255));
        strip2.setPixelColor(i, strip.Color(0, 0, 255));
        strip.show();
        strip2.show();
      }
    case 5:
      for (int i = 0; i < ledCount; i++)  {
        strip.setPixelColor(i, strip.Color(128, 0, 128));
        strip2.setPixelColor(i, strip.Color(128, 0, 128));
        strip.show();
        strip2.show();
      }
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
      break;
    case 2:
      Rainbow();
      break;
    case 3:
      ColorWipe();
      PixelHue = 0;
      break;  
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
