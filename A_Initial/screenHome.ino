void screenHome() {  
  tft.setRotation(0);
  tft.fillScreen(BACKGROUND);
  showmsgXY(50, 30, 2, NULL, "ULTRASONIC SENSORS");
  on_btn.initButton(&tft, 100, 80, 100, 40, WHITE, CYAN, BLACK, "ON", 2);
  off_btn.initButton(&tft, 220, 80, 100, 40, WHITE, CYAN, BLACK, "OFF", 2);
  on_btn.drawButton(false);
  off_btn.drawButton(false);
}
