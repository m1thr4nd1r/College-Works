#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

#include <cmath>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void fill(string *text, short count, char liquid='0');

string binToByte(string text);

void writeOutput(string output, string *file);

bool readFile(string *input);

bool writeFile(string content, string *file);

string intToBin(short n);

short binToInt(string n);

#endif	/* FUNCTIONS_H */

