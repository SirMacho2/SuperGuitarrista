#ifndef __SPRITE_S_H__
#define __SPRITE_S_H__

#include <snes.h>

typedef struct AnimationFrame
{
    u8 timer;
    s8 *tilset;
    u16 tilesetLen;
} AnimationFrame;

typedef struct Sprite
{
    u16 status;
    u16 visibility;
    s16 animInd;
    s16 frameInd;
    u16 timer;
    s16 x;
    s16 y;
    s16 depth;
    u16 attribut;
    u32 data;
    AnimationFrame *frame;
    u16 framesLen;
} Sprite;

void SPR_setFrame(u8 idx, u16 frameNumber);
void SPR_release(u8 idx);
s8 SPR_add(s16 oamx, s16 oamy, u8 oamattribute, u8 *tileset);
void SPR_update();

#endif