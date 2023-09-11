void init_button() {
  button1.attach(BUTTON1_PIN, INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  button1.interval(25); // Use a debounce interval of 25 milliseconds
}

void check_button() {
  button1.update();

  if (button1.fell()) {
    //Serial.println("================== Button 1 =================");
    cell_tare();
  }
}
