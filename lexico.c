#include "lexico.h"

//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h> // malloc calloc
//#include <ctype.h> // isdigit isalpha isalnum
//#include <limits.h> // INT_MAX INT_MIN

// --------------Analise Lexica-------------- //

const char terminals[][9] = {"$","%","(",")","*","+",",","-",".","/","<","<=","<>","=",">",">=","[","]","as","char","declare","do","else","for","foreach","from","id","if","in","letter","num","number","print","put","read","resize","string","then","to"};

void addToken(struct tokenList **l, struct token *token)
{
	struct tokenNode *t = calloc(1,sizeof(struct tokenNode));
	t->token = token;
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

char* toLower(char *word)
{
	int i;
	for (i = 0; i < strlen(word); i++)
		word[i] = tolower(word[i]);

	return word;
}

int terminalIndex(char *token)
{
	if (!strcmp(token,"&")) return INT_MIN;
	int size = 39; // baseado no vetor de terminais (terminals)
	int i = 0;
	while(i < size && strcmp(terminals[i], token))
		i++;
	if (i == size)
		i = 26;
	return i;
}

int tokenToCode(char *token, char type)
{
	int i = 0;
	token = toLower(token);

	switch(type)
	{
		case 't':
		case 'i':
					i = terminalIndex(token);
					break;
		case 'c':
					i = 19;
					break;
		case 's':
					i = 36;
					break;
		case 'n':
					i = 30;
					break;
	}

//	printf("Token:%s|i:%d\n", token, i);
	return i;
}

void printError(struct token *t)
{
	printf("LINHA %d: %s\n", t->line, t->text);
}

int isPrintable(int code)
{
	if (code >= 32 && code <= 126)
		return 1;
	return 0;
}

int isSeparator(int code)
{
	if (code == 37 || code == 91 || code == 93 ||
		code == 39 || code == 34 || code == 00 ||
		code == 9  || code == 10 || code == 32 ||
		(code > 59 && code < 63) ||
		(code > 38 && code < 48))
		return 1;
	return 0;
}

int nextSeparator(char *line, char type)
{
	int i = 0, size = (int) strlen(line);

	switch (type)
	{
		case 's':
					i++;

					while (	i < size &&
							line[i] != '\n' &&
							line[i] != '\t' &&
							line[i] != 0 &&
							line[i] != '\"' &&
							line[i] != EOF)
								if (line[i] == '\\' && (line[i+1] == '\'' || line[i+1] == '\"' || line[i+1] == 't' || line[i+1] == 'n' || line[i+1] == '\\'))
									i+=2;
								else
									i++;

						i++;

					break;
		case 'c':
					i++;

					while (	i < size &&
							line[i] != '\n' &&
							line[i] != '\t' &&
							line[i] != 0 &&
							line[i] != '\'' &&
							line[i] != EOF)
								if (line[i] == '\\' && (line[i+1] == '\'' || line[i+1] == '\"' || line[i+1] == 't' || line[i+1] == 'n' || line[i+1] == '\\'))
									i+=2;
								else
									i++;
						i++;

					break;
		case 'n':
		case 'i':
					while (	i < size &&
							line[i] != EOF &&
							!isSeparator(line[i]) &&
							isalnum(line[i]))
						i++;
					break;
		case 't':
					if ((line[i] == '<' && (line[i+1] == '>' || line[i+1] == '=')) ||
					    (line[i] == '>' && line[i+1] == '='))
							i = 2;
					else
							i = 1;
	}

	return i;
}

struct tokenList* tokenizer(char *file, int *amount, int *emptyAmount)
{
	int i = 0, j = 0, k = 0, line = 1;
	struct tokenList *tokens = NULL;
	struct token *token = NULL;

	do
	{
		tokens = (struct tokenList*) calloc((int)strlen(file), sizeof(struct tokenList));
	}
	while (tokens == NULL);

	while (file[i] > 0 && i < strlen(file))
	{
		token = (struct token*) calloc(1,sizeof(struct token));

		int separator = -1;

		if (file[i] == '\'')
			separator = nextSeparator(file+i,'c');
		else if (file[i] == '\"')
			separator = nextSeparator(file+i,'s');
		else if (isalpha(file[i]))
			separator = nextSeparator(file+i,'i');
		else if (isdigit(file[i]))
			separator = nextSeparator(file+i,'n');
		else
			separator = nextSeparator(file+i,'t');

		do
		{
			token->text = (char*) calloc(separator+1, sizeof(char));
		} while (token->text == NULL);

		strncat(token->text, file+i, separator);
		token->text[separator] = '\0';
		token->line = line;

		//printf("|(%d)%s/\n",j, token->text);

		if (token->text[(int)strlen(token->text) - 1] == '\n')
			line++;

		if (!strcmp(token->text," ") || !strcmp(token->text,"\n") || !strcmp(token->text,"\t"))
//			k++;
			free(token);
		else
			addToken(&tokens,token);

		j++;
		i += separator;
	}

	*amount = j;
	*emptyAmount = k;
	return tokens;
}

int validNumber(struct token *t)
{
	int j = 1;

	while (isdigit(t->text[j]) && j < 10)
		j++;

	if (j == strlen(t->text))
		return 1;
	else
	{
		printError(t);
		return 0;
	}
}

int validChar(struct token *t)
{
	int j = 1, size = strlen(t->text), count = 0;

	if (t->text[size-1] == '\'')
	{
		while (isPrintable(t->text[j]) && j < size - 1)
		{
			if ( t->text[j] == '\\' &&
				 (t->text[j+1] == '\"' || t->text[j+1] == '\\' || t->text[j+1] == 't' || t->text[j+1] == 'n'  || t->text[j+1] == '\''))
				j++;
			else if (t->text[j] == '\\' || t->text[j] == '\"')
				break;
			j++;
			count++;
		}

		if (j == size - 1 && count == 1)
			return 1;
		else
		{
			printError(t);
			return 0;
		}
	}
	else
	{
		if (t->text[size-1] == '\t' || t->text[size-1] == '\n')
		{
			char temp = t->text[size-1];
			t->text[size-1] = '\0';
			printError(t);
			t->text[size-1] = temp;
		}
		else
			printError(t);

		return 0;
	}
}

int validString(struct token *t)
{
	int j = 1, size = strlen(t->text), count = 0;

	if (t->text[size-1] == '\"')
	{
		while (isPrintable(t->text[j]) && j < size - 1)
		{
			if ( t->text[j] == '\\' &&
				 (t->text[j+1] == '\"' || t->text[j+1] == '\\' || t->text[j+1] == 't' || t->text[j+1] == 'n'  || t->text[j+1] == '\''))
				j++;
			else if (t->text[j] == '\\' || t->text[j] == '\'')
				break;
			j++;
			count++;
		}

		if (j == size - 1 && count <= 256)
			return 1;
		else
		{
			printError(t);
			return 0;
		}
	}
	else
	{
		if (t->text[size-1] == '\t' || t->text[size-1] == '\n')
		{
			char temp = t->text[size-1];
			t->text[size-1] = '\0';
			printError(t);
			t->text[size-1] = temp;
		}
		else
			printError(t);

		return 0;
	}
}

int validSeparator(struct token *t)
{
	if ((isSeparator(t->text[0]) && strlen(t->text) == 1) ||
		(strlen(t->text) == 2 && ((t->text[0] == '>' && t->text[1] == '=') ||
							(t->text[0] == '<' && (t->text[1] == '>' || t->text[1] == '=')))))
		return 1;
	else
	{
		printError(t);
		return 0;
	}
}

int verifyTokens(struct tokenList* tokens, int amount, int emptyAmount)
{
	int i, index = 0, flag = 0;
	struct tokenNode* node = tokens->first;

	for (i = 0; i < tokens->qnt; i++)
	{
		if (node->token->text[0] == '\'')
		{
			if (validChar(node->token))
			{
				node->token->code = tokenToCode(node->token->text,'c');
				index++;
			}
			else
				flag = 1;
		}
		else if (node->token->text[0] == '\"')
		{
			if (validString(node->token))
			{
				node->token->code = tokenToCode(node->token->text,'s');
				index++;
			}
			else
				flag = 1;
		}
		else if (isalpha(node->token->text[0]))
		{
			node->token->code = tokenToCode(node->token->text,'i');
			index++;
		}
		else if (isdigit(node->token->text[0]))
		{
			if (validNumber(node->token))
			{
				node->token->code = tokenToCode(node->token->text,'n');
				index++;
			}
			else
				flag = 1;
		}
		else if (validSeparator(node->token))
		{
			node->token->code = tokenToCode(node->token->text,'t');
			index++;
		}
		else
			flag = 1;

		node = node->next;
	}

	if (!flag)
		return 1;
//		return codes;
	else
//		return NULL;
		return 0;
}

char* readFile(FILE *file)
{
	char *text = NULL;

	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	rewind(file);

	text = calloc(size+2, sizeof(char));
	fread(text, 1, size+2, file);
	fclose(file);

	int i = 0;
	while (i < size && (isPrintable(text[i]) || text[i] == 9 || text[i] == 10))
		i++;
	text[size+1] = EOF;

	if (i == size)
		return text;
	else
		return NULL;
}

// --------------------------------------------- //
// --------------Analise Sintatica-------------- //

//const char nonterminals[][9] = {"ARIT","COMMAND","CONS","DEC","DECLARE","ELSE","F","FOR","FOREACH","G","ID","IF","OP","OPERANDO","PRINT","PUT","READ","REL","RESIZE","S","TYPE","VAR"};
//
//char p[] = {"SS > S $\nS > COMMAND\nCOMMAND > IF COMMAND\nCOMMAND > DECLARE COMMAND\nCOMMAND > RESIZE COMMAND\nCOMMAND > PUT COMMAND\nCOMMAND > FOR COMMAND\nCOMMAND > FOREACH COMMAND\nCOMMAND > READ COMMAND\nCOMMAND > PRINT COMMAND\nCOMMAND >\nDECLARE > declare ID DEC as TYPE .\nDEC > , ID DEC\nDEC >\nID > id\nID > id [ ]\nTYPE > number\nTYPE > letter\nRESIZE > resize id to ARIT .\nPUT > put ARIT in VAR .\nPUT > put string in id .\nARIT > ARIT + F\nARIT > ARIT - F\nARIT > F\nF > F * G\nF > F / G\nF > F % G\nF > G\nF > - G\nG > ( ARIT )\nG > OPERANDO\nOPERANDO > CONS\nOPERANDO > VAR\nCONS > num\nCONS > char\nVAR > id [ ARIT ]\nVAR > id\nREL > ARIT OP ARIT\nOP > <\nOP > >\nOP > <=\nOP > >=\nOP > <>\nOP > =\nIF > if REL then [ COMMAND ] ELSE\nELSE > else [ COMMAND ]\nELSE >\nFOR > for VAR from ARIT to ARIT do [ COMMAND ]\nFOREACH > foreach VAR in id do [ COMMAND ]\nREAD > read id .\nPRINT > print OPERANDO .\nPRINT > print string ."};
//
//struct prod{
//	int p, n, *q;
//	char *lhs, *productions; // Para Debug
//} *r;
//
//struct node{
//	int code;
//	struct node *next;
//};
//
//struct stack{
//	struct node *first;
//	struct node *last;
//	int qnt;
//};
//
//void addElementN(struct stack **l, int code)
//{
//	struct node *e = malloc(sizeof(struct node));
//	e->code = code;
//	e->next = NULL;
//
//	if ((*l)->first == NULL)
//	{
//		(*l)->first = e;
//		(*l)->last = e;
//	}
//	else
//	{
//		(*l)->last->next = e;
//		(*l)->last = e;
//	}
//	(*l)->qnt++;
//}
//
////void addElements(struct stack **l, int *nodes, int amount)
//void addElements(struct stack **l, struct tokenList *list)
//{
//	int i;
////	struct node *e;
//	struct tokenNode *node = list->first;
//	for (i = 0; i < list->qnt; i++)
//	{
////		e = malloc(sizeof(struct node));
////		e->code = nodes[i];
////		e->next = NULL;
//
////		addElement(l,e);
//		addElementN(l,node->token->code);
//		node = node->next;
//	}
//}
//
//void addElementI(struct stack **l, int code)
//{
//	struct node *e = malloc(sizeof(struct node));
//	e->code = code;
//	e->next = NULL;
//	if ((*l)->first == NULL)
//	{
//		(*l)->first = e;
//		(*l)->last = e;
//		(*l)->qnt++;
//	}
//	else
//	{
//		e->next = (*l)->first;
//		(*l)->first = e;
//		(*l)->qnt++;
//	}
//}
//
//struct node* popElement(struct stack **l)
//{
//	struct node *n = (*l)->first, *temp = (*l)->first;
//	if ((*l)->qnt == 1)
//	{
////		n = (*l)->first;
//		(*l)->first = NULL;
//		(*l)->last = NULL;
//	}
//	else
//	{
//		while (temp->next != (*l)->last)
//			temp = temp->next;
//
//		n = (*l)->last;
//		(*l)->last = temp;
//		temp->next = NULL;
//	}
//	(*l)->qnt--;
//
//	return n;
//}
//
//int popNElements(struct stack **l, int amount, int at)
//{
//	if (amount == 0) return at;
//	int i = 0;
//	struct node *e;
//	for (i = 0; i < amount; i++)
//		e = popElement(l);
//	return e->code;
//}
//
//struct node* popFirstElement(struct stack **l)
//{
//	struct node *n = (*l)->first;
//	if ((*l)->qnt <= 1)
//	{
////		n = (*l)->first;
//		(*l)->first = NULL;
//		(*l)->last = NULL;
//		(*l)->qnt = 0;
//	}
//	else
//	{
//		(*l)->first = (*l)->first->next;
//		(*l)->qnt--;
//	}
//
//	return n;
//}
//
//void clearStack(struct stack **l)
//{
//	struct node *e = (*l)->first;
//
//	while (e != NULL)
//	{
//		struct node *temp = e;
//		e = e->next;
//		free(temp);
//	}
//
//	(*l)->last = NULL;
//	(*l)->first = NULL;
//	(*l)->qnt = 0;
//}
//
//void printStack(struct stack *l)
//{
//	struct node *e = l->first;
//	int index = 0;
//
//	while (e != NULL)
//	{
////		printf("Elemento %d:\n", index);
////		printf("code:  %d:\n", e->code);
//		printf("(%d)%d ", index, e->code);
//		e = e->next;
//		index++;
//	}
//	printf("\n");
//}
//
//void initStack(struct stack **l)
//{
//	*l = malloc(sizeof(struct stack));
//	(*l)->first = NULL;
//	(*l)->last = NULL;
//	(*l)->qnt = 0;
//}
//
//int nonterminalIndex(char* token)
//{
//	int size = 22; // baseado no vetor de naoterminais (nonterminals)
//	int i = 0;
//	while(i < size && strcmp(nonterminals[i], token))
//		i++;
//
//	i = (i == size)? INT_MAX : i + 39;
//	return i;
//}
//
//struct prod* createProds()
//{
//	int size = 52, begin = 0, end = 0, amount, i = 0;
//	char *temp = NULL, *rhs = NULL, *lhs = NULL;
//
//	struct prod *prods = NULL;
//	prods = malloc(sizeof(struct prod) * size);
////	for (i = 0; i < size; i++)
////		prods[i] = calloc(1,sizeof(struct prod));
//
//	for (i = 0; i < size; i++)
////	while (p[begin] > 0)
//	{
//		amount = 1;
//		lhs = calloc(50,sizeof(char));
//		rhs = calloc(50,sizeof(char));
//		temp = calloc(50,sizeof(char));
//
//		end = strcspn(p+begin," >");
//		strncpy(lhs,p+begin,end);
//
//		begin += end + 2;
//		end = strcspn(p+begin,"\n");
//		if (!end)
//		{
//			strcat(rhs,"&"); // Qual o codigo para vazio ?
//			amount--;
//		}
//		else
//			strncpy(rhs,p+begin+1,end-1);
//
//		begin += end + 1;
//		temp = strchr(rhs,' ');
//		while (temp != NULL)
//		{
//			amount++;
//			temp = strchr(temp + 1,' ');
//		}
//
////		prods[i] = malloc(sizeof(struct prod));
//		prods[i].lhs = lhs;
//		prods[i].productions = rhs;
//		prods[i].p = nonterminalIndex(lhs);
//		prods[i].n = amount;
//		prods[i].q = malloc(sizeof(int) * amount);
//
//		char *t = calloc(50,sizeof(char));
//		strcpy(t,rhs);
//		temp = strtok(t," ");
//		int j;
//		for (j = 0; j < amount; j++)
//		{
//			prods[i].q[j] = (temp[0] > 64 && temp[0] < 91)? nonterminalIndex(temp) : terminalIndex(temp);
//			temp = strtok(NULL," ");
//		}
//	}
//
//	return prods;
//
////	for (i = 0; i < size; i++)
////	{
////		printf("(%d)%s -> %s", prods[i].p, prods[i].lhs, prods[i].productions);
////		int j;
////		printf("(");
////		for (j = 0; j < prods[i].n; j++)
////			printf("%d ", prods[i].q[j]);
////		printf(")\n");
////	}
//}
//
////int parseSLR(int** mat, int *input, int inputSize, struct prod *p)
//int parseSLR(int** mat, struct tokenList *list, int inputSize, struct prod *p)
//{
//	int at = 0;
//	struct stack *estados = NULL, *entrada = NULL;
//	initStack(&estados);
//	initStack(&entrada);
//	// struct tokenNode *n = list->first;
//	//addElements(&entrada,input,inputSize);
//	// addElements(&entrada,n,list->qnt);
//	addElements(&entrada,list);
//	addElementN(&entrada,0);
//
//	// printStack(entrada);
//
//	for (;;)
//	{
//		int elem = popFirstElement(&entrada)->code;
//		int acao = mat[at][elem];
//		if (acao == INT_MIN)
//		{
////			printf("estado: %d acao: %d elem: %d\n", at, acao, elem);
//			return 0;
//		}
//		else if (acao == INT_MAX)
//			return 1;
//		else if (acao > 0)
//		{
//			addElementN(&estados, at);
//			at = acao;
//		}
//		else
//		{
//			addElementI(&entrada,elem);
//			addElementI(&entrada, p[-acao].p);
//			at = popNElements(&estados,p[-acao].n,at);
//		}
//	}
//}
//
//int** readMatrix(FILE *file)
//{
//	char *text = NULL;
//	fseek(file, 0, SEEK_END);
//	int size = ftell(file);
//	rewind(file);
//
//	do
//	{
//		text = calloc(size+1,sizeof(char));//(char*) malloc(sizeof(char) * (size + 1));
//	} while (text == NULL);
//
//	fread(text, 1, size+1, file);
//	fclose(file);
//
//	int **mat;
//	int sizeI = 22+39;
//	int sizeJ = 119;
//	mat = malloc(sizeJ * sizeof(int*));
//
//	int i, j = 0;
//	for (i = 0; i < sizeJ; i++)
//		mat[i] = malloc(sizeI * sizeof(int));
//
//	char* temp = NULL;
//	temp = strtok(text,",\n");
//
//	i = 0;
//	while (temp != NULL)
//	{
//		if (temp[0] == ' ')
//			mat[j][i] = INT_MIN;
//		else if (temp[0] == 'a')
//			mat[j][i] = INT_MAX;
//		else if (isdigit(temp[0]))
//			mat[j][i] = atoi(temp);
//		else
//			mat[j][i] = (temp[0] == 's')? atoi(temp+1) : -atoi(temp+1);
//
//		i++;
//		if (i == sizeI)
//		{
//			j++;
//			i = 0;
//		}
//
//		temp = strtok(NULL,",\n\0");
//	}
//
////	for (i = 0; i < sizeJ; i++)
////	{
////		for (j = 0; j < sizeI; j++)
////			if (mat[i][j] != 0)
////				printf("%d ,", mat[i][j]);
////			else
////				printf("    ,");
////		printf("\n");
////	}
//
//	return mat;
//}

// --------------------------------------------- //

//int main(int argc, char** argv)
//{
//	FILE *file = NULL;
//	char *name = NULL;
//
//	if (argc == 1)
//	{
//		name = calloc(100, sizeof(char));
//		strcpy(name, "Entradas/-declare.in");
//	}
//	else
////		Caso seja passado como ./a.exe < test.in, entao o indice abaixo troca de 1 para 2
//		name = argv[1];
//
//	file = fopen(name , "rt");
//
//	if (file != NULL)
//	{
//		char *text = NULL;
//		text = readFile(file);
//
//		if (text != NULL)
//		{
//			struct tokenList *tokens;
////			char **tokens = NULL;
//			int tokensAmount = 0, emptyAmount = 0;
//			tokens = tokenizer(text, &tokensAmount, &emptyAmount);
//
////			printf("Amounts: %d %d\n", tokensAmount, emptyAmount);
////			int *codes = NULL;
////			codes = verifyTokens(tokens, tokensAmount, emptyAmount);
//			int codes = 0;
//			codes = verifyTokens(tokens, tokensAmount, emptyAmount);
//
////			if (codes != NULL)
//			if (codes)
//			{
////				int i;
////				for (i = 0; i <= tokensAmount-emptyAmount; i++)
////					printf("%d ",codes[i]);
//
//				int **mat = NULL;
//				struct prod *prods = NULL;
//				name = calloc(20,sizeof(char));
//				strcpy(name, "Data.csv");
//				file = fopen(name, "rt");
//				if (file != NULL)
//				{
//					mat = readMatrix(file);
//					prods = createProds();
////					if(parseSLR(mat,codes,tokensAmount - emptyAmount + 1,prods))
//					if(parseSLR(mat,tokens,tokensAmount - emptyAmount + 1,prods))
//						printf("SIM\n");
//					else
//						printf("NAO\n");
//				}
//				else
//					printf("Problemas na leitura da tabela\n");
//			}
//		}
//		else
//			printf("ARQUIVO INVALIDO!\n");
//	}
//	else
//		printf("Problemas na abertura do arquivo\n");
//
//	return 0;
//}
