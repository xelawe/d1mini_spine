#include "HX711.h"

#define CELLS                           2       // there are two load cells

#define LOADCELL1_SCK_PIN               D5       // CLK for HX711 for load cell
#define LOADCELL1_DOUT_PIN              D6      // data for HX711 for load cell
#define LOADCELL2_SCK_PIN               D5      // CLK for HX711 for load cell
#define LOADCELL2_DOUT_PIN              D7       // data for HX711 for load cell

#define CELLREADS               12      // readings to average when reading
#define SIGNIFICANTREADING              10      // reading different enough

static int CellDOutPin [] = {LOADCELL1_DOUT_PIN, LOADCELL2_DOUT_PIN};
static int CellSckPin [] = {LOADCELL1_SCK_PIN, LOADCELL2_SCK_PIN};
static float scale_f [] = { 724.768066, 792.108398 };

static float PeakForce [6] = {0, 0, 0, 0, 0, 0};

float Reading [CELLREADS][CELLS];
int LastRead;

HX711 ArrowScale[CELLS];

boolean gv_do_tare = false;
