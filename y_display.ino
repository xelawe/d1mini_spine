void init_display() {

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);             // Normal 2x pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.print("Init");
  display.display();

}

void print_dot( ) {
  display.print(".");
  display.display();
}

void show_weight( ) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);             // Normal 2x pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.println(Reading [LastRead][0]);
  display.println(Reading [LastRead][1]);
  float tot_weight = Reading [LastRead][0] + Reading [LastRead][1];
  display.println(tot_weight);

  Spine = ConvertForceToSpine (Force, SpineMethodology, false);
  display.println(Spine);

  display.display();
}
