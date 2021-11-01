#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <FreeDefaultFonts.h>
#include "Wire.h"
#include <SD.h>
#include <SPI.h>
#include <dht11.h>

//Headlight Setup
int ledHeadlight[4] = {35, 36, 37, 38};
int potPin = 5;

//Temp and Humidity Sensor
dht11 DHT;
#define dhtPin 34
int chk;
int temp;
int hum;

//SD setup
File myFile;
int CSPin = 53;

//DS3231 Clock setup
#define DS3231_I2C_ADDRESS 0x68

//Touchscreen Setup
MCUFRIEND_kbv tft;

#define MinPressure 200
#define MaxPressure 1000

const int XP=8,XM=A2,YP=A3,YM=9; //320x480 ID=0x9486
const int TS_LEFT=126,TS_RT=918,TS_TOP=952,TS_BOT=92;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button on_btn, off_btn;

int pixel_x;
int pixel_y;

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GREY    0x8410
#define BACKGROUND 0x0000


//Ultrasonic Sensor Setup
#define ledPinRight 33
#define echoPinRight 28
#define trigPinRight 29

#define ledPinLeft 30
#define echoPinLeft 22
#define trigPinLeft 23

#define ledPinBack 31
#define echoPinBack 24
#define trigPinBack 25

#define ledPinFront 32
#define echoPinFront 26
#define trigPinFront 27


int maximumRange = 200; 
int minimumRange = 0;
long durationRight, durationLeft, durationBack, durationFront;
long distanceRight, distanceLeft, distanceBack, distanceFront;
