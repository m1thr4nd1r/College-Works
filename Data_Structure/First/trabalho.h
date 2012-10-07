#ifndef __Main__
#define __Main__ 1

#include <stdio.h>
#include <math.h>

#include "EstruturasDeDados.h"

Lista Pontos;

no_l* sentinela;

Fila Vertices_Comuns;

Pilha Orelhas;

int Desenfileirar(Fila *F, tVertice *Aux);

int Empilhar(Pilha * P,tVertice E);

int Enfileirar(Fila * F,tVertice E);

void teclado(unsigned char key, int x, int y);

void mouse(int button, int button_state, int x, int y );

void desenho(void);

#endif	// __Main__

