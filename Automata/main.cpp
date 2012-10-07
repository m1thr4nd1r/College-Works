#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include "Automato.h"

using namespace std;

void mesclar_automatos(Automato *aut1, Automato *aut2, Automato **aut)
{
    string inicial = aut1->Inicial()->ID()+aut2->Inicial()->ID();
   
    *aut = new Automato(aut1->Qnt_Estados()*aut2->Qnt_Estados(),aut1->Qnt_Simbolos());
    
    (*aut)->Alfabeto(aut1->Alfabeto());
    
	int i,j,k;

    for(i = 0; i < aut1->Qnt_Estados(); i++)
        for (j = 0; j < aut2->Qnt_Estados(); j++)
        {
            string id = "";
            bool final = 0;
            id += aut1->Estados()[i]->ID();
            id += aut2->Estados()[j]->ID();
            if ((aut1->Estados()[i]->Final()) || (aut2->Estados()[j]->Final()))
                final = 1;
            (*aut)->addEstado(id,i * aut2->Qnt_Estados() + j,final);
        }
    
    for(i = 0; i < aut1->Qnt_Estados(); i++)
        for (j = 0; j < aut2->Qnt_Estados(); j++)
                for (k = 0; k < (*aut)->Qnt_Simbolos(); k++)
                {
                    int l;
                    string id = "";
                    id += aut1->Estados()[i]->Transicoes()[k]->ID();
                    id += aut2->Estados()[j]->Transicoes()[k]->ID();
                    for (l = 0; l < (*aut)->Qnt_Estados(); l++)
                        if ((*aut)->Estados()[l]->ID() == id)
                            break;
                    (*aut)->Estados()[i * aut2->Qnt_Estados() + j]->Transicoes(k,(*aut)->Estados()[l]);
                }
    
    for (int i = 0; i < (*aut)->Qnt_Estados(); i++)
        if ((*aut)->Estados()[i]->ID() == inicial)
        {
            (*aut)->Inicial((*aut)->Estados()[i]);
            break;
        }
   
        (*aut)->sign();        
}

int main(int argc, char** argv) {

    int qnt_automatos = 2;
    string linha,cadeia,cadeias="";
    Automato **automatos = NULL;
    
    automatos = new Automato*[qnt_automatos+1];
    
    for (int i = 0; i < qnt_automatos; i++)
    {
        getline(cin,linha);

        automatos[i] = new Automato(linha);

        getline(cin,linha);

        if (linha == (automatos[i]->Transicao() + " = {"))
        {
            getline(cin,linha);

            while (linha != "};")
            {
                automatos[i]->tratar_transicoes(linha);
                getline(cin,linha);
            }
            
            automatos[i]->sign();
        }
    }
    
    mesclar_automatos(automatos[0],automatos[1],&automatos[2]);
           
    while (cin>>cadeia)
    {
        cadeias+="\n";
        cadeias+=cadeia;
        cadeias+=" = ";
        if (automatos[2]->reconhecer(automatos[2]->Inicial(),cadeia))
            cadeias+="true";
        else
            cadeias+="false";
    }
   
    cout<<automatos[2]->Assinatura();
    
    cout<<cadeias;
    
    return 0;
}