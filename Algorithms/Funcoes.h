/* 
 * File:   Funcoes.h
 * Author: M1thr4nd1r
 *
 * Created on 9 de Outubro de 2012, 16:50
 */

#ifndef FUNCOES_H
#define	FUNCOES_H

#include <string>
#include <ctime>
#include <sstream>
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

void imprimirTempo(clock_t begin, clock_t end);

void dec2bin(int x,string &valor);

int getDigitos(float valor);

int getIndexOf(float * vet, float * vet2, float value, int t);

void troca(float &v1, float &v2);

int divide(float * vet,int ini,int fim);

void quicksort(float &vet,int ini,int fim);

long double potencia(int base, int expoente);

void imprimirResultado(int index,int maximo,float maximoF,int maxFracaoV,int* back,int qnt_objetos, clock_t begin, clock_t end);

int contaCasasDecimais(string num);

int contaCasasDecimaisF(float num);

int strToInt(string num, int max);

void imprimirObjetos(int qnt_objetos, int* peso, int* valor, int maxFracaoV, int maxFracaoP);

#endif	/* FUNCOES_H */