

#include "Temp.h"
#include "Button.h"

#define TEMP_HAT        PB_ODR_ODR1
#define Temp_LIGHT      PB_ODR_ODR2

void TempInit(void) {
    PB_DDR_DDR3 = 0; //temp 温度传感器
    PB_CR1_C13 = 0;
    PB_CR2_C23 = 0;
    
    PB_DDR_DDR1 = 1;//add hat 加热
    PB_CR1_C11 = 1;
    PB_CR2_C21 = 0;
    
    PB_DDR_DDR2 = 1;//light 补光灯
    PB_CR1_C12 = 1;
    PB_CR2_C22 = 0;
    
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
    if(ButtonGetLightFlag() == 1) {
        if(ButtonGetSwitch() == 0x80) {//判断是否已经打开
            Temp_LIGHT = cmd;
        }
    } else {
        Temp_LIGHT = 0;
    }
}















