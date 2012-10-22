/* 
 * File:   PD.h
 * Author: M1thr4nd1r
 *
 * Created on 9 de Outubro de 2012, 16:49
 */

#ifndef PD_H
#define	PD_H

#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib>

using namespace std;

int dynProg(int qnt_objetos, int tam_mochila, int* peso, int* valor, int* back);

int approximation(int qnt_objetos, int tam_mochilaI, int* peso, int* valor, int maxFracaoP, int maxP, float erro, int* back);

void backtracking(int resultado,int qnt_objetos,int* back, int** matriz, int* peso, int* valor,int i, int j);
 
void constroiMatriz(int qnt_objetos,int tam_mochila,int* peso,int* valor, int** matriz);

#endif	/* PD_H */

