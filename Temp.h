
#ifndef TEMP_H
#define TEMP_H

#include "Type.h"

#define TEMP_CH 4

void TempInit(void);
u16 TempGetAD(u8 chx);
void TempSetHat(u8 cmd);
void TempSetLight(u8 cmd);

#endif
