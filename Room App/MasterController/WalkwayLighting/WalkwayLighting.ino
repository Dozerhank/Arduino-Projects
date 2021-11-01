#include <Adafruit_NeoPixel.h>

//IR Sensors
int sensorPin = 3;
int indicator = 13;

//LED Strips
uint32_t white = (255, 255, 255);
int ledStatus = 0;
int ledTimer = 0;
int Duration = 100; //every 10 is 1 second, 600 = 1 min, 18000 = 30 min
int ledCount = 26 4;

//PWM Modules
int PWMPin = 0;
int ColorPWMPin = 1;

//Color Indicators
int RedPin = 5;
int GreenPin = 6;
int BluePin = 7;
int ColorButton = 4;
int ColorState = 0;
int Red = 255;
int Green = 255;
int Blue = 255;

//Switch Button
int SwitchPin = 8;
int Mode = 0; //Default is MotionSense()
int MaxMode = 2;  //How many modes there are

Adafruit_NeoPixel strip(ledCount, 2, NEO_GRB + NEO_KHZ800);

void setup()  {
  strip.begin();
  strip.show();
  strip.setBrightness(0);
  pinMode(sensorPin, INPUT);
  pinMode(indicator, OUTPUT);
  pinMode(ColorButton, INPUT);
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
  pinMode(SwitchPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  CheckButton();
  GetBrightness();
  if (Mode == 0) {
    MotionSense();
    Serial.println("Running Motion Sense.");
  } else if (Mode == 1) {
    Rainbow();
    Serial.println("Running Rainbow.");
  } else if (Mode == 2) {
    SolidColor();
  }
  Serial.println(Mode);
}

void MotionSense()  {
  CheckButton();
  if (Mode != 0)  {
    strip.clear();
    strip.show();
    return;
  }
  GetBrightness();
  int state = digitalRead(sensorPin);
  digitalWrite(indicator, state);
  if (state == 1) {
    GetBrightness();
    if (ledTimer == 0) {
      GetBrightness();
      FloorWhite();
    }
  } else if (state == 0)  {
    CheckButton();
    if (ledTimer == 0)  {
      ClearFloor();
    }
  }
  if (ledTimer > 0) {
    ledTimer--;
    CheckButton();
    GetBrightness();
  }  
}

void Rainbow()  {
  Serial.println("Running...");
  CheckButton();
  if (Mode != 1)  {
    strip.clear();
    strip.show();
    return;
  }
  GetBrightness();
  for (long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i = 0; i < strip.numPixels(); i++)  {
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    CheckButton();
    if (Mode != 1)  {
      return;
    }
    GetBrightness();
    strip.show();
    delay(10);
  }
}

void SolidColor() {
  CheckButton();
  if (Mode != 2)  {
    strip.clear();
    strip.show();
    return;
  }
  GetBrightness();
  strip.fill(strip.Color(Red, Green, Blue));
  strip.show();
}

void FloorWhite() {
  CheckButton();
  GetBrightness();
  for (int i = 0; i < ledCount; i++)  {
    strip.setPixelColor(i, strip.Color(Red, Green, Blue));
    GetBrightness();
    delay(10);
  }
  ledTimer = Duration;
}

void ClearFloor() {
  CheckButton();
  for (int i = 0; i < ledCount; i++)  {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    GetBrightness();
    delay(10);
  }
}

void GetBrightness() {
  int brightness = analogRead(PWMPin) / 3 - 50;
  if (brightness < 0) {
    brightness = 0;
  } else if (brightness > 255)  {
    brightness = 255;
  }
  strip.setBrightness(brightness);
  strip.show();
}

void CheckButton()  {
  delay(150);
  if (digitalRead(SwitchPin) == LOW)  {
    Mode++;
    delay(150);
    if (Mode > MaxMode) {
      Mode = 0;
    }
  }
  if (Mode != 1)  {
    if (digitalRead(ColorButton) == LOW) {
        ColorState++;
        ColorChange();
    } else if (digitalRead(ColorButton) == HIGH)  {
        ColorChange();
    }
    if (ledTimer != 0)  {
        strip.fill(strip.Color(Red, Green, Blue));
        Serial.println("Color filled");
        strip.show();
      }
  }
}

void ColorChange() {
  if (ColorState == 0 || ColorState == 4)  {
    ColorState = 0;
    digitalWrite(RedPin, LOW);
    digitalWrite(GreenPin, LOW);
    digitalWrite(BluePin, LOW);
    strip.show();
  } else if (ColorState == 1) {
    digitalWrite(RedPin, HIGH);
    digitalWrite(GreenPin, LOW);
    digitalWrite(BluePin, LOW);
    Red = analogRead(ColorPWMPin) / 3 - 50;
    if (Red > 255)  {
      Red = 255;
    } else if (Red < 0) {
      Red = 0;
    }
    strip.show();
  } else if (ColorState == 2) {
    digitalWrite(RedPin, LOW);
    digitalWrite(GreenPin, HIGH);
    digitalWrite(BluePin, LOW);
    Green = analogRead(ColorPWMPin) / 3 - 50;
    if (Green > 255)  {
      Green = 255;
    } else if (Green < 0) {
      Green = 0;
    }
    strip.show();
  } else if (ColorState == 3) {
    digitalWrite(RedPin, LOW);
    digitalWrite(GreenPin, LOW);
    digitalWrite(BluePin, HIGH);
    Blue = analogRead(ColorPWMPin) / 3 - 50;
    if (Blue > 255)  {
      Blue = 255;
    } else if (Blue < 0) {
      Blue= 0;
    }
    strip.show();
  }
}
