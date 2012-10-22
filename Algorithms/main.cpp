/* 
 * File:   main.cpp
 * Author: M1thr4nd1r
 *
 * Created on 9 de Outubro de 2012, 16:49
 */

#include <cstdlib>
#include <string>
#include <ctime>
#include <iostream>
#include <limits>
#include <cmath>
#include "PD.h"
#include "Funcoes.h"
#include "HeuristicasGulosas.h"
#include "BF.h"

using namespace std;

int main(int argc, char** argv) {

    int tam_mochilaI = 0,aux = 0,qnt_objetos = 0, maxFracaoP = 0,maxFracaoV = 0, tam, maxP = 0, maximo = 0, *valor, *peso, *back;
    float tam_mochilaF = 0, erro = 0, *pesoF, *valorF, *aux1, *aux2, *aux3, *aux4, maximoF=0;
    string linha = "", *auxP = NULL, *auxV = NULL;
    clock_t begin = 0, end = 0, b = 0, e = 0;
    
    cin>>qnt_objetos>>tam_mochilaF>>erro;
    
    if (qnt_objetos > numeric_limits<int>::max())
    {
        cout << "Erro: Quantidade de objetos muito grande";
        return 10;
    }
    
    auxP = new (nothrow) string [qnt_objetos]; // Vetor auxiliar contendo o peso de cada objeto;
    if (auxP == 0)      
    {
        cout << "Erro: Nao foi possivel alocar memoria para auxP";
        return 11;
    }
    
    auxV = new (nothrow) string [qnt_objetos]; // Vetor auxiliar contendo o valor de cada objeto;
    if (auxV == 0)
    {
        cout << "Erro: Nao foi possivel alocar memoria para auxV";
        return 12;
    }
    
    valor = new (nothrow) int [qnt_objetos]; // Vetor contendo os valores (inteiros) de cada objeto
    if (valor == 0)
    {
        cout << "Erro: Nao foi possivel alocar memoria para valor";
        return 13;
    }
    
    peso = new (nothrow) int [qnt_objetos]; // Vetor contendo os pesos (inteiros) de cada objeto
    if (peso == 0)
    {
        cout << "Erro: Nao foi possivel alocar memoria para peso";
        return 14;
    }
    
    valorF = new (nothrow) float [qnt_objetos]; // Vetor contendo os valores (floats) de cada objeto
    if (valorF == 0)
    {
        cout << "Erro: Nao foi possivel alocar memoria para valor";
        return 13;
    }
    
    pesoF = new (nothrow) float [qnt_objetos]; // Vetor contendo os pesos (floats) de cada objeto
    if (pesoF == 0)
    {
        cout << "Erro: Nao foi possivel alocar memoria para peso";
        return 14;
    }
    
    aux1 = new (nothrow) float [qnt_objetos]; // Vetor auxiliar, copia de valorF
    if (aux1 == 0)
    {
        cout << "Erro: Nao foi possivel alocar memoria para aux1";
        return 13;
    }
    
    aux2 = new (nothrow) float [qnt_objetos]; // Vetor auxiliar, copia de valorF
    if (aux2 == 0)
    {
        cout << "Erro: Nao foi possivel alocar memoria para aux2";
        return 13;
    }
    
    aux3 = new (nothrow) float [qnt_objetos]; // Vetor auxiliar, copia de valorF
    if (aux3 == 0)
    {
        cout << "Erro: Nao foi possivel alocar memoria para aux3";
        return 13;
    }
    
    aux4 = new (nothrow) float [qnt_objetos]; // Vetor auxiliar, copia de valorF
    if (aux4 == 0)
    {
        cout << "Erro: Nao foi possivel alocar memoria para aux4";
        return 13;
    }
    
    back = new (nothrow) int [qnt_objetos]; // Vetor com a seleção de objetos feita pelo algoritmo que resulta no valor final
    if (back == 0)
    {
        cout << "Erro: Nao foi possivel alocar memoria para back";
        return 15;
    }
    
    getline(cin,linha); // Pega a ultima quebra de linha dada ao digitar os valores
    
    for (int j = 0, i = 0; i < qnt_objetos && j < qnt_objetos; j++, i++)
    {
        getline(cin,linha); // Pega a linha completa
        
        aux = linha.find(',',0); //retorna o indice onde está a virgula
        
        auxV[i] = linha.substr(0,aux); // Pega a substring antes da virgula
        
        size_t pos = auxV[i].find('\r'); // Remove o \r da string (Linux Only)
        if (pos != -1)
            auxV[i].erase(pos);
        
        auxP[i] = linha.substr(aux+1,linha.size()); // Pega a substring depois da virgula
        
        pos = auxP[i].find('\r'); // Remove o \r da string (Linux Only)
        if (pos != -1)
            auxP[i].erase(pos);
        
        tam = contaCasasDecimais(auxV[i]);
        
        if (tam > maxFracaoV)
            maxFracaoV = tam;
        
        tam = contaCasasDecimais(auxP[i]);
        
        if (tam > maxFracaoP)
            maxFracaoP = tam;
    }
    
    tam = contaCasasDecimaisF(tam_mochilaF);
    
    if (maxFracaoP < tam)
        maxFracaoP = tam; 

    tam_mochilaI = (int)(tam_mochilaF * (pow(10,maxFracaoP))); // Transforma o tamanho da mochila em inteiro;
    
    maxP = 0;
    
    for (int i = 0; i < qnt_objetos; i++) // Transforma os vetores auxiliares em inteiros atraves de multiplicaçoes por potencias de 10
    {  
        valor[i] = strToInt(auxV[i],maxFracaoV);
        peso[i] = strToInt(auxP[i],maxFracaoP);
        
        if (peso[i] > maxP)
            maxP = peso[i];
    }
        
    delete [] auxP;
    delete [] auxV;
    
    if (tam_mochilaI > numeric_limits<int>::max())
    {
        cout << "Erro: Tamanho da mochila muito grande";
        return 16;
    }
    
    // -------------- FIM DO MAIN "GERAL" ------------- //
    
    for (int i = 0; i < qnt_objetos; i++)
        back[i] = 0;
    
    for (int i = 0; i < qnt_objetos; i++) // Transforma os numeros de inteiros para floats
    {
        valorF[i] = valor[i] / pow(10,maxFracaoV);
        aux1[i] = valorF[i];
        aux2[i] = valorF[i];
        aux3[i] = valorF[i];
        aux4[i] = valorF[i];
        pesoF[i] = peso[i] / pow (10,maxFracaoP);
    }
    
    begin = clock();
    
    // Chamada de cada um dos metodos
        
    b = begin;
    maximo = dynProg(qnt_objetos,tam_mochilaI,peso,valor,back); 
    e = clock();
    imprimirResultado(1,maximo,0,maxFracaoV,back,qnt_objetos,b,e);
    
    if (erro != 0) // Se o erro é zero, nem precisa chamar o algoritmo de aproximação
    {
        for (int i = 0; i < qnt_objetos; i++)
            back[i] = 0;
        
        b = clock();
        maximo = approximation(qnt_objetos,tam_mochilaI,peso,valor,maxFracaoP,maxP,erro,back);
        e = clock();
        imprimirResultado(2,maximo,0,maxFracaoV,back,qnt_objetos,b,e);
    }
        
    for (int i = 0; i < qnt_objetos; i++)
        back[i] = 0;
    
    b = clock();
    maximoF = heuristicaGulosaMenoresPesos(pesoF,qnt_objetos,aux1,tam_mochilaF,back);
    e = clock();
    imprimirResultado(3,0,maximoF,0,back,qnt_objetos,b,e);
    
    for (int i = 0; i < qnt_objetos; i++)
        back[i] = 0;
    
    b = clock();
    maximoF = heuristicaGulosaDensidade(pesoF,qnt_objetos,aux2,tam_mochilaF,back);
    e = clock();
    imprimirResultado(5,0,maximoF,0,back,qnt_objetos,b,e);
    
    for (int i = 0; i < qnt_objetos; i++)
        back[i] = 0;
    
    b = clock();
    maximoF = heuristicaGulosaMaioresValores(pesoF,qnt_objetos,aux3,tam_mochilaF,back);
    e = clock();
    imprimirResultado(6,0,maximoF,0,back,qnt_objetos,b,e);
    
    for (int i = 0; i < qnt_objetos; i++)
        back[i] = 0;
    
    b = clock();
    maximoF = ForcaBruta(pesoF,qnt_objetos,aux4,tam_mochilaF, back);
    e = clock();
    imprimirResultado(7,0,maximoF,0,back,qnt_objetos,b,e);
    
    end = clock();
    
    cout <<"\nTempo total necessario para a execucao: " << (double)(end-begin)/CLOCKS_PER_SEC << " segundos." << "\n";
    
    return 0;
}
