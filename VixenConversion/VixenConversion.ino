#include <FastLED.h>

#define NUM_LEDS 300
#define DATA_PIN 6

CRGB leds[NUM_LEDS];
CRGB *ledsRGB = (CRGB *) &leds[0];


void setup() {
  Serial.begin(115200);
}

void loop() {
  int cnt;
  unsigned int num_leds;
  unsigned int d1, d2, d3;
  for(;;) {
    cnt = 0;
    while(!Serial.available());
      if(Serial.read() != '>') {
        continue;
        }
    while(!Serial.available());
      if(Serial.read() != '>') {
        continue;
        }
    while(!Serial.available());
      d1 = Serial.read();
    while(!Serial.available());
      d2 = Serial.read();
    while(!Serial.available());
      d3 = Serial.read();
    while(!Serial.available());
      if(Serial.read() != '<') {
        continue;
        }
    while(!Serial.available());
      if(Serial.read() != '<') {
        continue;
        }
    num_leds = (d1-'0')*100+(d2-'0')*10+(d3-'0');
    if(num_leds > NUM_LEDS) {
      continue;
      }
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, num_leds);
    do {
      while(!Serial.available());
        leds[cnt].r = Serial.read();
      while(!Serial.available());
        leds[cnt].g = Serial.read();
      while(!Serial.available());
        leds[cnt++].b = Serial.read();
      } 
    while(--num_leds);
    FastLED.show();
    }
}
