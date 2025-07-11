#include "sprite_s.h"

static u8 oamUsed[128];

static int SPR_get_idx()
{
    int i;
    for (i = 0; i < 128; i++)
    {
        if (oamUsed[i] == 0)
        {
            break;
        }
    }
    return i;
}

void SPR_init()
{
    int i;
    for (i = 0; i < 128; i++)
    {
        oamUsed[i] = 0;
    }
}

void SPR_setFrame(u8 idx, u16 frameNumber)
{
    oambuffer[idx].oamframeid = frameNumber;
    oambuffer[idx].oamrefresh = 1;
}

s8 SPR_add(s16 oamx, s16 oamy, u8 oamattribute, u8 *tileset)
{
    int idx = SPR_get_idx();
    if (idx >= 0)
    {
        oambuffer[idx].oamx = oamx;
        oambuffer[idx].oamy = oamy;
        oambuffer[idx].oamframeid = 0;
        oambuffer[idx].oamrefresh = 1;

        oambuffer[idx].oamattribute = oamattribute;
        oambuffer[idx].oamgraphics = tileset;

        oamUsed[idx] = 1;
        consoleNocashMessage("tile idx %x\n", idx);
    }
    return idx;
}

void SPR_release(u8 idx)
{
    oambuffer[idx].oamx = -50;
    oamUsed[idx] = 0;
}

void SPR_update()
{
    int i;
    for (i = 0; i < 128; i++)
    {
        if (oamUsed[i] == 1)
        {
            oamDynamic32Draw(i);
        }
    }
    oamInitDynamicSpriteEndFrame();
}