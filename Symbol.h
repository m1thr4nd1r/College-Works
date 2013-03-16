/* 
 * File:   Symbol.h
 * Author: M1thr4nd1r
 *
 * Created on 6 de Março de 2013, 10:09
 */

#ifndef SYMBOL_H
#define	SYMBOL_H

#include <string>
#include <iostream>

using namespace std;

class Symbol {
public:
    Symbol(char x, unsigned short oc);
    void setCode(string code);
    void setProbability(double x);
    void addOcorrence(short ocorrence);
    unsigned short getOcorrence();
    double getProbability();
    string getCode();
    char getCaracter();
    void print();
private:
    char caracter;
    unsigned short ocorrence;
    double probability;
    string code;

};

#endif	/* SYMBOL_H */

