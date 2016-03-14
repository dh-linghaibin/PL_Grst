
#ifndef LED_H 
#define LED_H 

#include "Type.h"

void LedInit(void);
void LedSetSwitch(u8 cmd);
u8 LedGetSwitch(void);

//led指示灯设置
void LedSetLight(u8 cmd);
//三种模式灯设置
void LedSetMode(u8 cmd);
//没有水灯闪烁
void LedSwitchService(void);
void LedSedNeedwater(u8 cmd);

#endif
