#ifndef DECODE_H
#define	DECODE_H

#include "Node.h"
#include "Functions.h"
#include <string>

using namespace std;

void remake_tree(string *encoded, Node** root);

void finishTree(string *codes, Node* root);

char extractCharacter(Node *root, string *msg);

string shToIn(Node *root, string *msg);

string decode(string *input, string encoded);

#endif	/* DECODE_H */

