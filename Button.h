


#ifndef BUTTON_H
#define BUTTON_H

#include "Type.h"

void ButtonInit(void);
u8 ButtonReadSwitch(void);

u8 ButtonReadWater(void);

u8 ButtonReadWaterFlag(void);
void  ButtonSetWaterFlag(u8 cmd);

u8 ButtonGetSwitch(void);

//����ѡ�񰴼�
u8 ButtonReadMode(void);
//��ƿ��ؼ�
u8  ButtonReadLight(void);
u8 ButtonGetLightFlag(void);

#endif
