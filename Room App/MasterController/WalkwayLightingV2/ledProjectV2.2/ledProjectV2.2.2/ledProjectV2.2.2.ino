/*
Version 2.2.1 
  3 completed and working modes will be added (Solid, Rainbow, and ColorWipe).
  Motion Sensor timer will be updated to show minutes before seconds

Ideas for Version 2.2.2
  Add multicolor mode with up to x different colors
  optimize motionsensor and timer functions for Wipe function
*/
#define Version 2.2

//Library Setup
#include <BlynkSimpleShieldEsp8266.h>
#include <Adafruit_NeoPixel.h>

//Blynk Related Definitions, Variables, and Setups
char auth[] = "BwcgSJY_PNZSFHjnddyvZLX2zIoCkpoS";
char ssid[] = "suddenlink.net-5ACB";
char pass[] = "8C42W4443100314";
#define BLYNK_PRINT Serial
#define EspSerial Serial1
ESP8266 wifi(&EspSerial);
#define ESP8266_BAUD 9600
BlynkTimer timer;

//LED Related Definitions, Variables, and Setups
#define ledCount 725
#define ledPin 5
int Duration = 120;
int Brightness = 50;
int ledTimer = 10;
Adafruit_NeoPixel strip(ledCount, ledPin, NEO_GRB + NEO_KHZ800);
int Red = 255;
int Green = 0;
int Blue = 0;
int Mode = 1;
int ledStatus = 1;
long PixelHue = 0;
int TimerMinute = 0;
int TimerSecond = 0;
int ledTotal = 0;

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
  strip.fill(strip.Color(Red, Green, Blue), 0, ledCount);
  strip.setBrightness(Brightness);
  strip.show();
  
  pinMode(sensorPin, INPUT);
  Serial.println("Program Ready!");

  Blynk.virtualWrite(V1, Red);
  Blynk.virtualWrite(V2, Green);
  Blynk.virtualWrite(V3, Blue);
  Blynk.virtualWrite(V4, Brightness);
  Blynk.virtualWrite(V6, LOW);
  Blynk.virtualWrite(V8, Version);
}

void loop() {
  Blynk.run();
  timer.run();
  if (Mode == 2 & ledStatus == 1)  {
    Rainbow();  
  }
}

void timerFunction()  {
  Blynk.run();
  if (MotionSensor == 1)  {
    MotionDetect();
    TimerMinute = ledTimer / 60;
    TimerSecond = ledTimer - (TimerMinute * 60);
    Blynk.virtualWrite(V7, TimerMinute);
    Blynk.virtualWrite(V19, TimerSecond);
  } else if (MotionSensor == 0) {
    ledTimer = Duration;
    TimerMinute = ledTimer / 60;
    TimerSecond = ledTimer - (TimerMinute * 60);
    Blynk.virtualWrite(V7, TimerMinute);
    Blynk.virtualWrite(V19, TimerSecond);
  }
}

//Adjusting the Mode
BLYNK_WRITE(V0) { 
  switch(param[0].asInt())  {
    case 1:
      Mode = 1;
      strip.fill(strip.Color(Red, Green, Blue), 0, ledCount);
      strip.show();
      PixelHue = 0;
      break;
    case 2:
      Mode = 2;
      Rainbow();
      break;
  }
}

//Adjusting Color Values
BLYNK_WRITE(V1) {
  if (Mode != 4 | Mode != 5)  {
    Red = param[0].asInt();  
  }
  if (Mode == 1)  {
    strip.fill(strip.Color(Red, Green, Blue), 0, ledCount);
    strip.show();
  }
}
BLYNK_WRITE(V2) {
  if (Mode != 4 | Mode != 5)  {
    Green = param[0].asInt();
  }
  if (Mode == 1)  {
    strip.fill(strip.Color(Red, Green, Blue), 0, ledCount);
    strip.show();
  } 
}
BLYNK_WRITE(V3) {
  if (Mode != 4 | Mode != 5)  {
    Blue = param[0].asInt();
  }
  if (Mode == 1)  {
    strip.fill(strip.Color(Red, Green, Blue), 0, ledCount);
    strip.show();
  } 
}

//Adjusting Brightness Value
BLYNK_WRITE(V4) {
  Brightness = param[0].asInt();
  strip.setBrightness(Brightness);
  strip.show();
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
  }
  PixelHue += 256;
  if (PixelHue > 1310720) {
    PixelHue = 0;
  }
  strip.show();
  Blynk.virtualWrite(V18, PixelHue);
}

void ModeMaster() {
  switch(Mode)  {
    case 1:
      strip.fill(strip.Color(Red, Green, Blue), 0, ledCount);
      strip.show();
      PixelHue = 0;
      break;
    case 2:
      Rainbow();
      break;
  }
  ledStatus = 1;
}

void FillRoom() {
  Blynk.run();
  PixelHue = 0;
  for (int i = 0; i < ledCount; i++)  {
    strip.setPixelColor(i, strip.Color(Red, Green, Blue));
    strip.show();
  }
  ledStatus = 1;
}

void ledClear() {
  for (int i = ledCount; i > -1; i--) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.show();
  }
  ledStatus = 0;
}
