
#ifndef LED_H 
#define LED_H 

#include "Type.h"

void LedInit(void);
void LedSetSwitch(u8 cmd);
u8 LedGetSwitch(void);

//ledָʾ������
void LedSetLight(u8 cmd);
//����ģʽ������
void LedSetMode(u8 cmd);
//û��ˮ����˸
void LedSwitchService(void);
void LedSedNeedwater(u8 cmd);

#endif
