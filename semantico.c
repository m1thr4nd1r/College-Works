/*
 * semantico.c
 *
 *  Created on: 03/12/2014
 *      Author: m1thr4nd1r
 */

#include "semantico.h"

void printErrorCause(char *func, char *error, char *name)
{
	// if (name == NULL)
	// 	printf("%s: %s com problema\n",func,error);
	// else
		// printf("%s: %s (%s)\n",func,error,name);
}

void addId(struct idList **l, char *name)
{
	struct id *t = calloc(1,sizeof(struct id));
	t->name = name;
	t->alloc = 0;
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
					return i + 1;
				var = var->next;
			}
			i++;
		}

		context = context->parent;
	}

	return 0;
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
								printErrorCause("DECLARE","Redeclarar variáveis",root->elements[1].child->elements[0].token);
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
								printErrorCause("DECLARE","Redeclarar variáveis",root->elements[1].child->elements[0].token);
								return 1;
							}
						}
						break;
	}

	return 0;
}

int alloced(char *name, int type, struct context *context)
{
	struct id *var;

	while (context != NULL)
	{
		var = context->table[type-1]->first;
		while (var != NULL)
		{
			if (strcmp(var->name, name) == 0)
				return var->alloc;
			var = var->next;
		}

		context = context->parent;
	}

	return 0;
}

int arit(struct treeNode *root, struct context *context)
{
//	ARIT -> ARIT + F || ARIT - F || F
//	F -> F * G || F / G || F % G || G || - G
//	G -> ( ARIT ) || OPERANDO
//	OPERANDO -> CONS || VAR
//	CONS -> num || char
//	VAR -> id [ ARIT ] || id
	int i = 0, flag = 0;
	if (root != NULL)
	{
		while (i < root->qnt && !flag)
		{
			flag += arit(root->elements[i].child, context);
			i++;
		}

		if (!flag && root->elements[0].code == 26)
		{
			int j = declared(root->elements[0].token,context);
			if (!j)
			{
				printErrorCause("ARIT","Não declarar variáveis",root->elements[0].token);
				flag += 1;
			}
			else if ((j-1) % 2 && !alloced(root->elements[0].token, j, context))
			{
				printErrorCause("ARIT","Usar vetores não alocados",root->elements[0].token);
				flag += 1;
			}
			else if (root->qnt == 1 && (j-1) % 2)
			{
				printErrorCause("ARIT","Não indexar variáveis que sejam vetores",root->elements[0].token);
				flag += 1;
			}
			else if (root->qnt > 1 && j % 2)
			{
				printErrorCause("ARIT","Indexar variáveis que não sejam vetores",root->elements[0].token);
				flag += 1;
			}
		}
	}
	return flag;
}

int alloc(char *name, int type, struct context *context)
{
	struct id *var;

	while (context != NULL)
	{
		var = context->table[type-1]->first;
		while (var != NULL)
		{
			if (strcmp(var->name, name) == 0)
			{
				var->alloc = 1;
				return 0;
			}
			var = var->next;
		}

		context = context->parent;
	}

	return 1;
}

int resize(struct treeNode *root, struct context *context)
{
	// resize id to ARIT .
	int i = declared(root->elements[1].token, context);

	if (!i)
	{
		printErrorCause("RESIZE","Não declarar variáveis",root->elements[1].token);
		return 1;
	}
	else if (i % 2)
	{
		printErrorCause("RESIZE","Alocar variáveis que não sejam vetores",root->elements[1].token);
		return 1;
	}

	int j = arit(root->elements[3].child, context);

	if (!j)
	{
		j = alloc(root->elements[1].token, i, context);
		if (j)
			printErrorCause("RESIZE","alloc",NULL);
	}

	return j;
}

int var(struct treeNode *root, struct context *context)
{
	// id || id [ ARIT ]
	int i = declared(root->elements[0].token, context);

	if (!i)
	{
		printErrorCause("VAR","Não declarar variáveis",root->elements[0].token);
		return 1;
	}

	int j = 0;
	if ((i-1) % 2 && !alloced(root->elements[0].token, i, context))
	{
		printErrorCause("VAR","Usar vetores não alocados",root->elements[0].token);
		return 1;
	}
	if (root->qnt > 1 && i % 2)
	{
		printErrorCause("VAR","Indexar variáveis que não sejam vetores",root->elements[0].token);
		return 1;
	}
	else if (root->qnt > 1)
		j = arit(root->elements[2].child, context);

	if (j)
	{
		printErrorCause("VAR","ARIT",NULL);
		return 1;
	}

	return !i || j;
}

int put(struct treeNode *root, struct context *context)
{
//	put ARIT in VAR . || put string in id .
	int i, j = 0;
	if (root->elements[1].code == 39) // put ARIT in VAR .
	{
		i = arit(root->elements[1].child, context);

		if (!i)
			j = var(root->elements[3].child, context);
		else
			printErrorCause("PUT","ARIT",NULL);

		if (j)
			printErrorCause("PUT","VAR",NULL);

		return i || j;
	}
	else if (root->elements[1].code == 36) // put string in id .
	{
		i = declared(root->elements[3].token, context);
		if (!i)
		{
			printErrorCause("PUT","Não declarar variáveis",root->elements[3].token);
			return 1;
		}
		else if (i != 4)
		{
			printErrorCause("PUT","Variavel nao é vetor de letter",root->elements[3].token);
			return 1;
		}

		i = alloced(root->elements[3].token,i,context);
		if (!i)
		{
			printErrorCause("PUT","Vetor nao alocado",root->elements[3].token);
			return 1;
		}
	}

	return 0;
}

int rel(struct treeNode *root, struct context *context)
{
//	ARIT OP ARIT
	if (arit(root->elements[0].child,context) ||
		arit(root->elements[2].child,context))
	{
		printErrorCause("REL","ARIT",NULL);
		return 1;
	}
	return 0;
}

struct context* createContext()
{
	struct context *c = NULL;
	c = calloc(1,sizeof(struct context));
	int i;
	for (i = 0; i < 4; i++)
		c->table[i] = calloc(1,sizeof(struct idList));

	return c;
}

int cond(struct treeNode *root, struct context *context)
{
//	if REL then [ COMMAND ] ELSE
//	else [ COMMAND ] || &

	int i = rel(root->elements[1].child, context);
	if (i)
	{
		printErrorCause("IF","REL",NULL);
		return 1;
	}

	int j = 0;
	if (root->elements[4].child != NULL)
	{
		struct context *c = createContext();
		c->parent = context;
		j = treeCheck(root->elements[4].child, c);
		free(c);
	}

	if (j)
	{
		printErrorCause("IF","COMMAND",NULL);
		return 1;
	}

	int k = 0;
	if (root->elements[6].child != NULL)
	{
		struct context *c = createContext();
		c->parent = context;
		k = treeCheck(root->elements[6].child->elements[2].child, c);
		free(c);
	}

	if (k)
	{
		printErrorCause("ELSE","COMMAND",NULL);
		return 1;
	}

	return 0;
}

int loop(struct treeNode *root, struct context *context)
{
//	for VAR from ARIT to ARIT do [ COMMAND ]
	int i = var(root->elements[1].child, context);
	if (i)
	{
		printErrorCause("FOR","VAR",NULL);
		return 1;
	}

	i = arit(root->elements[3].child, context);
	if (i)
	{
		printErrorCause("FOR","ARIT",NULL);
		return 1;
	}

	i = arit(root->elements[5].child, context);
	if (i)
	{
		printErrorCause("FOR","ARIT",NULL);
		return 1;
	}

	if (root->elements[8].child != NULL)
	{
		struct context *c = createContext();
		c->parent = context;
		i = treeCheck(root->elements[8].child, c);
		free(c);
	}

	if (i)
	{
		printErrorCause("FOR","COMMAND",NULL);
		return 1;
	}

	return 0;
}

int foreach(struct treeNode *root, struct context *context)
{
//	foreach VAR in id do [ COMMAND ]
	int i = var(root->elements[1].child, context);
	if (i)
	{
		printErrorCause("FOREACH","VAR",NULL);
		return 1;
	}
	else
	{
		i = declared(root->elements[1].child->elements[0].token,context);
		if ((i-1) % 2 && root->elements[1].child->qnt == 1)
		{
			printErrorCause("FOREACH","Não indexar vetores", root->elements[1].child->elements[0].token);
			return 1;
		}
	}

	i = declared(root->elements[3].token,context);
	if (!i)
	{
		printErrorCause("FOREACH","Não declarar variáveis", root->elements[3].token);
		return 1;
	}
	else if (i % 2)
	{
		printErrorCause("FOREACH","Utilizar variáveis que não sejam vetores como vetores em loops vetoriais", root->elements[3].token);
		return 1;
	}
	else if (!alloced(root->elements[3].token, i, context))
	{
		printErrorCause("FOREACH","Usar vetores não alocados", root->elements[3].token);
		return 1;
	}

	i = 0;
	if (root->elements[6].child != NULL)
	{
		struct context *c = createContext();
		c->parent = context;
		i = treeCheck(root->elements[6].child, c);
		free(c);
	}

	if (i)
	{
		printErrorCause("FOREACH","COMMAND",NULL);
		return 1;
	}

	return 0;
}

int read(struct treeNode *root, struct context *context)
{
//	read VAR .
	int i = var(root->elements[1].child, context);
	if (i)
		printErrorCause("READ","VAR", NULL);

	return i;
}

int write(struct treeNode *root, struct context *context)
{
//	print OPERANDO . || print string .
	int i = 0;
	if (root->elements[1].child != NULL &&
		root->elements[1].child->elements[0].code == 60)
		i = var(root->elements[1].child->elements[0].child, context);

	if (i)
		printErrorCause("PRINT","VAR", NULL);

	return i;
}



int treeCheck(struct treeNode *root, struct context *context)
{
	int i;

	if (root != NULL)
	{
		for (i = 0; i < root->qnt; i++)
		{
			if (root->elements[i].code == 43)
			{
				if (declare(root->elements[i].child, context)) // DECLARE
					return 1;
			}
			else if (root->elements[i].code == 57) // RESIZE
			{
				if (resize(root->elements[i].child, context))
					return 2;
			}
			else if (root->elements[i].code == 54) // PUT
			{
				if (put(root->elements[i].child, context))
					return 3;
			}
			else if (root->elements[i].code == 50) // IF
			{
				if(cond(root->elements[i].child, context))
					return 4;
			}
			else if (root->elements[i].code == 46) // FOR
			{
				if(loop(root->elements[i].child, context))
					return 5;
			}
			else if (root->elements[i].code == 47) // FOREACH
			{
				if(foreach(root->elements[i].child,context))
					return 6;
			}
			else if (root->elements[i].code == 55) // READ
			{
				if (read(root->elements[i].child, context))
					return 7;
			}
			else if (root->elements[i].code == 53) // PRINT
			{
				if (write(root->elements[i].child, context))
					return 8;
			}
			else
				return treeCheck(root->elements[i].child, context);
		}
	}

	return 0;
}

int main(int argc, char** argv)
{
	FILE *file = NULL;
	char *name = NULL;

	if (argc == 1)
	{
		name = calloc(100, sizeof(char));
		strcpy(name, "foo.in");
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
						int t = treeCheck(root, context);
						if (t > 0)
//							printf("NAO(%d)\n",t);
							printf("NAO\n");
						else
							printf("SIM\n");
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
