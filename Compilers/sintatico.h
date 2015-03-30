/*
 * sintatico.h
 *
 *  Created on: 03/12/2014
 *      Author: m1thr4nd1r
 */

#ifndef SINTATICO_H_
#define SINTATICO_H_

#include "lexico.h"

struct prod{
	int p, n, *q;
//	char *lhs, *productions; // Para Debug
} *r;

struct treeNode{
	struct element *elements; // ou struct element elements[10]
	int qnt;
};

struct element{
	int code;
	char *token;
	struct treeNode *child;
};

struct stackNode{
	int code, state;
	char *token;
	struct treeNode *child;
	struct stackNode *next;
};

struct stack{
	struct stackNode *first;
	struct stackNode *last;
	int qnt;
};

void printTree(struct treeNode *root, char *parent);

void addLastElement(struct stack **l, struct stackNode *e);

void addElements(struct stack **l, struct tokenList *list);

void addFirstElement(struct stack **l, struct stackNode *e);

struct stackNode* popLastElement(struct stack **l);

struct treeNode* popElements(struct stack **l, int amount, int *at);

struct stackNode* popFirstElement(struct stack **l);

void clearStack(struct stack **l);

void printStack(struct stack *l);

void initStack(struct stack **l);

int nonterminalIndex(char* token);

struct prod* createProds();

struct treeNode* parseSLR(int** mat, struct tokenList *list, struct prod *p);

int** readMatrix(FILE *file);

#endif /* SINTATICO_H_ */
