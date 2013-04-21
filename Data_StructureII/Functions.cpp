#include "Functions.h"

// Transforma uma string binaria em um numero inteiro
short binToInt(string n)
{
    unsigned short sum = 0;
    for (unsigned short i = n.size(); i > 0; i--)
        if (n[i-1] == '1')
            sum += pow(2,n.size()-i);
    return sum;
}

// Transforma um numero inteiro em uma string binaria
string intToBin(short n)
{
    string text = "";
    stringstream ss;
    
    if (n == 0 || n == 1) 
    {
        ss << n; // Convertendo n para string
        text = ss.str(); // Atribuindo o valor de n em string para text
    }
    else {
        text = intToBin(n >> 1);
        ss.str(""); // Esvaziando a string de ss
        ss << (n & 0x1);
        text.append(ss.str());
    }
    
    return text;
}

// Preenche uma string com o liquid ate a mesma possuir o tamanho count
void fill(string *text, short count, char liquid)
{
    (*text).insert((*text).begin(),count,liquid);
}

// Transforma uma string binaria em byte(s)
string binToByte(string text)
{
    string bite = "", output = "";
    unsigned short j = 0;
    
    while (j + 8 < text.size())
    {
        bite.assign(text, j, 8); // Atribui a substring de text com tamanho 8 começando de j
        output += (char) binToInt(bite); // Transforma a string binaria bite em um numero inteiro
        j+= 8;
    }

    bite.assign(text, j, 8);
    output += (char) binToInt(bite);
    
    output += (char) bite.size();
    
    return output;
}

// Escreve a saida no arquivo
void writeOutput(string output, string *file)
{
    fstream outFile;
    
    file->append(".out");
    
    // Abre o arquivo no modo binario, para operaçoes de saida
    outFile.open(file->c_str(),  fstream::binary | fstream::out | fstream::ate);
    
    for (int i = 0; i < output.size(); i++)
    // Coloca output no arquivo byte a byte
        outFile.put(output[i]);
    
    outFile.close();
}

bool readFile(string *in)
{
    ifstream inFile;    
    
    inFile.open(in->c_str(), ios::in | ios::binary);
    
    if (!inFile)
        return false;
    
    in->clear();
    
    while(inFile.good())
        (*in) += inFile.get();
    
    in->erase(in->end()-1);
    
    return true;
}

bool writeFile(string output, string *file)
{
    fstream outFile;
    
    file->append(".dec");
    
    // Abre o arquivo no modo binario, para operaçoes de saida
    outFile.open(file->c_str(),  fstream::binary | fstream::out | fstream::ate);
    
    if (!outFile)
        return false;
    
    for (int i = 0; i < output.size(); i++)
    // Coloca output no arquivo byte a byte
        outFile.put(output[i]);
    
    outFile.close();
    
    return true;
}