#include <IRremote.h>
#include <Adafruit_NeoPixel.h>

#define ledPin 10
int ledBrightness = 5;
int ledCount = 256;
int ledPower = 0;
int Red = 0;
int Green = 0;
int Blue = 0;

Adafruit_NeoPixel strip(ledCount, ledPin, NEO_GRB + NEO_KHZ800);

const int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);

  strip.begin();
  strip.show();
  strip.setBrightness(ledBrightness);
}

void loop(){
  if (irrecv.decode(&results)){
 
        if (results.value == 0XFFFFFFFF)
          results.value = key_value;

        switch(results.value){
          case 0xF720DF:
            Serial.println("BRIGHTNESS UP");
            ledBrightness += 10;
            strip.setBrightness(ledBrightness);
            strip.show();
            break;
          case 0xFFA857:
            Serial.println("BRIGHTNESS DOWN");
            ledBrightness -= 10;
            strip.setBrightness(ledBrightness);
            strip.show();
            break;    
          case 0xF740BF:
            Serial.println("Off");
            PowerOff();
            break;  
          case 0xF7C03F:
            Serial.println("On");
            ColorPick();
            break;       
          //case 0xF720DF:
            Serial.println("Red");
            Red = 255;
            Green = 0;
            Blue = 0;
            strip.fill(strip.Color(Red, Green, Blue), 0, ledCount);
            strip.show();
          case 0xF7A05F:
            Serial.println("Green");
            Red = 0;
            Green = 255;
            Blue = 0; 
            strip.fill(strip.Color(Red, Green, Blue), 0, ledCount);      
            strip.show();
          case 0xF7609F:
            Serial.println("Blue");
            Red = 0;
            Green = 0;
            Blue = 255; 
            strip.fill(strip.Color(Red, Green, Blue), 0, ledCount);      
            strip.show();
        key_value = results.value;
        irrecv.resume(); 
    }
  }
}

void PowerOff() {
  for (int i = ledCount; i >= 0; i--)  {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.show();
    delay(10);
  }
}

void ColorPick()  {
  ledPower = 1;
  for (int i = 0; i < ledCount; i++)  {
    strip.setPixelColor(i, strip.Color(Red, Green, Blue));
    strip.show();
    delay(10);
  }
}
