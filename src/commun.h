#ifndef __COMMUN_H__
#define __COMMUN_H__

//(vhoopppc v : vertical flip h: horizontal flip o: priority bits p: palette num c : last byte of tile num)
#include <snes.h>
typedef struct spriteAttr
{
    u8 lastBit : 1;
    u8 pallNum : 3;
    u8 priority : 2;
    u8 hflip : 1;
    u8 vflip : 1;
} SpriteAttr;

#endif