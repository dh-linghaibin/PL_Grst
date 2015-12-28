

#include "Button.h"

#define BUTTON_FRUITS       PC_IDR_IDR4
#define BUTTON_FLOWERS      PC_IDR_IDR4
#define BUTTON_SWITCH       PA_IDR_IDR3
#define BUTTON_SEEDLING     PA_IDR_IDR2
#define BUTTON_MATURE       PA_IDR_IDR1


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
}

u8 ButtonReadSwitch(void) {
    static u16 buntu_count = 0;
    if(BUTTON_SWITCH == 0) {
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
    static u16 buntu_count = 0;
}
