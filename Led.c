

#include "Led.h"
#include "Button.h"

//指示led区域
#define LED_SWITCH      PC_ODR_ODR3 
#define LED_LIGHT       PC_ODR_ODR2
#define LED_SEEDLING    PC_ODR_ODR4
#define LED_GROW        PC_ODR_ODR5
#define LED_FRUIT       PC_ODR_ODR6



void LedInit(void) {
    PC_DDR_DDR2 = 1;//灯
    PC_CR1_C12 = 1;
    PC_CR2_C22 = 0;
    
    PC_DDR_DDR3 = 1;//开关
    PC_CR1_C13 = 1;
    PC_CR2_C23 = 0;
    
    PC_DDR_DDR4 = 1;//幼苗
    PC_CR1_C14 = 1;
    PC_CR2_C24 = 0;
    
    PC_DDR_DDR5 = 1;//生长
    PC_CR1_C15 = 1;
    PC_CR2_C25 = 0;
    
    PC_DDR_DDR6 = 1;//花果
    PC_CR1_C16 = 1;
    PC_CR2_C26 = 0;

}


//没有水后提醒
static u8 led_need_water = 0;

void LedSedNeedwater(u8 cmd) {
    led_need_water = cmd;
}
//没有水灯闪烁
void LedSwitchService(void) {
    static u16 count = 0;
    static u8 bit = 0;
    if(led_need_water == 1) {
        count++;
        if(count > 50000) {
            count = 0;
            if(bit == 0) {
                bit = 1;
                LED_SWITCH = 1;
            } else {
                bit = 0;
                LED_SWITCH = 0;
            }
        }
    }
}

void LedSetSwitch(u8 cmd) {
    if(cmd == 0) {
        LED_SWITCH = 0;
    } else {
        LED_SWITCH = 1;
    }
}


//led指示灯设置
void LedSetLight(u8 cmd) {
    if(cmd == 0) {
        LED_LIGHT = 0;
    } else {
        LED_LIGHT = 1;
    }
}
//三种模式灯设置
void LedSetMode(u8 cmd) {
    switch(cmd) {
        case 0:LED_SEEDLING = 0;LED_GROW = 1;LED_FRUIT = 1;
        break;
        case 1:LED_SEEDLING = 1;LED_GROW = 0;LED_FRUIT = 1;
        break;
        case 2:LED_SEEDLING = 1;LED_GROW = 1;LED_FRUIT = 0;
        break;
        default:break;
    }
}


