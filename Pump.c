
#include "Pump.h"

#define PUMP_NUTRITION PD_ODR_ODR2
#define PUMP_WATER PC_ODR_ODR6

void PumpInit(void) {
    PD_DDR_DDR2 = 1;//pump nutritton
    PD_CR1_C12 = 1;
    PD_CR2_C22 = 0;
    
    PC_DDR_DDR6 = 1;//pump water
    PC_CR1_C16 = 1;
    PC_CR2_C26 = 0;
    
    PUMP_NUTRITION = 0;
    PUMP_WATER = 0;
}

void PumpSetWater(u8 cmd) {
    PUMP_WATER = cmd;
}


void PumpSetNutrition(u8 cmd) {
    PUMP_NUTRITION = cmd;
}