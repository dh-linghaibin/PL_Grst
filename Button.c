

#include "Button.h"
#include "Eeprom.h"

#define BUTTON_FRUITS       PC_IDR_IDR4
#define BUTTON_FLOWERS      PC_IDR_IDR3
#define BUTTON_SWITCH       PA_IDR_IDR3
#define BUTTON_SEEDLING     PA_IDR_IDR2
#define BUTTON_MATURE       PA_IDR_IDR1

#define BUTTON_WATER        PD_IDR_IDR1

static u8 button_species_flag = 0;
static u8 button_period_flag = 0;

void ButtonInit(void) {
    PA_DDR_DDR1 = 0;
    PA_CR1_C11 = 1;
    PA_CR2_C21 = 0;
    
    PA_DDR_DDR2 = 0;
    PA_CR1_C12 = 1;
    PA_CR2_C22 = 0;
    
    PA_DDR_DDR3 = 0;
    PA_CR1_C13 = 1;
    PA_CR2_C23 = 0;
    
    PC_DDR_DDR3 = 0;
    PC_CR1_C13 = 1;
    PC_CR2_C23 = 0;
    
    PC_DDR_DDR4 = 0;
    PC_CR1_C14 = 1;
    PC_CR2_C24 = 0;
    
    PD_DDR_DDR1 = 0;
    PD_CR1_C11 = 1;
    PD_CR2_C21 = 0;
    
    if(EepromRead(10) == 0x55) {
        button_species_flag = EepromRead(11);
        button_period_flag = EepromRead(12);    
    } else {
        EepromWrite(10,0x55);
        EepromWrite(11,0x01);
        EepromWrite(12,0x01);
        button_species_flag = EepromRead(11);
        button_period_flag = EepromRead(12);    
    }
}

static u8 button_water_flag = 0;

u8 ButtonReadWaterFlag(void) {
    return button_water_flag;
}

void  ButtonSetWaterFlag(u8 cmd) {
    button_water_flag = cmd;
}

u8 ButtonReadWater(void) {
    if(BUTTON_WATER == 0) {
        return 0x80;
    } else {
        return 0x00;
    }
}

u8 ButtonReadSwitch(void) {
    static u16 buntu_count = 0;
    if(BUTTON_SWITCH == 1) {
        if(buntu_count < 1000) {
            buntu_count++;
        } else {
            if(buntu_count == 1000) {
                buntu_count++;
                return 0x80;
            }
        }
    } else {
        buntu_count = 0;
    }
    return 0x00;
}

u8 ButtonReadSpecies(void) {
    static u16 buntu_count1 = 0;
    static u16 buntu_count2 = 0;
    if(BUTTON_FRUITS == 1) {
        if(buntu_count1 < 1000) {
            buntu_count1++;
        } else {
            if(buntu_count1 == 1000) {
                buntu_count1++;
                button_species_flag = 1;
                EepromWrite(11,button_species_flag);
                return 0x80;
            }
        }
    } else {
        buntu_count1 = 0;
    }
    
    if(BUTTON_FLOWERS == 1) {
        if(buntu_count2 < 1000) {
            buntu_count2++;
        } else {
            if(buntu_count2 == 1000) {
                buntu_count2++;
                button_species_flag = 2;
                EepromWrite(11,button_species_flag);
                return 0x81;
            }
        }
    } else {
        buntu_count2 = 0;
    }
    return 0;
}

u8 ButtonReadSpeciesFlag(void) {
    return button_species_flag;
}



u8 ButtonReadPeriodFlag(void) {
    return button_period_flag;
}

u8 ButtonReadPeriod(void) {
    static u16 buntu_count1 = 0;
    static u16 buntu_count2 = 0;
    if(BUTTON_SEEDLING == 1) {
        if(buntu_count1 < 1000) {
            buntu_count1++;
        } else {
            if(buntu_count1 == 1000) {
                buntu_count1++;
                button_period_flag = 1;
                EepromWrite(12,button_period_flag);
                return 0x80;
            }
        }
    } else {
        buntu_count1 = 0;
    }
    
    if(BUTTON_MATURE == 1) {
        if(buntu_count2 < 1000) {
            buntu_count2++;
        } else {
            if(buntu_count2 == 1000) {
                buntu_count2++;
                button_period_flag = 2;
                EepromWrite(12,button_period_flag);
                return 0x81;
            }
        }
    } else {
        buntu_count2 = 0;
    }
    return 0;
}

