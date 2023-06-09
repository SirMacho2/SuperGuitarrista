/*---------------------------------------------------------------------------------


    Simple tile mode 1 demo with png graphic
    -- alekmaul


---------------------------------------------------------------------------------*/
#include <snes.h>
#include "menu.h"
#include "translate.h"
#include <stdio.h>
#include "commun.h"

enum States
{
    CREDITOS,
    MENU_INICIAL,
    MUSICA,
    MUSICAS,
    PAUSA,
    FIM_MUSICA,
};

extern char k7_patterns, k7_patterns_end;
extern char k7_palette, k7_palette_end;
extern char k7_map, k7_map_end;

extern char creditos_patterns, creditos_patterns_end;
extern char creditos_palette, creditos_palette_end;
extern char creditos_map, creditos_map_end;

extern char concert_patterns, concert_patterns_end;
extern char concert_palette, concert_palette_end;
extern char concert_map, concert_map_end;

extern char bg_musica_patterns, bg_musica_patterns_end;
extern char bg_musica_palette, bg_musica_palette_end;
extern char bg_musica_map, bg_musica_map_end;

extern char tilfont, palfont;

extern char btY_gfx, btY_gfx_end;
extern char btY_pal, btY_pal_end;

void setFontColour(u16 color)
{
    u16 palfont2[16];
    int i;
    for (i = 0; i < 16; i++)
    {
        palfont2[i] = color;
    }
    setPalette((unsigned char *)palfont2, 32, 32);
}

//---------------------------------------------------------------------------------
int main(void)
{

    enum States state = CREDITOS;
    enum States state_anterior = -1;
    // Initialize SNES
    consoleInit();

    // Initialize text console with our font
    consoleSetTextVramBGAdr(0x6800);
    consoleSetTextVramAdr(0x3000);
    consoleSetTextOffset(0x0100);

    consoleInitText(2, 16 * 2, &tilfont, (unsigned char *)palfont);

    // Init background
    bgSetGfxPtr(0, 0x2000);
    bgSetMapPtr(0, 0x6800, SC_32x32);

    // Now Put in 16 color mode and disable other BGs except 1st one
    setMode(BG_MODE1, 0);
    // bgSetDisable(1);
    bgSetDisable(2);
    setScreenOn();

    // Wait for nothing :P
    u16 scrX = 0, scrY = 0;
    u16 pad0, menu_movendo = 0;
    u16 cursorY = 0;
    u16 creditos_time = 0;

    u16 sprite_x = 0;
    u16 sprite_y = 0;

    u16 sprite_offset = 0;
    while (1)
    {
        // Refresh pad values
        scanPads();

        // Get current #0 pad
        pad0 = padsCurrent(0);

        switch (state)
        {
        case CREDITOS:

            if (state_anterior != state)
            {
                state_anterior = state;
                bgInitTileSet(1, &creditos_patterns, &creditos_palette, 0,
                              (&creditos_patterns_end - &creditos_patterns),
                              (&creditos_palette_end - &creditos_palette), BG_16COLORS, 0x4000);

                // Copy Map to VRAM
                bgInitMapSet(1, &creditos_map, (&creditos_map_end - &creditos_map), SC_32x32, 0x0000);
                setScreenOn();
                creditos_time = getTick();
            }
            if (getTick() - creditos_time > 900)
            {
                setFadeEffect(FADE_OUT);
                state = MENU_INICIAL;
            }
            break;
        case MENU_INICIAL:
            if (state_anterior != state)
            {
                state_anterior = state;
                bgInitTileSet(1, &concert_patterns, &concert_palette, 0,
                              (&concert_patterns_end - &concert_patterns),
                              (&concert_palette_end - &concert_palette), BG_16COLORS, 0x4000);

                // Copy Map to VRAM
                bgInitMapSet(1, &concert_map, (&concert_map_end - &concert_map), SC_32x32, 0x0000);
                mostra_menu_inicial();
                setFontColour(0x7fff);
                setFadeEffect(FADE_IN);
            }
            if (pad0 & KEY_START)
            {
                // XGM_startPlayPCM(SFX_CLICK, 1, SOUND_PCM_CH2);
                // J1S = 0;
                state = MUSICAS;
                // SPR_releaseSprite(cursor);
                VDP_clearTextLine(14);
                setFadeEffect(FADE_OUT);
            }
            break;
        case MUSICAS:
            if (state_anterior != state)
            {
                state_anterior = state;

                cursorY = 0;
                menu_movendo = 0;
                // Copy tiles to VRAM
                bgInitTileSet(1, &k7_patterns, &k7_palette, 0, (&k7_patterns_end - &k7_patterns),
                              (&k7_palette_end - &k7_palette), BG_16COLORS, 0x4000);

                // Copy Map to VRAM
                bgInitMapSet(1, &k7_map, (&k7_map_end - &k7_map), SC_32x32, 0x0000);

                setFontColour(0xcb7);
                setFadeEffect(FADE_IN);
                VDP_drawText(opcoes_musicas[cursorY].texto, opcoes_musicas[cursorY].x,
                             opcoes_musicas[cursorY].y);
            }
            if ((pad0 & KEY_DOWN) && menu_movendo == 0)
            {
                menu_movendo = 1;
                if (cursorY < NUM_MUSICAS - 1)
                {
                    cursorY++;
                }
                else
                {
                    cursorY = 0;
                }
                VDP_clearTextArea(0, 12, 31, 1);
            }
            if ((pad0 & KEY_UP) && menu_movendo == 0)
            {
                menu_movendo = -1;
                if (cursorY > 0)
                {
                    cursorY--;
                }
                else
                {
                    cursorY = NUM_MUSICAS - 1;
                }
                VDP_clearTextArea(0, 12, 31, 1);
            }
            if (menu_movendo)
            {
                scrY = scrY + 8 * menu_movendo;
                bgSetScroll(1, scrX, scrY);
                if (scrY == 128 || scrY == -128)
                {
                    scrY = 0;
                    menu_movendo = 0;
                    VDP_drawText(opcoes_musicas[cursorY].texto, opcoes_musicas[cursorY].x,
                                 opcoes_musicas[cursorY].y);
                    setScreenOn();
                }
            }
            if (pad0 & KEY_START)
            {
                state = MUSICA;
                // SPR_releaseSprite(cursor);
                VDP_clearTextLine(opcoes_musicas[cursorY].y);
                setFadeEffect(FADE_OUT);
                bgSetScroll(1, 0, 0);
            }
            break;
        case MUSICA:
            if (state_anterior != state)
            {
                state_anterior = state;
                // Copy tiles to VRAM
                bgInitTileSet(1, &bg_musica_patterns, &bg_musica_palette, 0,
                              (&bg_musica_patterns_end - &bg_musica_patterns),
                              (&bg_musica_palette_end - &bg_musica_palette), BG_16COLORS, 0x4000);

                // Copy Map to VRAM
                bgInitMapSet(1, &bg_musica_map, (&bg_musica_map_end - &bg_musica_map),
                             SC_32x32, 0x0000);
                setFadeEffect(FADE_IN);

                VDP_clearTextArea(0, 0, 32, 28);

                oamInitDynamicSprite(0x2000, 0x2000, 0x2000, 0x2000, OBJ_SIZE8_L32);

                oambuffer[0].oamx = sprite_x;
                oambuffer[0].oamy = sprite_y;
                oambuffer[0].oamframeid = 0;
                oambuffer[0].oamrefresh = 1;

                SpriteAttr teste;
                teste.pallNum = 0;
                teste.priority = 2;
                teste.vflip = 0;
                teste.lastBit = 0;
                teste.hflip = 0;
                consoleDrawText(1, 1, " attr : %u", teste);

                oambuffer[0].oamattribute = (u8)teste; // palette 0 of sprite and sprite 16x16 and priority 2
                oambuffer[0].oamgraphics = &btY_gfx;
                oamDynamic32Draw(0);

                setPalette(&btY_pal, 16 * 8, (&btY_pal_end - &btY_pal));
            }
            else
            {
                if (pad0 & KEY_DOWN)
                {
                    sprite_y++;
                    oambuffer[0].oamrefresh = 1;
                }
                else if (pad0 & KEY_UP)
                {
                    sprite_y--;
                    oambuffer[0].oamrefresh = 1;
                }
                if (pad0 & KEY_RIGHT)
                {
                    sprite_x++;
                    oambuffer[0].oamrefresh = 1;
                }
                else if (pad0 & KEY_LEFT)
                {
                    sprite_x--;
                    oambuffer[0].oamrefresh = 1;
                }
                if (sprite_y > 70)
                {
                    oambuffer[0].oamframeid = (sprite_y - 70) / 20;
                    oambuffer[0].oamrefresh = 1;
                }
                oambuffer[0].oamx = sprite_x;
                oambuffer[0].oamy = sprite_y;
                oamDynamic32Draw(0);
                oamInitDynamicSpriteEndFrame();
                oamVramQueueUpdate();
            }
            break;
        }

        WaitForVBlank();
    }
    return 0;
}