void UltraSonic() {
  digitalWrite(trigPinRight, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPinRight, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPinRight, LOW);
  durationRight = pulseIn(echoPinRight, HIGH);
  distanceRight = durationRight/58.2;
  
  digitalWrite(trigPinLeft, LOW);
  delayMicroseconds(2); 
  digitalWrite(trigPinLeft, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinLeft, LOW);
  durationLeft = pulseIn(echoPinLeft, HIGH);
  distanceLeft = durationLeft/58.2;
  
  digitalWrite(trigPinBack, LOW);
  delayMicroseconds(2); 
  digitalWrite(trigPinBack, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinBack, LOW);
  durationBack = pulseIn(echoPinBack, HIGH);
  distanceBack = durationBack/58.2;
  
  digitalWrite(trigPinFront, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPinFront, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinFront, LOW);
  durationFront = pulseIn(echoPinFront, HIGH);
  distanceFront = durationFront/58.2;



  if (distanceRight <= 5 or distanceLeft <= 5 or distanceBack <= 5 or distanceFront <= 5) {
    if (distanceRight <= 5) {
      digitalWrite(ledPinRight, HIGH);
      tft.fillRect(300, 0, 320, 480, RED);
    } else  {
      digitalWrite(ledPinRight, LOW);
      tft.fillRect(300, 0, 320, 480, BACKGROUND);
    }
    
    if (distanceLeft <= 5) {
      digitalWrite(ledPinLeft, HIGH);
      tft.fillRect(0, 0, 20, 480, RED);
    } else  {
      digitalWrite(ledPinLeft, LOW);
      tft.fillRect(0, 0, 20, 480, BACKGROUND);
    }
    
    if (distanceBack <= 5) {
      digitalWrite(ledPinBack, HIGH);
      tft.fillRect(0, 460, 320, 480, RED);
    } else  {
      digitalWrite(ledPinBack, LOW);
      tft.fillRect(0, 460, 320, 480, BACKGROUND);
    }
    
    if (distanceFront <= 5) {
      digitalWrite(ledPinFront, HIGH);
      tft.fillRect(0, 0, 320, 20, RED);
    } else  {
      digitalWrite(ledPinFront, LOW);
      tft.fillRect(0, 0, 320, 20, BACKGROUND);
    } 
  } else  {
    tft.fillRect(300, 0, 320, 480, BACKGROUND);
    tft.fillRect(0, 0, 20, 480, BACKGROUND);
    tft.fillRect(0, 460, 320, 480, BACKGROUND);
    tft.fillRect(0, 0, 320, 20, BACKGROUND);
    digitalWrite(ledPinLeft, LOW);
    digitalWrite(ledPinRight, LOW);
    digitalWrite(ledPinBack, LOW);
    digitalWrite(ledPinFront, LOW);
  }
  delay(50);
}
