
#ifndef LED_H 
#define LED_H 

#include "Type.h"

void LedInit(void);
void LedSetSwitch(void);

void LedSetSpecies(u8 cmd);
void LedSetPeriod(u8 cmd);

u8 LedGetSwitch(void);


#endif
