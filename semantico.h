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

int declared(char *c, struct context *context);

int declare(struct treeNode *root, struct context *context);

int resize(struct treeNode *root, struct context *context);

int arit(struct treeNode *root, struct context *context);

int put(struct treeNode *root, struct context *context);

void cond(struct treeNode *root);

void loop(struct treeNode *root);

void foreach(struct treeNode *root);

void read(struct treeNode *root);

void write(struct treeNode *root);

int treeCheck(struct treeNode *root, struct context *context);

#endif /* SEMANTICO_H_ */
