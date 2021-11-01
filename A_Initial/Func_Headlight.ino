void Headlight()  {
  Serial.println(analogRead(potPin));
  if (analogRead(potPin) > 500)  {
    for (int i = 0; i < 4; i++) {
      digitalWrite(ledHeadlight[i], LOW);
    }
  } else  {
    for (int i = 0; i < 4; i++) {
      digitalWrite(ledHeadlight[i], HIGH);
    }
  }
}
