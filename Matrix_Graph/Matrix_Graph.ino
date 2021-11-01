#include <Adafruit_NeoPixel.h>

#define ledPin 7
#define ledCount 256
int ledBrightness = 5;
int x, y = 0;
int i = 0;

Adafruit_NeoPixel strip(ledCount, ledPin, NEO_GRB + NEO_KHZ800);

void setup()  {
  Serial.begin(9600);
  strip.begin();
  strip.clear();
  strip.setBrightness(ledBrightness);
  x = 8;
  y = 6;
  for (int i = 0; i <= ledCount; i++) {
    strip.setPixelColor(i, strip.Color(255, 0, 0));
    strip.show();
  }
}

void loop() {
  i = ((x * -1) + 16) + (16 * (y - 1));
  Serial.println(i);
  strip.setPixelColor(i, strip.Color(0, 0, 255));
  strip.show();
  Slope();
  delay(5000);
}

int Slope()  {

}
