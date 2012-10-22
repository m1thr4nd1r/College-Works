#include "PD.h"

void backtracking(int resultado,int qnt_objetos,int* back, vector< vector<int> >& matriz, int* peso, int* valor,int i, int j)
// Funcao para descobrir o vetor de objetos selecionados apartir do valor maximo obtido
{  
    if (resultado != 0) // Se resultado for igual a zero, terminou o retrocesso
    {
        int aux = j-peso[i];
        int a = 0,b = 0;
        
        // Seta os valores de a e b
        
        if ((i!=0) && (aux >= 0))
        {
            a = matriz[i-1][aux] + valor[i];
            b = matriz[i-1][j];
        }
        else if (aux < 0) // Se aux é menor que zero o objeto nao cabe na mochila
            backtracking(resultado,qnt_objetos-1,back,matriz,peso,valor,i-1,j);
        else
        {
            a = valor[i];
            b = 0;
        }

        // Preenche o valor de objetos selecionados de acordo com os valores de a e b
        
        if (a == resultado) 
        {
            back[qnt_objetos-1] = 1;
            backtracking(a-valor[i],qnt_objetos-1,back,matriz,peso,valor,i-1,j-peso[i]);
        }
        else if (b == resultado)
            backtracking(b,qnt_objetos-1,back,matriz,peso,valor,i-1,j);
    }
}

void constroiMatriz(int qnt_objetos,int tam_mochila,int* peso,int* valor, vector<vector<int> >& matriz)
{
    for (int i=0;i<qnt_objetos;i++)
        matriz[i][0] = 0;
    
    for (int i = 0; i < qnt_objetos; i++)
        for (int j = 1; j < tam_mochila; j++)
        {
            if (j>= peso[i])
            {
                int a = 0;
                
                if (i > 0)
                    a = matriz[i-1][j-peso[i]] + valor[i];
                else
                    a = valor[i];
                
                if ((i==0) || (a > matriz[i-1][j]))
                    matriz[i][j] = a;
                else
                    matriz[i][j] = matriz[i-1][j];
            }
            else if (i==0)
                matriz[i][j] = 0;
            else
                matriz[i][j] = matriz[i-1][j];
        }
}

int dynProg(int qnt_objetos, int tam_mochila, int* peso, int* valor, int* back)
{
    vector< vector <int> > resultados (qnt_objetos, vector<int>(tam_mochila));
    
    constroiMatriz(qnt_objetos,tam_mochila,peso,valor,resultados);
    
    int maximo = resultados[qnt_objetos-1][tam_mochila-1];
    
    backtracking(maximo,qnt_objetos,back,resultados,peso,valor,qnt_objetos-1,tam_mochila-1);
    
    resultados.clear(); // Deleta o vetor de resultados
    
    return maximo;
}

int approximation(int qnt_objetos, int tam_mochila, int* peso, int* valor, int maxFracaoP, int maxP, float erro, int* back)
{
    float k = maxP * erro / qnt_objetos; 

    for (int i = 0; i < qnt_objetos; i++)
        peso[i] = floor(peso[i]/k * pow(10,maxFracaoP)); // Arrendondamento do peso baseado na variavel k
                                                           // o pow é devido ao peso[i] ser inteiro
    tam_mochila = floor(tam_mochila/k * pow(10,maxFracaoP));
    
    return dynProg(qnt_objetos,tam_mochila,peso,valor,back);
}