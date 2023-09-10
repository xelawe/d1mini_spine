void init_hx711() {

  for (int Cell = 0; Cell < CELLS; Cell++)
  {
    Serial.print("========= ");
    Serial.print(Cell);
    Serial.println(" =========");

    // initialise the pins connecting the HX711
    ArrowScale [Cell].begin (CellDOutPin [Cell], CellSckPin [Cell]);

    // set the calibration factor to make the load cell read in grams
    // ArrowScale [Cell].set_scale (NVM->ScaleCalibration [Cell]);

    for (int Read = 0; Read < CELLREADS; Read++)
      Reading [Read][Cell] = 0;




    Serial.println("Before setting up the scale:");
    Serial.print("read: \t\t");
    Serial.println(ArrowScale [Cell].read());      // print a raw reading from the ADC
    print_dot( );
    Serial.print("read average: \t\t");
    Serial.println(ArrowScale [Cell].read_average(20));   // print the average of 20 readings from the ADC
    print_dot( );
    Serial.print("get value: \t\t");
    Serial.println(ArrowScale [Cell].get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)
    print_dot( );
    Serial.print("get units: \t\t");
    Serial.println(ArrowScale [Cell].get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided
    // by the SCALE parameter (not set yet)
    print_dot( );

    ArrowScale [Cell].set_scale(724.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
    ArrowScale [Cell].tare();               // reset the scale to 0

    Serial.println("After setting up the scale:");

    Serial.print("read: \t\t");
    Serial.println(ArrowScale [Cell].read());                 // print a raw reading from the ADC
    print_dot( );
    Serial.print("read average: \t\t");
    Serial.println(ArrowScale [Cell].read_average(20));       // print the average of 20 readings from the ADC
    print_dot( );
    Serial.print("get value: \t\t");
    Serial.println(ArrowScale [Cell].get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()
    print_dot( );
    Serial.print("get units: \t\t");
    Serial.println(ArrowScale [Cell].get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
    // by the SCALE parameter set with set_scale
    print_dot( );
    //scale1.power_down();              // put the ADC in sleep mode


    delay(500);
  }

  LastRead = CELLS - 1;

  Serial.println("Readings:");
}

void read_hx711() {

  // increment the reading array position pointer
  LastRead++;
  if (LastRead >= CELLREADS) LastRead = 0;

  // read the scales - result will be in grams - limit reading to 0 or above
  for (int Cell = 0; Cell < CELLS; Cell++)
  {
    if (ArrowScale [Cell].wait_ready_timeout(1000))
    {
      Reading [LastRead][Cell] = ArrowScale [Cell].get_units (1);
      //Serial.print("\t| average:\t");
      //Serial.println(Reading [LastRead][Cell], 1);
    }
    else
    {
      DEBUG(FUNC, "HX711 not found.");
    }

    if (Reading [LastRead][Cell] < 0)
      Reading [LastRead][Cell] = 0;
  }

  float tot_weight = Reading [LastRead][0] + Reading [LastRead][1];

  // DEBUG (FUNC, Reading [LastRead][0], Reading [LastRead][1], tot_weight );

  Force = ReadArrowScale ();
}


/*******************************************************************************
*                                                                              *
                                  ReadArrowScale
*                                                                              *
        Gather up the HX711 force history of readings and average them.
        This is better than using the library's averaging code as that
        code blocks while taking all the readings and kills operator
        responsiveness.  It doesn't matter if older readings are zero as
        the readings array will fill up over time and converge to a good
        reading.
*                                                                              *
*******************************************************************************/

float ReadArrowScale ()
{
  float Total = 0;

  // average the cell reading history
  for (int Cell = 0; Cell < CELLS; Cell++)
    for (int Read = 0; Read < CELLREADS; Read++)
      Total += Reading [Read][Cell];
  Total = Total / (float) (CELLREADS);

 // DEBUG (FUNC, Total);

  // return force on scale in grams
  return (Total);

} /* ArrowSpineClass::ReadArrowScale */
