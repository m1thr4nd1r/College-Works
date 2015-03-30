/*
 * semantico.h
 *
 *  Created on: 03/12/2014
 *      Author: m1thr4nd1r
 */

#ifndef SEMANTICO_H_
#define SEMANTICO_H_

#include "sintatico.h"

struct id{
	char *name;
	int alloc;
	struct id *next;
};

struct idList{
	struct id *first;
	struct id *last;
	int qnt;
};

//struct varTable{
//	struct idList *table[4];
	// 0 -> num
	// 1 -> numVec
	// 2 -> letter
	// 3 -> letterVec
//};

struct context{
//	struct varTable *table;
	struct idList *table[4];
	struct context *parent;
};

void printErrorCause(char *func, char *error, char *name);

int declared(char *c, struct context *context);

int declare(struct treeNode *root, struct context *context);

int resize(struct treeNode *root, struct context *context);

int arit(struct treeNode *root, struct context *context);

int put(struct treeNode *root, struct context *context);

int cond(struct treeNode *root, struct context *context);

int loop(struct treeNode *root, struct context *context);

int foreach(struct treeNode *root, struct context *context);

int read(struct treeNode *root, struct context *context);

int write(struct treeNode *root, struct context *context);

int treeCheck(struct treeNode *root, struct context *context);

#endif /* SEMANTICO_H_ */
