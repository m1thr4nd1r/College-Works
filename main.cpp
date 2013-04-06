#include <cstdlib>
#include <iostream>
#include "Encode.h"
#include "Decode.h"

using namespace std;

int main(int argc, char** argv) {

    string input = "", coded = "", decoded = "", file = "";
//  coded   = Mensagem codificada utilizando o metodo de Shannon-Fano e representada em bytes
//  input   = Entrada (string simples)
//  decoded = Mensagem, lida do arquivo, decodificada
    char choice = ' ';
 
    if (argc == 3)
    {
        choice = (*argv)[1];
        input = argv[2];
    }
    else
    {
        cout << " ------  Codificacao de um texto utilizando o algoritmo de Shannon-Fano  ------" << endl;
        cout << "E: Codificar" << endl;
        cout << "D: Decodificar" << endl;
        cout << "Escolha a opcao (0 para sair) : ";

        cin>>choice;
    }
    
    switch (choice)
    {
        case 'E':
                cout << "Digite o nome do arquivo a ser codificado :" << endl;
                cin >> input;
        case 'e':
                coded = encode(&input,NULL);
                break;
        case 'D':
                cout << "Digite o nome do arquivo a ser decodificado: " << endl;
                cin >> input;
        case 'd':
                decoded = decode(&input,"");
                break;
        case 't':
                input = "bd.jpeg";
                coded = encode(&input, &file);
                cout<< "Decodificando....(" << input.size() << ")" << endl;
                decoded = decode(&file,input);
                choice = 0;
                break;
    }
    
//  Limpando Memoria
    
    coded.clear();
    decoded.clear();
    input.clear();
    
    return 0;
}