#include "translate.h"

void VDP_drawText(char *text, s16 x, s16 y)
{
    consoleDrawText(x, y, text);
}

void VDP_clearTextLine(u8 line)
{
    VDP_clearTextArea(0, line, 32, 1);
}

s16 VDP_clearTextArea(s16 x, s16 y, u8 width, u8 height)
{
    char text[33] = "                                \0";
    if (width < 33 && height < 33)
    {
        u8 i;
        text[width] = '\0';
        for (i = y; i < (y + height); i++)
        {
            consoleDrawText(x, i, text);
        }
    }
    else
    {
        return -1;
    }
}

u16 getTick()
{
    return snes_vblank_count * 5;
}