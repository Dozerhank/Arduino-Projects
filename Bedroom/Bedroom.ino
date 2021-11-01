#define BLYNK_TEMPLATE_ID "TMPLx_dZEbtr"
#define BLYNK_DEVICE_NAME "Arduino Uno"
char auth[] = "A60hTHiqgCRL0STvQzSyYV6SrC6LS2X5";

#define BLYNK_PRINT Serial
#define ESP8266_BAUD 9600
#define LED_PIN    6
#define LED_COUNT 300

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
//#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
//SoftwareSerial EspSerial(2, 3); // RX, TX

#define EspSerial Serial1

char ssid[] = "WhiteSky-TheArch";
char pass[] = "kctzvfuq";

ESP8266 wifi(&EspSerial);

BlynkTimer timer;

int temperature = 0, 
    power = 0, 
    menu = 0, 
    r = 0, g = 0, b = 0, 
    brightness = 0;

void myTimerEvent() {
  
}

//Temperature
BLYNK_WRITE(V0) {

}

//Power
BLYNK_WRITE(V1) {
  power = param.asInt();
}

//Menu
BLYNK_WRITE(V2) {
  menu = param.asInt();
}

//Red
BLYNK_WRITE(V3) {
  r = param.asInt();
  updateStrip();
}

//Green
BLYNK_WRITE(V4) {
  g = param.asInt();
  updateStrip();
}

//Blue
BLYNK_WRITE(V5) {
  b = param.asInt();
  updateStrip();
}

//Brightness
BLYNK_WRITE(V6) {
  brightness = param.asInt();
  updateStrip();
}

void updateStrip()  {
  strip.fill(strip.Color(r, g, b), 0, LED_COUNT);
  strip.setBrightness(brightness);
  strip.show();
}

void setup()
{
  Serial.begin(115200);

  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);

  strip.begin();
  strip.fill(strip.Color(0, 0, 100), 0, LED_COUNT);
  strip.setBrightness(100);      
  strip.show();  

  Blynk.virtualWrite(V3, r);
  Blynk.virtualWrite(V4, g);
  Blynk.virtualWrite(V5, b);
  Blynk.virtualWrite(V6, brightness);
}

void loop()
{
  Blynk.run();
  timer.run();
}
