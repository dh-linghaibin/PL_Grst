
#include "Sys.h"
#include "Button.h"
#include "Led.h"
#include "Temp.h"
#include "Pump.h"
#include "Time.h"
#include "Eeprom.h"
#include "Grsttime.h"

int main(void)
{
    SysInit();
    EeepromInit();
    TimeInit();
    ButtonInit();
    LedInit();
    TempInit();
    PumpInit();
    GrsttimeInit();
    INTEN                                                                                    
    while(1) {
        u8 bun_bit = 0;
        if(LedGetSwitch() == 0x80) {
            LedSwitchService();
            if(TimeGetSecFlag() == 0x80) {
                TimeSetSecFlag(0x00);
                //Read water level 
                if(ButtonReadWater() == 0x80) {
                    LedSedNeedwater(1);
                    if(ButtonReadWaterFlag() == 0) {
                        ButtonSetWaterFlag(1);
                    }
                } else {
                    if(ButtonReadWaterFlag() == 1) {
                        ButtonSetWaterFlag(0);
                        TimeSetNutritionFlag(1);//statrt
                        PumpSetNutrition(0);//open   //test
                        //cloose Remind add water
                        LedSedNeedwater(0);
                        TimeSetDay(0x00);//clear
                    }
                }    
                //Read
                if(TimeGetNutritionFlag() > 2){ //时间1
                    PumpSetNutrition(0);//close 
                    TimeSetNutritionFlag(0);//end   2016/1/19/ for test so clear
                }
                //Read day
                if(TimeGetDay() >= 14) {
                    TimeSetDay(0x00);//clear
                    //Remind add water
                    LedSedNeedwater(1);
                }
                if(ButtonReadWaterFlag() == 0) { 
                    //Read temperature
                    if(TempGetAD(TEMP_CH) < 29137) {
                        //open add hat
                        TempSetHat(1);
                    } else {
                        //cloose add hat
                        TempSetHat(0);
                    }
                    //light arrived
                    if(TimeGetLightFlag() > 7200) {//补光LED灯（大灯）
                        static u8 light_bit = 0;
                        if(TimeGetLightFlag() > 7200+GrstReadLightTime() ) {
                            TimeSetLightFlag(1);//clear
                            //cloose
                            if(light_bit == 1) {
                                light_bit = 0;
                                TempSetLight(0);
                            }
                        } else if(TimeGetLightFlag() > 7200) {
                             //open light 
                            if(light_bit == 0) {
                                light_bit = 1;
                                TempSetLight(1);
                            }
                        }
                    }
                    //weater arrived
                    if(TimeGetWaterFlag() > GrstReadWaterTime()) {//洒水的水泵（不是营养泵）
                        if(TimeGetWaterFlag() > GrstReadWaterTime()+60) {//打开多久后关闭
                            TimeSetWaterFlag(1);//clear
                            //cloose
                            PumpSetWater(0);
                        } else if(TimeGetWaterFlag() > GrstReadWaterTime()) {//打开的时间
                            //open Water
                            PumpSetWater(1);
                        }
                    }
                } else {
                    //cloose
                    TimeSetLightFlag(1);//clear
                    TimeSetWaterFlag(1);//clear
                    TempSetLight(0);
                    PumpSetWater(0);
                    TempSetHat(0);
                }
            }
            if(ButtonReadSpecies() > 0x00) {
                LedSetSpecies(ButtonReadSpeciesFlag());     
            } 
            if(ButtonReadPeriod() > 0x00) {
                LedSetPeriod(ButtonReadPeriodFlag());
                if(ButtonReadPeriodFlag() == 1) {
                    GrstSetWaterTime(3600);
                    GrstSetLightTime(3600);//1512
                } else if(ButtonReadPeriodFlag() == 2){
                    GrstSetWaterTime(7200);
                    GrstSetLightTime(3000);//1800
                }
            }
        } else {
            if(TimeGetSecFlag() == 0x80) {
                TimeSetSecFlag(0x00);
                //Read water level 
                if(ButtonReadWater() == 0x80) {
                    if(ButtonReadWaterFlag() == 0) {
                        ButtonSetWaterFlag(1);
                    }
                } else {
                    if(ButtonReadWaterFlag() == 1) {
                        ButtonSetWaterFlag(0);
                        TimeSetNutritionFlag(1);//statrt
                        PumpSetNutrition(1);//open 
                        //cloose Remind add water
                        LedSedNeedwater(0);
                        TimeSetDay(0x00);//clear
                    }
                }    
                //Read
                if(TimeGetNutritionFlag() > 2){
                    PumpSetNutrition(0);//close 
                    TimeSetNutritionFlag(0);//end
                }
                //Read day
                if(TimeGetDay() >= 14) {
                    TimeSetDay(0x00);//clear
                    //Remind add water
                    LedSedNeedwater(1);
                }
                
                //cloose
                TimeSetLightFlag(1);//clear
                TimeSetWaterFlag(1);//clear
                PumpSetNutrition(0);//close 
                TempSetLight(0);
                PumpSetWater(0);
                TempSetHat(0);
            }
        }
        bun_bit = ButtonReadSwitch();
       if(bun_bit == 0x80) {
            LedSetSwitch();
            TimeSetLightFlag(7201);//clear
            TimeSetWaterFlag(GrstReadWaterTime()+1);//clear
       } else if(bun_bit == 0x90) {
            static u8 bit = 0;
            if(bit == 0) {
                bit = 1;
                TempSetLight(1);
            } else {
                bit = 0;
                TempSetLight(0);
            }
       }
    }
}
