/* 
 * File:   HeuristicasGulosas.h
 * Author: M1thr4nd1r
 *
 * Created on 9 de Outubro de 2012, 16:49
 */

#ifndef HEURISTICASGULOSAS_H
#define	HEURISTICASGULOSAS_H

#include "Funcoes.h"

float heuristicaGulosaDensidade(float * pes, int n,float * val, float tamanhoMochila, int *back);

float heuristicaGulosaMenoresPesos(float * pes, int n,float * val, float tamanhoMochila, int *back);

float heuristicaGulosaMaioresValores(float * pes, int n,float * val, float tamanhoMochila, int *back);

float heuristicaGulosaGetValoresEmOrdem(float * pes, int n,float * val, float tamanhoMochila, int *back);

#endif	/* HEURISTICASGULOSAS_H */

