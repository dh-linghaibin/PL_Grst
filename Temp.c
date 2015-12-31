

#include "Temp.h"

#define TEMP_HAT        PC_ODR_ODR7
#define Temp_LIGHT      PC_ODR_ODR5

void TempInit(void) {
    PD_DDR_DDR3 = 0; //temp
    PD_CR1_C13 = 0;
    PD_CR2_C23 = 0;
    
    PC_DDR_DDR7 = 1;//add hat
    PC_CR1_C17 = 1;
    PC_CR2_C27 = 0;
    
    PC_DDR_DDR5 = 1;//light
    PC_CR1_C15 = 1;
    PC_CR2_C25 = 0;
    
    ADC_CSR &= ~BIT(6);
	ADC_CSR &= ~BIT(4);
	ADC_CR1 |= BIT(1);
	ADC_CR2 |= BIT(1);
	ADC_TDRL = 0x01;
    
    TEMP_HAT = 0;
    Temp_LIGHT = 0;
}

u16 TempGetAD(u8 chx)
{
    u16 ad_value;
    u8 i,h = 0,l = 0;
    ADC_CSR = chx;
    ADC_CR1 = 0x01;
    for(i=0;i<100;i++); 
    ADC_CR1 = ADC_CR1 | 0x01; 
    while((ADC_CSR & 0x80) == 0); 
    h = ADC_DRH;
    l = ADC_DRL;
    ad_value = (h<<8) + l;
    return ad_value;
}

void TempSetHat(u8 cmd) {
    TEMP_HAT = cmd;
}

void TempSetLight(u8 cmd) {
    Temp_LIGHT = cmd;
}















