#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <ctime>
#include "Encode.h"
#include "Decode.h"

using namespace std;

int main(int argc, char** argv) {

    string input = "", coded = "", decoded = "", file = "";
//  coded   = Mensagem codificada utilizando o metodo de Shannon-Fano e representada em bytes
//  input   = Entrada (string simples)
//  decoded = Mensagem, lida do arquivo, decodificada
    char choice = ' ';
    int after = 0, before = 0; // Inteiros para comparação da compressao
    double rate = 0; // Taxa de compressao
    clock_t begin = 0, end = 0, b = 0,e = 0; // Timers
 
    if (argc == 3)
//  Nesse caso, os argumentos foram passados na chamada do programa      
    {
        choice = *(argv[1]);
        input = argv[2];
    }
    else
//  Caso os argumentos não tenham sido passados  
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
                file = input;
        case 'e':
                begin = clock();
                coded = encode(&input,&before,&after);
                end = clock();
                
                if (coded != "")
                {
                    rate =  ((double) after / before) * 100;
                    
                    cout << endl << "Tempo total necessario para a codificacao: " << (double)(end-begin)/CLOCKS_PER_SEC << " segundos." << endl;
                    cout << "Taxa de compressao: " << std::setprecision((rate > 100)? 5 : 4) << rate << "%" << endl;
                    cout << "Economia de espaco: " << std::setprecision(4) << 100 - rate << "%" << endl;
                    cout << "Arquivo '" + file + ".out' foi criado" << endl;
                }
                else
                    cout << "Arquivo '" + file + "' nao encontrado" << endl;
                break;
        case 'D':
                cout << "Digite o nome do arquivo a ser decodificado: " << endl;
                cin >> input;
                file = input;
        case 'd':
                begin = clock();
                decoded = decode(&input);
                end = clock();    
                
                if (decoded != "")
                {
                    cout << "Arquivo '" + file + "' foi criado" << endl;
                    cout << endl << "Tempo total necessario para a decodificacao: " << (double)(end-begin)/CLOCKS_PER_SEC << " segundos." << endl;
                }
                else
                    cout << "Arquivo '" + file + "' nao encontrado" << endl;
                break;
        case 'h':
//              Caso para testes, ja realiza a codificação e decodificação
                input = "3.txt";
        case 't':
                file = input;
                cout<< endl << "Codificando...." << endl;
                
                begin = clock();
                
                b = begin;
                coded = encode(&input,&before,&after);
                e = clock();
                
                if (coded != "")
                {
                    rate =  ((double) after / before) * 100;
                    file += ".out";
                    cout << "Tempo necessario para a codificacao: " << (double)(e-b)/CLOCKS_PER_SEC << " segundos." << endl;
                    cout << "Taxa de compressao: " << std::setprecision((rate > 100)? 5 : 4) << rate << "%" << endl;
                    cout << "Economia de espaco: " << std::setprecision(4) << 100 - rate << "%" << endl;
                    
                    cout << "Arquivo '" + file + "' foi criado" << endl;
                    
                    cout << endl << "Decodificando....(" << coded.size() << ")" << endl; // Valor entre parentese significa o tamanho da entrada em bytes
                
                    b = clock();
                    decoded = decode(&file);
                    e = clock();
                    
                    if (decoded != "")
                    {
                        cout << "Tempo necessario para a decodificacao: " << (double)(e-b)/CLOCKS_PER_SEC << " segundos." << endl;
                        cout << "Arquivo '" + file + "' foi criado" << endl;
                        
                        end = clock();
                    
                        cout << endl << "Tempo total necessario para a execucao: " << (double)(end-begin)/CLOCKS_PER_SEC << " segundos.";
                    }
                    else
                        cout << "Arquivo '" + file + "' nao encontrado" << endl;
                }
                else
                    cout << "Arquivo '" + file + "' nao encontrado" << endl;

                choice = 0;
                break;
        default:
            cout << "Opção Invalida" << endl;
    }
    
//  Limpando Memoria
    
    coded.clear();
    decoded.clear();
    input.clear();
    
    return 0;
}