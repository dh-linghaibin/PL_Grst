
#ifndef GRSTTIME_H
#define GRSTTIME_H

#include "Type.h"

void GrsttimeInit(void);
u16 GrstReadLightTime(void);
void GrstSetLightTime(u16 cmd);
u16 GrstReadWaterTime(void);
void GrstSetWaterTime(u16 cmd);

#endif
