/* 
 * File:   Node.cpp
 * Author: M1thr4nd1r
 * 
 * Created on 24 de Março de 2013, 15:03
 */

#include "Node.h"

Node::Node() 
{
    this->parent = NULL;
    this->child0 = NULL;
    this->child1 = NULL;
    this->symbol = ' ';
    this->bit = ' ';
}

char Node::getSymbol()
{
    return this->symbol;
}

char Node::getBit()
{
    return this->bit;
}

void Node::setBit(char bit)
{
    this->bit = bit;
}

void Node::setSymbol(char symbol)
{
    this->symbol = symbol;
}