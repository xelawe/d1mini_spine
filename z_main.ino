void setup() {
  // put your setup code here, to run once:
  delay(500);
  // initialise everything
  Debug = new SerialDebug("================ " ARROWSCALETITLE " - " ARROWSCALEVERSION " - " __DATE__ " " __TIME__ " ================");

  init_display();

  init_hx711();

  init_button();
}

void loop() {
  float Force;

  check_button();

  read_hx711();

  check_menu();

  show_dis();


  if (gv_do_tare) {
    cell_tare();
    gv_do_tare = false;
  }

  // Force = ReadArrowScale ();
  if ((Force > SIGNIFICANTREADING) && (Force > PeakForce[0])) {
    //LCD->WriteSpineOnScreen (Force, NVM->SpineMethodology, Buttons->Get23InchMode());
    PeakForce[0] = Force;
  }
}
