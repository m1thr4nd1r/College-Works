#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "opGeometricas.h"
#include "Triangulacao.h"
#include "trabalho.h"
#include "winGL.h"

void initVertices(no_l *atual,no_l *anterior,no_l *proximo) {
	
	// Se o vertice e seus vizinhos (anterior e posterior) formam uma diagonal entao
	if (eDiagonal(*anterior,*proximo)) // pega os vizinhos ant e prox e envia para o ediagonal
		atual->Dado.orelha = TRUE; 	// é orelha      		
	else // caso contrario
		atual->Dado.orelha = FALSE; // nao é orelha;
}

bool	eDiagonal(no_l anterior, no_l proximo /* a, p */) { 
	no_l ant_p = *proximo.ant; // Atribuo o anterior do proximo para ant_p e prox_a
	no_l prox_a = *proximo.ant; // O proximo do anterior é o mesmo do anterior do proximo = o elemento que estou verificando se é orelha
	no_l ant_a = *anterior.ant; // Atribuo o anterior do anterior para ant_a
	no_l prox_p = *proximo.prox; // Atribuo o proximo do proximo pra prox_p
	bool k=FALSE,l=FALSE;
	
	k = InCone(anterior.Dado.p,prox_a.Dado.p,ant_a.Dado.p,proximo.Dado.p); // Se os pontos (a, a->proximo, a->anterior, p) formam uma diagonal interna
	l = InCone(proximo.Dado.p,prox_p.Dado.p,ant_p.Dado.p,anterior.Dado.p); // E os pontos (p, p->proximo, p->anterior, a) formam uma diagonal interna

	if ((k) && (l) && (eDiagonalPropria(anterior,proximo))) // Se k e l e o anterior e o proximo for diagonal propria
		return TRUE;
	return FALSE;	
}

bool   eDiagonalPropria(no_l anterior , no_l proximo  /* a, p */ ) {
		
	no_l *pos = Pontos.inicio; // variavel que ira percorrer toda a lista
	bool k,l;
		
	do {	// Para cada vertice c da poligonal - pos
			//  c1 = proximo vertice de c; - pos->prox;
			
			// k verifica se c,c1 é incidente a a,b. Se for k é 1
			k = ((pos->Dado.ID == anterior.Dado.ID) || (pos->Dado.ID == proximo.Dado.ID) || (pos->prox->Dado.ID == anterior.Dado.ID) || (pos->prox->Dado.ID == proximo.Dado.ID));
			
			// l verifica se existe intersecao entre as arestas (a,b) e (c,c1). Se existir l é 1
			l = Intersect(anterior.Dado.p,proximo.Dado.p,pos->Dado.p,pos->prox->Dado.p);
			
			// se a aresta (c,c1) nao é incidente a (a,b)
			// e existe intersecao entre as arestas (a,b) e (c, c1)
					
			if ((!k) && (l)) 
				return FALSE; //retornar falso => diagonal nao valida;
			pos = pos->prox;
		}while(pos != Pontos.inicio); // percorrendo a lista toda.
	return TRUE; //retornar verdadeiro => e diagonal valida;
}
 
void Triangular(no_l *atual,no_l *anterior,no_l *proximo) 
{
	if (atual->Dado.orelha == TRUE) //Se o vertice corrente eh orelha entao
	{
      // cria um triangulo da triangulacao com o vertices e seus vizinhos anterior e posterior;
      // no caso, criamos somente a linha que delimita a triangulacao
				
				// Empilha as linhas na pilha Orelhas (para uso no desenhaTriangulacao)
				 
				Empilhar(&Orelhas,anterior->Dado);
				Empilhar(&Orelhas,proximo->Dado);
	
		// Codigo para mostrar os valores de anterior,atual e proximo. Mostrando que a classificacao esta certa:
		
				printf("\nTriangular\n"); 
				printf("Vertice Atual - Ponto %d | x = %d | y = %d | Orelha = %d\n",atual->Dado.ID,atual->Dado.p.x,atual->Dado.p.y,atual->Dado.orelha);
				printf("Vertice Anterior a Atual - Ponto %d | x = %d | y = %d | Orelha = %d\n",anterior->Dado.ID,anterior->Dado.p.x,anterior->Dado.p.y,anterior->Dado.orelha);
				printf("Vertice Proximo a Atual - Ponto %d | x = %d | y = %d | Orelha = %d\n",proximo->Dado.ID,proximo->Dado.p.x,proximo->Dado.p.y,proximo->Dado.orelha);

		/////////////////////////////////////////////////////
		
	}	
}
