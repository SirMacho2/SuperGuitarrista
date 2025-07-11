#include "lista.h"
#include "musicas.h"
#include "commun.h"

#define TEMPO_FOGO 110
#define DIFY ALTURA_MIRA - ALTURA_PISTA
#define DIFX AMARELO_X_INICIO - AMARELO_X
#define SCALE DIFX / DIFY

static LNotas notas[128];

// static u32 tempoFogoR = 0, tempoFogoG = 0, tempoFogoY = 0;

// //--------------------------------------------------------
// Funcao que define a lista como vazia.
void CriaLista_Nota()
{
    int i;
    for (i = 0; i < 128; i++)
    {
        notas[i].sprite_id = -1;
    }
}
//--------------------------------------------------------
// Funcao que insere um elemento do inicio da lista.
// Retorna:
//	0 - se nao ha'  memoria para inserir
//	1 - se conseguiu inserir
u8 Insere_Nota(s8 idx, s16 x, s16 y, Nota tipo)
{

    int i;
    if (idx < 0)
    {
        consoleNocashMessage("idx < 0, falha ao incerir nota\n");
        return 0;
    }

    for (i = 0; i < 128; i++)
    {
        if (notas[i].sprite_id == -1)
        {
            notas[i].sprite_id = idx;
            notas[i].x = x;
            notas[i].y = y;
            notas[i].tipo = tipo;
            break;
        }
    }
    if (i < 128)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// //--------------------------------------------------------
// // Funcao que define a lista como vazia.
// void CriaLista_Barra()
// {
//     inicio_Barra = NULL;
// }
// //--------------------------------------------------------
// // Funcao que insere um elemento do inicio da lista.
// // Retorna:
// //	0 - se nao ha'  memoria para inserir
// //	1 - se conseguiu inserir
// u8 Insere_Barra(t_sprites *sprite, s16 x, s16 y, Nota tipo, s16 duracao)
// {
//     LBarras *p;

//     // MEM_pack();
//     p = (LBarras *)malloc(sizeof(LBarras));
//     if (p == NULL || sprite == NULL)
//     {
//         // erro de alocação
//         // KLog("error in allocation");
//         return 0;
//     }

//     p->sprite = sprite;
//     p->x = x;
//     p->y = y;
//     p->tipo = tipo;
//     p->duracao = duracao;
//     p->prox = NULL;

//     // SPR_setDepth(sprite, SPR_MIN_DEPTH);

//     if (inicio_Barra == NULL)
//         inicio_Barra = p;
//     else
//     {
//         LBarras *atual = inicio_Barra;
//         while (atual->prox != NULL)
//         {
//             atual = atual->prox;
//         }
//         atual->prox = p;
//     }
//     return 1;
// }

// //--------------------------------------------------------
// Funcao diz o tamanho da lista.
// Retorna:
//	tamanho da lista
u16 tamanhoLista_Nota(u8 lista)
{
    u16 tamanho = 0;
    int i;
    if (lista == 0)
    {
        for (tamanho = 0, i = 0; i < 128; i++)
        {
            if (notas[i].sprite_id != -1)
            {
                tamanho++;
            }
        }
    }
    else if (lista == 1)
    {
        if (inicio_Barra == NULL)
            return 0;
        LBarras *ptr = inicio_Barra;
        for (tamanho = 0; ptr != NULL; tamanho++)
        {
            ptr = ptr->prox;
        }
    }

    return tamanho;
}

//--------------------------------------------------------
// Funcao que atualiza a posição das notas e detecta se o usuario aperto o botão na hora correta.
// Retorna:
// numero de notas acertadas, ou -1 se passou uma nota sem acertar;
s16 atualizaPosicao_Nota(u8 velocidade, s16 placar)
{
    int i;
    u16 v = velocidade;
    consoleNocashMessage("atualizando posicao das notas:\n");
    for (i = 0; i < 128; i++)
    {
        if (notas[i].sprite_id != -1)
        {

            notas[i].y = notas[i].y + velocidade;
            if (notas[i].y >= ALTURA) // passou do limite
            {
                // if (SPR_isVisible(notas[i].sprite, 1))
                // {
                //     placar--;
                // }

                SPR_release(notas[i].sprite_id);
                notas[i].sprite_id = -1;
                continue;
            }
            else
            {
                if (notas[i].tipo == AMARELA)
                {
                    if (v = 1)
                    {
                        if (frame % 2 == 0)
                        {
                            notas[i].x--;
                        }
                    }
                    else
                    {
                        notas[i].x = notas[i].x - v / 2;
                    }

                    oambuffer[notas[i].sprite_id].oamx = notas[i].x;
                    oambuffer[notas[i].sprite_id].oamy = notas[i].y;
                }
                else if (notas[i].tipo == VEMELHA)
                {
                    if (v = 1)
                    {
                        if (frame % 2 == 0)
                        {
                            notas[i].x++;
                        }
                    }
                    else
                    {
                        notas[i].x = notas[i].x + v / 2;
                    }
                    oambuffer[notas[i].sprite_id].oamx = notas[i].x;
                    oambuffer[notas[i].sprite_id].oamy = notas[i].y;
                }
                else
                {
                    oambuffer[notas[i].sprite_id].oamx = notas[i].x;
                    oambuffer[notas[i].sprite_id].oamy = notas[i].y;
                }
                if (notas[i].y < 214) // Divide a pista em 7 seguimentos de 19px de altura cada um com um tamanho de nota
                {
                    if (notas[i].y == 80)
                    {
                        SPR_setFrame(notas[i].sprite_id, 1);
                        consoleNocashMessage("atualizando frame da nota %d:%d\n", i, 1);
                    }
                    else if (notas[i].y == 98)
                    {
                        SPR_setFrame(notas[i].sprite_id, 2);
                        consoleNocashMessage("atualizando frame da nota %d:%d\n", i, 2);
                    }
                    else if (notas[i].y == 116)
                    {
                        SPR_setFrame(notas[i].sprite_id, 3);
                        consoleNocashMessage("atualizando frame da nota %d:%d\n", i, 3);
                    }
                    else if (notas[i].y == 134)
                    {
                        SPR_setFrame(notas[i].sprite_id, 4);
                        consoleNocashMessage("atualizando frame da nota %d:%d\n", i, 4);
                    }
                    else if (notas[i].y == 152)
                    {
                        SPR_setFrame(notas[i].sprite_id, 5);
                        consoleNocashMessage("atualizando frame da nota %d:%d\n", i, 5);
                    }
                    else if (notas[i].y == 170)
                    {
                        SPR_setFrame(notas[i].sprite_id, 6);
                        consoleNocashMessage("atualizando frame da nota %d:%d\n", i, 6);
                    }
                }
                if (notas[i].y > ALTURA_MIRA - 15 && notas[i].y < ALTURA_MIRA + 15)
                {
                    // if (SPR_isVisible(notas[i].sprite, 1))
                    // {
                    //     // sobe placar e deixa sprite invisivel
                    //     if (notas[i].tipo == AMARELA && J1A)
                    //     {
                    //         placar++;
                    //         J1A = 0;
                    //         SPR_setVisibility(notas[i].sprite, HIDDEN);
                    //         SPR_setFrame(fogoY, 0);
                    //         SPR_setVisibility(fogoY, VISIBLE);
                    //         tempoFogoY = getTick();
                    //     }
                    //     if (notas[i].tipo == VERDE && J1B)
                    //     {
                    //         placar++;
                    //         J1B = 0;
                    //         SPR_setVisibility(notas[i].sprite, HIDDEN);
                    //         SPR_setFrame(fogoG, 0);
                    //         SPR_setVisibility(fogoG, VISIBLE);
                    //         tempoFogoG = getTick();
                    //     }
                    //     if (notas[i].tipo == VEMELHA && J1C)
                    //     {
                    //         placar++;
                    //         J1C = 0;
                    //         SPR_setVisibility(notas[i].sprite, HIDDEN);
                    //         SPR_setFrame(fogoR, 0);
                    //         SPR_setVisibility(fogoR, VISIBLE);
                    //         tempoFogoR = getTick();
                    //     }
                    // }
                }
            }
        }
    }
    return placar;
}

//--------------------------------------------------------
// Funcao que atualiza a posição das barras e detecta se o usuario aperto o botão na hora correta.
// Retorna:
// pontuação referente as barras;
s16 atualizaPosicao_Barra(u8 velocidade, s16 placar)
{
    LBarras *ptr, *antes;
    if (inicio_Barra == NULL)
    {
        return placar; // Lista vazia !!!
    }
    else
    {
        ptr = inicio_Barra;
        antes = inicio_Barra;
        s16 v = velocidade;
        bool update = FALSE;
        while (ptr != NULL)
        {
            ptr->y = ptr->y + velocidade;

            if (ptr->y >= ALTURA) // passou do limite
            {
                if (ptr == inicio_Barra) // se esta removendo o primeiro da lista
                {
                    inicio_Barra = inicio_Barra->prox;
                    SPR_release(ptr->sprite_id);
                    free(ptr);
                    ptr = inicio_Barra;
                    update = TRUE;
                }
                else // esta removendo do meio da lista
                {
                    antes->prox = ptr->prox; // Refaz o encadeamento
                    SPR_release(ptr->sprite_id);
                    free(ptr); // Libera a area do nodo
                    ptr = antes->prox;
                    update = TRUE;
                }
            }
            else
            {
                if (ptr->tipo == AMARELA)
                {
                    ptr->x = ptr->x - SCALE * v;
                    oamSetXY(ptr->sprite_id, ptr->x, ptr->y);
                }
                else if (ptr->tipo == VEMELHA)
                {
                    ptr->x = ptr->x + SCALE * v;
                    oamSetXY(ptr->sprite_id, ptr->x, ptr->y);
                }
                else
                {
                    oamSetXY(ptr->sprite_id, ptr->x, ptr->y);
                }
                if (velocidade == 3)
                {
                    // if (ptr->duracao > 0 && ptr->y == 6 + ALTURA_PISTA)
                    // {
                    //     if (ptr->tipo == AMARELA)
                    //     {
                    //         Insere_Barra(SPR_addSprite(&barraY, ptr->x, ALTURA_PISTA, TILE_ATTR(PAL2, FALSE, FALSE, FALSE)), AMARELO_B_X_INICIO, ALTURA_PISTA, AMARELA, ptr->duracao - 45);
                    //     }
                    //     if (ptr->tipo == VERDE)
                    //     {
                    //         Insere_Barra(SPR_addSprite(&barraG, ptr->x, ALTURA_PISTA, TILE_ATTR(PAL2, FALSE, FALSE, FALSE)), ptr->x, ALTURA_PISTA, VERDE, ptr->duracao - 45);
                    //     }
                    //     if (ptr->tipo == VEMELHA)
                    //     {
                    //         Insere_Barra(SPR_addSprite(&barraR, ptr->x, ALTURA_PISTA, TILE_ATTR(PAL2, FALSE, FALSE, FALSE)), VEMELHO_B_X_INICIO, ALTURA_PISTA, VEMELHA, ptr->duracao - 45);
                    //     }
                    // }
                }
                else
                {
                    // if (ptr->duracao > 0 && ptr->y == 8 + ALTURA_PISTA)
                    // {
                    //     if (ptr->tipo == AMARELA)
                    //     {
                    //         Insere_Barra(SPR_addSprite(&barraY, ptr->x, ALTURA_PISTA, TILE_ATTR(PAL2, FALSE, FALSE, FALSE)), AMARELO_B_X_INICIO, ALTURA_PISTA, AMARELA, ptr->duracao - 45);
                    //     }
                    //     if (ptr->tipo == VERDE)
                    //     {
                    //         Insere_Barra(SPR_addSprite(&barraG, ptr->x, ALTURA_PISTA, TILE_ATTR(PAL2, FALSE, FALSE, FALSE)), ptr->x, ALTURA_PISTA, VERDE, ptr->duracao - 45);
                    //     }
                    //     if (ptr->tipo == VEMELHA)
                    //     {
                    //         Insere_Barra(SPR_addSprite(&barraR, ptr->x, ALTURA_PISTA, TILE_ATTR(PAL2, FALSE, FALSE, FALSE)), VEMELHO_B_X_INICIO, ALTURA_PISTA, VEMELHA, ptr->duracao - 45);
                    //     }
                    // }
                }
                // if (ptr->y > ALTURA_MIRA - 5 && ptr->y < ALTURA_MIRA + 7)
                // {
                //     u16 JOY1 = JOY_readJoypad(JOY_1);
                //     if (SPR_isVisible(ptr->sprite, 1))
                //     {
                //         // sobe placar e deixa sprite invisivel                         200
                //         if (ptr->tipo == AMARELA)
                //         {
                //             if ((JOY1 & BUTTON_A))
                //             {
                //                 placar++;
                //                 SPR_setVisibility(ptr->sprite, HIDDEN);
                //                 SPR_setFrame(fogoY, 0);
                //                 SPR_setVisibility(fogoY, VISIBLE);
                //                 tempoFogoY = getTick();
                //             }
                //         }
                //         if (ptr->tipo == VERDE)
                //         {
                //             if ((JOY1 & BUTTON_B))
                //             {
                //                 placar++;
                //                 SPR_setVisibility(ptr->sprite, HIDDEN);
                //                 SPR_setFrame(fogoG, 0);
                //                 SPR_setVisibility(fogoG, VISIBLE);
                //                 tempoFogoG = getTick();
                //             }
                //         }
                //         if (ptr->tipo == VEMELHA)
                //         {
                //             if ((JOY1 & BUTTON_C))
                //             {
                //                 placar++;
                //                 SPR_setVisibility(ptr->sprite, HIDDEN);
                //                 SPR_setFrame(fogoR, 0);
                //                 SPR_setVisibility(fogoR, VISIBLE);
                //                 tempoFogoR = getTick();
                //             }
                //         }
                //     }
                // }
            }
            if (update == FALSE)
            {
                antes = ptr;
                ptr = ptr->prox;
            }
            else
            {
                update = FALSE;
            }
        }
    }
    return placar;
}

// void limpa_listas()
// {
//     LNotas *ptr;
//     LBarras *ptr2;
//     for (ptr = inicio_Nota; ptr != NULL; ptr = inicio_Nota)
//     {
//         inicio_Nota = inicio_Nota->prox;
//         SPR_release(ptr->sprite_id);
//         free(ptr);
//     }

//     for (ptr2 = inicio_Barra; ptr2 != NULL; ptr2 = inicio_Barra)
//     {
//         inicio_Barra = inicio_Barra->prox;
//         SPR_releaseSprite(ptr2->sprite);
//         free(ptr2);
//     }
// }

// void esconde_fogo()
// {
//     u32 tempo = getTick();
//     if (tempo - tempoFogoR >= TEMPO_FOGO)
//     {
//         SPR_setVisibility(fogoR, HIDDEN);
//     }
//     if (tempo - tempoFogoG >= TEMPO_FOGO)
//     {
//         SPR_setVisibility(fogoG, HIDDEN);
//     }
//     if (tempo - tempoFogoY >= TEMPO_FOGO)
//     {
//         SPR_setVisibility(fogoY, HIDDEN);
//     }
// }