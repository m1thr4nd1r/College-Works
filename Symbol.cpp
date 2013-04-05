#include "Symbol.h"

Symbol::Symbol(char x, unsigned short oc) {
    this->character = x;
    this->ocorrence = oc;
    this->code = "";
    this->probability = 0;
}

void Symbol::addOcorrence(short ocorrence)
{
    this->ocorrence+= ocorrence;
}

char Symbol::getCharacter()
{
    return this->character;
}

unsigned short Symbol::getOcorrence()
{
    return this->ocorrence;
}

void Symbol::setCharacter(char ch)
{
    this->character = ch;
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

void Symbol::print()
{
    cout<< this->character << " " << this->ocorrence << " " << this->code << " " << this->probability << endl;
}

void Symbol::calculateProbability(unsigned short prob_total)
{
    this->setProbability( abs( (double) this->getOcorrence() / ( (double)prob_total ) ) );
}