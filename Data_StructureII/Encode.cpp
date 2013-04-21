#include "Encode.h"

// Converte a mensagem in para binario de acordo com a codificação de Shannon-Fano
string charToSF(string in, vector<Symbol> v)
{
    string out = "";
//    --- Metodo utilizando PesquisaBinaria (Com erro) ---
//    sort(v.begin(), v.end(), ordena);
//    for (int j = 0; j < in.size(); j++)
//        out+=PesquisaBinaria(v,in[j],v.size());
//    --- ---- --- --- ---- --- --- ---- --- --- ---- ---
    
    for (int j = 0; j < in.size(); j++)
        for (short i = 0; i < v.size(); i++)
            if (in[j] == v[i].getCharacter())
            {
                out+= v[i].getCode();
                break;
            }
    
    return out;
}

// Funcão para realizar PesquisaBinaria (Atualmente com erro)
string PesquisaBinaria ( vector<Symbol> v, char in , int N)
{
     int inf = 0; //Limite inferior      (o primeiro elemento do vetor em C é zero          )
     int sup = N-1; //Limite superior    (termina em um número a menos 0 à 9 são 10 numeros )
     int meio;
     while (inf <= sup) 
     {
          meio = inf + (sup-inf)/2;
          if (in == v[meio].getCharacter())
               return v[meio].getCode();
          else if (in > v[meio].getCharacter())
               sup = meio-1;
          else
               inf = meio+1;
     }
     return "";   // não encontrado
}

// Se um o caracter ja existe na lista de simbolos, incrementa a ocorrencia deste simbolo
bool exists(vector<Symbol> & v, int *ocorrence, char *caracter, char current)
{
    for (int i = 0; i < v.size(); i++) // Varrendo a lista de simbolos
        if (v[i].getCharacter() == *caracter)
        {
            v[i].addOcorrence(*ocorrence);
            *caracter = current; // Pega o proximo caracter (current) para ser analisado
            *ocorrence = 1; // Reseta a ocorrencia
            return true;
        }
    return false;
}

// Função de comparação para saber qual simbolo tem mais ocorrencia
bool maior(Symbol s1, Symbol s2)
{
    return (s1.getOcorrence() > s2.getOcorrence());
}

// Funcao de comparaçao para saber qual é o que tem caracter mais alto
bool ordena(Symbol s1, Symbol s2)
{
    return ((unsigned char)s1.getCharacter() > (unsigned char)s2.getCharacter());
}

// Cria os codigos de cada simbolo de acordo com Shannon-Fano
void makeCodes(vector<Symbol> & s)
{
    double x = 0, w = 0, a =0;
    short i = 0, j = 0, z = 0;
    
    for (short i = 0; i < s.size(); i++)
    // Calcula a quantidade total de simbolos
        z+= s[i].getOcorrence();
    
    for (short i = 0; i < s.size(); i++)
        s[i].calculateProbability(z);
    
    do
    // Atribui o codigo zero aos simbolos do lado esquerdo da arvore
    {
        x += s[i].getProbability();
        s[i].addCharCode('0');
        i++;
        w = x + s[i].getProbability();
    }while (w < 0.5);
    
    // Calcula a diferença de probabilidade das partes da arvore
    w = abs(0.5 - w);
    x = abs(0.5 - x);
    a = abs(w - x);
    
    if (!((a < std::numeric_limits<double>::epsilon())&&(a!=0))&&(w < x))
//  Neste caso é melhor pegar o proximo elemento 
//  (sua probabilidade fica mais equilibrada com a do outro lado da arvore)
    {
        s[i].addCharCode('0');
        i++;
    }    
    
    j = i;
    while (i < s.size())
    // Atribui o codigo um aos simbolos do lado direito da arvore
    {
        s[i].addCharCode('1');
        i++;
    }
    
    // Separa o vector de simbolos em duas partes a depender da probabilidade dos mesmos
    vector<Symbol> newS (s.begin(),s.begin()+j); 
    vector<Symbol> newS1 (s.begin()+j,s.end()); // (s.begin()+j+1 se for no windows)
        
    if (j > 1)
//  Neste caso existem mais do que um elementos do lado esquerdo, logo é necessario expandir ambos os lados da arvore  
    {
        makeCodes(newS);
        makeCodes(newS1);
    }
    else if (i > 2)
//  Neste caso existe mais do que dois elementos do lado direito, logo so é necessario expandir o lado direito da arvore
        makeCodes(newS1);
    
    for (int y = 0; y < s.size(); y++)
    // Atribui o codigo dos simbolos de acordo com a posição dos mesmos na arvore
        if (y < j)
           s[y].setCode(newS[y].getCode());
        else
            s[y].setCode(newS1[y-j].getCode());
}

string outArvore(vector <Symbol> symbols, string encoded, string *code)
{
    string outBin = "", c1 = "", c2 = "";
    *code = symbols.front().getCode();
    short unsigned index = 0;
    
    while (index < symbols.size() - 1)
    {
        c1 = symbols[index].getCode(); // Codigo do elemento mais significativo
        c2 = symbols[index+1].getCode(); // Codigo do segundo elemento mais significativo
        
        index++;
        
        int i = 0;
        while (c1[i] == c2[i]) // Enquanto os bits de dois simbolos vizinhos forem iguais
            i++;
        
        c2.erase(0,i); // Remova os i bits iguais entre os dois simbolos
        
        (*code) += c2; // Adicione o resto ao codigo da arvore
    }
    
    *code += '1'; // Adiciona-se o bit 1 para finalizar a representação da arvore
    
    outBin = *code; 
    
//    code.clear();
    c1.clear();
    c2.clear();
    
    for (short i = 0; i < symbols.size(); i++)
    {
        c1 = intToBin((unsigned char) symbols[i].getCharacter()); // Transforma o codigo ASCII do simbolo em binario
        fill(&c1, 8-c1.size()); // Aumenta a quantidade de bits do codigo para um byte
        outBin += c1; // Adiciona-se o codigo de cada simbolo
    }
    
    c1.clear();
    outBin += encoded; // Adiciona-se a mensagem codificada em Shannon-Fano
    
    encoded.clear();
    
    index = 0;
    
    while (index + 8 < outBin.size())
    {
        c1.assign(outBin, index, 8); // Atribui a substring de text com tamanho 8 começando de j
        outBin.erase(index,8);
        c2 += (char) binToInt(c1); // Transforma a string binaria bite em um numero inteiro
    }

    c1.assign(outBin, index, 8);
    
    c2 += (char) binToInt(c1);
    
    c2 += (char) c1.size();
    
    return c2;
}

// Constroi o vector que guardará todos os simbolos
void makeVector(string input, vector <Symbol> &symbols)
{
    char symbol = ' ';
    int ocorrence = 0;
    
    symbol = input[0];
    
    for (int i = 0; i < input.size(); i++)
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
}

// Codifica uma entrada num arquivo binario utilizando a codificação de Shannon-Fano
string encode(string *input, int *sizeB, int *sizeA)
{
    std::vector<Symbol> symbols;
    unsigned short num_bit = 1;
    bool flag = false;
    string file = "";

    if ((input != NULL) && (!input->empty()))
    {
        file = *input;
        flag = readFile(input);
    }
    
    if (flag)
    {
        *sizeB = input->size();
        
        makeVector(*input,symbols); // Constroi o vector com os simbolos

        while (symbols.size() > pow(2,num_bit)) // Conta quantos bits serao necessarios para representar os simbolos
            num_bit++;

        makeCodes(symbols); // Cria os codigos em Shannon-Fano de cada simbolo
        
        string encoded = charToSF(*input,symbols); // String com a mensagem na codificação de Shannon-Fano

        input->clear();
        
        string output = outArvore(symbols, encoded, input); // Saida do algoritmo de Shannon-Fano

        *sizeA = output.size();
        
        writeOutput(output, &file); // Escreve a(s) saida(s) no arquivo

        // Limpando memoria

        symbols.clear();
    
        // ---------------
        
        return output;
    }
    
    return "";
}