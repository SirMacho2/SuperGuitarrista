#include "sprite_s.h"

s8 SPR_changeFrame(Sprite *s, s16 frameNumber, u16 address)
{
    u8 *source = NULL;
    u16 size;
    u16 i;

    if (frameNumber > s->framesLen)
    {
        return FALSE;
    }

    source = s->frame[frameNumber].tilset;
    size = s->frame[frameNumber].tilesetLen;

    s->frame[frameNumber].timer = 0;

    consoleNocashMessage("3 - tileset addres %p, size: %u\n", source, size);
    dmaCopySpr32Vram(source, 0);

    oamSet(0, s->x, s->y, s->depth, 0, 0, 0, 0);
    return TRUE;
}