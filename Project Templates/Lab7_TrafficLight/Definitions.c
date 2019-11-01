
#include "inc\tm4c123gh6pm.h"

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
#define PF_DATA GPIO_PORTF_DATA_R

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
#define PE_DATA GPIO_PORTE_DATA_R

// PAX pins INPUT
#define WALK_IN 0x10                    // PA4
#define SOUTH_IN 0x08                   // PA3
#define WEST_IN 0x04                    // PA2

#define PA 0x01
#define PAX_DIR 0x1C                    // PA2 - PA4
#define PAX_DEN 0x1C                    // PA2 - PA4
#define PAX_PDR 0x1C                    // PA2 - PA4
#define PA_DATA GPIO_PORTA_DATA_R

// PEX State Outputs
#define GO_S_OUT_PE 0x0C
#define WAIT_S_OUT_PE 0x14
#define GO_W_OUT_PE 0x21
#define WAIT_W_OUT_PE 0x22
#define STOP_ALL_OUT_PE 0x24
#define CHECK_PX_OUT_PE 0x24            // checkP1, P2

// PFX State Outputs
#define WALK_P_OUT_PF 0x08
#define WARNING_PX_OFF_OUT_PF 0x00      // warningP1Off, warningP2Off, etc
#define WARNING_PX_ON_OUT_PF 0x02       // warningP1On, warningP2On, etc
#define NO_WALK_P_OUT_PF 0x02

// State indicies
#define goS 0
#define waitS 1
#define goW 2
#define waitW 3
#define checkP1 4
#define checkP2 5
#define stopAll 6
#define walkP 7
#define warningP1Off 8
#define warningP1On 9
#define warningP2Off 10
#define warningP2On 11
#define warningP3Off 12
#define warningP3On 13
#define noWalkP 14
