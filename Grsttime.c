

#include "Grsttime.h"
#include "Eeprom.h"

//µÆ¹â¿ØÖÆ
static u16 grst_light_time = 3600;
static u16 grst_water_time = 7200;

void GrsttimeInit(void) {
    if(EepromRead(30) != 0x55) {
        EepromWrite(30,0x55);
        EepromWrite(31,(u8)grst_light_time);
        EepromWrite(32,(u8)(grst_light_time >> 8));
        EepromWrite(33,(u8)grst_water_time);
        EepromWrite(34,(u8)(grst_water_time >> 8));
    }
    grst_light_time = EepromRead(31);
    grst_light_time |= EepromRead(32) << 8;
    grst_water_time = EepromRead(33); 
    grst_water_time |= EepromRead(34) << 8;    
}

u16 GrstReadLightTime(void) {
    return grst_light_time;
}

void GrstSetLightTime(u16 cmd) {
    grst_light_time = cmd;
    EepromWrite(31,(u8)grst_light_time);
    EepromWrite(32,(u8)(grst_light_time >> 8));
}


u16 GrstReadWaterTime(void) {
    return grst_water_time;
}

void GrstSetWaterTime(u16 cmd) {
    grst_water_time = cmd;
    EepromWrite(33,(u8)grst_water_time);
    EepromWrite(34,(u8)(grst_water_time >> 8));
}
