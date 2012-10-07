#include "Automato.h"

Automato::Automato(string automato) 
{
    tratar_automato(automato);
}

Automato::Automato(int qnt_estados, int qnt_simbolos)
{
    this->qnt_estados = qnt_estados;
    this->qnt_simbolos = qnt_simbolos;
    this->alfabeto = new string[qnt_simbolos];
    this->estados = new Estado*[qnt_estados];
    this->f_transicao = "f";
    nome = "M";
}

Automato::Automato(const Automato& orig) {
}

Automato::~Automato() {
}

void Automato::addEstado(string id,int pos, bool final)
{
    estados[pos] = new Estado(id,qnt_simbolos);
    estados[pos]->Final(final);
}

void Automato::addTransicao(string origem, string destino, string simbolo)
{
    int i ,j,k;
    for (i = 0; i < qnt_estados; i++)
        if (estados[i]->ID() == origem)
            break;
    for (j = 0; j < qnt_estados; j++)
        if (estados[j]->ID() == destino)
            break;
    
    for (k = 0; k < qnt_simbolos; k++)
        if (alfabeto[k] == simbolo)
			break;
    
    if ((i < qnt_estados) && (j < qnt_estados) && (k < qnt_simbolos))
	estados[i]->Transicoes(k,estados[j]);
}

void Automato::sign()
{
    assinatura+= nome;
    
    assinatura+=" = {{";
    
    for (int i = 0; i < qnt_estados; i++)
    {
        assinatura+= estados[i]->ID();
        if (i+1 != qnt_estados)
            assinatura+=",";
    }
    assinatura+="},{";
    for (int i = 0; i < qnt_simbolos; i++)
    {
        assinatura+= alfabeto[i];
        if (i+1 != qnt_simbolos)
            assinatura+=",";
    }
    
    assinatura+="},";
    assinatura+=f_transicao;
    assinatura+=",";
    assinatura+=inicial->ID();
    assinatura+=",{";
    
    int count = 0;
    
    for (int i = 0; i < qnt_estados; i++)
    {
        if (count != 0)
        {
            assinatura+=",";
            count--;
        }
        if (estados[i]->Final())
        {
            assinatura+=estados[i]->ID();
            count++;
        }
    }
    
    assinatura+= "}}\n";
    assinatura+= f_transicao;
    assinatura+= " = {";
    
    for (int i = 0; i < qnt_estados; i++)
    {
        for (int j = 0; j < qnt_simbolos; j++)
        {
            if (estados[i]->Transicoes()[j] != NULL)
            {
                assinatura+="\n";
                assinatura+="(";
                assinatura+=estados[i]->ID();
                assinatura+=",";
                assinatura+=alfabeto[j];
                assinatura+=")={";
                assinatura+=estados[i]->Transicoes()[j]->ID();
                assinatura+="}";
            }
        }
    }
    assinatura+= "\n};";
}

bool Automato::reconhecer(Estado* estado, string cadeia)
{
    if ((cadeia == "") && ((*estado).Final()))
        return 1;
    else if ((cadeia == "") && (!(*estado).Final()))
        return 0;
    else
    {
        int num = -1,tam=0;
        string aux = "";
        for (int i = 0; i < qnt_simbolos; i++)
        {
            tam = alfabeto[i].size();
            aux = cadeia.substr(0,tam);
            if (aux == alfabeto[i])
            {
                num = i;
                cadeia.erase(0,tam);
                break;
            }
        }
        if (num != -1)
                return reconhecer((*estado).transicao(num),cadeia);
        else return 0;
    }
}

void Automato::tratar_automato(string automato)
{
    int inicio,fim;
    string estados,alfabeto,finais,inicial;
    
    inicio = automato.find_first_of(' ');
    
    nome += automato.substr(0,inicio);
    
    inicio = automato.find_first_of('{');
    automato.erase(inicio,1);
    automato.erase(automato.length()-1,1);
    
    inicio = automato.find_first_of('{');
    fim = automato.find_first_of('}');
    
    estados = automato.substr(inicio+1,fim-inicio-1); 
    automato.erase(0,fim+2);
    
    inicio = automato.find_last_of('{');
    fim = automato.find_last_of('}');
    
    finais = automato.substr(inicio+1,fim-inicio-1);
    automato.erase(inicio-1,fim);
    
    inicio = automato.find_first_of('{');
    fim = automato.find_first_of('}');
    
    alfabeto = automato.substr(inicio+1,fim-inicio-1);
    automato.erase(inicio,fim+2);
    
    inicio = automato.find_first_of(',');
    fim = automato.length();
    
    inicial = automato.substr(inicio+1,fim-inicio-1);
    automato.erase(inicio,fim);

    f_transicao = automato.substr(0,automato.length());
    
    qnt_estados = 1;
    for (int i = 0; i < estados.length() ; i++)
        if (estados[i] == ',')
            qnt_estados++;
   
    qnt_simbolos = 1;
    for (int i = 0; i < alfabeto.length(); i++)
        if (alfabeto[i] == ',')
            qnt_simbolos++;
    
    int qnt_finais = 1;
    for (int i = 0; i < finais.length(); i++)
        if (finais[i] == ',')
            qnt_finais++;
    
    this->alfabeto = new string[qnt_simbolos];
    
    tratar_alfabeto(alfabeto);
    tratar_estado(estados);
    
    for (int i = 0; i < qnt_estados; i++)
        if (this->estados[i]->ID() == inicial)
        {
            this->inicial = this->estados[i];
            break;
        }
    
    tratar_finais(finais);
}

void Automato::tratar_alfabeto(string alfabeto)
{
    int inicio;
    
    for (int i = 0; i < qnt_simbolos; i++)
    {
        inicio = alfabeto.find_first_of(',');
        if (inicio != -1)
        {
            this->alfabeto[i] = alfabeto.substr(0,inicio);
            alfabeto.erase(0,inicio+1);
        }
        else
		{
            this->alfabeto[i] = alfabeto;
			alfabeto.clear();
		}
	}
}

void Automato::tratar_estado(string estado)
{
    int aux;
    string aux2;
        
    estados = new Estado*[this->qnt_estados];
    
    for (int i = 0; i < this->qnt_estados; i++)
    {
        aux = estado.find_first_of(',');
        if (aux != -1)
            aux2 = estado.substr(0,aux);
        else
            aux2 = estado;
        estados[i] = new Estado(aux2,qnt_simbolos);
        estado.erase(0,aux+1);
    }
}

void Automato::tratar_finais(string finais)
{
    int aux;
    string aux2;
    
    while(!finais.empty())
    {
        aux = finais.find_first_of(',');
        if (aux != -1)
        {
            aux2 = finais.substr(0,aux);
            for (int i = 0; i < qnt_estados; i++)
                if (estados[i]->ID() == aux2)
                {
                        estados[i]->Final(true);
                        break;
                }
            finais.erase(0,aux+1);
        }
        else
        {
           for (int i = 0; i < qnt_estados; i++)
                if (estados[i]->ID() == finais)
                {
                        estados[i]->Final(true);
                        break;
                }
                        finais.clear();
        }
    }    
}

void Automato::tratar_transicoes(string linha)
{
    int inicio = 0, fim = 0;
    string origem,destino,simbolo;
    
    inicio = linha.find_first_of('(');
    fim = linha.find_first_of(',');
    
    origem = linha.substr(inicio+1,fim-inicio-1);
    
    inicio = fim;
    fim = linha.find_first_of(')');
    
    simbolo = linha.substr(inicio+1,fim-inicio-1);
    
    inicio = linha.find_first_of('{');
    fim = linha.find_first_of('}');
    
    destino = linha.substr(inicio+1,fim-inicio-1);
    
    addTransicao(origem,destino,simbolo);
    /*
    linha.erase(0,fim+2);
    
    if (linha.length() != 0)
        tratar_transicoes(linha);
    */
}

int Automato::Qnt_Simbolos()
{
	return this->qnt_simbolos;
}

Estado* Automato::Inicial()
{
    return this->inicial;
}

void Automato::Inicial(Estado *inicio)
{
    this->inicial = inicio;
}

string Automato::F_Transicao()
{
    return this->f_transicao;
}

int Automato::Qnt_Estados()
{
    return this->qnt_estados;
}

Estado** Automato::Estados()
{
    return this->estados;
}

string* Automato::Alfabeto()
{
    return this->alfabeto;
}

void Automato::Alfabeto(string* alfabeto)
{
    this->alfabeto = alfabeto;
}

string Automato::Transicao()
{
    return this->f_transicao;
}

string Automato::Assinatura()
{
    return this->assinatura;
}