#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#if defined (__APPLE__) || defined(MACOSX)
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

#include "EstruturasDeDados.h"
#include "Triangulacao.h"
#include "winGL.h"
		
int		wLargura 	= 500,
		wAltura 	= 500;

no_l* sentinela;	// Variavel para inicializaçao da lista
Fila Vertices_Comuns;	// Fila que ira armazenar os vertices da poligonal
Pilha Orelhas;	// Pilha que ira armazenar as orelhas
int		numPtos=-1,T=0; // T é a variavel que servirá de flag para o desenhaTriangulacao
Lista   Pontos;	// Lista que ira armazenar os vertices da poligonal
		
/// ***********************************************************************
/// ** 
/// ***********************************************************************

void initrand()	//Inicializando o rand para gerar numeros aleatorios
{
    srand((unsigned)(time(0)));
} 

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void init_Fila(Fila *F) // Inicializando a Fila
{
	F->inicio=NULL;
	F->fim=NULL;
	F->qnt = 0;
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

int Enfileirar(Fila * F,tVertice E) // Funcao para Enfileirar os Vertices
{
	no *pos=F->inicio,*Novo;

	Novo = (no*) malloc (sizeof(no)); // Mallocando o espaço de um no
	if (Novo == NULL) // Se n for possivel alocar o espaço de memoria
		printf("Memoria cheia");
	else
	{
		// Inicializa o novo dado //
		
		Novo->prox = NULL;
		Novo->Dado = E;
		
		////////////////////////////
		
		// Atribuindo o novo elemento no inicio ou fim da fila
		
		if (F->qnt == 0) // Se a fila estiver vazia
		{
			F->inicio = Novo; // Aloca o novo elemento como inicio e fim da fila
			F->fim = Novo;
		}
		else // Se a fila nao estiver vazia
		{
			while (pos->prox != NULL) // Procura o ultimo elemento da fila
				pos = pos->prox;
			
			// Faz a linkagem do elemento adicionado com os elementos ja presentes na pilha
			
			F->fim = Novo;	
			pos->prox = Novo;
			
			////////////////////////////////////////////
		}
		
		F->qnt++; // Incrementa a quantidade de elementos da fila
		
		return 1;
	}
	
	return 0;
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

int Desenfileirar(Fila *F, tVertice *Aux) // Funcao para Desenfileirar os Vertices
{
	no *pos=F->inicio;
	
	if (F->qnt == 0) // Se a fila estiver vazia
		return 0;
	else
	{
		*Aux = F->inicio->Dado; // Atribui o conteudo do primeiro elemento a Aux
		F->inicio = F->inicio->prox; // "Incrementa" o inicio da fila
		free(pos); // libera a memoria do antigo inicio
		F->qnt--; // diminui a quantidade de elementos da fila
		return 1;
	}
}
		
/// ***********************************************************************
/// ** 
/// ***********************************************************************

void ImprimeFila(Fila F) // Funcao para Imprimir a Fila
{
	no *pos=F.inicio;
	if (F.qnt == 0) // Se a fila estiver vazia
		printf("\nFila Vazia\n");
	else
		while (pos != NULL) // Enquanto nao achar o fim da fila
		{
			printf("Fila - Ponto %d | x = %d | y = %d | Orelha = %d\n",pos->Dado.ID,pos->Dado.p.x,pos->Dado.p.y,pos->Dado.orelha);
			pos = pos->prox; // Varre a fila
		}	
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void init_Pilha(Pilha *P) // Funcao para inicializar a Pilha
{
	P->inicio=NULL;
	P->topo=NULL;
	P->qnt = 0;
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

int Empilhar(Pilha * P,tVertice E) // Funcao para Empilhar as linhas de cada uma das Orelhas (para a triangulacao)
{
	no *pos=P->inicio,*Novo;

	Novo = (no*) malloc (sizeof(no)); // Mallocando o espaço de um no da pilha (no_p)
	if (Novo == NULL) // Se n for possivel alocar o espaço de memoria
		printf("Memoria cheia");
	else
	{
		// Inicializa o novo dado //
		
		Novo->Dado = E;
		Novo->prox = NULL;
		
		////////////////////////////
		
		// Atribuindo o novo elemento no inicio ou fim da pilha
		
		if (P->qnt == 0) // Se a pilha estiver vazia
		{
			P->inicio = Novo; // Aloca o novo elemento como inicio e topo da pilha
			P->topo = Novo;
		}
		else // Se a pilha nao estiver vazia
		{
			while (pos->prox != NULL) // Procura o ultimo elemento da pilha
				pos = pos->prox; 
			
			// Faz a linkagem do elemento adicionado com os elementos ja presentes na pilha
			
			P->topo = Novo;	
			pos->prox = Novo;
			
			///////////////////////
		}
		
		P->qnt++; // Incrementa a quantidade de elementos da pilha
		
		return 1;
	}
	
	return 0;
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

int Desempilhar(Pilha *P,tVertice *E) // Funcao para desempilhar a Pilha que contem as linhas da triangulacao 
{
	no *pos=P->inicio,*Aux=P->inicio; 
	
	if (P->qnt == 0) // Se a pilha estiver vazia
		return 0;
	else
	{
		while (pos != P->topo) // Enquanto nao achar achar o topo
		{
			Aux = pos; // Aux eh o elemento anterior a pos
			pos= pos->prox; // Pos percorre a lista
		}
		
		pos->prox = NULL; //Aux eh setado como o novo topo
		P->topo = Aux; 
		
		*E = Aux->Dado; // Atribui o conteudo de Aux->Dado a E
		
		P->qnt--; // Diminui a quantidade de elementos na pilha
		free(pos); // Libera a memoria
	}
	return 1;
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void ImprimePilha(Pilha P) // Funcao para Imprimir a Pilha (para teste)
{
	no *pos=P.inicio;
	if (P.qnt == 0) // Se a pilha estiver vazia
		printf("\nPilha Vazia\n");
	else
		while (pos != NULL) // Enquanto nao achar o fim da pilha
		{
			printf("Pilha - Ponto %d | x = %d | y = %d | Orelha = %d\n",pos->Dado.ID,pos->Dado.p.x,pos->Dado.p.y,pos->Dado.orelha);
			pos = pos->prox; // Varre a pilha
		}	
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void init_lista (Lista* L) // Funcao para inicializar a lista
{
	L->inicio = sentinela;
	L->inicio->prox = sentinela;
	L->inicio->ant = sentinela;
}
		
/// ***********************************************************************
/// ** 
/// ***********************************************************************

int AdicionarElemento (Lista* L,tVertice E) // Funcao para adicionar os vertices na Lista
{
	no_l *No_aux,*pos_atual=L->inicio;
	No_aux = (no_l*)malloc(sizeof(no_l));
	
	if (No_aux == NULL) // Se n for possivel alocar o espaço de memoria
		return 0;
	else
	{
		// Inicializa o novo dado //
		
		No_aux->Dado = E;
		No_aux->prox = L->inicio;
		No_aux->ant = NULL;
	
		////////////////////////////
	}
	
	// Atribuindo o novo elemento no inicio ou fim da lista
	
	if (L->inicio == sentinela) // Se a lista estiver Vazia
	{
		No_aux->ant = No_aux;
		No_aux->prox = No_aux;
		L->inicio = No_aux; // Atribui o elemento no inicio;
	}
	else // Se a lista nao estiver vazia
	{
		while (pos_atual->prox != L->inicio) // Procura o ultimo elemento
				pos_atual = pos_atual->prox;
		
		// Faz a linkagem do elemento adicionado com os elementos ja presentes na lista
		
		pos_atual->prox = No_aux; 
		No_aux->ant = pos_atual;
		L->inicio->ant = No_aux; 
		
		////////////////////////////////////////////////////////////////////////////////
		
	}
	return 1; // Elemento adicionado
}
		
/// ***********************************************************************
/// ** 
/// ***********************************************************************

void ApagarLista (Lista* L) // Funcao para apagar a lista (e recomeçar o programa)
{
	int num=numPtos;
	no_l* aux;
	while (num >= 0) // Libera as posiçoes de memoria
	{
		aux = L->inicio; 
		L->inicio = L->inicio->prox;
		free(aux);
		num--;
	}
	numPtos = -1; // Reseta o numero de Pontos
	
	init_lista(&Pontos); // Reinicializa a lista
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void ImprimeLista (Lista L) // Funcao para Imprimir a Lista (para teste)
{
	no_l* pos=L.inicio;
	if (L.inicio != sentinela) // Se o inicio for diferente de sentinela
	{	
		do
		{
			printf("Lista - Ponto %d | x = %d | y = %d | Orelha = %d\n",pos->Dado.ID,pos->Dado.p.x,pos->Dado.p.y,pos->Dado.orelha);
			pos = pos->prox; // Varre a lista ate chegar no inicio novamente
		}while (pos != L.inicio);
	}
	else
		printf("Lista Vazia\n");
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void restart() // Funcao para recomeçar a desenhar
{
	tVertice Aux;
	
	ApagarLista(&Pontos); // Apaga a lista
	
	printf("\nLista apagada\n");
	
	while (Orelhas.qnt > 0)
		Desempilhar(&Orelhas,&Aux); // Apaga a Pilha
		
	printf("\nPilha apagada\n");
	
	while (Vertices_Comuns.qnt > 0)
		Desenfileirar(&Vertices_Comuns,&Aux); // Apaga a Fila
		
	printf("\nFila apagada\n");
		
    glColor3f (1.0, 1.0, 1.0);
	
	glClear (GL_COLOR_BUFFER_BIT); // Apaga a Tela
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void geraTriangulacao() {
	
	no aux;
	no_l *atual = Pontos.inicio;
	no_l* anterior;
	no_l* proximo;	
	
/*  	Algoritmo Triangulacao
	
	Passo 1: Classifica todos os vertices se sao orelhas; */
	
	Desenfileirar(&Vertices_Comuns,&aux.Dado); // Desenfileira o primeiro vertice da fila
		
	while (atual->Dado.ID != aux.Dado.ID) // Procura na lista o dado desenfileirado
		atual = atual->prox;
		
	anterior = atual;
	proximo = atual;	
	
	do
	{
		anterior = anterior->ant;
	}while (anterior->Dado.orelha == TRUE); // Procurando o primeiro anterior valido
		
	do
	{
		proximo = proximo->prox;
	}while (proximo->Dado.orelha == TRUE); // Procurando o primeiro posterior valido
	
	if (Vertices_Comuns.qnt > 2) // So procura se é orelha se for maior que triangulo
	{
		initVertices(atual,anterior,proximo); // Classifica se o vertice é orelha
				
		if (atual->Dado.orelha == FALSE) // Se o vertice nao for orelha...
			Enfileirar(&Vertices_Comuns,aux.Dado); // enfileira novamente o vertice
	}		
	else
	{
		atual->Dado.orelha = TRUE; // Se for um triangulo a triangulacao esta feita e o primeiro vertice do triangulo é classificado como orelha
		Vertices_Comuns.qnt = 0;   // Nesse caso, chegamos ao final da triangulaçao e zeramos a pilha
	}

/*		Passo 2: Enquanto for possivel formar triangulos na poligonal
					Chama rotina Triangular;
*/     			
		Triangular(atual,anterior,proximo); // Empilha em Orelha as linhas que cada uma das orelhas definem
		
		if (Vertices_Comuns.qnt > 0) // Enquanto for possivel triangular, chamamos a funçao geraTriangulacao
			geraTriangulacao();
}	

void desenhaPoligonal() { // Funcao para desenhar a poligonal
	
	// Utilizando o random para variar a cor do poligono //
	
	initrand();	// Chama a funcao para inicializar o rand		
	
	// Pega o numero gerado por rand (que é muito grande)
	// e atribui o resto de sua divisao por 3 a r
	
	int r=rand()%3; 
	
	float cor1 = r * 0.5;
	float cor2 = r+1 * 0.5;
	float cor3 = r+2 * 0.5;
	
	while (cor2>=1) // Decrementa ate cor2 ser menor ou igual a 1
		cor2--;
	while (cor3>=1) // Decrementa ate cor3 ser menor ou igual a 1
		cor3--;
	
	if (((cor1) == 0) && ((cor2) == 0) && ((cor3) == 0)) // Se todos forem = 0 entao
		cor1 = 1;	// Incrementa para nao ficar preto (e invisivel na tela)
		
	//////////////////////
	
	no_l * pos = Pontos.inicio;
	
	glColor3f(cor1,cor2,cor3); // A cor usada para desenhar o poligono sera a gerada acima
	glBegin(GL_LINE_LOOP);
		do
		{
			glVertex2f(pos->Dado.p.x,pos->Dado.p.y); // Ira imprimir o ponto na tela e liga-lo com o a figura ja existente, formando um novo poligono
			pos = pos->prox; // Varrendo a Lista
		}while (pos != Pontos.inicio); // Para o loop se chegar no fim
	glEnd();
}
		
/// ***********************************************************************
/// ** 
/// ***********************************************************************

void desenhaTriangulacao() {	// Funcao para desenhar a Triangulacao
	
	T=0;
	
	tVertice v1,v2; // Os 2 vertices da triangulaçao
	
	if(Orelhas.qnt == 2) // Se o poligono for um triangulo
	{
		no_l * pos = Pontos.inicio;
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_LINE_LOOP);
			do
			{
				glVertex2f(pos->Dado.p.x,pos->Dado.p.y); // Ira imprimir o triangulo (vazado) na tela (triangulacao)
				pos = pos->prox; // Varre ate achar o fim da Lista de pontos
			}while (pos != Pontos.inicio);
		glEnd();
	}
	else
		do
		{
			// Desempilha os 2 vertices que formam a triangulacao de cada orelha
			
			Desempilhar(&Orelhas,&v1); 
			Desempilhar(&Orelhas,&v2);
			
			desenhaLinha(v1.p,v2.p,Orelhas.qnt%7+1); // Desenha a linha entre os 2 vertices (triangulacao)
			
		}while (Orelhas.qnt > 0); // Desenha enquanto for possivel formar linhas 
} 
		
/// ***********************************************************************
/// ** 
/// ***********************************************************************


void mouse(int button, int button_state, int x, int y ) { // Funcao que controla o que cada clique do mouse faz
	
	tVertice Ponto;
	if 	(button_state == GLUT_DOWN ) {
		switch (button) {
			
			case GLUT_LEFT_BUTTON	: 	numPtos++;
										
										// Inicializacao do elemento que sera adicionado na fila e na lista
										
										Ponto.p.x = x; 
										Ponto.p.y = wAltura - y;
										Ponto.ID = numPtos;
										Ponto.orelha = FALSE;
										
										///////////////////////
										
										AdicionarElemento(&Pontos,Ponto); // Adiciona o elemento Ponto a lista Pontos
										
										Enfileirar(&Vertices_Comuns,Ponto); // Enfileira o elemento na Fila para uso posterior
										
										break;
	
			case GLUT_RIGHT_BUTTON	:	glColor3f (1.0, 1.0, 1.0);
										
										glClear (GL_COLOR_BUFFER_BIT); // Limpa a tela
										
										desenhaPoligonal();	// Desenha a Poligonal (sem triangulacao)
										
										break;
			}
		glutPostRedisplay();
		}
}
		
/// ***********************************************************************
/// ** 
/// ***********************************************************************

void desenho(void) {
	
	no_l * Ponto=Pontos.inicio;

    glClear (GL_COLOR_BUFFER_BIT); // Limpa a tela
    
    glColor3f (1.0, 1.0, 1.0);
    
    switch (numPtos%2) {
    	case 0	:	desenhaPonto(Ponto->Dado.p, BLUE); // Desenha o primeiro ponto do Poligono
    				break;
    	case 1	:	desenhaLinha(Ponto->Dado.p, Ponto->prox->Dado.p, YELLOW); // Desenha a primeira reta do Poligono
    				break;
    	}
    
    if (numPtos > 1)	// Se a quantidade de pontos for maior que 2 (ou seja, uma reta)
		desenhaPoligonal(); // Chama a funcao para Desenhar a Poligonal
    
    if (T) // Se T = 1
		desenhaTriangulacao(); // Chama a funcao para desenhar a Triangulacao
    	
    glutSwapBuffers ();
}

/// ***********************************************************************
/// **
/// ***********************************************************************


void teclado(unsigned char key, int x, int y) {
	switch (key) {
		case 27		: 	exit(0);
						break;

		case 'l'	:
		case 'L'	:	ImprimeLista(Pontos); // Se o usuario teclar L ou l imprime a lista
						break;
		
		case 'p'	:
		case 'P'    : 	ImprimePilha(Orelhas); // Se o usuario teclar P ou p imprime a pilha
						break;
						
		case 'f'	:
		case 'F'	:	ImprimeFila(Vertices_Comuns); // Se o usuario teclar F ou f imprime a fila
						break;
		case 'r'    :
		case 'R'    :	restart(); // Recomeca o processo de desenho
						break;
		case 't'	: 	
		case 'T'	: 	geraTriangulacao(); // Gera a triangulacao
						T=1; // Ativa o flag da funçao desenhaTriangulacao na funçao Desenho
						break;				
	}
	glutPostRedisplay(); 
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

int main(int argc, char** argv) {
	
	sentinela = (no_l*) malloc(sizeof(no_l)); // Malloca o espaço de um no_l e atribui seu endereço para sentinela
	
	criaJanela(argc, argv);
	
	init_lista(&Pontos); // Inicializa a lista
	init_Fila(&Vertices_Comuns); // Inicializa a fila
	init_Pilha(&Orelhas); // Inicializa a pilha
	
    initOpenGL();
    
    initEventos();
    
    return 0;   
}
