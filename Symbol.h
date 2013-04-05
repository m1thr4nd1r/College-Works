#ifndef SYMBOL_H
#define	SYMBOL_H

#include <iostream>
#include "Functions.h"

using namespace std;

class Symbol {
public:
    Symbol(char x, unsigned short oc);
    void setCode(string code);
    void setProbability(double x);
    void setCharacter(char ch);
    void addOcorrence(short ocorrence);
    unsigned short getOcorrence();
    double getProbability();
    void calculateProbability(unsigned short prob_total);
    string getCode();
    char getCharacter();
    void print();
    void addCharCode(char ch);
    string signature();
private:
    char character;
    unsigned short ocorrence;
    double probability;
    string code;

};

#endif	/* SYMBOL_H */