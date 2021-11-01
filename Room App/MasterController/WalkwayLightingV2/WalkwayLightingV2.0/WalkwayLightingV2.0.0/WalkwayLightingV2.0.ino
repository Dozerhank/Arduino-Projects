#define BLYNK_PRINT Serial
#include <SoftwareSerial.h>
#include <SPI.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <Adafruit_NeoPixel.h>

//Initial Blynk Setup
SoftwareSerial EspSerial(2, 3); // RX, TX
char auth[] = "BwcgSJY_PNZSFHjnddyvZLX2zIoCkpoS";
char ssid[] = "Wireless 2.4Ghz";
char pass[] = "dozerhank";
ESP8266 wifi(&EspSerial);
#define ESP8266_BAUD 9600

//IR Motion Sensors
int sensorPin = 7;
int indicator = 13;

//Color Values
int Red = 0;
int Green = 0;
int Blue = 255;

//Mode Values
int Mode = -1; //0 is solid already ran, 1 is solid, 2 is rainbow, 3 is Fade
int ModeMotionSensor = 0;

//Other LED Values
int Brightness = 150;
int ModeSpeed = 500;
int ledCount = 417;
int Duration = 1000; // every 100 = 1 sec
int ledTimer = 0;
int ledPin = 5;

//Define Strip object
Adafruit_NeoPixel strip(ledCount, ledPin, NEO_GRB + NEO_KHZ800);



void setup()  {
  Serial.begin(9600);
  EspSerial.begin(ESP8266_BAUD);
  Blynk.begin(auth, wifi, ssid, pass);
  
  strip.begin();
  strip.show();
  strip.setBrightness(Brightness);

  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(indicator, OUTPUT);
  
  FillRoom();
}

void loop() {
  Blynk.run();
  //Decide which mode to run on LED lights
  if (Mode == 1)  {
    Solid();
  } else if (Mode == 2) {
    Rainbow();
  } else if (Mode == 3) {
    //Fade();
  }

  //When motion sensor is on
  if (ModeMotionSensor == 1)  {
    MotionSensor();
    ledTimer--;
  } else if (ModeMotionSensor == 0) {
    ledTimer = Duration;
  }
  if (ledTimer == 0) {
    ledClear();
  }
}

//Controlling Mode Value and reassings mode in function
BLYNK_WRITE(V0) {
  if (param[0].asInt() == 1)  {
    if (Mode != 0)  {
      Mode = 1;
    }
  } else if (param[0].asInt() == 2) {
    Mode = 2;
  } else if (param[0].asInt() == 3) {
    Mode = 3;
  }
}

//Controls the RGB Color and reassigns RGB values in function
BLYNK_WRITE(V1)  {
  Red = param[0].asInt();
  Green = param[1].asInt();
  Blue = param[2].asInt();
}

//Controlls the Mode speed for effects and assigns value
BLYNK_WRITE(V2) {
  ModeSpeed = param[0].asInt();
}

//Check if Motion Sensor is on or off and reassigns value
BLYNK_WRITE(V3) {
  ModeMotionSensor = param[0].asInt();
}

//Adjust Brightness and reassigns value
BLYNK_WRITE(V4) {
  Brightness = param[0].asInt();
}

void FillRoom() {
  strip.clear();
  strip.show();
  for (int i = 0; i < ledCount; i++)  {
    strip.setPixelColor(i, strip.Color(Red, Green, Blue));
    strip.setBrightness(Brightness);
    strip.show();
  }
}

//Solid Mode Function
void Solid() {
  if (ledTimer == 0)  {
    return;
  }
  strip.setBrightness(Brightness);
  strip.fill(strip.Color(Red, Green, Blue));
  strip.show();
  Mode = 0;
}

//Rainbow Mode Function
void Rainbow()  {
  if (ledTimer == 0)  {
    return;
  }
  strip.setBrightness(Brightness);
  for (long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i = 0; i < strip.numPixels(); i++)  {
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();
    delay(ModeSpeed / 20);
  }
}

//Detect when someone is present
void MotionSensor() {
  if (digitalRead(sensorPin) > 0) {
    ledTimer = Duration;
  }
}

//When no motion is detected, turn off
void ledClear() {
  for (int i = 0; i < ledCount; i++)  {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
}
