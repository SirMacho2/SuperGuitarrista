#include "menu.h"
#include "string.h"
#include "translate.h"
// #include "bg.h"

#define CENTRO_X 16
#define CENTRO_Y 14

const Opcao opcoes_pause[NUM_OPCOES_PAUSA] = {
    {CENTRO_X - 2, CENTRO_Y, "VOLTAR"},
    {CENTRO_X - 2, CENTRO_Y + 1, "SAIR"},
    {CENTRO_X - 2, CENTRO_Y + 2, "REINICIAR"},
};

const OpcaoMusica opcoes_musicas[NUM_MUSICAS] = {
    {CENTRO_X - 2, CENTRO_Y - 2, "Green Hill Zone", /*&sonic_cover,*/ 3},
    {CENTRO_X - 1, CENTRO_Y - 2, "Back in Black", /*&sonic_cover,*/ 1},
    {CENTRO_X - 2, CENTRO_Y - 2, "Streets of Rage", /*&sor_conver,*/ 2},
    {CENTRO_X, CENTRO_Y - 2, "Guile theme", /*&guile_cover,*/ 2},
    {CENTRO_X - 2, CENTRO_Y - 2, "Zelda-overworld", /*&zelda_cover,*/ 3},
    {CENTRO_X - 2, CENTRO_Y - 2, "Dracula's castle", /*&sont_conver,*/ 2},
    {CENTRO_X - 2, CENTRO_Y - 2, "Top Gear", /*&topgear_cover,*/ 3},
    {CENTRO_X - 2, CENTRO_Y - 2, "Altered Beast", /*&alterd_cover,*/ 1},
    {CENTRO_X - 2, CENTRO_Y - 2, "Smooth Criminal", /*&moonwalker_conver,*/ 1},
    {CENTRO_X - 2, CENTRO_Y - 2, "Motavia Town", /*&phantasy_cover,*/ 1},
};

const Opcao opcoes_menu_inicial = {CENTRO_X - 8, CENTRO_Y, "Pressione Start"};

const Opcao opcoes_fim[NUM_OPCOES_FIM] = {
    {CENTRO_X - 2, CENTRO_Y, "SAIR"},
    {CENTRO_X - 2, CENTRO_Y + 1, "REINICIAR"},
};

void mostra_menu_inicial()
{
    VDP_drawText(opcoes_menu_inicial.texto, opcoes_menu_inicial.x, opcoes_menu_inicial.y);
}

void mostra_menu_pausa()
{
    u8 i;
    for (i = 0; i < NUM_OPCOES_PAUSA; i++)
    {
        VDP_drawText(opcoes_pause[i].texto, opcoes_pause[i].x, opcoes_pause[i].y);
    }
}

void mostra_menu(const Opcao *opcoes, u8 tamanho)
{
    u8 i;
    for (i = 0; i < tamanho; i++)
    {
        VDP_drawText(opcoes[i].texto, opcoes[i].x, opcoes[i].y);
    }
}