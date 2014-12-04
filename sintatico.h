/*
 * sintatico.h
 *
 *  Created on: 03/12/2014
 *      Author: m1thr4nd1r
 */

#ifndef SINTATICO_H_
#define SINTATICO_H_

//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h> // malloc calloc
//#include <ctype.h> // isdigit isalpha isalnum
//#include <limits.h> // INT_MAX INT_MIN
#include "lexico.h"

//const char nonterminals[][9] = {"ARIT","COMMAND","CONS","DEC","DECLARE","ELSE","F","FOR","FOREACH","G","ID","IF","OP","OPERANDO","PRINT","PUT","READ","REL","RESIZE","S","TYPE","VAR"};

//char p[] = {"SS > S $\nS > COMMAND\nCOMMAND > IF COMMAND\nCOMMAND > DECLARE COMMAND\nCOMMAND > RESIZE COMMAND\nCOMMAND > PUT COMMAND\nCOMMAND > FOR COMMAND\nCOMMAND > FOREACH COMMAND\nCOMMAND > READ COMMAND\nCOMMAND > PRINT COMMAND\nCOMMAND >\nDECLARE > declare ID DEC as TYPE .\nDEC > , ID DEC\nDEC >\nID > id\nID > id [ ]\nTYPE > number\nTYPE > letter\nRESIZE > resize id to ARIT .\nPUT > put ARIT in VAR .\nPUT > put string in id .\nARIT > ARIT + F\nARIT > ARIT - F\nARIT > F\nF > F * G\nF > F / G\nF > F % G\nF > G\nF > - G\nG > ( ARIT )\nG > OPERANDO\nOPERANDO > CONS\nOPERANDO > VAR\nCONS > num\nCONS > char\nVAR > id [ ARIT ]\nVAR > id\nREL > ARIT OP ARIT\nOP > <\nOP > >\nOP > <=\nOP > >=\nOP > <>\nOP > =\nIF > if REL then [ COMMAND ] ELSE\nELSE > else [ COMMAND ]\nELSE >\nFOR > for VAR from ARIT to ARIT do [ COMMAND ]\nFOREACH > foreach VAR in id do [ COMMAND ]\nREAD > read id .\nPRINT > print OPERANDO .\nPRINT > print string ."};

struct prod{
	int p, n, *q;
	char *lhs, *productions; // Para Debug
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

void addElementN(struct stack **l, int code);

void addElements(struct stack **l, struct tokenList *list);

void addElementI(struct stack **l, int code);

struct node* popElement(struct stack **l);

int popNElements(struct stack **l, int amount, int at);

struct node* popFirstElement(struct stack **l);

void clearStack(struct stack **l);

void printStack(struct stack *l);

void initStack(struct stack **l);

int nonterminalIndex(char* token);

struct prod* createProds();

int parseSLR(int** mat, struct tokenList *list, int inputSize, struct prod *p);

int** readMatrix(FILE *file);

#endif /* SINTATICO_H_ */
