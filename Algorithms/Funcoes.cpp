#include "Funcoes.h"

void dec2bin(int x,string &valor) 
{	
    int i = 0;

    if(x == 0){
            valor[i] = '0';
            return;
    }

    while(x > 1){
            if(x % 2 == 0)
            {
                    valor[i] = '0';
            }else
            {
                    valor[i] = '1';			
            }

            x /= 2;	
            i++;
    }

    valor[i]   = '1';		
}

int getDigitos(float valor) // Conta os digitos de um float
{
	stringstream ss (stringstream::in | stringstream::out);

	ss << valor;

	string contaDigitos = ss.str();    
	
    return contaDigitos.size();
}

int getIndexOf(float * vet, float * vet2, float value, int t)
{
    int i = -1;
    i = 0;

    float x;
    
    do{ 
        x = vet2[i]/vet[i];
        i+= (x != value) ? 1 : 0;
    }while((i < t) && (x != value));
    
    return (i < t) ? i : -1;
}

void troca(float &v1, float &v2) // troca o endereço de duas variaveis
{
    float vaux = v1;
    v1 = v2;
    v2 = vaux;
} 
 
int divide(float * vet,int ini,int fim) //divide o array em dois
{
    int i = ini;
    int j = fim;
    int dir = 1; 
    while (j > i)
    {
        if (vet[i] < vet[j])
        {
            troca(vet[i], vet[j]);
            dir =- dir;
        }
        if (dir == 1)
            j--; 
        else
            i++;
    }
    return i;
}

void quicksort(float &vet,int ini,int fim) 
{
    if (ini < fim)
    {
        int k = divide(&vet, ini, fim);
        quicksort(vet, ini, k-1);
        quicksort(vet, k+1, fim);
    }
}

long double potencia(int base, int expoente){
  if(expoente == 0)
    return 1;
  else
    return base * potencia(base, expoente - 1);
}

void imprimirResultado(int index,int maximo,float maximoF,int maxFracaoV,int *back,int qnt_objetos, clock_t begin, clock_t end)
// Imprime o valor maximo e o vetor de objetos escolhido
{
    switch(index)
    {
            case 1:
                cout<<"\nMetodo de Programacao Dinamica: "<< ((float)maximo)/pow(10,maxFracaoV) << " ,";
                break;
            case 2:
                cout<<"\nMetodo de Aproximacao: "<< ((float)maximo)/pow(10,maxFracaoV) << " ,";
                break;
            case 3:
                cout << "\n"<< "Metodo Guloso heuristica Menores pesos:" << maximoF << " ,";
                break;
            case 5:
                cout << "\n"<< "Metodo Guloso heuristica maior densidade:" << maximoF << " ,";
                break;
            case 6:
                cout << "\n"<< "Metodo Guloso heuristica Maiores valores:" << maximoF << " ,";
                break;
            case 7:
                cout << "\n"<< "Metodo Forca Bruta:" << maximoF << " ,";
                break;
    }
    
    for (int i = 0; i < qnt_objetos; i++)
        cout<<' '<<back[i];
    
    cout<<endl;
    imprimirTempo(begin,end);
}

void imprimirTempo(clock_t begin, clock_t end)
// Imprime o tempo entre begin e end
{
    cout <<"Tempo necessario para a execucao: " << (double)(end-begin)/CLOCKS_PER_SEC << " segundos." << "\n";
}

int contaCasasDecimais(string num) // Conta os digitos de uma string
{
    int aux = num.find('.',0);
        
    if (aux > 0)
        return num.size() - aux - 1; // -1 Porque conta a posicao da virgula
    
    return 0;
}

int contaCasasDecimaisF(float num) // Conta os digitos de um float
{
    stringstream aux;
    int pos = 0;
    string numero;
    aux << num;
    numero = aux.str();
    pos = numero.find_first_of('.'); 
    if (pos == -1) // Se pos é igual a -1, entao o numero é inteiro
        return 0;
    numero.erase(0,pos+1);
    return numero.size();
}

int strToInt(string num, int max)
{
    int tam = 0;
    tam = contaCasasDecimais(num);
    int aux = num.find('.',0);
    // Se aux for positivo entao a virgula foi encontrada, e sera eliminada
    if (tam > 0) 
        num.erase(aux,1);
    for (int j = 0; j < abs(max - tam); j++)
        num.append("0");
    return atoi(num.c_str());
}

void imprimirObjetos(int qnt_objetos, int* peso, int* valor, int maxFracaoV, int maxFracaoP) 
// Imprime todos os objetos com seus respectivos pesos e valores
{
    for (int i = 0; i < qnt_objetos; i++)
        cout << "Elemento " << i+1 << ": Valor = " << valor[i]/pow(10,maxFracaoV) << " Peso = " << peso[i]/pow(10,maxFracaoP) << endl;
}