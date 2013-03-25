#include <cstdlib>
#include <iostream>
#include "Encode.h"
#include "Decode.h"

using namespace std;

string tests()
{
    string input = "";
//    input = "AAAAAABBBBBCCCCDDDEEF";
//    input = "AAAAAAAAAAAAAAABBBBBBBCCCCCCDDDDDDEEEEE";
//    input = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC";
//    input = "AAAAABBBCD";
//    input = "AABCCD";
//    input = "AABAAB";
//    input = "AABABBCCCD";
//    input = "AB";
    input = "AAAAABCD";
    return input;
}

int main(int argc, char** argv) {

    string input = "", coded = "", decoded = "", raw = "", bin = "", sh = "";
//  coded   = Mensagem codificada utilizando o metodo de Shannon-Fano e representada em bytes
//  input   = Entrada (string simples)
//  bin     = Mensagem binaria simples
//  sh      = Mensagem binaria utilizando Shannon-Fano
//  decoded = Mensagem, lida do arquivo, decodificada
    unsigned short choice;
    
    do
    {
        cout << "Codificação de um texto utilizando o algoritmo de Shannon-Fano" << endl << endl;
        cout << "1: Codificar" << endl;
        cout << "2: Decodificar" << endl;
        cout << "Escolha a opcao (0 para sair) : ";
    
    
        cin>>choice;
    
        switch (choice)
        {
            case 1:
                    cout << "Digite a string a ser codificada: " << endl;
                    cin >> input;
                    coded = encode(input, &bin, &sh);
                    cout << "Mensagem binaria (Simples)       : " << bin << " | numero de bits: " << bin.size() << endl;
                    cout << "Mensagem binaria (Shannon-Fano)  : " << sh << " | numero de bits: " << sh.size() << endl << endl;
                    cout << "Entrada            : " << input << endl;
                    cout << "Entrada Codificada : " << coded << endl;
                    break;
            case 2:
                    cout << "Arquivo 'output.out' a ser decodificado, certifique-se que o mesmo existe" << endl;
                    decoded = decode(&raw);
                    cout << "Saida              : " << raw << endl;
                    cout << "Saida Decodificada : " << decoded << endl;
                    break;
            case 3:
                    input = tests();
                    coded = encode(input, &bin, &sh);
                    decoded = decode(&raw);
                    cout << "Mensagem binaria (Simples)       : " << bin << " | numero de bits: " << bin.size() << endl;
                    cout << "Mensagem binaria (Shannon-Fano)  : " << sh << " | numero de bits: " << sh.size() << endl << endl;
                    cout << "Entrada            : " << input << endl;
                    cout << "Entrada Codificada : " << coded << endl << endl;
                    cout << "Saida              : " << raw << endl;
                    cout << "Saida Decodificada : " << decoded << endl << endl;
                break;
        }
    }while (choice != 0);
    
//  Limpando Memoria
    
    sh.clear();
    coded.clear();
    decoded.clear();
    input.clear();
    bin.clear();
    raw.clear();
    
    return 0;
}