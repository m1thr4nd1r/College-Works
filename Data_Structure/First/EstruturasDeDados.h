#ifndef __EstruturasDeDados__
#define __EstruturasDeDados__ 1


typedef enum { FALSE, TRUE } bool;

typedef struct point 	{	int x;
							int y;
						} tPonto;
						
typedef struct	{ 	int 	ID;
					bool 	orelha;
					tPonto	p;
				} tVertice;

typedef struct  no_l {
						tVertice Dado;
						struct no_l *ant;
						struct no_l *prox;
				    } no_l; // No_l é o No da Lista (que é Dinamica, Duplamente Encadeada e Circular)

typedef struct {
					no_l *inicio;
			    } Lista; // Usada para armazenar os pontos do Poligono
								
typedef struct no {
						tVertice Dado;
						struct no *prox;
				  } no; // No da Pilha e da Fila (ambas Dinamicas)

typedef struct {
					no *inicio;
					no *topo;
			   		int qnt;
			   } Pilha; // Usada para armazenar os pontos, que formam as linhas, de cada orelha do Poligono
				
typedef struct 	{	
					no* inicio;
					no* fim;
					int qnt;
				} Fila;	// Usada para armazenar os pontos do Poligono que ainda nao foram classificados em orelha (utilizada na classificaçao das orelhas)

#endif		// __EstruturasDeDados__
