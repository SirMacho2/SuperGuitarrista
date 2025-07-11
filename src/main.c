/*---------------------------------------------------------------------------------


    Simple tile mode 1 demo with png graphic
    -- alekmaul


---------------------------------------------------------------------------------*/
#include "menu.h"
#include "translate.h"
#include <stdio.h>
#include "commun.h"
#include "musicas.h"
#include "lista.h"

#include "lib/sprite_s.h"

enum States
{
    CREDITOS,
    MENU_INICIAL,
    MUSICA,
    MUSICAS,
    PAUSA,
    FIM_MUSICA,
};

#define SPRNUMBER 5
#define ALTURA_PISTA 62

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

extern char vu2_patterns, vu2_end;
extern char vu2_palette, vu2_palette_end;
// extern char vu2_map, vu2_map_end;

extern char tilfont, palfont;

extern char bt_f1_gfx, bt_f1_gfx_end;
extern char bt_f1_pal, bt_f1_pal_end;
extern char bt_f2_pal, bt_f2_pal_end;
extern char bt_f3_pal, bt_f3_pal_end;

Sprite nota;

AnimationFrame nota_f[2];
bool doDMAQUEUE;
u32 frame;

u16 Hudmap[32][32];

const Nota *notas;
const u32 *tempos;
const u16 *duracoes;
u16 tamanho_musica;
u8 velocidade;
const u8 *musica_xgm;
u16 delay;
u8 loops;

Musica musica = BACK_IN_BLACK;

bool notas_faltando = 1;

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

u8 i;
//---------------------------------------------------------------------------------
int main(void)
{
    doDMAQUEUE = FALSE;

    enum States state = CREDITOS;
    enum States state_anterior = -1;
    // Initialize SNES
    consoleInit();

    // Initialize text console with our font
    consoleSetTextGfxPtr(0x6800);
    consoleSetTextMapPtr(0x3000);
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

    s16 placar = 0;
    s8 consecutivas = 0;
    u8 multiplicador = 1;
    bool perdeu = FALSE;

    u32 init_time = getTick();
    u32 pause_time = 0;
    u32 final_time = 0xFFFFFFFF;
    bool start_music = 0;
    bool notas_faltando = 1;
    u16 nota_index = 0;
    bool resume = 0;

    frame = 0;
    while (1)
    {

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

                if (cursorY == 0)
                {
                    musica = SONIC;
                }
                // select back in black
                else if (cursorY == 1)
                {
                    musica = BACK_IN_BLACK;
                }
                else if (cursorY == 2)
                {
                    musica = STREETS_OF_RAGE;
                }
                else if (cursorY == 3)
                {
                    musica = GUILE_THEME;
                }
                else if (cursorY == 4)
                {
                    musica = ZELDA;
                }
                else if (cursorY == 5)
                {
                    musica = DRACULA;
                }
                else if (cursorY == 6)
                {
                    musica = TOP_GEAR;
                }
                else if (cursorY == 7)
                {
                    musica = ALTERED;
                }
                else if (cursorY == 8)
                {
                    musica = SMOOTH;
                }
                else if (cursorY == 9)
                {
                    musica = PHATASY;
                }

                VDP_clearTextLine(opcoes_musicas[cursorY].y);
                setFadeEffect(FADE_OUT);
                bgSetScroll(1, 0, 0);
            }
            break;
        case MUSICA:
            if (state_anterior != state)
            {
                state_anterior = state;

                setMode(BG_MODE1, BG3_MODE1_PRIORITY_HIGH);
                bgSetDisable(3);
                // Copy tiles to VRAM
                bgInitTileSet(1, &bg_musica_patterns, &bg_musica_palette, 0,
                              (&bg_musica_patterns_end - &bg_musica_patterns),
                              (&bg_musica_palette_end - &bg_musica_palette), BG_16COLORS, 0x4000);

                // WaitForVBlank();
                bgInitTileSet(0, &vu2_patterns, &vu2_palette, 2, 1824, 16 * 2, BG_16COLORS, 0x6000);

                // Copy Map to VRAM
                bgInitMapSet(1, &bg_musica_map, (&bg_musica_map_end - &bg_musica_map),
                             SC_32x32, 0x0000);

                bgSetMapPtr(0, 0x0000 + 2048, SC_32x32);

                int i, j;
                for (i = 0; i < 11; i++)
                {
                    for (j = 0; j < 11; j++)
                    {
                        Hudmap[i][j] = 0x2804;
                    }
                }
                dmaCopyVram((u8 *)Hudmap, 0x0000 + 2048, 0x400);
                setFadeEffect(FADE_IN);

                oamInitDynamicSprite(0x2000, 0x1000, 0, 0, OBJ_SIZE8_L32);
                // Init Sprites palette
                setPalette(&bt_f1_pal, 128 + 0 * 16, 16 * 2);

                setPalette(&bt_f2_pal, 128 + 1 * 16, 16 * 2);
                setPalette(&bt_f3_pal, 128 + 2 * 16, 16 * 2);

                // // clear bg1
                // VDP_clearTextArea(0, 0, 32, 28);
                // bgSetDisable(0);
                SPR_init();

                CriaLista_Nota();

                switch (musica)
                {
                case SONIC:
                    notas = notas_sonic;
                    tempos = tempos_sonic;
                    tamanho_musica = tamanho_sonic;
                    velocidade = velocidade_sonic;
                    duracoes = duracao_sonic;
                    // musica_xgm = sonic_music;
                    delay = delay_sonic;
                    loops = loops_sonic;
                    break;

                case BACK_IN_BLACK:
                    notas = notas_bib;
                    tempos = tempos_bib;
                    tamanho_musica = tamanho_bib;
                    velocidade = velocidade_bib;
                    duracoes = duracao_bib;
                    // musica_xgm = back_music;
                    delay = delay_bib;
                    loops = loops_bib;
                    break;

                case STREETS_OF_RAGE:
                    notas = notas_sor;
                    tempos = tempos_sor;
                    tamanho_musica = tamanho_sor;
                    velocidade = velocidade_sor;
                    duracoes = duracao_sor;
                    // musica_xgm = sor_music;
                    delay = delay_sor;
                    loops = loops_sor;
                    break;

                case GUILE_THEME:
                    notas = notas_guile;
                    tempos = tempos_guile;
                    tamanho_musica = tamanho_guile;
                    velocidade = velocidade_guile;
                    duracoes = duracao_guile;
                    // musica_xgm = guile_music;
                    delay = delay_guile;
                    loops = loops_guile;
                    break;

                case ZELDA:
                    notas = notas_zelda;
                    tempos = tempos_zelda;
                    tamanho_musica = tamanho_zelda;
                    velocidade = velocidade_zelda;
                    duracoes = duracao_zelda;
                    // musica_xgm = zelda_music;
                    delay = delay_zelda;
                    loops = loops_zelda;
                    break;

                case DRACULA:
                    notas = notas_castle;
                    tempos = tempos_castle;
                    tamanho_musica = tamanho_castle;
                    velocidade = velocidade_castle;
                    duracoes = duracao_castle;
                    // musica_xgm = castle_music;
                    delay = delay_castle;
                    loops = loops_castle;
                    break;

                case TOP_GEAR:
                    notas = notas_topGear;
                    tempos = tempos_topGear;
                    tamanho_musica = tamanho_topGear;
                    velocidade = velocidade_topGear;
                    duracoes = duracao_topGear;
                    // musica_xgm = topGear_music;
                    delay = delay_topGear;
                    loops = loops_topGear;
                    break;

                case ALTERED:
                    notas = notas_ateredBeast;
                    tempos = tempos_ateredBeast;
                    tamanho_musica = tamanho_ateredBeast;
                    velocidade = velocidade_ateredBeast;
                    duracoes = duracao_ateredBeast;
                    // musica_xgm = ateredBeast_music;
                    delay = delay_ateredBeast;
                    loops = loops_ateredBeast;
                    break;

                case SMOOTH:
                    notas = notas_smooth;
                    tempos = tempos_smooth;
                    tamanho_musica = tamanho_smooth;
                    velocidade = velocidade_smooth;
                    duracoes = duracao_smooth;
                    // musica_xgm = smooth_music;
                    delay = delay_smooth;
                    loops = loops_smooth;
                    break;

                case PHATASY:
                    notas = notas_phantasy;
                    tempos = tempos_phantasy;
                    tamanho_musica = tamanho_phantasy;
                    velocidade = velocidade_phantasy;
                    duracoes = duracao_phantasy;
                    // musica_xgm = phantasy_music;
                    delay = delay_phantasy;
                    loops = loops_phantasy;
                    break;

                default:
                    break;
                }

                nota_index = 0;
                placar = 0;
                consecutivas = 0;
                multiplicador = 1;

                init_time = frame * 5;
                start_music = 0;
                pause_time = 0;
                notas_faltando = 1;
            }
            else
            {
                if (frame * 5 - init_time >= delay && !start_music)
                {
                    // XGM_startPlay(musica_xgm);
                    // XGM_setLoopNumber(loops);

                    start_music = 1;
                }
                while (notas_faltando && (frame * 5 - init_time >= tempos[nota_index]))
                {
                    if (notas[nota_index] & AMARELA)
                    {
                        Insere_Nota(SPR_add(AMARELO_X_INICIO, ALTURA_PISTA, TILE_ATTR(1, 2, 0, 0), &bt_f1_gfx), AMARELO_X_INICIO, ALTURA_PISTA, AMARELA);
                        // if (duracoes[nota_index] > 0)
                        // {
                        //     Insere_Barra(SPR_addSprite(&barraY, AMARELO_B_X, ALTURA_PISTA, TILE_ATTR(PAL2, FALSE, FALSE, FALSE)), AMARELO_B_X_INICIO, ALTURA_PISTA, AMARELA, duracoes[nota_index]);
                        // }
                    }
                    else if (notas[nota_index] & VERDE)
                    {
                        Insere_Nota(SPR_add(VERDE_X, ALTURA_PISTA, TILE_ATTR(0, 2, 0, 0), &bt_f1_gfx), VERDE_X, ALTURA_PISTA, VERDE);
                        // if (duracoes[nota_index] > 0)
                        // {
                        //     Insere_Barra(SPR_addSprite(&barraG, VERDE_B_X, ALTURA_PISTA, TILE_ATTR(PAL2, FALSE, FALSE, FALSE)), VERDE_B_X, ALTURA_PISTA, VERDE, duracoes[nota_index]);
                        // }
                    }
                    else if (notas[nota_index] & VEMELHA)
                    {
                        Insere_Nota(SPR_add(VEMELHO_X_INICIO, ALTURA_PISTA, TILE_ATTR(2, 2, 0, 0), &bt_f1_gfx), VEMELHO_X_INICIO, ALTURA_PISTA, VEMELHA);
                        // if (duracoes[nota_index] > 0)
                        // {
                        //     Insere_Barra(SPR_addSprite(&barraR, VEMELHO_B_X, ALTURA_PISTA, TILE_ATTR(PAL2, FALSE, FALSE, FALSE)), VEMELHO_B_X_INICIO, ALTURA_PISTA, VEMELHA, duracoes[nota_index]);
                        // }
                    }
                    if (nota_index < tamanho_musica - 1)
                    {
                        nota_index++;
                        consoleNocashMessage("nota indexx %d de %d \n", nota_index, tamanho_musica - 1);
                    }
                    else
                    {
                        notas_faltando = 0;
                        final_time = frame * 5;
                        break;
                    }
                }
                if (notas_faltando)
                {
                    atualizaPosicao_Nota(velocidade, 0);
                    SPR_update();
                    doDMAQUEUE = TRUE;
                }
            }
            break;
        }
        WaitForVBlank();
        if (doDMAQUEUE)
        {
            oamVramQueueUpdate();
            doDMAQUEUE = FALSE;
        }
        frame++;
    }
    return 0;
}