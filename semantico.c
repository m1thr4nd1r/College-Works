/*
 * semantico.c
 *
 *  Created on: 03/12/2014
 *      Author: m1thr4nd1r
 */

#include "semantico.h"

void addId(struct idList **l, char *name)
{
	struct id *t = calloc(1,sizeof(struct id));
	t->name = name;
	t->next = NULL;

	if ((*l)->first == NULL)
	{
		(*l)->first = t;
		(*l)->last = t;
	}
	else
	{
		(*l)->last->next = t;
		(*l)->last = t;
	}
	(*l)->qnt++;
}

int declared(char *c, struct context *context)
{
	int flag = 0, i;
	struct id *var;

	while (context != NULL)
	{
		i = 0;
		while (i < 4 && !flag)
		{
			var = context->table[i]->first;
			while (var != NULL && !flag)
			{
				if (strcmp(var->name, c) == 0)
					flag = 1;
				var = var->next;
			}
			i++;
		}

		context = context->parent;
	}

	return flag;
}

int declare(struct treeNode *root, struct context *context)
{
	// declare ID DEC as TYPE .
	int vector;

	switch(root->elements[root->qnt - 2].child->elements[0].code)
	{
		case 29: // letter
						while (root != NULL && root->elements[1].child != NULL)
						{
							if (!declared(root->elements[1].child->elements[0].token, context))
							{
								vector = (root->elements[1].child->qnt > 1)? 1 : 0;
								if (vector)
									addId(&context->table[3], root->elements[1].child->elements[0].token);
								else
									addId(&context->table[2], root->elements[1].child->elements[0].token);
								root = root->elements[2].child;
							}
							else
							{
								printf("NAO");
								return 1;
							}
						}
						break;
		case 31: // number
						while (root != NULL && root->elements[1].child != NULL)
						{
							if (!declared(root->elements[1].child->elements[0].token, context))
							{
								vector = (root->elements[1].child->qnt > 1)? 1 : 0;
								if (vector)
									addId(&context->table[1], root->elements[1].child->elements[0].token);
								else
									addId(&context->table[0], root->elements[1].child->elements[0].token);
								root = root->elements[2].child;
							}
							else
							{
								printf("NAO");
								return 1;
							}
						}
						break;
	}

	return 0;
}

//void resize(struct treeNode *root);
//void put(struct treeNode *root);
//void cond(struct treeNode *root);
//void loop(struct treeNode *root);
//void foreach(struct treeNode *root);
//void read(struct treeNode *root);
//void write(struct treeNode *root);

struct context* createContext()
{
	struct context *c = NULL;
	c = calloc(1,sizeof(struct context));
//	c->table = calloc(1,sizeof(struct varTable));
	int i;
	for (i = 0; i < 4; i++)
		c->table[i] = calloc(1,sizeof(struct idList));
//	c->table->letter = calloc(1,sizeof(struct idList));
//	c->table->letterVec = calloc(1,sizeof(struct idList));
//	c->table->num = calloc(1,sizeof(struct idList));
//	c->table->numVec = calloc(1,sizeof(struct idList));

	return c;
}

void treeCheck(struct treeNode *root, struct context *context)
{
	if (root != NULL)
	{
		int i, flag;
		for (i = 0; i < root->qnt; i++)
		{
			if (root->elements[i].code == 43) // DECLARE
				declare(root->elements[i].child, context);
//			else if (root->elements[i].code == 57) // RESIZE
//				resize(root->elements[i].child);
//			else if (root->elements[i].code == 54) // PUT
//				put(root->elements[i].child);
//			else if (root->elements[i].code == 50) // IF
//				cond(root->elements[i].child);
//			else if (root->elements[i].code == 46) // FOR
//				loop(root->elements[i].child);
//			else if (root->elements[i].code == 47) // FOREACH
//				foreach(root->elements[i].child);
//			else if (root->elements[i].code == 55) // READ
//				read(root->elements[i].child);
//			else if (root->elements[i].code == 53) // PRINT
//				write(root->elements[i].child);
			else
				treeCheck(root->elements[i].child, context);
		}
	}
}

int main(int argc, char** argv)
{
	FILE *file = NULL;
	char *name = NULL;

	if (argc == 1)
	{
		name = calloc(100, sizeof(char));
		strcpy(name, "Entradas/declare.in");
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
			struct tokenList *tokens = NULL;
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
					struct treeNode* root;
					root = parseSLR(mat,tokens,prods);
					if(root != NULL)
					{
						printf("SIM\n");
						struct context *context = createContext();
						treeCheck(root, context);
						printf("s");
					}
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


