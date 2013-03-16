/* 
 * File:   ain.cpp
 * Author: M1thr4nd1r
 *
 * Created on 6 de Março de 2013, 10:00
 */

#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Symbol.h"

using namespace std;

unsigned short calculateProbability(vector<Symbol> & s)
{
    unsigned short prob_total = 0;
    
    for (short i = 0; i < s.size(); i++)
        prob_total+= s[i].getOcorrence();
    
    for (short i = 0; i < s.size(); i++)
        s[i].setProbability( abs( (double) s[i].getOcorrence() / ( (double)prob_total ) ) );
    
    return prob_total;
}

bool exists(vector<Symbol> & v, unsigned short *ocorrence, char *caracter, char current)
{
    short j = 0;
    while(j < v.size())
    {
        if (v[j].getCaracter() == *caracter)
        {
            v[j].addOcorrence(*ocorrence);
            *caracter = current;
            *ocorrence = 1;
            return true;
        }
        j++;
    }
    return false;
}

bool compare(Symbol s1, Symbol s2)
{
    return (s1.getOcorrence() > s2.getOcorrence());
}

string integerToBinary(short n)
{
    string text = "";
    stringstream ss;
    
    if (n == 0 || n == 1) 
    {
        ss << n;
        text = ss.str();
    }
    else {
        text = integerToBinary(n >> 1);
        ss.str("");
        ss << (n & 0x1);
        text.append(ss.str());
    }
    
    return text;
}

string encode(string in, vector<Symbol> v)
{
    string out = "";
    for (short j = 0; j < in.size(); j++)
        for (short i = 0; i < v.size(); i++)
        {
            if (in[j] == v[i].getCaracter())
                out+= v[i].getCode();
        }
    return out;
}

void makeTree(vector<string> & t, vector<Symbol> s, vector<Symbol> s1, bool flag)
{
    double sum = 0;
    short i = 0, j = 0;
    string symbols = "", rest = "";
    
    calculateProbability(s);
    
    do
    {
        sum += s[i].getProbability();
        symbols.push_back(s[i].getCaracter());
        i++;
        j++;
    }while (sum < 0.5);
    
    while (i < s.size())
    {
        rest.push_back(s[i].getCaracter());
        i++;
    }
    
    t.push_back(symbols);
    t.push_back(rest);
    
    if (j > 1)
    {
        vector<Symbol> newS (s.begin(),s.begin()+j);
        vector<Symbol> newS1 (s.begin()+j,s.end()); // (s.begin()+j+1 se for no windows)
        
        if (flag)    
        {
            makeTree(t,newS1,newS,false);
            makeTree(t,newS,newS1,false);
        }
        else
        {
            makeTree(t,newS,newS1,true);
            makeTree(t,newS1,newS,false);
        }
    }
    else if (i > 2)
    {
        vector<Symbol> newS1 (s.begin(),s.begin()+j);
        vector<Symbol> newS (s.begin()+j,s.end()); // (s.begin()+j+1 se for no windows)
        
        makeTree(t,newS,newS1,false);
    }
}

int main(int argc, char** argv) 
{
    std::vector<Symbol> symbols;
    string input = "";
    char symbol = ' ';
    unsigned short ocorrence = 0;
    unsigned short num_bit = 1;
    
    input = "AAAAAABBBBBCCCCDDDEEF";
//    input = "AABCCD";
//    input = "AABAAB";
    
//    cin>>input;
    
    symbol = input[0];
    
    for (short i = 0; i < input.size(); i++)
    {
        bool flag = false;
        if (input[i] != symbol)
        {
            if (!exists(symbols,&ocorrence,&symbol,input[i]))
            {
                Symbol* s = new Symbol(symbol,ocorrence);
                symbols.push_back(*s);
                ocorrence = 1;
                symbol = input[i];
            }
        }
        else
        {
            flag = false;
            ocorrence++;
        }
    }
    
    if (!exists(symbols,&ocorrence,&symbol,' '))
    {
        Symbol* s = new Symbol(symbol,ocorrence);
        symbols.push_back(*s);
    }
    
    sort(symbols.begin(), symbols.end(), compare);
    
    while (symbols.size() > pow(2,num_bit))
        num_bit++;
    
    
    string chars = "";
        
    for (short i = 0; i < symbols.size(); i++)
    {
        string code = integerToBinary(i);
        code.insert(code.begin(),num_bit-code.size(),'0');
        symbols[i].setCode(code);
        chars += symbols[i].getCaracter();
    }
    
    cout<<encode(input,symbols)<<" Bits: "<<encode(input,symbols).size();
    
    vector<string> tree;
    
    tree.push_back(chars);
    
    makeTree(tree,symbols,symbols,false);
    
    for (int i = 0; i < tree.size(); i++)
        cout << " " << tree[i] << " ";
    
    return 0;
}