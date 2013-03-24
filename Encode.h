/* 
 * File:   Encode.h
 * Author: M1thr4nd1r
 *
 * Created on 23 de Março de 2013, 21:52
 */

#ifndef ENCODE_H
#define	ENCODE_H

#include "Symbol.h"
#include <vector>

unsigned short calculateProbability(vector<Symbol> & s);

bool compare(Symbol s1, Symbol s2);

string encode(string input);

bool exists(vector<Symbol> & v, unsigned short *ocorrence, char *caracter, char current);

void makeCodes(vector<Symbol> & s, bool flag);

string stringToBits(string text);

string charToBin(string in, vector <Symbol> v, short num_bit);

string charToSF(string in, vector<Symbol> v);

#endif	/* ENCODE_H */

