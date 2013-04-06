#ifndef ENCODE_H
#define	ENCODE_H

#include "Symbol.h"
#include <vector>
#include <algorithm>
#include <limits>


unsigned short calculateProbability(vector<Symbol> & s);

bool compare(Symbol s1, Symbol s2);

string encode(string *input, string *bin, string *encoded, string *file = NULL);

bool exists(vector<Symbol> & v, unsigned short *ocorrence, char *caracter, char current);

void makeCodes(vector<Symbol> & s, bool flag);

string stringToBits(string text);

string charToBin(string in, vector <Symbol> v, short num_bit);

string charToSF(string in, vector<Symbol> v);

#endif	/* ENCODE_H */