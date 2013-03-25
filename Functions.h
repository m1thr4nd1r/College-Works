#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

#include <sstream>
#include <cmath>
#include <fstream>

using namespace std;

void fill(string *text, short count, char liquid='0');

string binToByte(string text);

void writeOutput(string output, string outputOLD);

string readOutput(string *raw);

string intToBin(short n);

short binToInt(string n);

#endif	/* FUNCTIONS_H */

