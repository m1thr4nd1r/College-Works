#ifndef AUTOMATO_H
#define	AUTOMATO_H

#include <string>
#include "Estado.h"
using namespace std;

class Automato {
public:
    Automato(string automato);
    Automato(int qnt_estados, int qnt_simbolos);
    Automato(const Automato& orig);
    virtual ~Automato();
    Estado** Estados();
    int Qnt_Estados();
    int Qnt_Simbolos();
    string F_Transicao();
    string* Alfabeto();
    void Alfabeto(string* alfabeto);
    Estado* Inicial();
    void Inicial(Estado* inicio);
    string Transicao();
    void addEstado(string id, int pos, bool final);
    void addTransicao(string origem, string destino, string simbolo);
    void sign();
    string Assinatura();
    void tratar_transicoes(string linha);
    void tratar_automato(string automato);
    void tratar_alfabeto(string alfabeto);
    bool reconhecer(Estado *estado, string cadeira);
    void tratar_estado(string estado);
    void tratar_finais(string finais);
private:
    int qnt_estados,qnt_simbolos;
    string *alfabeto,f_transicao,assinatura,nome;
    Estado **estados,*inicial;
};

#endif	/* AUTOMATO_H */

