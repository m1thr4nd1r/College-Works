#ifndef __Triangulacao__
#define __Triangulacao__ 1

#include "EstruturasDeDados.h"

void	initVertices(no_l *atual,no_l *anterior,no_l *proximo);
void	Triangular(no_l *atual,no_l *anterior,no_l *proximo);
bool	eDiagonal(no_l anterior, no_l proximo);
bool	eDiagonalPropria(no_l anterior, no_l proximo);

#endif 	// __Triangulacao__

