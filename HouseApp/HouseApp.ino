#define Version 1.0

//Library Setup
#include <BlynkSimpleShieldEsp8266.h>
#include <Adafruit_NeoPixel.h>

//Blynk Related Definitions, Variables, and Setups
char auth[] = "uRk91MMv0ZLvabP0-f37MHvphbENkVqP"; //BwcgSJY_PNZSFHjnddyvZLX2zIoCkpoS
char ssid[] = "Wireless 2.4Ghz";                  //suddenlink.net-5ACB
char pass[] = "dozerhank";                        //8C42W4443100314
#define BLYNK_PRINT Serial
#define EspSerial Serial1
ESP8266 wifi(&EspSerial);
#define ESP8266_BAUD 9600
BlynkTimer timer;

//LED Related Definitions, Variables, and Setups
#define ledCount 725
#define ledPin 5
int Brightness = 50;
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


void setup() {
  Serial.begin(9600);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass);
  timer.setInterval(1000L, timerFunction);
  
  strip.begin();
  strip.fill(strip.Color(Red, Green, Blue), 0, ledCount);
  strip.setBrightness(Brightness);
  strip.show();
  
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
}
