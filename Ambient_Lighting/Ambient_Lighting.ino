#include <IRremote.h>
#include <Adafruit_NeoPixel.h>

#define ledPin 10
int ledBrightness = 100;
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
          case 0xFF629D:
          Serial.println("BRIGHTNESS UP");
          ledBrightness += 10;
          strip.setBrightness(ledBrightness);
          strip.show();
          break;
          case 0xFF22DD:
          Serial.println("EMPTY LEFT");
          break;
          case 0xFF02FD:
          Serial.println("ON/OFF");
          if (ledPower == 0)  {
            ColorPick();
          } else if (ledPower == 1) {
            ledPower = 0;
            PowerOff();
          }
          break ;  
          case 0xFFC23D:
          Serial.println("EMPTY RIGHT");
          break ;               
          case 0xFFA857:
          Serial.println("BRIGHTNESS DOWN");
          ledBrightness -= 10;
          strip.setBrightness(ledBrightness);
          strip.show();
          break ;    
          case 0xFF6897:
          Serial.println("1");
          Red = 255;
          Green = 255;
          Blue = 255;
          ColorPick();
          break ;  
          case 0xFF9867:
          Serial.println("2");
          Red = 255;
          Green = 0;
          Blue = 0;
          ColorPick();
          break ;
          case 0xFFB04F:
          Serial.println("3");
          Red = 05;
          Green = 255;
          Blue = 0;
          ColorPick();
          break ;
          case 0xFF30CF:
          Serial.println("4");
          Red = 0;
          Green = 0;
          Blue = 255;
          ColorPick();
          break ;
          case 0xFF18E7:
          Serial.println("5");
          Red = 255;
          Green = 255;
          Blue = 0;
          ColorPick();
          break ;
          case 0xFF7A85:
          Serial.println("6");
          Red = 255;
          Green = 0;
          Blue = 255;
          ColorPick();
          break ;
          case 0xFF10EF:
          Serial.println("7");
          Red = 0;
          Green = 255;
          Blue = 255;
          ColorPick();
          break ;
          case 0xFF38C7:
          Serial.println("8");
          Red = 255;
          Green = 0;
          Blue = 0;
          ColorPick();
          break ;
          case 0xFF5AA5:
          Serial.println("9");
          Red = 255;
          Green = 0;
          Blue = 0;
          ColorPick();
          break ;
          case 0xFF42BD:
          Serial.println("EMPTY *");
          break ;
          case 0xFF4AB5:
          Serial.println("0");
          Red = 255;
          Green = 0;
          Blue = 0;
          ColorPick();
          break ;
          case 0xFF52AD:
          Serial.println("EMPTY #");
          break ;      
        }
        key_value = results.value;
        irrecv.resume(); 
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
