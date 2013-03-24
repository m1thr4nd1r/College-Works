/* 
 * File:   Node.h
 * Author: M1thr4nd1r
 *
 * Created on 24 de Março de 2013, 15:03
 */

#ifndef NODE_H
#define	NODE_H

#include <cstdlib>

class Node {
public:
    Node();
    Node *parent, *child0, *child1;
    char getSymbol();
    char getBit();
    void setBit(char bit);
    void setSymbol(char symbol);
private:
    char symbol, bit;
};

#endif	/* NODE_H */

