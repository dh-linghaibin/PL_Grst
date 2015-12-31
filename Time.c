

#include "Time.h"



void TimeInit(void) {
    TIM4_IER = 0x00;   
    TIM4_EGR = 0x01;
    TIM4_PSCR = 0x07;
    TIM4_ARR = 0xFA;
    TIM4_IER = 0x01;
    TIM4_CR1 = 0x01;  
}
/*

*/
static u8 time_sec_flag = 0;

u8 TimeGetSecFlag(void) {
    return time_sec_flag;
}

void TimeSetSecFlag(u8 cmd) {
    time_sec_flag = cmd;
}
/*
light---------------------
*/
static u16 time_light_flag = 1;

u16 TimeGetLightFlag(void) {
    return time_light_flag;
}

void TimeSetLightFlag(u8 cmd) {
    time_light_flag = cmd;
}
/*
water---------------------
*/
static u16 time_water_flag = 1;

u16 TimeGetWaterFlag(void) {
    return time_water_flag;
}

void TimeSetWaterFlag(u8 cmd) {
    time_water_flag = cmd;
}
/*
nutrition---------------------
*/
static u16 time_nutrition_flag = 0;

u16 TimeGetNutritionFlag(void) {
    return time_nutrition_flag;
}

void TimeSetNutritionFlag(u8 cmd) {
    time_nutrition_flag = cmd;
}

static u8 time_sec = 0;
static u8 time_min = 0;
static u8 time_hou = 0;
static u8 time_day = 0;

#pragma vector=0x19
__interrupt void TIM4_UPD_OVF_IRQHandler(void)
{
    static u16 count_time = 0;
    
    TIM4_SR = 0x00;
    
    if(count_time < 500) {
        count_time++;
    } else {
        count_time = 0;
        time_sec_flag = 0x80;
        if(time_light_flag > 0) {
            time_light_flag++;
        }
        if(time_water_flag > 0) {
            time_water_flag++;
        }
        if(time_nutrition_flag > 0) {
            time_nutrition_flag++;
        }
        if(time_sec < 60) {
            time_sec++;
        } else {
            time_sec = 0;
            if(time_min < 60) {
                time_min++;
            } else {
                time_min = 0;
                if(time_hou < 24) {
                    time_hou++;
                } else {
                    time_hou = 0;
                    if(time_day < 14) {
                        time_day++;
                    } else {
                        //tow week arrived
                    }
                }
            }
        }
    }
    
    return;
}