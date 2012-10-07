#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#if defined (__APPLE__) || defined(MACOSX)
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

#include "EstruturasDeDados.h"
#include "winGL.h"
#include "quadtree.h"
	
unsigned char* 	imageGray = NULL;	// image file
int 			iHeight, 
				iWidth;

tNoArvore* 		raiz = NULL;

int nivel_max;	// Maior nivel da quadtree
int nivel_desejado;	// Nivel desejado pelo usuario (para ter seus nos desenhados)
int flag=0; // Flag para desenhar com erro ou nao
int nivel_dim_menor; // Nivel maximo considerando-se uma figura quadrada de dimensao = a menor dimensao da figura
float error = 0; // Porcentagem de erro aceitavel

bool desenha = FALSE;

/// ***********************************************
/// ******                                   ******
/// ***********************************************

void calcular_erro(tNoArvore *a , tNoArvore *pai)
{	
	if (pai != NULL)
		if (((pai->q->cor != 255) && ( pai->q->cor != 0)))
		{
			calcular_erro(a,pai->filho[0]); // Chama a funcao recursivamente para cada um dos filhos do nó
			calcular_erro(a,pai->filho[1]);
			calcular_erro(a,pai->filho[2]);
			calcular_erro(a,pai->filho[3]);
		
			// O erro eh a diferença entre a cor media e a cor de cada pixel dos filhos (1) , dividido pela quantidade de pixels (2)
			
			if (pai->q->nivel == nivel_max - 1) // Se o nó pai for pai de folhas, entao realiza a conta
			{	// (1) - O erro é calculado fazendo abs(cor do filho[0] - cor do pai) + abs(cor do filho[1] - cor do pai)...
				//       Isso é feito para todos os filhos folha do nó
				if (pai->filho[0] != NULL)
					a->q->erro = a->q->erro + abs(pai->filho[0]->q->cor - a->q->cor);
				if (pai->filho[1] != NULL)
					a->q->erro = a->q->erro + abs(pai->filho[1]->q->cor - a->q->cor);
				if (pai->filho[2] != NULL)
					a->q->erro = a->q->erro + abs(pai->filho[2]->q->cor - a->q->cor);
				if (pai->filho[3] != NULL)
					a->q->erro = a->q->erro + abs(pai->filho[3]->q->cor - a->q->cor);								
			}
		}
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

tNoArvore* preencher_no(int nivel,int filho,tPonto base_pai); // Prototipo da funçao preencher_no (para nao dar erro no separar_retangulo)

/// ***********************************************************************
/// ** 
/// ***********************************************************************

// Funcao que separa um retangulo 

void separar_retangulo(tNoArvore *a)
{
	// O filho[1] de um retangulo sempre é nulo
	// O filho[3] de um retangulo sempre é nao nulo
	
	a->filho[3] = preencher_no(a->q->nivel+1,3,a->q->pBase); // Preenche o filho[3] do nó
	if (a->q->h > a->q->w) // Se a altura do no for maior que sua largura (retangulo em pe)
		a->filho[0] = preencher_no(a->q->nivel+1,0,a->q->pBase);  // Filho[0] nao eh nulo e é preenchido
	else if (a->q->w > a->q->h) // Se a largura do no for maior que sua altura (retangulo deitado)
		a->filho[2] = preencher_no(a->q->nivel+1,2,a->q->pBase); // Filho[2] nao eh nulo e é preenchido			
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

// Funcao que define os valores de um novo no

tNoArvore* preencher_no(int nivel,int filho,tPonto base_pai)
{
	tNoArvore *Novo;
	
	Novo = (tNoArvore*) malloc (sizeof(tNoArvore)); // Aloca o no Novo
	Novo->q = (tQuadrante*) malloc (sizeof(tQuadrante)); // Inicializo o quadrante de Novo;
	
	if (Novo != NULL) // Se conseguir alocar o no Novo
	{
		Novo->q->nivel = nivel;	// Seta o nivel do no para o nivel que ele esta na arvore
		
		if ((iWidth > iHeight) && (nivel > nivel_dim_menor)) 
		// Se a largura for maior que a altura e o nivel for maior que o nivel da dimensao menor
		{
			Novo->q->w = (iWidth /exp2(nivel-1)); // Largura de um no é: Largura_Max / 2^(nivel-1)
																					   // Nivel - 1 porque o nivel começa de 1
												
			Novo->q->h = (Novo->q->w + 1) / 2; // A altura sera a largura + 1 (devido ao arredondamento) dividido por 2 para formar um novo
											   // retangulo
		}
		else if ((iHeight > iWidth) && (nivel > nivel_dim_menor))
		// Se a altura for maior que a largura e o nivel for maior que o nivel da dimensao menor
		{
			Novo->q->h = (iHeight /exp2(nivel-1)); // Altura de um no é: Altura_Max / 2^(nivel-1) 
																			   		  // Nivel - 1 porque o nivel começa de 1
			Novo->q->w = (Novo->q->h + 1) / 2; // A largura sera a altura + 1 (devido ao arredondamento) dividido por 2 para formar um novo
											   // retangulo
		}
		else
		// Senao a figura é quadrada (iWidth == iHeight)
		{
			Novo->q->h = (iHeight /exp2(nivel-1)); // Altura de um no é: Altura_Max / 2^(nivel-1) 
																					 // Nivel - 1 porque o nivel começa de 1
														
			Novo->q->w = (iWidth /exp2(nivel-1)); // Largura de um no é: Largura_Max / 2^(nivel-1)
																					   // Nivel - 1 porque o nivel começa de 1
		}
				
		if (filho == 0) // Se for o filho[0] (filho do noroeste)
		{
			Novo->q->pBase.x = base_pai.x; // base.x = base do pai
			Novo->q->pBase.y = base_pai.y + Novo->q->h; // base.y = base do pai + h
		}
		else if (filho == 1) // Se for o filho[1] (filho do nordeste)
		{
			Novo->q->pBase.x = base_pai.x + Novo->q->w; // base.x = base do pai + w
			Novo->q->pBase.y = base_pai.y + Novo->q->h; // base.y = base do pai + h
		}
		else if (filho == 2) // Se for o filho[2] (filho do sudeste)
		{
			Novo->q->pBase.x = base_pai.x + Novo->q->w; // base.x = base do pai + w
			Novo->q->pBase.y = base_pai.y; // base.y = base do pai
		}
		else if (filho == 3)  // Se for o filho[3] (filho do sudoeste)
			Novo->q->pBase = base_pai; // base = base do pai
						
		if ((Novo->q->h == 1) && (Novo->q->w == 1)) // Se o no tiver a altura e largura de um pixel e nao estiver fora da imagem
		{
			Novo->q->cor = (int) imageGray[ Novo->q->pBase.y * iWidth + Novo->q->pBase.x];
			// Sua cor eh dada pelo y de sua base * Maior Dimensao da imagem + o x de sua base
			Novo->q->erro = 0; // E nesse caso, o erro do no é 0 (o nó eh um pixel)
		}
		else 
		{
			Novo->q->cor = 0; // Senao, seta a cor para 0
			Novo->q->erro = -1; // E seta o erro para -1 (valor padrao para erros que ainda nao foram calculados)
		}
							
		Novo->filho[0] = NULL; // Seta seus filhos para Nulo
		Novo->filho[1] = NULL;
		Novo->filho[2] = NULL;
		Novo->filho[3] = NULL;
	
		if (((Novo->q->h == 1) && (Novo->q->w != 1)) || ((Novo->q->h != 1) && (Novo->q->w == 1))) 
		// Se o no formar um retangulo que nao possa ser dividido em uma das dimensoes (h ou w == 1)
			separar_retangulo(Novo);
	}	
	
	return Novo; // Retorna o no Novo, parcialmente preenchido
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

// Funcao que coloca o no em sua posicao na arvore

void alocar_no(tNoArvore **Folha,int nivel,int filho,tPonto base_pai)
{
	if ((iHeight > iWidth) || (iWidth > iHeight)) // Se a figura é nao quadrada
	{
		if (nivel <= nivel_dim_menor) // Cria a arvore ate o nivel da menor dimensao 
									  // (ou seja, chega no ponto onde nao se pode mais dividir o retangulo em uma das dimensoes)
		{
			if (*Folha == NULL) // Se a Folha atual for nula
				*Folha = preencher_no(nivel,filho,base_pai);  // Aloca Novo no lugar de Folha
			if (((*Folha)->filho[0] == NULL) && ((*Folha)->q->erro != -2)) // Se o filho[0] nao for nulo
				alocar_no(&(*Folha)->filho[0],nivel+1,0,(*Folha)->q->pBase); 
				// Chama alocar_no, utilizando o filho[0], o nivel incrementado, a posiçao do filho no vetor dos filhos (NW) e a base do pai
			if (((*Folha)->filho[1] == NULL) && ((*Folha)->q->erro != -2)) // Se o filho[1] nao for nulo
				alocar_no(&(*Folha)->filho[1],nivel+1,1,(*Folha)->q->pBase);
				// Chama alocar_no, utilizando o filho[1], o nivel incrementado, a posiçao do filho no vetor dos filhos (NE) e a base do pai
			if (((*Folha)->filho[2] == NULL) && ((*Folha)->q->erro != -2)) // Se o filho[2] nao for nulo
				alocar_no(&(*Folha)->filho[2],nivel+1,2,(*Folha)->q->pBase);
				// Chama alocar_no, utilizando o filho[2], o nivel incrementado, a posiçao do filho no vetor dos filhos (SE) e a base do pai
			if (((*Folha)->filho[3] == NULL) && ((*Folha)->q->erro != -2)) // Se o filho[3] nao for nulo
				alocar_no(&(*Folha)->filho[3],nivel+1,3,(*Folha)->q->pBase);
				// Chama alocar_no, utilizando o filho[3], o nivel incrementado, a posiçao do filho no vetor dos filhos (SW) e a base do pai
		}
	}
	else
	{
		if (nivel <= nivel_max) // Se o nivel for menor ou igual ao nivel maximo, e a figura for quadrada
		{
			if (*Folha == NULL) // Se a Folha atual for nula
				*Folha = preencher_no(nivel,filho,base_pai);  // Aloca Novo no lugar de Folha
			if (((*Folha)->filho[0] == NULL) && ((*Folha)->q->erro != -2)) // Se o filho[0] nao for nulo
				alocar_no(&(*Folha)->filho[0],nivel+1,0,(*Folha)->q->pBase); 
				// Chama alocar_no, utilizando o filho[0], o nivel incrementado, a posiçao do filho no vetor dos filhos (NW) e a base do pai
			if (((*Folha)->filho[1] == NULL) && ((*Folha)->q->erro != -2)) // Se o filho[1] nao for nulo
				alocar_no(&(*Folha)->filho[1],nivel+1,1,(*Folha)->q->pBase);
				// Chama alocar_no, utilizando o filho[1], o nivel incrementado, a posiçao do filho no vetor dos filhos (NE) e a base do pai
			if (((*Folha)->filho[2] == NULL) && ((*Folha)->q->erro != -2)) // Se o filho[2] nao for nulo
				alocar_no(&(*Folha)->filho[2],nivel+1,2,(*Folha)->q->pBase);
				// Chama alocar_no, utilizando o filho[2], o nivel incrementado, a posiçao do filho no vetor dos filhos (SE) e a base do pai
			if (((*Folha)->filho[3] == NULL) && ((*Folha)->q->erro != -2)) // Se o filho[3] nao for nulo
				alocar_no(&(*Folha)->filho[3],nivel+1,3,(*Folha)->q->pBase);
				// Chama alocar_no, utilizando o filho[3], o nivel incrementado, a posiçao do filho no vetor dos filhos (SW) e a base do pai
		}
	}
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

// Funcao para adicionar o no na arvore 

int criar_arvore(tNoArvore **a)
{
	tPonto aux; // Variavel auxiliar, para utilizar na chamada da funçao alocar_no
	
	// Formula para calcular a quantidade de nos totais dado o maior nivel:
	// 1 * (1 - (4 ^ n) ) / (1 - 4)
		// ((4^maior_nivel) - 1 ) / 3
	
	aux.x = 0; // Inicializar o auxiliar
	aux.y = 0;
	
	alocar_no(a,1,3,aux); 
	// Cria a arvore, chama a funcao pela primeira vez, usando a raiz da arvore (a), o nivel (1), a posiçao (3 ou SW) e a base do pai (aux)
	
	return 1; // Retorna 1 (conseguiu adicionar)
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

// Funcao para imprimir a arvore

void imprimir (tNoArvore *a)
{
	if (a != NULL) // Se a raiz nao for nula
	{
		if (a->q->erro > 0)	
		// O if nao eh nescessario, utiliza-se so para limitar os elementos que vao ser impressos
			printf("Altura: %d, Largura: %d, Nivel: %d, Base(x: %d | y: %d), Cor: %d, Erro: %0.2f\n",a->q->h,a->q->w,a->q->nivel,a->q->pBase.x,a->q->pBase.y,a->q->cor,a->q->erro); // Imprime o no
		if (a->filho[0] != NULL) // Se o filho[0] nao for nulo
			imprimir(a->filho[0]); // Chama a funcao imprimir tendo o filho[0] como raiz
		if (a->filho[1] != NULL) // Se o filho[0] nao for nulo
			imprimir(a->filho[1]); // Chama a funcao imprimir tendo o filho[1] como raiz
		if (a->filho[2] != NULL) // Se o filho[0] nao for nulo
			imprimir(a->filho[2]); // Chama a funcao imprimir tendo o filho[2] como raiz
		if (a->filho[3] != NULL) // Se o filho[0] nao for nulo
			imprimir(a->filho[3]); // Chama a funcao imprimir tendo o filho[3] como raiz
	}
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

// Funcao para dar cor e calcular o erro em todos os nos

void preenche_cor_erro (tNoArvore *a)
{
	int i=0,qnt=0;
	
	if ((a != NULL) && (a->q != NULL))
	{
		if (a->q->erro == -1) // Se o erro for -1 (flag para erro ainda nao atualizado)
		{
			preenche_cor_erro(a->filho[0]); // Chama recursivamente os elementos da arvore
			preenche_cor_erro(a->filho[1]);
			preenche_cor_erro(a->filho[2]);
			preenche_cor_erro(a->filho[3]);
			
			// A cor do pai eh a media aritmetica da cor dos filhos
			
			for (i=0;i<4;i++)
				if (a->filho[i] != NULL) // Se o filho nao for nulo
				{
					a->q->cor = a->q->cor + a->filho[i]->q->cor; // Seu pai tem sua cor adicionada a do filho
					qnt++; // Incrementa o contador de filhos
				}
					
			a->q->cor = a->q->cor / qnt; // Divide a soma da cor dos filhos pela quantidade de filhos
			
			a->q->erro = 0;  // Seta erro para zero
			
			if ((a->q->cor != 255) && (a->q->cor != 0)) // Se a cor do no não for 255 nem 0 (branco nem preto)
			{
				calcular_erro(a,a); // Chama a funcão calcular_erro
				a->q->erro = a->q->erro  / (a->q->w * a->q->h); 
				// (2) - O resultado da funçao calcular erro é dividido pela quantidade de pixels que o nó substitui
			}
		}
	}
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

// Funcao para desenhar a Quadtree

void desenhaQuadtree(tNoArvore* a) 
{	
	tPonto p1; // Variavel auxiliar
		
	if (a != NULL)
	{
		if ((flag) && (a->q->erro <= error) && (a->q->nivel <= nivel_desejado)) 
		// Se o flag estiver ativado, o erro do nó for menor ou igual ao erro pedido
		// e o nivel do nó for menor ou igual ao nivel desejado (entao o nó esta dentro do erro pedido)
		{	
			// Desenha a area do no
		
			p1.x = a->q->pBase.x + a->q->w;
			p1.y = a->q->pBase.y + a->q->h;
			desenhaQuadrante(a->q->pBase,p1,a->q->cor);		 	
		}
		else // Senao
		{				
			if (a->q->nivel == nivel_desejado) // Se o no estiver no nivel desejado 
			{
				// Desenha a area do no
			
				p1.x = a->q->pBase.x + a->q->w;
				p1.y = a->q->pBase.y + a->q->h;
				desenhaQuadrante(a->q->pBase,p1,a->q->cor);		 	
			}
		
			if (a->filho[0] != NULL) // Se o filho[0] nao for nulo
				desenhaQuadtree(a->filho[0]); // Chama a funcao para desenhar os nos da subarvore de raiz a->filho[0]
			if (a->filho[1] != NULL) // Se o filho[1] nao for nulo
				desenhaQuadtree(a->filho[1]); // Chama a funcao para desenhar os nos da subarvore de raiz a->filho[1]
			if (a->filho[2] != NULL) // Se o filho[2] nao for nulo
				desenhaQuadtree(a->filho[2]); // Chama a funcao para desenhar os nos da subarvore de raiz a->filho[2]
			if (a->filho[3] != NULL) // Se o filho[3] nao for nulo
				desenhaQuadtree(a->filho[3]); // Chama a funcao para desenhar os nos da subarvore de raiz a->filho[3]
		}
	}
}
	
/// ***********************************************************************
/// ** 
/// ***********************************************************************

// Funcao para montar a Quadtree

void montaQuadtree() {
		
	criar_arvore(&raiz);	// Chama a funcao criar_arvore			
	preenche_cor_erro(raiz); // Chama a funcao preencher_cor_erro
	printf("\nMontou a Quadtree\n");
}
	
/// ***********************************************************************
/// ** 
/// ***********************************************************************

void teclado(unsigned char key, int x, int y) {

	switch (key) {
		case 27		: 	exit(0);
						break;				
		case 'q'	:
		case 'Q'	: 	montaQuadtree();
						break;
		case 'F'	:
		case 'f'	:	flag = !flag; // Ativa o flag
						break;
		case 'k'	:
		case 'K'	:	if ((error >= 0.05) && (flag) && (desenha))	// Se o erro desejado for maior que 0.04
						{
							error -= 0.05; // Incrementa o erro de 0.05 (5%)
							printf("Erro: %f\n",error);
						}
						break;
		case 'l'	:
		case 'L'	:	if ((flag) && (desenha)) // Se o erro desejado for menor que 1
						{
							error += 0.05; // Incrementa o erro de 0.05 (5%)
							printf("Erro: %f\n",error);
						}
						break;
						
		case 'm'	:
		case 'M'	:	if((nivel_desejado < nivel_max) && (desenha)) // Se o nivel desejado for menor que o nivel maximo
						{
							nivel_desejado++; // Incrementa o nivel desejado
							printf("Nivel Desejado: %d\n",nivel_desejado);
						}
						break;
		case 'n'	:
		case 'N'	:	if ((nivel_desejado > 1) && (desenha)) // Se o nivel desejado for maior que 1
						{
							nivel_desejado--; // Decrementa o nivel desejado
							printf("Nivel Desejado: %d\n",nivel_desejado);
						}
						break;					
		case 'i'	:
		case 'I'	: 	desenha = !desenha; // Flag para ativar o desenhaQuadtree
						break;				
		}
	glutPostRedisplay();
}
		
/// ***********************************************************************
/// **
/// ***********************************************************************

void mouse(int button, int button_state, int x, int y ) {

	if 	(button_state == GLUT_DOWN ) {
		switch (button) {
			
			case GLUT_LEFT_BUTTON	: 	printf("botao esquerdo?\n");
										break;
	
			case GLUT_RIGHT_BUTTON	:	imprimir(raiz); // Clique com o botao direito imprime a arvore
										break;
			}
		glutPostRedisplay();
		}
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void desenho(void) {

    glClear (GL_COLOR_BUFFER_BIT); 
    
    glColor3f (1.0, 1.0, 1.0);
    
    if (desenha)
    {
		tPonto p0, p1;
	 
		p0.x = p0.y = 0;
		p1.x = iWidth;
		p1.y = iHeight;
	
		desenhaQuadrante(p0, p1, 128);

    	desenhaQuadtree(raiz); // Chama a funcao para desenhar a Quadtree
    }
    
    else
    	glDrawPixels( iWidth, iHeight, GL_LUMINANCE, GL_UNSIGNED_BYTE, imageGray );
   	
    glutSwapBuffers ();
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

int main(int argc, char** argv) {
	
	char* filename = "PPM/retangular3.ppm";
	
	if (argc > 1)
		filename = argv[1];
	
	imageGray = leImagem(filename);
			
	/*		
	   log 4 da quantidade maxima de nos do maior nivel = maior nivel - 1 ( maior nivel - 1 porque nivel começa de 1)
	   log de 4 = log 2 /2
	   Quantidade maxima de nos no maior nivel = Altura_Max * Largura_Max
	*/
		
	if (iWidth > iHeight) // Se a largura da figura for maior que sua altura
	{
		nivel_max = (((log2(iWidth * iWidth))/2)) + 1; // Calcula o nivel maximo tendo como base um quadrado com o tamanho da largura
		nivel_dim_menor = (((log2(iHeight * iHeight))/2)) + 1;
		// Calcula o nivel maximo de uma figura quadrada de dimensao igual a menor dimensao da figura
	}
	else // Senao
	{
		nivel_max = (((log2(iHeight * iHeight))/2)) + 1; // Calcula o nivel maximo tendo como base um quadrado com o tamanho da altura
		nivel_dim_menor = (((log2(iWidth * iWidth))/2)) + 1; 
		// Calcula o nivel maximo de uma figura quadrada de dimensao igual a menor dimensao da figura
	}
	
	nivel_desejado = nivel_max; // Inicializa o nivel desejado com o nivel maximo
	
	criaJanela(argc, argv);

    initOpenGL();
    
    initEventos();
    
    return 0;   
}
