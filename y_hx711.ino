void init_hx711() {

  for (int Cell = 0; Cell < CELLS; Cell++)
  {
    Serial.print("====== Cell ");
    Serial.print(Cell);
    Serial.println(" =========");

    // initialise the pins connecting the HX711
    ArrowScale [Cell].begin (CellDOutPin [Cell], CellSckPin [Cell]);

    // set the calibration factor to make the load cell read in grams
    // ArrowScale [Cell].set_scale (NVM->ScaleCalibration [Cell]);

    for (int Read = 0; Read < CELLREADS; Read++)
      Reading [Read][Cell] = 0;

    print_dot( );

    ArrowScale [Cell].set_scale(scale_f[Cell]);                      // this value is obtained by calibrating the scale with known weights; see the README for details
    
    cell_Tare(Cell);            // reset the scale to 0

    Serial.println("After setting up the scale:");

    Serial.print("get units: \t\t");
    Serial.println(ArrowScale [Cell].get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided

    print_dot( );

    delay(100);
  }

  LastRead = CELLS - 1;

  Serial.println("Readings:");
}

void cell_tare() {
  for (int Cell = 0; Cell < CELLS; Cell++)
  {
    cell_Tare(Cell);
  }
}

void cell_Tare(int Cell) {
  print_dot();
  ArrowScale [Cell].tare();
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
  CoG = ReadArrowCOG ( false );
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

/*******************************************************************************
*                                                                              *
*                                  ReadArrowCOG                                *
*                                                                              *
*       Gather up the HX711 force history of readings and average them,        *                                 
*       keeping the force averages for the two gauges separate.  Use the       *
*       forces on the two gauges to calculate the position of the centre       *
*       of gravity in millimetres in front of the first gauge.                 *
*                                                                              *
*******************************************************************************/

float ReadArrowCOG (bool Mode23Inch)
{
  float HalfSupportSpacing = (SUPPORTSPACING28/2);
  float Total [CELLS];
  float CoG;

  for (int Cell = 0; Cell < CELLS; Cell++) Total [Cell] = 0;

  // figure out support spacing
  if (Mode23Inch)
    HalfSupportSpacing = (SUPPORTSPACING23/2); 
  
  // average the cell reading history
  for (int Cell = 0; Cell < CELLS; Cell++)
    for (int Read = 0; Read < CELLREADS; Read++)
      Total [Cell] += Reading [Read][Cell];
  for (int Cell = 0; Cell < CELLS; Cell++)
    Total [Cell] = Total [Cell] / (float) (CELLREADS);

  // calculate the centre of gravity distance from support 1
  if ((Total[1] < 1) || (Total[0] < 1))
    CoG = 0;
  else
    CoG = (((Total[1] - Total[0]) * HalfSupportSpacing) / (Total[1] + Total[0]))
                                  + HalfSupportSpacing;

  //DEBUG (FUNC, CoG, HalfSupportSpacing);

  // return position of COG in mm from the first support
  return (CoG);  
  
} /* ArrowSpineClass::ReadArrowCOG */
