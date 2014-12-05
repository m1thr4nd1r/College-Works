#include "sintatico.h"

const char nonterminals[][9] = {"ARIT","COMMAND","CONS","DEC","DECLARE","ELSE","F","FOR","FOREACH","G","ID","IF","OP","OPERANDO","PRINT","PUT","READ","REL","RESIZE","S","TYPE","VAR"};

char p[] = {"SS > S $\nS > COMMAND\nCOMMAND > IF COMMAND\nCOMMAND > DECLARE COMMAND\nCOMMAND > RESIZE COMMAND\nCOMMAND > PUT COMMAND\nCOMMAND > FOR COMMAND\nCOMMAND > FOREACH COMMAND\nCOMMAND > READ COMMAND\nCOMMAND > PRINT COMMAND\nCOMMAND >\nDECLARE > declare ID DEC as TYPE .\nDEC > , ID DEC\nDEC >\nID > id\nID > id [ ]\nTYPE > number\nTYPE > letter\nRESIZE > resize id to ARIT .\nPUT > put ARIT in VAR .\nPUT > put string in id .\nARIT > ARIT + F\nARIT > ARIT - F\nARIT > F\nF > F * G\nF > F / G\nF > F % G\nF > G\nF > - G\nG > ( ARIT )\nG > OPERANDO\nOPERANDO > CONS\nOPERANDO > VAR\nCONS > num\nCONS > char\nVAR > id [ ARIT ]\nVAR > id\nREL > ARIT OP ARIT\nOP > <\nOP > >\nOP > <=\nOP > >=\nOP > <>\nOP > =\nIF > if REL then [ COMMAND ] ELSE\nELSE > else [ COMMAND ]\nELSE >\nFOR > for VAR from ARIT to ARIT do [ COMMAND ]\nFOREACH > foreach VAR in id do [ COMMAND ]\nREAD > read id .\nPRINT > print OPERANDO .\nPRINT > print string ."};

void printTree(struct treeNode *root, char *parent)
{
	int i;
	printf("%s:",parent);
	for (i = 0; i < root->qnt; i++)
		printf("%s(%d) ",root->elements[i].token,root->elements[i].code);
	printf("\n");

	for (i = 0; i < root->qnt; i++)
		if (root->elements[i].child != NULL)
					printTree(root->elements[i].child, root->elements[i].token);
}

void addLastElement(struct stack **l, struct stackNode *e)
{
	if ((*l)->first == NULL)
	{
		(*l)->first = e;
		(*l)->last = e;
	}
	else
	{
		(*l)->last->next = e;
		(*l)->last = e;
	}
	(*l)->qnt++;
}

void addElements(struct stack **l, struct tokenList *list)
{
	int i;
	struct tokenElement *elem = list->first;
	struct stackNode *node = NULL;

	for (i = 0; i < list->qnt; i++)
	{
		node = calloc(1,sizeof(struct stackNode));
		node->token = calloc(strlen(elem->token->text)+1,sizeof(char));
		strcpy(node->token, elem->token->text);
		node->code = elem->token->code;
		node->state = -1;
		node->child = NULL;
		node->next = NULL;

		addLastElement(l,node);
		elem = elem->next;
	}

	// Adicionando o $ no final da entrada
	node = calloc(1,sizeof(struct stackNode));
	node->token = calloc(2,sizeof(char));
	strcpy(node->token, "$");
	node->code = 0;
	node->state = -1;
	node->child = NULL;
	node->next = NULL;

	addLastElement(l,node);
	// ---------------------------------//
}

void addFirstElement(struct stack **l, struct stackNode *e)
{
	if ((*l)->first == NULL)
	{
		(*l)->first = e;
		(*l)->last = e;
		(*l)->qnt++;
	}
	else
	{
		e->next = (*l)->first;
		(*l)->first = e;
		(*l)->qnt++;
	}
}

struct stackNode* popLastElement(struct stack **l)
{
	struct stackNode *n = (*l)->first, *temp = (*l)->first;
	if ((*l)->qnt == 1)
	{
		(*l)->first = NULL;
		(*l)->last = NULL;
	}
	else
	{
		while (temp->next != (*l)->last)
			temp = temp->next;

		n = (*l)->last;
		(*l)->last = temp;
		temp->next = NULL;
	}
	(*l)->qnt--;

	return n;
}

struct treeNode* popElements(struct stack **l, int amount, int* at)
{
	int i = 0;
	struct stackNode *e = NULL;
	struct treeNode *t = calloc(1,sizeof(struct treeNode));
	t->elements = calloc(amount,sizeof(struct element));
	t->qnt = amount;

	for (i = 0; i < amount; i++)
	{
		e = popLastElement(l);
		t->elements[amount - i - 1].code = e->code;
		t->elements[amount - i - 1].token = e->token;
		t->elements[amount - i - 1].child = e->child;
	}

	*at = e->state;
	return t;
}

struct stackNode* popFirstElement(struct stack **l)
{
	struct stackNode *n = (*l)->first;
	if ((*l)->qnt <= 1)
	{
		(*l)->first = NULL;
		(*l)->last = NULL;
		(*l)->qnt = 0;
	}
	else
	{
		(*l)->first = (*l)->first->next;
		(*l)->qnt--;
	}

	return n;
}

void clearStack(struct stack **l)
{
	struct stackNode *e = (*l)->first;

	while (e != NULL)
	{
		struct stackNode *temp = e;
		e = e->next;
		free(temp);
	}

	(*l)->last = NULL;
	(*l)->first = NULL;
	(*l)->qnt = 0;
}

void printStack(struct stack *l)
{
	struct stackNode *e = l->first;
	int index = 0;

	while (e != NULL)
	{
//		printf("Elemento %d:\n", index);
//		printf("code:  %d:\n", e->code);
		printf("(%d)%d : %s - %d\n", index, e->state, e->token, e->code);
		e = e->next;
		index++;
	}
	printf("\n");
}

void initStack(struct stack **l)
{
	*l = malloc(sizeof(struct stack));
	(*l)->first = NULL;
	(*l)->last = NULL;
	(*l)->qnt = 0;
}

int nonterminalIndex(char* token)
{
	int size = 22; // baseado no vetor de naoterminais (nonterminals)
	int i = 0;
	while(i < size && strcmp(nonterminals[i], token))
		i++;

	i = (i == size)? INT_MAX : i + 39;
	return i;
}

struct prod* createProds()
{
	int size = 52, begin = 0, end = 0, amount, i = 0;
	char *temp = NULL, *rhs = NULL, *lhs = NULL;

	struct prod *prods = NULL;
	prods = malloc(sizeof(struct prod) * size);

	for (i = 0; i < size; i++)
	{
		amount = 1;
		lhs = calloc(50,sizeof(char));
		rhs = calloc(50,sizeof(char));
		temp = calloc(50,sizeof(char));

		end = strcspn(p+begin," >");
		strncpy(lhs,p+begin,end);

		begin += end + 2;
		end = strcspn(p+begin,"\n");
		if (!end)
		{
			strcat(rhs,"&");
			amount--;
		}
		else
			strncpy(rhs,p+begin+1,end-1);

		begin += end + 1;
		temp = strchr(rhs,' ');
		while (temp != NULL)
		{
			amount++;
			temp = strchr(temp + 1,' ');
		}

//		prods[i].lhs = lhs;
//		prods[i].productions = rhs;
		prods[i].p = nonterminalIndex(lhs);
		prods[i].n = amount;
		prods[i].q = malloc(sizeof(int) * amount);

		char *t = calloc(50,sizeof(char));
		strcpy(t,rhs);
		temp = strtok(t," ");
		int j;
		for (j = 0; j < amount; j++)
		{
			prods[i].q[j] = (temp[0] > 64 && temp[0] < 91)? nonterminalIndex(temp) : terminalIndex(temp);
			temp = strtok(NULL," ");
		}
	}

	return prods;

//	for (i = 0; i < size; i++)
//	{
//		printf("(%d)%s -> %s", prods[i].p, prods[i].lhs, prods[i].productions);
//		int j;
//		printf("(");
//		for (j = 0; j < prods[i].n; j++)
//			printf("%d ", prods[i].q[j]);
//		printf(")\n");
//	}
}

struct treeNode* parseSLR(int** mat, struct tokenList *list, struct prod *p)
{
	int at = 0, acao;
	struct stack *stack = NULL, *input = NULL;
	struct stackNode *elem = NULL;
	struct treeNode *root = NULL, *node = NULL;

	initStack(&stack);
	initStack(&input);
	addElements(&input,list);

//	printStack(input);

	for (;;)
	{
		elem = popFirstElement(&input);
		acao = mat[at][elem->code];

		if (acao == INT_MIN)
		{
//			printf("estado: %d acao: %d elem: (%d)%s - %s\n", at, acao, elem->code, elem->token, input->first->token);
			return NULL;
		}
		else if (acao == INT_MAX)
		{
			node = popElements(&stack,stack->qnt,&at);
			root = node;
//			printTree(root,"SS");
			return root;
		}
		else if (acao > 0)
//		Mudança de estado
		{
			elem->state = at;
			addLastElement(&stack, elem);
			at = acao;
		}
		else
//		Redução
		{
			addFirstElement(&input,elem);

			if (p[-acao].n > 0)
			{
				node = popElements(&stack,p[-acao].n,&at);
				root = node;
			}
			else
				node = NULL;

			elem = calloc(1,sizeof(struct stackNode));
			elem->state = -1;
			elem->code = p[-acao].p;
			elem->token = calloc(9,sizeof(char));
			strcat(elem->token,nonterminals[p[-acao].p - 39]);
			elem->child = node;

			addFirstElement(&input, elem);
		}
	}

	return NULL;
}

int** readMatrix(FILE *file)
{
	char *text = NULL;
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	rewind(file);

	do
	{
		text = calloc(size+1,sizeof(char));
	} while (text == NULL);

	fread(text, 1, size+1, file);
	fclose(file);

	int **mat;
	int sizeI = 22+39;
	int sizeJ = 119;
	mat = malloc(sizeJ * sizeof(int*));

	int i, j = 0;
	for (i = 0; i < sizeJ; i++)
		mat[i] = malloc(sizeI * sizeof(int));

	char* temp = NULL;
	temp = strtok(text,",\n");

	i = 0;
	while (temp != NULL)
	{
		if (temp[0] == ' ')
			mat[j][i] = INT_MIN;
		else if (temp[0] == 'a')
			mat[j][i] = INT_MAX;
		else if (isdigit(temp[0]))
			mat[j][i] = atoi(temp);
		else
			mat[j][i] = (temp[0] == 's')? atoi(temp+1) : -atoi(temp+1);

		i++;
		if (i == sizeI)
		{
			j++;
			i = 0;
		}

		temp = strtok(NULL,",\n\0");
	}

//	for (i = 0; i < sizeJ; i++)
//	{
//		for (j = 0; j < sizeI; j++)
//			if (mat[i][j] != 0)
//				printf("%d ,", mat[i][j]);
//			else
//				printf("    ,");
//		printf("\n");
//	}

	return mat;
}
