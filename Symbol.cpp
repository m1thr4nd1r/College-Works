/* 
 * File:   Symbol.cpp
 * Author: M1thr4nd1r
 * 
 * Created on 6 de Março de 2013, 10:09
 */

#include "Symbol.h"

Symbol::Symbol(char x, unsigned short oc) {
    this->caracter = x;
    this->ocorrence = oc;
    this->code = "";
    this->probability = 0;
}

void Symbol::addOcorrence(short ocorrence)
{
    this->ocorrence+= ocorrence;
}

char Symbol::getCaracter()
{
    return this->caracter;
}

unsigned short Symbol::getOcorrence()
{
    return this->ocorrence;
}

void Symbol::setCode(string code)
{
    this->code = code;
}

string Symbol::getCode()
{
    return this->code;
}

void Symbol::setProbability(double x)
{
    this->probability = x;
}

double Symbol::getProbability()
{
    return this->probability;
}

void Symbol::print()
{
    cout<< this->caracter << " " << this->ocorrence << " " << this->code << " " << this->probability << endl;
}