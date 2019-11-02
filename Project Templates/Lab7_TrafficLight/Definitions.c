
#include "inc\tm4c123gh6pm.h"

// Note: Not all of these are used, however they are here for easily determining
//       what goes where.

// general conveniences
#define ZERO 0x00
#define TRUE 1
#define FALSE 0

// PFX pins OUTPUT - Walk LEDs
#define GREEN_WALK 0x08                 // PF3
#define RED_WALK 0x02                   // PF1

#define PF 0x20
#define PFX_DIR 0xA                     // PF1, PF3
#define PFX_DEN 0xA                     // PF1, PF3
#define PF_DATA &GPIO_PORTF_DATA_R

// PEX pins OUTPUT - Traffic LEDs
#define RED_SOUTH 0x20                  // PE5
#define YELLOW_SOUTH 0x10               // PE4
#define GREEN_SOUTH 0x08                // PE3
#define RED_WEST 0x04                   // PE2
#define YELLOW_WEST 0x02                // PE1
#define GREEN_WEST 0x01                 // PE0

#define PE 0x10
#define PEX_DIR 0x3F                    // PE0 - PE5
#define PEX_DEN 0x3F                    // PE0 - PE5
#define PE_DATA &GPIO_PORTE_DATA_R

// PAX pins INPUT
#define WALK_IN 0x10                    // PA4
#define SOUTH_IN 0x08                   // PA3
#define WEST_IN 0x04                    // PA2

#define ALL_INPUTS 0x1C

#define PA 0x01
#define PAX_DIR 0x1C                    // PA2 - PA4
#define PAX_DEN 0x1C                    // PA2 - PA4
#define PAX_PDR 0x1C                    // PA2 - PA4
#define PA_DATA &GPIO_PORTA_DATA_R

// PEX State Outputs
#define INIT_SW_OUT 0x3F                // turn PE0 - PE5 on
#define GO_S_OUT 0x0C
#define WAIT_SX_OUT 0x14                // waitS1, waitS2
#define GO_W_OUT 0x21
#define WAIT_WX_OUT 0x22                // waitW1, waitW2
#define HALT_SW_OUT 0x24
#define CHECK_PXS_OUT 0x0C
#define CHECK_PXS_OUT 0x0C
#define CHECK_PXW_OUT 0x21
#define CHECK_PXW_OUT 0x21

// PFX State Outputs
#define INIT_P_OUT 0x02                 // turn no walk LED on
#define WALK_P_OUT 0x08
#define WARNING_PX_OFF_OUT 0x00         // warningP1Off, warningP2Off, etc
#define WARNING_PX_ON_OUT 0x02          // warningP1On, warningP2On, etc
#define NO_WALK_P_OUT 0x02

// State indecies
#define initSW 0
#define initP 1
#define goS 2
#define waitS1 3
#define goW 4
#define waitW1 5
#define checkP1S 6
#define checkP2S 7
#define waitS2 8
#define haltSW 9
#define checkP1W 10
#define checkP2W 11
#define waitW2 12
#define walkP 13
#define warningP1Off 14
#define warningP1On 15
#define warningP2Off 16
#define warningP2On 17
#define warningP3Off 18
#define warningP3On 19
#define warningP4Off 20
#define noWalkP 21

// Time (ms)
#define GO_MS 50
#define WAIT_MS 2000
#define CHECK_MS 1000
#define STOP_MS 2000
#define WALK_MS 5000
#define WARNING_MS 500
