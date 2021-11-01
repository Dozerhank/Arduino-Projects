void saveTemp() {
  chk = DHT.read(dhtPin);
  Serial.print("Tempurature: ");
  temp = (DHT.temperature * 1.8) + 32;
  Serial.println(temp);
  Serial.print("Humidity: ");
  hum = DHT.humidity;
  Serial.println(hum);

  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  
  GetTime(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);

  myFile = SD.open("temp.txt", FILE_WRITE);
  
  if (myFile) {    
    myFile.print(hour, DEC);
    myFile.print(":");
    if (minute<10)  {
      myFile.print("0");
    }
    myFile.print(minute, DEC);
    myFile.print(":");
    if (second<10){
      myFile.print("0");
    }
    myFile.print(second, DEC);
    myFile.print(" ");
    myFile.print(dayOfMonth, DEC);
    myFile.print("/");
    myFile.print(month, DEC);
    myFile.print("/");
    myFile.print(year, DEC);
    myFile.print(" Day of week: ");
    myFile.print(" | ");    
    myFile.print("Tempurature: ");
    myFile.print(temp);
    myFile.print(" | ");
    myFile.print("Humidity: ");
    myFile.println(hum);
    myFile.close(); 
  } else {
    Serial.println("error opening test.txt");
  }
}
