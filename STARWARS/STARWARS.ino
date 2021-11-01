#include <Adafruit_NeoPixel.h>

#define LED_PIN    6
#define LED_COUNT 750
#define BRIGHTNESS 35
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial.begin(9600);
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop() {  
  fadeBlue();
  fadeRed();
}

void fadeBlue()  {
  for (int i = 0; i <= LED_COUNT; i+=2) {
    if (i <= BRIGHTNESS and i%10==0)  {
      strip.setBrightness(i);
    }
    strip.setPixelColor(i, strip.Color(0, 0, 200));
    strip.setPixelColor(i + 1, strip.Color(0, 0, 200));
    strip.show();
    delay(5);
  }
  delay(45000);
  for (int i = BRIGHTNESS; i >= 0; i--) {
    strip.setBrightness(i);
    strip.show();
    delay(100);
  }
  strip.clear();
}

void fadeRed()  {
  for (int i = 0; i <= LED_COUNT; i+=2) {
    if (i <= BRIGHTNESS and i%10==0)  {
      strip.setBrightness(i);
    }
    strip.setPixelColor(i, strip.Color(255, 0, 0));
    strip.setPixelColor(i + 1, strip.Color(255, 0, 0));
    strip.show();
    delay(5);
  }
  delay(45000);
  for (int i = BRIGHTNESS; i >= 0; i--) {
    strip.setBrightness(i);
    strip.show();
    delay(100);
  }
  strip.clear();  
}
