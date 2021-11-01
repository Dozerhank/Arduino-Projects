#include <Wire.h>
#include "Sodaq_DS3231.h"

char weekDay[][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

String BitcoinUSD;

void setup() {
  //Arduino Communication Setup
  Serial.begin(115200);
  while (!Serial) {
    Serial.print(".");
    delay(500); 
  }
  Serial.println(" ");

  Wire.begin();
  rtc.begin();
}

void loop() {
  if (Serial.available()) {
    DateTime now = rtc.now();
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.print(" ");
    Serial.print(weekDay[now.dayOfWeek()]);
    Serial.print(" ");
    Serial.print(now.month(), DEC);
    Serial.print("/");
    Serial.print(now.date(), DEC);
    Serial.print("/");
    Serial.print(now.year(), DEC);
    Serial.print(" --> BTC (USD): $");
    
    BitcoinUSD = Serial.readString();
    Serial.print(BitcoinUSD);
  }
}
