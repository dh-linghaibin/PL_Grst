
#include "Pump.h"

#define PUMP_NUTRITION PB_ODR_ODR6
#define PUMP_WATER PB_ODR_ODR0

void PumpInit(void) {
    PB_DDR_DDR6 = 1;//pump nutritton  ˮ��--��Ӫ��Һ
    PB_CR1_C16 = 1;
    PB_CR2_C26 = 0;
    
    PB_DDR_DDR0 = 1;//pump water  ˮ��--��ˮ
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