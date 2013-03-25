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

//void Symbol::print()
//{
//    cout<< this->character << " " << this->ocorrence << " " << this->code << " " << this->probability << endl;
//}

string Symbol::signature()
// Cria a assinatura de um simbolo (Utilizado no metodo antigo de representação da tabela de Shannon-Fano)
{
    string out = "", temp = "";
    
    temp = intToBin((short)this->character);
    
    // O primeiro byte é para o caracter
    fill(&temp, 8 - temp.size());
    
    out+= temp;
    
    temp = intToBin((short)this->code.size());
    
    // Os proximos 6 bits dizem com quantos bits sao necessarios para representar o codigo Shannon-Fano do simbolo
    fill(&temp,6 - temp.size());
    
    unsigned short a = 6 + this->code.size();
    
    out+= temp;
    
    temp = this->code;
    
    unsigned diff = (!(a % 8)) ? 0 : (a/8) + 1;
    
    if (diff != 0)
//      Os proximos bits sao o codigo Shannon-Fano do simbolo  
        fill(&temp, (8 * diff) - a);
    
    out+= temp;
    
    return out;
}

void Symbol::calculateProbability(unsigned short prob_total)
{
    this->setProbability( abs( (double) this->getOcorrence() / ( (double)prob_total ) ) );
}