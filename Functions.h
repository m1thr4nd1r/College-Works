/* 
 * File:   Functions.h
 * Author: M1thr4nd1r
 *
 * Created on 23 de Março de 2013, 18:32
 */

#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

#include <sstream>
#include <cmath>

using namespace std;

void fill(string *text, short count, char liquid='0');

string binToByte(string text);

string intToBin(short n);

short binToInt(string n);

#endif	/* FUNCTIONS_H */

