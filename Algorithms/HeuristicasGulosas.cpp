#include "HeuristicasGulosas.h"

float heuristicaGulosaDensidade(float * pes, int n,float * val, float tamanhoMochila, int *back)
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

    float totalpeso = 0,totalvalor = 0,totaldensidade = 0;
    for(int i = 0;i<n; i++){
            if(escolhidos[i] != -1){
                    float a = valor[escolhidos[i]]/peso[escolhidos[i]];
                    totalpeso += peso[escolhidos[i]];
                    totalvalor += valor[escolhidos[i]];
                    totaldensidade += a;
            }
    }
    for(int i = 0;i<n;back[escolhidos[i]] = 1,i++);
    return totalvalor;
}

float heuristicaGulosaMenoresPesos(float * pes, int n,float * val, float tamanhoMochila, int *back)
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
//                    cout << '\n' << val[escolhidos[i]] << setw(20 - digitos) << peso[escolhidos[i]] << setw(20);
                    totalpeso += peso[escolhidos[i]];
                    totalvalor += val[escolhidos[i]];
            }
    }
//    cout << "\n\n"<<totalvalor << setw(20 - getDigitos(totalvalor) - getDigitos(totalpeso)) << "" << totalpeso  << endl;
    for(int i = 0;i<n;back[escolhidos[i]] = 1,i++);
    return totalvalor;
}

float heuristicaGulosaMaioresValores(float * pes, int n,float * val, float tamanhoMochila, int *back)
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
//			cout << '\n' << val[escolhidos[i]] << setw(20 - digitos) << pes[escolhidos[i]] << setw(20);
			totalpeso += pes[escolhidos[i]];
			totalvalor += val[escolhidos[i]];
		}
	}
	//cout << "\n\n"<<totalvalor << setw(20 - getDigitos(totalvalor) - getDigitos(totalpeso)) << "" << totalpeso  << endl;
        for(int i = 0;i<n;back[escolhidos[i]] = 1,i++);
        return totalvalor;
}