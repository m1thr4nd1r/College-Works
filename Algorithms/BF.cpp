#include "BF.h"

float ForcaBruta(float * pes, int n,float * val, float tamanhoMochila, int* back)
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
                        back[y] = 1;
                        totalpeso += pes[y];
			totalvalor += val[y];
		}
	}
        return totalvalor;
	//cout << "\n\n"<<totalvalor << setw(20 - getDigitos(totalvalor)) << totalpeso  << endl;	
}
