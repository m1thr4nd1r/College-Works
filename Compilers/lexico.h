/*
 * lexico.h
 *
 *  Created on: 03/12/2014
 *      Author: m1thr4nd1r
 */

#ifndef LEXICO_H_
#define LEXICO_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h> // malloc calloc
#include <ctype.h> // isdigit isalpha isalnum
#include <limits.h> // INT_MAX INT_MIN

struct token{
	int code, value, line;
	char *text, type;
};

struct tokenElement{
	struct token *token;
	struct tokenElement *next;
};

struct tokenList{
	struct tokenElement *first, *last;
	int qnt;
};

char* readFile(FILE *file);

int verifyTokens(struct tokenList* tokens);

int validSeparator(struct token *t);

int validString(struct token *t);

int validChar(struct token *t);

int validNumber(struct token *t);

struct tokenList* tokenizer(char *file);

int nextSeparator(char *line, char type);

int isSeparator(int code);

int isPrintable(int code);

void printError(struct token *t);

int tokenToCode(char *token, char type);

int terminalIndex(char *token);

char* toLower(char *word);

void addToken(struct tokenList **l, struct token *token);

#endif /* LEXICO_H_ */
