

#ifndef TIME_H
#define TIME_H

#include "Type.h"

void TimeInit(void);
u8 TimeGetSecFlag(void);
void TimeSetSecFlag(u8 cmd);

u16 TimeGetLightFlag(void);
void TimeSetLightFlag(u8 cmd);

u16 TimeGetWaterFlag(void);
void TimeSetWaterFlag(u8 cmd);

u16 TimeGetNutritionFlag(void);
void TimeSetNutritionFlag(u8 cmd);

#endif