/* 
 * File:   Symbol.h
 * Author: M1thr4nd1r
 *
 * Created on 6 de Março de 2013, 10:09
 */

#ifndef SYMBOL_H
#define	SYMBOL_H

//#include <iostream>
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
    string getCode();
    char getCharacter();
//    void print();
    void addCharCode(char ch);
    string signature();
private:
    char character;
    unsigned short ocorrence;
    double probability;
    string code;

};

#endif	/* SYMBOL_H */

