/*
 * semantico.c
 *
 *  Created on: 03/12/2014
 *      Author: m1thr4nd1r
 */

#include "semantico.h"

int main(int argc, char** argv)
{
	FILE *file = NULL;
	char *name = NULL;

	if (argc == 1)
	{
		name = calloc(100, sizeof(char));
		strcpy(name, "Entradas/-declare.in");
	}
	else
//		Caso seja passado como ./a.exe < test.in, entao o indice abaixo troca de 1 para 2
		name = argv[1];

	file = fopen(name , "rt");

	if (file != NULL)
	{
		char *text = NULL;
		text = readFile(file);

		if (text != NULL)
		{
			struct tokenList *tokens;
			int tokensAmount = 0, emptyAmount = 0;
			tokens = tokenizer(text);

			int codes = 0;
			codes = verifyTokens(tokens);

			if (codes)
			{
				int **mat = NULL;
				struct prod *prods = NULL;
				name = calloc(20,sizeof(char));
				strcpy(name, "Data.csv");
				file = fopen(name, "rt");
				if (file != NULL)
				{
					mat = readMatrix(file);
					prods = createProds();
					if(parseSLR(mat,tokens,tokensAmount - emptyAmount + 1,prods))
						printf("SIM\n");
					else
						printf("NAO\n");
				}
				else
					printf("Problemas na leitura da tabela\n");
			}
		}
		else
			printf("ARQUIVO INVALIDO!\n");
	}
	else
		printf("Problemas na abertura do arquivo\n");

	return 0;
}


