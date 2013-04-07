#ifndef ENCODE_H
#define	ENCODE_H

#include "Symbol.h"
#include <vector>
#include <algorithm>
#include <limits>

string encode(string *input, int *sizeB, int *sizeA);

bool exists(vector<Symbol> & v, unsigned short *ocorrence, char *caracter, char current);

void makeCodes(vector<Symbol> & s, bool flag);

string PesquisaBinaria ( vector<Symbol> v, char in , int N);

bool ordena(Symbol s1, Symbol s2);

string charToSF(string in, vector<Symbol> v);

#endif	/* ENCODE_H */