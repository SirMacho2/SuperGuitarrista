#ifndef __MUSICAS_H__
#define __MUSICAS_H__

#include <snes.h>
#define FIX16

#define VEMELHO_X 231
#define VEMELHO_X_INICIO 130
#define VERDE_X 122
#define AMARELO_X 49
#define AMARELO_X_INICIO 110

#define VEMELHO_B_X VEMELHO_X + 17
#define VEMELHO_B_X_INICIO VEMELHO_X_INICIO + 17
#define VERDE_B_X VERDE_X + 17
#define AMARELO_B_X AMARELO_X + 16
#define AMARELO_B_X_INICIO AMARELO_X_INICIO + 17
#define TAMANHO_SONIC 434

typedef enum // Cria uma ENUM para indetificar uma nota
{
    AMARELA = 1,
    VERDE = 2,
    VEMELHA = 4
} Nota; // Define uma nota

typedef enum // Cria uma ENUM para indetificar uma nota
{
    SONIC,
    BACK_IN_BLACK,
    STREETS_OF_RAGE,
    GUILE_THEME,
    ZELDA,
    DRACULA,
    TOP_GEAR,
    ALTERED,
    SMOOTH,
    PHATASY,
    NUM_MUSICAS
} Musica; // Define uma nota

extern const u32 tempos_sonic[434];
extern const Nota notas_sonic[434];
extern const u16 duracao_sonic[434];
extern const u16 tamanho_sonic;
extern const u8 velocidade_sonic;
extern const u16 delay_sonic;
extern const u8 loops_sonic;

extern const Nota notas_bib[223];
extern const u16 duracao_bib[223];
extern const u32 tempos_bib[223];
extern const u16 tamanho_bib;
extern const u8 velocidade_bib;
extern const u16 delay_bib;
extern const u8 loops_bib;

extern const Nota notas_sor[165];
extern const u16 duracao_sor[165];
extern const u32 tempos_sor[165];
extern const u16 tamanho_sor;
extern const u8 velocidade_sor;
extern const u16 delay_sor;
extern const u8 loops_sor;

extern const Nota notas_guile[259];
extern const u16 duracao_guile[259];
extern const u32 tempos_guile[259];
extern const u16 tamanho_guile;
extern const u8 velocidade_guile;
extern const u16 delay_guile;
extern const u8 loops_guile;

extern const Nota notas_castle[443];
extern const u16 duracao_castle[443];
extern const u32 tempos_castle[443];
extern const u16 tamanho_castle;
extern const u8 velocidade_castle;
extern const u16 delay_castle;
extern const u8 loops_castle;

extern const Nota notas_zelda[491];
extern const u16 duracao_zelda[491];
extern const u32 tempos_zelda[491];
extern const u16 tamanho_zelda;
extern const u8 velocidade_zelda;
extern const u16 delay_zelda;
extern const u8 loops_zelda;

extern const Nota notas_topGear[1196];
extern const u16 duracao_topGear[1196];
extern const u32 tempos_topGear[1196];
extern const u16 tamanho_topGear;
extern const u8 velocidade_topGear;
extern const u16 delay_topGear;
extern const u8 loops_topGear;

extern const Nota notas_ateredBeast[125];
extern const u16 duracao_ateredBeast[125];
extern const u32 tempos_ateredBeast[125];
extern const u16 tamanho_ateredBeast;
extern const u8 velocidade_ateredBeast;
extern const u16 delay_ateredBeast;
extern const u8 loops_ateredBeast;

extern const Nota notas_smooth[404];
extern const u16 duracao_smooth[404];
extern const u32 tempos_smooth[404];
extern const u16 tamanho_smooth;
extern const u8 velocidade_smooth;
extern const u16 delay_smooth;
extern const u8 loops_smooth;

extern const Nota notas_phantasy[119];
extern const u16 duracao_phantasy[119];
extern const u32 tempos_phantasy[119];
extern const u16 tamanho_phantasy;
extern const u8 velocidade_phantasy;
extern const u16 delay_phantasy;
extern const u8 loops_phantasy;

#endif