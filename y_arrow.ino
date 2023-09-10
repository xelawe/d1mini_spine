float ConvertForceToSpine (float Force, int SpineMethodology,  bool Mode23Inch)
{
  float ASTMSpine;
  float Spine;

  // DEBUG (FUNC, Force, (float) SpineMethodology);

  // convert the grams force to an ASTM spine as most spines start from this
  if (Force <= 0)
    ASTMSpine = MAXSPINE;
  else
    //Apply or not the 23" factor
    if (Mode23Inch)
      ASTMSpine = (float) (ASTMFACTOR / Force * ATASPINEFACTORMEASUREDAT23);
    else
      ASTMSpine = (float) (ASTMFACTOR / Force);

  // switch according to what kind of spine is to be displayed
  switch (SpineMethodology)
  {
    // AMO spine - a simple multiplier converts from ASTM
    case AMOAT26:
      if (ASTMSpine >= MAXSPINE)
        Spine =  MAXSPINE;
      else if (ASTMSpine <= 0)
        Spine =  0;
      else
        Spine = constrain (ASTMSpine * AMOMULTIPLIER, 0, MAXSPINE);
      break;

    // the bow poundage is a conversion to AMO as above then 26/AMO to give lbs
    case AMOLBSAT26:
      if (ASTMSpine >= MAXSPINE)
        Spine =  MAXSPINE;
      else if (ASTMSpine <= 0)
        Spine =  0;
      else
      {
        Spine = constrain ((float)ASTMSpine * AMOMULTIPLIER, 0, MAXSPINE);
        Spine = 26.0 / (Spine / 1000.0);
      }
      break;

    // grams force is just a range check
    case GRAMSAT28:
      Spine = constrain (Force, 0, MAXSPINE);
      break;

    // ASTM spine - this needs no further conversion, just range check
    case ASTMAT28:
    default:
      Spine = constrain (ASTMSpine, 0, MAXSPINE);
      break;
  }

  // DEBUG (FUNC, ASTMSpine, Spine, Mode23Inch);

  return (Spine);

}
