#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "Symbol.h"

using namespace std;

string inToBin(string in, vector <Symbol> v, short num_bit)
{
    string out = "", code = "";
    for (short j = 0; j < in.size(); j++)
        for (short i = 0; i < v.size(); i++)
        {
            code = "";
            if (in[j] == v[i].getCharacter())
            {
                code = intToBin(i);
                fill(&code,num_bit-code.size());
                out+= code;
            }
        }
    return out;
}

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
        if (v[j].getCharacter() == *caracter)
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

bool maior(Symbol s1, Symbol s2)
{
    return (s1.getOcorrence() > s2.getOcorrence());
}

string charToSF(string in, vector<Symbol> v)
{
    string out = "";
    for (short j = 0; j < in.size(); j++)
        for (short i = 0; i < v.size(); i++)
        {
            if (in[j] == v[i].getCharacter())
                out+= v[i].getCode();
        }
    return out;
}

void makeCodes(vector<Symbol> & s)
{
    double sum = 0, w = 0;
    short i = 0, j = 0, z = 0;
    string symbols = "", rest = "";
    
    z = calculateProbability(s);
    
    do
    {
        sum += s[i].getProbability();
        s[i].addCharCode('0');
        symbols.push_back(s[i].getCharacter());
        i++;
        w += sum + s[i].getProbability();
    }while (w < 0.5);
    
    double a = abs((1 - w) - w);
    double b = abs((1 - sum) - sum);
    
    if (b > a)
    {
        sum = w;
        symbols.push_back(s[i].getCharacter());
        s[i].addCharCode('0');
        i++;
    }
    
    j = i;
    
    while (i < s.size())
    {
        rest.push_back(s[i].getCharacter());
        s[i].addCharCode('1');
        i++;
    }
    
    vector<Symbol> newS (s.begin(),s.begin()+j);
    vector<Symbol> newS1 (s.begin()+j,s.end()); // (s.begin()+j+1 se for no windows)
    
    if (j > 1)
    {
        makeCodes(newS); // true
        makeCodes(newS1);
    }
    else if (i > 2)
        makeCodes(newS1);
    
    for (int i = 0; i < s.size(); i++)
        if (i < j)
            s[i].setCode(newS[i].getCode());
        else
            s[i].setCode(newS1[i-j].getCode());
}

string outArvore(vector <Symbol> symbols, string encoded)
{
    string output = intToBin(symbols.size()), code = symbols.front().getCode(), c1 = "", c2 = "";
    short unsigned index = 0;
    
    while (index < symbols.size() - 1)
    {
        c1 = symbols[index].getCode();
        c2 = symbols[index+1].getCode();
        
        index++;
        
        code+= '1';
        
        if (((c1.size() == c2.size()) && (c1[0] != c2[0])) || (c1.size() != c2.size()))
            code+= '0';
    }
    
    fill(&output,8-output.size());
    
    output+= code + '1';
    
    for (short i = 0; i < symbols.size(); i++)
    {
        string ch = intToBin(symbols[i].getCharacter());
        fill(&ch, 8-ch.size());
        output += ch;
    }
    
    output += encoded;
    
    return output;
}

void writeOutput(string output, string outputOLD)
{
    fstream outFile;
    
    outFile.open("output.out",  fstream::binary | fstream::out | fstream::ate);
    
    for (int i = 0; i < output.size(); i++)
        outFile.put(output[i]);
    
    outFile.close();
    
    outFile.open("output.old",  fstream::binary | fstream::out | fstream::ate);
    
    for (int i = 0; i < output.size(); i++)
        outFile.put(outputOLD[i]);
    
    outFile.close();
}

string encode(string input)
{
    std::vector<Symbol> symbols;
    char symbol = ' ';
    unsigned short ocorrence = 0;
    unsigned short num_bit = 1;
    
    symbol = input[0];
    
    for (short i = 0; i < input.size(); i++)
    {
        if (input[i] != symbol)
        {
            if (!exists(symbols,&ocorrence,&symbol,input[i])) // Se o simbolo não existe na lista de simbolos...
            {
                Symbol* s = new Symbol(symbol,ocorrence); // Cria um novo simbolo
                symbols.push_back(*s); // Adiciona na lista de simbolos
                ocorrence = 1;
                symbol = input[i]; // Pega o proximo simbolo
            }
        }
        else
            ocorrence++;
    }
    
    if (!exists(symbols,&ocorrence,&symbol,' ')) // Se o ultimo simbolo nao existe na lista de simbolos...
    {
        Symbol* s = new Symbol(symbol,ocorrence); // Cria um novo simbolo
        symbols.push_back(*s); // Adiciona na lista de simbolos
    }
    
    sort(symbols.begin(), symbols.end(), maior); // Ordenar os simbolos crescentemente de acordo com a ocorrencia
    
    while (symbols.size() > pow(2,num_bit)) // Conta quantos bits serao necessarios para representar os simbolos
        num_bit++;
        
    cout<<inToBin(input,symbols, num_bit)<<" Bits: "<<inToBin(input,symbols, num_bit).size()<< endl; // Imprime os simbolos em binario de acordo com sua ocorrencia
   
    makeCodes(symbols); // Cria os codigos em Shannon Fano de cada simbolo
    
    string encoded = charToSF(input,symbols);
    
    cout<< encoded <<" Bits: "<< encoded.size() << " " << endl;
    
    string output = outArvore(symbols, encoded);
    
    output = binToByte(output);
    
//    METODO ANTIGO PARA EFEITO DE COMPARACAO
    
    string outputOLD = "";
    
    for (unsigned short i = 0; i < symbols.size(); i++)
        outputOLD += binToByte(symbols[i].signature());
    
    outputOLD += binToByte(encoded);
    
//    FIM METODO ANTIGO
    
    writeOutput(output, outputOLD);
    
    return encoded;
}