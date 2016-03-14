
#include "Pump.h"

#define PUMP_NUTRITION PB_ODR_ODR6
#define PUMP_WATER PB_ODR_ODR0

void PumpInit(void) {
    PB_DDR_DDR6 = 1;//pump nutritton  水泵--抽营养液
    PB_CR1_C16 = 1;
    PB_CR2_C26 = 0;
    
    PB_DDR_DDR0 = 1;//pump water  水泵--洒水
    PB_CR1_C10 = 1;
    PB_CR2_C20 = 0;
    
    PUMP_NUTRITION = 0;
    PUMP_WATER = 0;
}

void PumpSetWater(u8 cmd) {
    PUMP_WATER = cmd;
}


void PumpSetNutrition(u8 cmd) {
    PUMP_NUTRITION = cmd;
}