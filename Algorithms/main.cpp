#include <cstdlib>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <ctime>
#include <vector>

using namespace std;

void imprimirResultado(int index,int maximo,int maxFracaoV,int *back,int qnt_objetos, clock_t begin, clock_t end)
{
    cout<<"Metodo "<<index<<": "<< ((float)maximo)/pow(10,maxFracaoV) << " , ";
    
    for (int i = 0; i < qnt_objetos; i++)
        cout<<back[i]<<' ';
    
    cout<<endl;
    
    cout <<"Tempo necessario para a execucao: " << (double)(end-begin)/CLOCKS_PER_SEC << " segundos." << "\n\n";
}

int contaCasasDecimais(string num)
{
    int aux = num.find('.',0);
        
    if (aux > 0)
        return num.size() - aux - 1; // -1 Porque conta a posicao da virgula
    
    return 0;
}

int contaCasasDecimaisF(float num)
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
{
    for (int i = 0; i < qnt_objetos; i++)
        cout << "Elemento " << i+1 << ": Valor = " << valor[i]/pow(10,maxFracaoV) << " Peso = " << peso[i]/pow(10,maxFracaoP) << endl;
}

void backtracking(int resultado,int qnt_objetos,int* back, int** matriz, int* peso, int* valor,int i, int j)
{
    if (resultado != 0)
    {
        // Caso a solucao com ponteiros pare de funcionar
        //float a = constroiCampo(i-1,j-peso[i],peso,valor) + valor[i]; 
        //float b = constroiCampo(i-1,j,peso,valor);

        //if (left.str().compare(right.str())) - Compara uma stringstream a outra
        
        int aux = j-peso[i];
        int a = 0,b = 0;
        if ((i!=0) && (aux >= 0))
        {
            a = matriz[i-1][aux] + valor[i];
            b = matriz[i-1][j];
        }
        else if (aux < 0)
            backtracking(resultado,qnt_objetos-1,back,matriz,peso,valor,i-1,j);
        else
        {
            a = valor[i];
            b = 0;
        }

        if (a == resultado)
        {
            back[qnt_objetos-1] = 1;
            backtracking(a-valor[i],qnt_objetos-1,back,matriz,peso,valor,i-1,j-peso[i]);
        }
        else if (b == resultado)
            backtracking (b,qnt_objetos-1,back,matriz,peso,valor,i-1,j);
    }
}

void backtracking2(int resultado,int qnt_objetos,int* back, vector< vector<int> >& matriz, int* peso, int* valor,int i, int j)
{  
    if (resultado != 0)
    {
        // Caso a solucao com ponteiros pare de funcionar
        //float a = constroiCampo(i-1,j-peso[i],peso,valor) + valor[i]; 
        //float b = constroiCampo(i-1,j,peso,valor);

        //if (left.str().compare(right.str())) - Compara uma stringstream a outra
        
        int aux = j-peso[i];
        int a = 0,b = 0;
        if ((i!=0) && (aux >= 0))
        {
            a = matriz[i-1][aux] + valor[i];
            b = matriz[i-1][j];
        }
        else if (aux < 0)
            backtracking2(resultado,qnt_objetos-1,back,matriz,peso,valor,i-1,j);
        else
        {
            a = valor[i];
            b = 0;
        }

        if (a == resultado)
        {
            back[qnt_objetos-1] = 1;
            backtracking2(a-valor[i],qnt_objetos-1,back,matriz,peso,valor,i-1,j-peso[i]);
        }
        else if (b == resultado)
            backtracking2(b,qnt_objetos-1,back,matriz,peso,valor,i-1,j);
    }
}

void constroiMatriz(int qnt_objetos,int tam_mochila,int* peso,int* valor, int** matriz)
{
    matriz = new (nothrow) int*[qnt_objetos]; 
    if (matriz == 0)
    {
        cout << "Erro: memoria nao pode ser alocada para matriz (quantidade de objetos muito grande)";
        exit(0);
    }
    
    for (int i = 0; i < qnt_objetos; i++)
    {
        matriz[i] = new (nothrow) int[tam_mochila];
        if (matriz[i] == 0)
        {
            cout << "Erro: memoria nao pode ser alocada para matriz (tamanho da mochila muito grande)";
            exit(0);
        }
    }
    
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

void constroiMatriz2(int qnt_objetos,int tam_mochila,int* peso,int* valor, vector<vector<int> >& matriz)
{
//    int** matriz;
//    matriz = new (nothrow) int*[qnt_objetos]; 
//    if (matriz == 0)
//    {
//        cout << "Erro: memoria nao pode ser alocada para matriz (quantidade de objetos muito grande)";
//        exit(0);
//    }
//    
//    for (int i = 0; i < qnt_objetos; i++)
//    {
//        matriz[i] = new (nothrow) int[tam_mochila];
//        if (matriz[i] == 0)
//        {
//            cout << "Erro: memoria nao pode ser alocada para matriz (tamanho da mochila muito grande)";
//            exit(0);
//        }
//    }
    
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
    
    //return matriz;
}

int dynProg(int qnt_objetos, int tam_mochila, int* peso, int* valor, int* back)
{
    /* dynProg com Vector
    vector< vector <int> > resultados (qnt_objetos, vector<int>(tam_mochila));
    
    constroiMatriz2(qnt_objetos,tam_mochila,peso,valor,resultados);
    
    int maximo = resultados[qnt_objetos-1][tam_mochila-1];
    
    backtracking2(maximo,qnt_objetos,back,resultados,peso,valor,qnt_objetos-1,tam_mochila-1);
    
    resultados.clear();
    */
    
    int **resultados=NULL; // dynProg com Ponteiros
    
    constroiMatriz(qnt_objetos,tam_mochila,peso,valor,resultados);
    
    int maximo = resultados[qnt_objetos-1][tam_mochila-1];
    
    backtracking(maximo,qnt_objetos,back,resultados,peso,valor,qnt_objetos-1,tam_mochila-1);
    
    delete [] resultados;
    
    
    /* Criacao da matriz da mochila, caso de erro com o metodo utilizado
    
    // Create the first dimension
    float **resultados = new float*[qnt_objetos]; 
    // Create each second dimension
    for (int i = 0; i < qnt_objetos; i++)
        resultados[i] = new float[tam_mochilaI];
    
    for (int i = 0; i < qnt_objetos; i++)
        for (int j = 0; j < tam_mochilaI; j++)
                resultados[i][j] = constroiCampo(i,j,peso,valor);
    */
    
    /* Para exibir a matriz resultados
    
    for (int i = 0; i < qnt_objetos; i++)
    {
        for (int j = 0; j < tam_mochilaI; j++)
                cout<<resultados[i][j]<<' ';
        cout<<endl;
    }
     
    for (int i = 0; i < tam_mochilaI; i++)
    {
        for (int j = 0; j < qnt_objetos; j++)
            cout<<resultados[j][i]<<' ';
        cout<<endl;
    }*/
    
    return maximo;
}

int approximation(int qnt_objetos, int tam_mochilaI, int* peso, int* valor, int maxFracaoV, int maxV, float erro, int* back)
{
    float k = maxV * erro / qnt_objetos;

    for (int i = 0; i < qnt_objetos; i++)
        valor[i] = floor(valor[i]/k * pow(10,maxFracaoV));
    return dynProg(qnt_objetos,tam_mochilaI,peso,valor,back);
}

/* ---------------------- Funcoes Antigas ---------------- 

int constroiCampo(int i,int j,int* peso, int* valor)
{
    //cout<<i<<" | "<<j<<endl;
    if ((i == -1) || (j == -1))
        return 0;
    int b = constroiCampo(i-1,j,peso,valor);
    if (j > peso[i])
    {
        int a = constroiCampo(i-1,j-peso[i],peso,valor) + valor[i];
        if (a > b)
            return a;
    }
    return b;
}

string dec2bin(int x){

    string valor;
    
    int i = 0;

    while(x > 1)
    {
        if(x % 2 == 0)
            valor.at(i) = '0';
        else
            valor.at(i) = '1';			
        
        x /= 2;	
        i++;
    }

    valor.at(i)   = '1';
    
    return valor;
}

void meetInTheMiddle(int qnt_objetos, int tam_mochilaI, int* peso, int* valor, int maxFracaoV)
{
    int aux = floor(qnt_objetos/2);
    int tamA = pow(2,aux)-1, tamB = pow(2,qnt_objetos-aux)-1;
    string A[tamA], B[tamB], ax;
    int vA[tamA],vB[tamB], j, v, p;
    int pA[tamA],pB[tamB];
    
    for (int i = 0; i < tamA; i++)
    {
        ax = dec2bin(i+1);
        v = 0;
        p = 0;
        for (j = 0; j < i+1; j++)
            if ((ax[j] == '1') && (p < tam_mochilaI))
            {
                v+= valor[i-j];
                p+= peso[i-j];
            }
        if (!((j < i) || (p > tam_mochilaI)))
        {
            A[i] = ax;
            vA[i]+= v;
            pA[i]+= p;
        }
        while (A[i].size()+1 < aux)
            A[i].append("0");
    }
    
    for (int i = 0; i < tamB; i++)
    {
        B[i] = dec2bin(i+1);
        if (B[i].size() > 1)
        {
            ax = B[i].substr(0,B[i].size());
            for (int j = 0; j < ax.size(); j++)
                B[i][j] = ax[ax.size()-j];
        }
        while (B[i].size() < qnt_objetos-aux)
            B[i].append("0");
    }
    
    for (int i = 0; i < tamA; i++)
    {
        for (int j = 0; j < aux; j++)
            if ((A[i][j] == '1') && (peso[j] <= pA[i]))
            {
                vA[i]+= valor[j];
                pA[i]+= peso[j];
            }
    }
}

int** constroiMatriz(int qnt_objetos,int tam_mochila,int* peso,int* valor)
{    
    int** matriz;
    matriz = new int*[qnt_objetos]; 
    for (int i = 0; i < qnt_objetos; i++)
        matriz[i] = new int[tam_mochila];
    
    for (int i=0;i<qnt_objetos;i++)
        matriz[i][0] = 0;
    
    for (int i = 1; i < qnt_objetos; i++)
        for (int j = 0; j < tam_mochila; j++)
        {
            matriz[0][j] = 0;
            if (j == 70)
                cout<<"";
            matriz[i][j] = constroiCampo(i,j,peso,valor);
        }
    
    return matriz;
}

*/

void troca(float &v1, float &v2)
{
    float vaux = v1;
    v1 = v2;
    v2 = vaux;
} 
 
//divide o array em dois
int divide(float * vet,int ini,int fim)
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

//ordena
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

void copyFloat(float * v1, float * v2,int n)
{
	int i;
	for(i = 0;i<n;v1[i] = v2[i], i++);
	v1[i] = '\0';
}

//void copyChar(char * v1, char * v2,int n)
//{
//	int i;
//	for(i = 0;i<n;v1[i] = v2[i], i++);
//	v1[i] = '\0';
//}

//void init(char * valor, int n)
//{
//	int a;
//	for(a = 0;a<n;valor[a] = '0',a++);	
//	valor[a] = '\0';
//}

//void inverte(string valor)
//{
//    return 
//}

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

int getDigitos(float valor)
{
	stringstream ss (stringstream::in | stringstream::out);

	ss << valor;

	string contaDigitos = ss.str();    
	
    return contaDigitos.size();
}

int getIndexOf(float * vet, float * vet2, float value, int t)
{
    int i = -1;
    float x = vet2[0]/vet[0];
    if(x == value) return 0;
    for(i = 1;((i < t) && (x != value));i++){
            x = vet2[i]/vet[i];
    }
    return (i < t) ? i : -1;
}

void heuristicaGulosaFracionaria(float * pes, int n,float * val, float tamanhoMochila){
    
//    Objetos * obj = new Objetos;
    float * valor = val;
    float * peso = pes;
    float w = 0;
    float valorPorPeso[n];
    int escolhidos[n];
    float t;
    float fracao[n];
    
    for(int i= 0; i<n;fracao[i] = escolhidos[i]= -1,i++);    
    for(int i = 0; i<n; valorPorPeso[i]=valor[i]/peso[i],i++);
    
    quicksort(*valorPorPeso,0,n-1);
    int a = 0;
    
    w = t = tamanhoMochila;
    do{
        int j = getIndexOf(peso,valor,valorPorPeso[a],n);
        if(j!=-1){
            (a == 0)? fracao[j] = 1: fracao[j] = (t - peso[j])/valor[j];
            if(w > 0 && fracao[j] <= w){
                //se não for o primeiro elemento escolhido tiramos o volume residual e dividimos pelo valor
                escolhidos[a] = j;
                tamanhoMochila -= peso[j];
            }
        }
        a++;
        w = tamanhoMochila;
    }while(w > 0 && a < n);

    float totalpeso,totalvalor,totaldensidade = 0;
    for(int i = 0;i<n; i++){
            if(escolhidos[i] != -1){
                    float a = valor[escolhidos[i]]/peso[escolhidos[i]];
                    totalpeso += peso[escolhidos[i]];
                    totalvalor += valor[escolhidos[i]];
                    totaldensidade += a;
            }
    }
    char escolha[n];
//    init(escolha,n);
    for(int i = 0;i<n;escolha[escolhidos[i]] = fracao[i],i++);
    cout << "\n"<< "Metodo Guloso heuristica Fracionaria:" << totalvalor << "," << escolha << endl;	
        
}

void heuristicaGulosaDensidade(float * pes, int n,float * val, float tamanhoMochila)
{
    float * valor = val;
    float * peso = pes;
    float w = 0;
    float valorPorPeso[n];
    int escolhidos[n];
    
    for(int i= 0; i<n;escolhidos[i]= -1,i++);    
    for(int i = 0; i<n; valorPorPeso[i]=valor[i]/peso[i],i++);
    
    quicksort(*valorPorPeso,0,n-1);
	int a = 0;
    
        w = tamanhoMochila;
        do{
            int j = getIndexOf(peso,valor,valorPorPeso[a],n);
            if(j!=-1){
                if(w > 0 && peso[j] <= w){
                    escolhidos[a] = j;
                    tamanhoMochila -= peso[j];
                }
            }
            a++;
            w = tamanhoMochila;
    }while(w > 0 && a < n);

    float totalpeso,totalvalor,totaldensidade = 0;
    for(int i = 0;i<n; i++){
            if(escolhidos[i] != -1){
                    float a = valor[escolhidos[i]]/peso[escolhidos[i]];
                    totalpeso += peso[escolhidos[i]];
                    totalvalor += valor[escolhidos[i]];
                    totaldensidade += a;
            }
    }
    char escolha[n];
//    init(escolha,n);
    for(int i = 0;i<n;escolha[escolhidos[i]] = '1',i++);
    cout << "\n"<< "Metodo Guloso heuristica maior densidade:" << totalvalor << "," << escolha << endl;	
}

void heuristicaGulosaMenoresPesos(float * pes, int n,float * val, float tamanhoMochila)
{
    int escolhidos[n];
    int ordenado[n];
    float w;
    float valor[n];
    float peso[n];
    float peso_asc[n];
    
    for(int i= 0; i<n;escolhidos[i]= -1,valor[i] = val[i],peso[i] = pes[i],i++);

    quicksort(*peso,0,n-1);	

    for(int i= 0; i<n;peso_asc[i] = peso[n-i-1],i++);

    /** pegar indices **/
    int k = 0;
    while(k < n){
            int j = 0;
            for(j = 0; ((j<n) && (peso_asc[k] != pes[j])) ;j++);
            ordenado[k] = j;
            k++;
    }

    int a = 0;

    w = tamanhoMochila;
    do{
            if(w > 0 && pes[ordenado[a]] <= w){
                    escolhidos[a] = ordenado[a];
                    tamanhoMochila -= pes[ordenado[a]];
            }	
            a++;
            w = tamanhoMochila;
    }while(w > 0 && a < n);

//    cout << "\nValor" << setw(16) << "Peso" << "\n";
    float totalpeso = 0,totalvalor = 0;
    for(int i = 0;i<n; i++){
            if(escolhidos[i] != -1){
                    int digitos = getDigitos(val[escolhidos[i]]);
//                    cout << '\n' << val[escolhidos[i]] << setw(20 - digitos) << peso[escolhidos[i]] << setw(20);
                    totalpeso += peso[escolhidos[i]];
                    totalvalor += val[escolhidos[i]];
            }
    }
//    cout << "\n\n"<<totalvalor << setw(20 - getDigitos(totalvalor) - getDigitos(totalpeso)) << "" << totalpeso  << endl;
    char escolha[n];
//    init(escolha,n);
    for(int i = 0;i<n;escolha[escolhidos[i]] = '1',i++);
    cout << "\n"<< "Metodo Guloso heuristica Menores pesos:" << totalvalor << "," << escolha << endl;	
	
}

void heuristicaGulosaMaioresValores(float * pes, int n,float * val, float tamanhoMochila)
{
    int escolhidos[n];
    int ordenado[n];
    float w;
    float valor[n];
    float peso[n];
    
    for(int i= 0; i<n;escolhidos[i]= -1,valor[i] = val[i],peso[i] = pes[i],i++);
		
    quicksort(*valor,0,n-1);	

    /** pegar indices **/
    int k = 0;
    while(k < n){
            int j = 0;
            for(j = 0; ((j<n) && (valor[k] != val[j])) ;j++);
            ordenado[k] = j;
            k++;
    }
	
	int a = 0;
	
	w = tamanhoMochila;
        do{
		if(w > 0 && peso[ordenado[a]] <= w){
			escolhidos[a] = ordenado[a];
			tamanhoMochila -= peso[ordenado[a]];
		}	
		a++;
		w = tamanhoMochila;
	}while(w > 0 && a < n);
	
//	cout << "\nValor" << setw(16) << "Peso" << "\n";
	float totalpeso = 0,totalvalor = 0;
	for(int i = 0;i<n; i++){
		if(escolhidos[i] != -1){
			int digitos = getDigitos(val[escolhidos[i]]);
//			cout << '\n' << val[escolhidos[i]] << setw(20 - digitos) << pes[escolhidos[i]] << setw(20);
			totalpeso += pes[escolhidos[i]];
			totalvalor += val[escolhidos[i]];
		}
	}
	//cout << "\n\n"<<totalvalor << setw(20 - getDigitos(totalvalor) - getDigitos(totalpeso)) << "" << totalpeso  << endl;
        char escolha[n];
//        init(escolha,n);
        for(int i = 0;i<n;escolha[escolhidos[i]] = '1',i++);
        cout << "\n"<< "Metodo Guloso heuristica Maiores valores:" << totalvalor << "," << escolha << endl;	
	
}

void heuristicaGulosaGetValoresEmOrdem(float * pes, int n,float * val, float tamanhoMochila)
{
	
    int escolhidos[n];
    float w;
    float * valor = val;
    float * peso = pes;
    
    for(int i= 0; i<n;escolhidos[i]= -1,i++);
    
    int a = 0;
	
	w = tamanhoMochila;
    do{
            if(w > 0 && peso[a] <= w){
                    escolhidos[a] = a;
                    tamanhoMochila -= peso[a];
            }
            a++;
            w = tamanhoMochila;
    }while(w > 0 && a < n);

    //cout << "\nValor" << setw(16) << "Peso" << "\n";
    float totalpeso,totalvalor = 0;
    for(int i = 0;i<n; i++){
            if(escolhidos[i] != -1){
                    int digitos = getDigitos(valor[escolhidos[i]]);
                    //cout << '\n' << valor[escolhidos[i]] << setw(20 - digitos) << peso[escolhidos[i]];
                    totalpeso += peso[escolhidos[i]];
                    totalvalor += valor[escolhidos[i]];
            }
    }
    //cout << "\n\n"<<totalvalor << setw(20 - getDigitos(totalvalor)) << totalpeso  << endl;
    char escolha[n];
//    init(escolha,n);
    for(int i = 0;i<n;escolha[escolhidos[i]] = '1',i++);
    cout << "\n"<< "Metodo Guloso heuristica Valor em ordem:" << totalvalor << "," << escolha << endl;	
        
}

void ForcaBruta(float * pes, int n,float * val, float tamanhoMochila)
{
	
    float maiorValor = 0,maiorPeso = 0;
    float w = tamanhoMochila;
    string escolha;

    long double num_combinacao = potencia(2,n);
    
    for(long double  i = 0;i <= (num_combinacao);i++)
    {

        float somaPeso = 0, somaValor = 0 ;
        string valorBin;
        string atual;

        /** Inicio da conversão para bin */

        //preenchendo o valor com '0'
        
        valorBin.insert(valorBin.begin(),n,'0');
        
        dec2bin(i,valorBin);

        valorBin = string ( valorBin.rbegin(), valorBin.rend() );

        size_t pos = valorBin.find_first_of('1');
        if (pos != -1)
        {
            atual = valorBin.substr(pos);
        
            //somando os pesos itens escolhidos
            for(int ini = 0;ini<n;ini++){
                    if(valorBin[ini] == '1'){
                                somaPeso+=pes[ini];
                                somaValor+=val[ini];
                    }
            }

            if(((w - somaPeso) >= 0) && (somaValor > maiorValor)){
                    maiorValor = somaValor;
                    maiorPeso = somaPeso;
                    escolha = valorBin;
            }
        }
        /** Fim da conversão */
    
    }
	
	float totalpeso = 0, totalvalor = 0;
	//cout << "\nValor" << setw(16) << "Peso " << endl;
	for(int y = 0;y < n;y++){
		if(escolha[y] == '1'){
//			int digitos = getDigitos(val[y]);
	//		cout << '\n' << val[y] << setw(20 - digitos) << pes[y];
			totalpeso += pes[y];
			totalvalor += val[y];
		}
	}
	//cout << "\n\n"<<totalvalor << setw(20 - getDigitos(totalvalor)) << totalpeso  << endl;
	cout << "\n"<< "Metodo Forca Bruta:" << totalvalor << "," << escolha << endl;
	
}

int main(int argc, char** argv) {
    
    int tam_mochilaI = 0,aux = 0,qnt_objetos = 0, maxFracaoP = 0,maxFracaoV = 0, tam, maxV = 0, maximo = 0, *valor, *peso, *back;
    float tam_mochilaF = 0, erro = 0, *pesoF, *valorF;
    string linha = "", *auxP = NULL, *auxV = NULL;
    clock_t begin = 0, end = 0, b = 0, e = 0;
    
    cin>>qnt_objetos>>tam_mochilaF>>erro;
    
    if (qnt_objetos > numeric_limits<int>::max())
    {
        cout << "Erro: Quantidade de objetos muito grande";
        return 10;
    }
    
    auxP = new (nothrow) string [qnt_objetos]; // Vetor auxiliar contendo o peso de cada objeto;
    if (auxP == 0)      
    {
        cout << "Erro: Nao foi possivel alocar memoria para auxP";
        return 11;
    }
    
    auxV = new (nothrow) string [qnt_objetos]; // Vetor auxiliar contendo o valor de cada objeto;
    if (auxV == 0)
    {
        cout << "Erro: Nao foi possivel alocar memoria para auxV";
        return 12;
    }
    
    valor = new (nothrow) int [qnt_objetos];
    if (valor == 0)
    {
        cout << "Erro: Nao foi possivel alocar memoria para valor";
        return 13;
    }
    
    peso = new (nothrow) int [qnt_objetos];
    if (peso == 0)
    {
        cout << "Erro: Nao foi possivel alocar memoria para peso";
        return 14;
    }
    
    valorF = new (nothrow) float [qnt_objetos];
    if (valorF == 0)
    {
        cout << "Erro: Nao foi possivel alocar memoria para valor";
        return 13;
    }
    
    pesoF = new (nothrow) float [qnt_objetos];
    if (pesoF == 0)
    {
        cout << "Erro: Nao foi possivel alocar memoria para peso";
        return 14;
    }
    
    back = new (nothrow) int [qnt_objetos];
    if (back == 0)
    {
        cout << "Erro: Nao foi possivel alocar memoria para back";
        return 15;
    }
    
    getline(cin,linha); // Pega o ultimo enter dado ao digitar os valores
    
    for (int j = 0, i = 0; i < qnt_objetos && j < qnt_objetos; j++, i++)
    {
        getline(cin,linha); // Pega a linha completa
        
        aux = linha.find(',',0); //retorna o indice onde está a virgula
        
        auxV[i] = linha.substr(0,aux); // Pega a substring antes da virgula
        
        size_t pos = auxV[i].find('\r');
        if (pos != -1)
            auxV[i].erase(pos);
        
        auxP[i] = linha.substr(aux+1,linha.size()); // Pega a substring depois da virgula
        
        pos = auxP[i].find('\r');
        if (pos != -1)
            auxP[i].erase(pos);
        
        tam = contaCasasDecimais(auxV[i]);
        
        if (tam > maxFracaoV)
            maxFracaoV = tam;
        
        tam = contaCasasDecimais(auxP[i]);
        
        if (tam > maxFracaoP)
            maxFracaoP = tam;
    }
    
    tam = contaCasasDecimaisF(tam_mochilaF);
    
    if (maxFracaoP < tam)
        maxFracaoP = tam; 

    for (int i = 0; i < qnt_objetos; i++) // Transforma os vetores auxiliares em inteiros atraves de multiplicaçoes sucessivas por 10
    {  
        valor[i] = strToInt(auxV[i],maxFracaoV);
         
        if (valor[i] > maxV)
            maxV = valor[i];
        
        peso[i] = strToInt(auxP[i],maxFracaoP);
    }
    
    delete [] auxP;
    delete [] auxV;
    
    tam_mochilaI = (int)(tam_mochilaF * (pow(10,maxFracaoP))); // Transforma o tamanho da mochila em inteiro;
    
    if (tam_mochilaI > numeric_limits<int>::max())
    {
        cout << "Erro: Tamanho da mochila muito grande";
        return 16;
    }
    
    // -------------- FIM DO MAIN "GERAL" ------------- //
    
    for (int i = 0; i < qnt_objetos; i++)
        back[i] = 0;
    
    begin = clock();
    
    // Chamada de cada um dos metodos
    
    /*
    b = begin;
    maximo = dynProg(qnt_objetos,tam_mochilaI,peso,valor,back); 
    e = clock();
    imprimirResultado(1,maximo,maxFracaoV,back,qnt_objetos,b,e);
    
    if (erro != 0)
    {
        for (int i = 0; i < qnt_objetos; i++)
            back[i] = 0;
        
        b = clock();
        maximo = approximation(qnt_objetos,tam_mochilaI,peso,valor,maxFracaoV,maxV,erro,back);
        e = clock();
        imprimirResultado(2,maximo,maxFracaoV,back,qnt_objetos,b,e);
    }
    */
    //meetInTheMiddle(qnt_objetos,tam_mochilaI,peso,valor,maxFracaoV);
    
    for (int i = 0; i < qnt_objetos; i++)
    {
        valorF[i] = valor[i] / pow(10,maxFracaoV);
        pesoF[i] = peso[i] / pow (10,maxFracaoP);
    }
    
    float aux1[qnt_objetos], aux2[qnt_objetos], aux3[qnt_objetos], aux4[qnt_objetos];
   
    copyFloat(aux1,valorF,qnt_objetos);
    copyFloat(aux2,valorF,qnt_objetos);
    copyFloat(aux3,valorF,qnt_objetos);
    copyFloat(aux4,valorF,qnt_objetos);
    
//    heuristicaGulosaMenoresPesos(pes,n,aux1,tamanhoMochila);
//    heuristicaGulosaFracionaria(pes,n,aux1,tamanhoMochila);
//    heuristicaGulosaGetValoresEmOrdem(pes,n,aux1,tamanhoMochila);
//    heuristicaGulosaDensidade(pes,n,aux2,tamanhoMochila);
//    heuristicaGulosaMaioresValores(pes,n,aux3,tamanhoMochila);
    ForcaBruta(pesoF,qnt_objetos,aux4,tam_mochilaF);
    
    end = clock();
    
    delete [] back;
    delete [] peso;
    delete [] valor;
    
    // imprimirObjetos(qnt_objetos,peso,valor,maxFracaoV,maxFracaoP); // Para exibir os elementos e suas caracteristicas
    
    cout <<"Tempo total necessario para a execucao: " << (double)(end-begin)/CLOCKS_PER_SEC << " segundos." << "\n";
    
    return 0;
}
