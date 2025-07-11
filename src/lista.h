#ifndef __LISTA_H__
#define __LISTA_H__

#include <snes.h>
#include "musicas.h"
#include "lib/sprite_s.h"

#define LARGURA 254
#define ALTURA 224
#define ALTURA_MIRA 195
#define ALTURA_PISTA 62

// define a estrutura do nodo
typedef struct Temp
{
    s16 sprite_id;
    s16 x;
    s16 y;
    Nota tipo;
} LNotas;

// define a estrutura do nodo
typedef struct TempB
{
    u8 sprite_id;
    s16 x;
    s16 y;
    Nota tipo;
    s16 duracao;
    struct TempB *prox;
} LBarras;

LBarras *inicio_Barra;

t_sprites *fogoR, *fogoG, *fogoY;

void CriaLista_Nota();
u8 Insere_Nota(s8 idx, s16 x, s16 y, Nota tipo);
s16 atualizaPosicao_Nota(u8 velocidade, s16 placar);
u16 tamanhoLista_Nota(u8 lista);

void CriaLista_Barra();
u8 Insere_Barra(t_sprites *sprite, s16 x, s16 y, Nota tipo, s16 duracao);
s16 atualizaPosicao_Barra(u8 velocidade, s16 placar);

void limpa_listas();

void esconde_fogo();

#endif