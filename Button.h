


#ifndef BUTTON_H
#define BUTTON_H

#include "Type.h"

void ButtonInit(void);
u8 ButtonReadSwitch(void);
u8 ButtonReadSpecies(void);
u8 ButtonReadPeriod(void);

u8 ButtonReadSpeciesFlag(void);
u8 ButtonReadPeriodFlag(void);

u8 ButtonReadWater(void);

u8 ButtonReadWaterFlag(void);
void  ButtonSetWaterFlag(u8 cmd);

#endif
