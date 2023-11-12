// conversion factors
#define ATASPINEFACTORMEASUREDAT23 1.804224542  // convert 23" measure to 28
#define AMOMULTIPLIER 0.825                     // convert 26" AMO to 28
#define ASTMFACTOR 440000.0                     // convert force to ASTM
#define SIXTEENTHSTOMM (25.4 / 16)              // convert 1/16" to mm
#define GRAMTOGRAINS 15.4324                    // convert grams to grains

// arrow data definitions
#define MAXSPINE 9999  // max spine for display

#define SUPPORTSPACING28 711.2  // dist between load cells (28")
#define SUPPORTSPACING23 584.2  // dist between load cells (23")

// spine methodology constants
enum SpineMethodologies {
  ASTMAT28,  // ASTM spine - thou depression caused
  // by 1.94lb weight with arrow supported
  // at 28" centres
  AMOAT26,  // ATA spine - thou depression caused
  // by 2lb weight with arrow supported at
  // 26" centres
  AMOLBSAT26,  // bow poundage measured according to
  // deflection caused by 2lb weight to
  // arrow supported at 26" centres
  GRAMSAT28,  // grams force on one support pillar
  // caused by 1/2" deflection supported
  // at 28" centres
  MAXSPINEMETHOD
};

#define DEFAULTSPINEMETHOD ASTMAT28  // default is 28" ASTM spine
int SpineMethodology = DEFAULTSPINEMETHOD;

float Spine;
float Force;
float CoG;
