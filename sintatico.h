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

struct node{
	int code;
	struct node *next;
};

struct stack{
	struct node *first;
	struct node *last;
	int qnt;
};

void addFirstElement(struct stack **l, int code);

void addElements(struct stack **l, struct tokenList *list);

void addLastElement(struct stack **l, int code);

struct node* popLastElement(struct stack **l);

int popElements(struct stack **l, int amount, int at);

struct node* popFirstElement(struct stack **l);

void clearStack(struct stack **l);

void printStack(struct stack *l);

void initStack(struct stack **l);

int nonterminalIndex(char* token);

struct prod* createProds();

int parseSLR(int** mat, struct tokenList *list, int inputSize, struct prod *p);

int** readMatrix(FILE *file);

#endif /* SINTATICO_H_ */
