

#include "Led.h"
#include "Button.h"

#define Led_FRUITS       PD_ODR_ODR4
#define Led_FLOWERS      PD_ODR_ODR5
#define Led_SWITCH       PD_ODR_ODR6
#define Led_SEEDLING     PB_ODR_ODR5
#define Led_MATURE       PB_ODR_ODR4

static u8 led_switch_flag = 0;

void LedInit(void) {
    PD_DDR_DDR4 = 1;
    PD_CR1_C14 = 1;
    PD_CR2_C24 = 0;
    
    PD_DDR_DDR5 = 1;
    PD_CR1_C15 = 1;
    PD_CR2_C25 = 0;
    
    PD_DDR_DDR6 = 1;
    PD_CR1_C16 = 1;
    PD_CR2_C26 = 0;
    
    PB_DDR_DDR4 = 1;
    PB_CR1_C14 = 1;
    PB_CR2_C24 = 0;
    
    PB_DDR_DDR5 = 1;
    PB_CR1_C15 = 1;
    PB_CR2_C25 = 0;
    
    led_switch_flag = 0;
    Led_SWITCH = 1;
    
    LedSetSpecies(0);
    LedSetPeriod(0);
}

static u8 led_need_water = 0;

void LedSedNeedwater(u8 cmd) {
    led_need_water = 0;
}

void LedSwitchService(void) {
    static u16 count = 0;
    if(led_need_water == 1) {
        count++;
        if(count > 50000) {
            count = 0;
            if(Led_SWITCH == 0) {
                Led_SWITCH = 1;
            } else {
                Led_SWITCH = 0;
            }
        }
    }
}

void LedSetSwitch(void) {
    if(led_switch_flag == 0) {
        led_switch_flag = 0x80;
        Led_SWITCH = 0;
        LedSetSpecies(ButtonReadSpeciesFlag());   
        LedSetPeriod(ButtonReadPeriodFlag());
    } else {
        led_switch_flag = 0;
        Led_SWITCH = 1;
        LedSetSpecies(0);
        LedSetPeriod(0);
    }
}

u8 LedGetSwitch(void) {
    return led_switch_flag;
}

void LedSetSpecies(u8 cmd) {
    if(cmd == 1) {
        Led_FRUITS = 0;
        Led_FLOWERS = 1;
    } else if(cmd == 2) {
        Led_FRUITS = 1;
        Led_FLOWERS = 0;
    } else {
        Led_FRUITS = 1;
        Led_FLOWERS = 1;
    }
}

void LedSetPeriod(u8 cmd) {
    if(cmd == 1) {
        Led_SEEDLING = 0;
        Led_MATURE = 1;
    } else if(cmd == 2) {
        Led_SEEDLING = 1;
        Led_MATURE = 0;
    } else {
        Led_SEEDLING = 1;
        Led_MATURE = 1;
    }
}