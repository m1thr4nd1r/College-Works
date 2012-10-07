#ifndef ESTADO_H
#define	ESTADO_H

#include <string>
using namespace std;

class Estado {
public:
    Estado(string id,int qnt_simbolos);
    Estado(const Estado& orig);
    virtual ~Estado();
    string ID(); // get
    bool Final(); //get
    void Final(bool stat); // set
    Estado** Transicoes();
    void Transicoes(int pos, Estado* destino); // set
    Estado* transicao(int pos);
private:
    string id;
    Estado **transicoes;
    bool final;
};

#endif	/* ESTADO_H */