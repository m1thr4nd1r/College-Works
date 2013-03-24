/* 
 * File:   main.cpp
 * Author: M1thr4nd1r
 *
 * Created on 23 de Março de 2013, 21:48
 */

#include <iostream>
#include <fstream>
#include "Encode.h"

using namespace std;

Symbol makeSymbol(string glyphs, unsigned short *i)
{
    Symbol *s = new Symbol(glyphs[0], 0);
    string bite = "", qnt = "", code = "";
    unsigned short count = 0;
    
    bite = intToBin(glyphs[1]);
    
    fill(&bite,8-bite.size());
    
    qnt.assign(bite,0,6);
    code.assign(bite,6,2);
    
    count = binToInt(qnt);
    
    (*i)+= 2;
    
    if (count > 2)
    {
        bite = intToBin((short)glyphs[2]);
        fill(&bite,8-bite.size());
        code+= bite;
        (*i)++;
        
        if (count > 10)
        {
            bite = intToBin((short)glyphs[3]);
            fill(&bite,8-bite.size());
            code+= bite;
            (*i)++;
        }
        
        code.erase(code.begin(),code.end()-count);
    }
        
    s->setCode(code);
    
    return *s;
}

int main(int argc, char** argv) {

    string input = "", output = "", encoded = "";
    
    input = "AAAAAABBBBBCCCCDDDEEF";
//    input = "AAAAAAAAAAAAAAABBBBBBBCCCCCCDDDDDDEEEEE";
//    input = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC";
//    input = "AAAAABBBCD";
//    input = "AABCCD";
//    input = "AABAAB";
    
//    cin>>input;
    
    output = encode(input);
    
    fstream inFile;
    
    inFile.open("output.out",  fstream::binary | fstream::in | fstream::app);
    
    while(inFile.good())
        encoded+= inFile.get();
    
    inFile.close();
    
    encoded.erase(encoded.end()-1); // Removendo o caracter do EOF
    
    unsigned short start = 0;
    string current = "";
    bool flag = false;
    vector <Symbol> symbols;
    
    while (!flag)
    {
        current.assign(encoded,start,start+4);
        
        if (current.empty())
            flag = true;
        else
            symbols.push_back(makeSymbol(current, &start));
    }
    
    encoded.erase(encoded.begin(),encoded.end()-start);
    
    cout << "tes";
    
    return 0;
}

