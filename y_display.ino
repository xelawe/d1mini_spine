void init_display() {

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(500); // Pause for 2 seconds

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


void print_tare() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Tara");
  display.display();
}

void show_weight( ) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);             // Normal 2x pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.print(Reading [LastRead][0], 1);
  display.print("g");
  display.print(" <--<< ");
  display.print(Reading [LastRead][1], 1);
  display.println("g");

  display.setTextSize(2);
  float tot_weight = Reading [LastRead][0] + Reading [LastRead][1];
  display.print(tot_weight, 1);
  display.println("g");

  display.print("Spine ");
  Spine = ConvertForceToSpine (Force, SpineMethodology, false);
  display.println(Spine, 0);

  display.display();
}
