#include "Estado.h"

Estado::Estado(string id,int qnt_simbolos) 
{
    this->transicoes = new Estado*[qnt_simbolos];
    for (int i = 0; i < qnt_simbolos; i++)
        transicoes[i] = NULL;
    this->id = id;
    this->final = 0;
}

Estado::Estado(const Estado& orig) {
}

Estado::~Estado() {
}

string Estado::ID()
{
    return this->id;
}

void Estado::Final(bool stat)
{
    this->final = stat;
}

bool Estado::Final()
{
    return this->final;
}

Estado** Estado::Transicoes()
{
    return this->transicoes;
}

void Estado::Transicoes(int posicao, Estado* destino)
{
    this->transicoes[posicao] = destino;
}

Estado* Estado::transicao(int pos)
{
    if (&this->transicoes[pos] != NULL)
        return this->transicoes[pos];
}