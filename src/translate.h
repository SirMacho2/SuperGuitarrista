#ifndef __TRANSLATE_H__
#define __TRANSLATE_H__

#include <snes.h>

void VDP_drawText(char *text, s16 x, s16 y);
s16 VDP_clearTextArea(s16 x, s16 y, u8 width, u8 height);
void VDP_clearTextLine();
u16 getTick();
#endif