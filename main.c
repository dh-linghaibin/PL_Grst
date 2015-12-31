
#include "Sys.h"
#include "Button.h"
#include "Led.h"
#include "Temp.h"
#include "Pump.h"
#include "Time.h"
#include "Eeprom.h"

int main(void)
{
    SysInit();
    EeepromInit();
    TimeInit();
    ButtonInit();
    LedInit();
    TempInit();
    PumpInit();
    INTEN
    while(1) {
        if(LedGetSwitch() == 0x80) {
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
                    }
                }
                    
                //Read
                if(TimeGetNutritionFlag() > 2){
                    PumpSetNutrition(0);//close 
                    TimeSetNutritionFlag(0);//end
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
                    if(TimeGetLightFlag() > 5) {
                        if(TimeGetLightFlag() > 5+5) {
                            TimeSetLightFlag(1);//clear
                            //cloose
                            TempSetLight(0);
                        } else if(TimeGetLightFlag() > 5) {
                             //open light 
                            TempSetLight(1);
                        }
                    }
                    //weater arrived
                    if(TimeGetWaterFlag() > 2) {
                        
                        
                        if(TimeGetWaterFlag() > 2+2) {
                            TimeSetWaterFlag(1);//clear
                            //cloose
                            PumpSetWater(0);
                        } else if(TimeGetWaterFlag() > 2) {
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
            }
        } else {
            if(TimeGetSecFlag() == 0x80) {
                TimeSetSecFlag(0x00);
                //cloose
                TimeSetLightFlag(1);//clear
                TimeSetWaterFlag(1);//clear
                TempSetLight(0);
                PumpSetWater(0);
                TempSetHat(0);
                PumpSetNutrition(0);
            }
        }
       if(ButtonReadSwitch() == 0x80) {
            LedSetSwitch();
        }
    }
}
