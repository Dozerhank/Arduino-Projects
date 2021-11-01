void setup() {
  Serial.begin(9600);
  Serial.println("Startup Initiated");
  Wire.begin();

  pinMode(CSPin, OUTPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(ledHeadlight[i], OUTPUT);
  }
  
  if (SD.begin()) {
    Serial.println("SD card is ready to use.");
  } else  {
    Serial.println("SD card initialization failed");
  }

  randomSeed(analogRead(0));
  uint16_t ID = tft.readID();
  Serial.print("TFT ID = 0x");
  Serial.println(ID, HEX);
  if (ID == 0xD3D3) ID = 0x9486;
  tft.begin(ID);
  screenHome(); 
  
  pinMode(trigPinRight, OUTPUT);
  pinMode(echoPinRight, INPUT);
  pinMode(ledPinRight, OUTPUT);

  pinMode(trigPinLeft, OUTPUT);
  pinMode(echoPinLeft, INPUT);
  pinMode(ledPinLeft, OUTPUT);

  pinMode(trigPinBack, OUTPUT);
  pinMode(echoPinBack, INPUT);
  pinMode(ledPinBack, OUTPUT);

  pinMode(trigPinFront, OUTPUT);
  pinMode(echoPinFront, INPUT);
  pinMode(ledPinFront, OUTPUT);

  
  Serial.println("PROGRAM INITIATED");
}
