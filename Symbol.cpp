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

void Symbol::addCharCode(char ch)
{
    this->code.push_back(ch);
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

//void Symbol::print()
//{
//    cout<< this->caracter << " " << this->ocorrence << " " << this->code << " " << this->probability << endl;
//}

string Symbol::signature()
{
    string out = "", temp = "";
    
    temp = integerToBinary((short)this->caracter);
    
    fill(&temp, 8 - temp.size());
    
    out+= temp;
    
    temp = integerToBinary((short)this->code.size());
    
    fill(&temp,6 - temp.size());
    
    unsigned short a = temp.size() + this->code.size();
    
    out+= temp;
    
    temp = this->code;
    
    unsigned diff = (!(a % 8)) ? 0 : (a/8) + 1;
    
    if (diff != 0)
        fill(&temp, (8 * diff) - a);
    
    out+= temp;
    
    return out;
}