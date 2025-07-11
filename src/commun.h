#ifndef __COMMUN_H__
#define __COMMUN_H__

//(vhoopppc v : vertical flip h: horizontal flip o: priority bits p: palette num c : last byte of tile num)
#include <snes.h>

/**
 *  \brief
 *      Bit shift for the tile priority attribute in tilemap data.
 */
#define TILE_ATTR_PRIORITY_SFT 4
/**
 *  \brief
 *      Bit shift for the tile palette attribute in tilemap data.
 */
#define TILE_ATTR_PALETTE_SFT 1
/**
 *  \brief
 *      Bit shift for the tile V flip attribute in tilemap data.
 */
#define TILE_ATTR_VFLIP_SFT 7
/**
 *  \brief
 *      Bit shift for the tile H flip attribute in tilemap data.
 */
#define TILE_ATTR_HFLIP_SFT 6

#define TILE_ATTR(pal, prio, flipV, flipH) (((flipH) << TILE_ATTR_HFLIP_SFT) + ((flipV) << TILE_ATTR_VFLIP_SFT) + ((pal) << TILE_ATTR_PALETTE_SFT) + ((prio) << TILE_ATTR_PRIORITY_SFT))
typedef struct spriteAttr
{
    u8 lastBit : 1;
    u8 pallNum : 3;
    u8 priority : 2;
    u8 hflip : 1;
    u8 vflip : 1;
} SpriteAttr;

extern u32 frame;

#endif