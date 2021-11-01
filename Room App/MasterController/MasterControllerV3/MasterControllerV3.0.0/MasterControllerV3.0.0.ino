/*
 * MasterController Version 3.0.0
 * Reorganize code, shortening and optimizing
 * Document code better using comments
 * Automatically update app values to hardware values
 * Cut out modes that cause performance issues and save for later work
 */

//Libraries
#include <BlynkSimpleShieldEsp8266.h>
#include <Adafruit_NeoPixel.h>

//Definition of permanent values
#define BLYNK_PRINT Serial
#define EspSerial Serial1
ESP8266 wifi(&EspSerial);
#define ESP8266_BAUD 9600
#define ledCount 417
#define ledCount2 264
#define ledPin 5
#define ledPin2 6
#define sensorPin 7
#define Version 3.0

//Wifi connection values
char auth[] = "BwcgSJY_PNZSFHjnddyvZLX2zIoCkpoS";
char ssid[] = "Wireless 2.4Ghz";
char pass[] = "dozerhank";
BlynkTimer timer;

//LED Related Variables
Adafruit_NeoPixel strip(ledCount, ledPin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(ledCount2, ledPin2, NEO_GRB + NEO_KHZ800);
int Duration = 120;           //Value that determines motion sensor countdown time in seconds
int ledTimer;                 //Value that is set to Duration value and is used as the timer for the motion sensor 
int TimerMinute;              //Value that is given the minute value of ledTimer to display in app
int TimerSecond;              //Value that is given the second value of ledTimer after minutes is taken out. It is displayed in the app
int Red[3] = {0,0,0};         //Array holding the maximum of 3 different Red values
int Green[3] = {0,0,0};       //Array holding the maximum of 3 different Green values
int Blue[3] = {255,0,0};      //Array holding the maximum of 3 different Blue values
int Brightness = 50;          //Array holding the maximum of 3 different Brightness values
bool ledStatus = true;        //Boolean value that determines whether the LED strip is activated or not due to the motion sensor
bool MotionSensor;            //Boolean value that determines whether or not the motion sensor is activated
int Mode = 1;                 //Value that holds which mode the LED strip is currently on
                              //1) Solid, 2) Rainbow, 3) Multicolor
  //Mode Values
  long RainbowHue = 0;        //Holds the hue value for the rainbow mode
  int ledArray = 0;           //Decides which array value for colors to adjust
  int CurrentLED;             //Holds the value of the current led for modes
  

void setup() {
  Serial.begin(9600);
  EspSerial.begin(ESP8266_BAUD);
  Blynk.begin(auth, wifi, ssid, pass);
  timer.setInterval(1000L, timerFunction);

  strip.begin();
  strip2.begin();
  
  pinMode(sensorPin, INPUT);

  Blynk.virtualWrite(V1, Red[0]);
  Blynk.virtualWrite(V2, Green[0]);
  Blynk.virtualWrite(V3, Blue[0]);
  Blynk.virtualWrite(V4, Brightness);
  Blynk.virtualWrite(V6, LOW);
  Blynk.virtualWrite(V5, 1);
  Blynk.virtualWrite(V8, Version);
}

void loop() {
  Blynk.run();
  timer.run();
  //Every loop will run the next step in the current mode
  if (ledStatus == true)  {
    switch(Mode)  {
      case 1:
        break;
      case 2:
        Rainbow();
        break;
    }
  }
}

void timerFunction()  {
  if (MotionSensor == true) {
    MotionDetect();
  } else  {
    ledTimer = Duration;
  }
  TimerMinute = ledTimer / 60;
  TimerSecond = ledTimer - (TimerMinute * 60);
  Blynk.virtualWrite(V7, TimerMinute);
  Blynk.virtualWrite(V19, TimerSecond);
}

//Changing Mode
BLYNK_WRITE(V0) {
  Serial.println("Mode changed");
  Mode = param[0].asInt();
  Serial.println(Mode);
  RainbowHue = 0;
  ledArray = 0;
  Blynk.virtualWrite(V5, ledArray);
  if (Mode == 1)  {
    Solid();
  }
}

//Changing Colors
BLYNK_WRITE(V1) {
  Serial.println("Red updated");
  Red[ledArray] = param[0].asInt();
  if (Mode == 1)  {
    Solid();
  }
}
BLYNK_WRITE(V2) {
  Serial.println("Green updated");
  Green[ledArray] = param[0].asInt();
  if (Mode == 1)  {
    Solid();
  }
}
BLYNK_WRITE(V3) {
  Serial.println("Blue updated");
  Blue[ledArray] = param[0].asInt();
  if (Mode == 1)  {
    Solid();
  }
}

BLYNK_WRITE(V4) {
  Serial.println("Brightness updated");
  Brightness = param[0].asInt();
  strip.setBrightness(Brightness);
  strip2.setBrightness(Brightness);
  strip.show();
  strip2.show();
  if (Mode == 1)  {
    Solid();
  }
}

BLYNK_WRITE(V5) {
  Serial.println("ledArray updated");
  ledArray = param[0].asInt() - 1;
  Serial.println(ledArray);
  Blynk.virtualWrite(V1, Red[ledArray]);
  Blynk.virtualWrite(V2, Green[ledArray]);
  Blynk.virtualWrite(V3, Blue[ledArray]);
}

BLYNK_WRITE(V6) {
  Serial.println("Motionsensor updated");
  MotionSensor = param[0].asInt();
}

void MotionDetect() {
  if (digitalRead(sensorPin) > 0) {
    Serial.println("Someone is in the room!");
    if (ledStatus == false) {
      FillRoom();
    }
    ledTimer = Duration;
  } else {
    ledTimer--;
    if (ledTimer < 0) {
      ledTimer = 0;
    }
    if (ledTimer == 0 & ledStatus == true)  {
      ledClear();
    }
  }
}

void Solid()  {
  Serial.println("Solid Mode Ran");
  strip.fill(strip.Color(Red[0], Green[0], Blue[0]), 0, ledCount);
  strip2.fill(strip.Color(Red[0], Green[0], Blue[0]), 0, ledCount);
  strip.setBrightness(Brightness);
  strip2.setBrightness(Brightness);
  strip.show();
  strip2.show();
}

void Rainbow()  {
  for(int i = 0; i < strip.numPixels(); i++)  {
    int RainbowHue = RainbowHue + (i * 65536L / strip.numPixels());
    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(RainbowHue)));
    strip2.setPixelColor(i, strip2.gamma32(strip2.ColorHSV(RainbowHue)));
  }
  RainbowHue += 256;
  if (RainbowHue > 1310720) {
    RainbowHue = 0;
  }
  strip.show();
  strip2.show();
  Blynk.virtualWrite(V8, Version);
}

void FillRoom() {
  Serial.println("FillRoom Ran");
  for (int i = 0; i < ledCount; i++)  {
    strip.setPixelColor(i, strip.Color(Red, Green, Blue));
    strip2.setPixelColor(i, strip.Color(Red, Green, Blue));
    strip.show();
    strip2.show();
  }
  ledStatus = true;
}

void ledClear() {
  Serial.println("ledClear Ran");
  for (int i = ledCount; i > -1; i--) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip2.setPixelColor(i, strip.Color(0, 0, 0));
    strip.show();
    strip2.show();
  }
  ledStatus = false;
}
