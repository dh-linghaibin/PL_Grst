
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
        if(ButtonGetSwitch() == 0x80) {//判断是否已经打开
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
                    if(TimeGetLightFlag() < GrstReadLightTime() ) {//补光LED灯（大灯）
                        //open light 
                        TempSetLight(1);
                    } else if(TimeGetLightFlag() < 3600+GrstReadLightTime()) {
                        //cloose
                        TempSetLight(0);
                    } else if(TimeGetLightFlag() > 3600+GrstReadLightTime()){
                        TimeSetLightFlag(1);//clear
                    }
                    //weater arrived
                    if(TimeGetWaterFlag() < GrstReadWaterTime()) {//洒水的水泵（不是营养泵）
                        //open Water
                        PumpSetWater(1);  
                    } else if(TimeGetWaterFlag() < GrstReadWaterTime()+7200) {
                        //cloose
                        PumpSetWater(0);
                    } else if(TimeGetWaterFlag() > GrstReadWaterTime()+7200){
                        TimeSetWaterFlag(1);//clear
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
        ButtonReadSwitch();//读取开关
        bun_bit = ButtonReadMode();//设置模式
        ButtonReadLight();//灯设置键
        if(bun_bit >= 1) {
            switch( bun_bit ) {
                case 1:
                GrstSetWaterTime(60);
                GrstSetLightTime(5040);//设置灯亮的时间
                break;
                case 2:
                GrstSetWaterTime(60);
                GrstSetLightTime(3600);//设置灯亮的时间
                break;
                case 3:
                GrstSetWaterTime(60);
                GrstSetLightTime(7200);//设置灯亮的时间
                break;
                default:
                break;
            }
            TimeSetLightFlag(1);//clear
            TimeSetWaterFlag(1);//clear
        }
    }
}
