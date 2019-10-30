
#include "inc\tm4c123gh6pm.h"

#define ZERO 0x00;

// PFX pins OUTPUT
#define PF3_WALK_GREEN 0x02
#define PF1_WALK_RED 0x04

#define PF 0x20
#define PFX_DIR 0x10
#define PFX_DEN 0x10

// 7 6 5 4 3 2 1 0
// PEX pins OUTPUT
#define PE5_RED_SOUTH 0x20
#define PE4_YELLOW_SOUTH 0x10
#define PE3_GREEN_SOUTH 0x08
#define PE2_RED_WEST 0x04
#define PE1_YELLOW_WEST 0x02
#define PE0_GREEN_WEST 0x01

#define PE 0x10
#define PEX_DIR 0x3F
#define PEX_DEN 0x3F

// PAX pins INPUT
#define PA4_WALK_INPUT 0x10
#define PA3_SOUTH_INPUT 0x08
#define PA2_WEST_INPUT 0x04

#define PA 0x01
#define PAX_DIR 0x1C
#define PAX_DEN 0x1C
#define PAX_PDR 0x1C
