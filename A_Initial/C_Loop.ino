void loop() {
  bool down = GetTouch();
  on_btn.press(down && on_btn.contains(pixel_x, pixel_y));
  off_btn.press(down && off_btn.contains(pixel_x, pixel_y));
  if (on_btn.justReleased())  {
     on_btn.drawButton();
  }
  if (off_btn.justReleased()) {
    off_btn.drawButton();
  }
  Headlight();
  UltraSonic();
  displayTime();
  //saveTemp();
}

/*
 * Save temp will be inside a timer function
 */
