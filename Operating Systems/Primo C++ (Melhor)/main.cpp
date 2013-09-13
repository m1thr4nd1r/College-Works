/*
 * main.cpp
 *
 *  Created on: 05/06/2013
 *      Author: m1thr4nnd1r
 */

#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <sstream>
#include <cmath>

using namespace std;

struct thread_data{
   unsigned int thread_id; // ID da thread
   unsigned int start; // Inicio do intervalo de checagem da thread
   unsigned int end; // Fim do intervalo de checagem da thread
};

void *Prime(void *td)
{
	struct thread_data *data; // Dados necessarios para a thread executar
	bool flag; // Flag para dizer se um numero é primo ou nao
	stringstream ss; // Variavel para converter inteiro para string
	string prime = ""; // Numeros primos de acordo com a thread

	data = (struct thread_data *) td;

	for (unsigned int i = data->start; i <= data->end; i++)
	{
		flag = false;

		for (unsigned int j = 2; j < sqrt(i); j++)
			if (i % j == 0) // Se i é multiplo de um numero j (j != 1 e j != i)
			{
				flag = true; // O numero é primo
				break;
			}

		if (!flag) // Se i nao é multiplo de nenhum numero x (x != 1 e x != i)
		{
			ss << i; // Envia i para ss
			prime+= ss.str() + " "; // Converte i para String
			ss.str(""); // Limpa a variavel
		}
	}

	cout << "Thread " << data->thread_id << " : " << prime << endl;

	pthread_exit(NULL);
}

int main(int argc,char **argv)
{
	unsigned int th; // Numero de Threads
	unsigned int n; // Intervalo de numeros para testar (0 ate n)
	unsigned int start = 2; // Inicio do intervalo para cada thread

	n = (argv[1] != NULL) ? atoi(argv[1]) : 200;
//  Caso o argumento 1 tenha sido passado, entao n = argumento, caso contrario n = 200
	th = (argv[2] != NULL) ? atoi(argv[2]) : 2;
//  Caso o argumento 2 tenha sido passado, entao th = argumento, caso contrario th = 2

	cout << th << " Threads e " << n << " numeros" << endl;

	unsigned int range = (n - 2) / th; // Intervalo de numeros para cada thread

//  --- Alocaçao das threads ---

	pthread_t * threads = (pthread_t *) malloc(sizeof(pthread_t)*th);

	thread_data * td = (thread_data *) malloc(sizeof(thread_data)*th);

//	---- --- --- --- --- --- ---

//	--- Inicializa os dados de cada uma das threads ---

	for (unsigned int i = 0; i < th; i++)
	{
		td[i].end = (start + range > n)? n : start + range;
		// td.end = Fim do intervalo de checagem da thread
		td[i].start = start;
		// td.start = Inicio do intervalo de checagem da thread
		td[i].thread_id = i + 1;
		// td.id = ID da thread
		start+= range + 1;
	}

//  --- --- --- --- --- --- --- --- --- --- --- --- ----

//	--- Chamada de cada thread ---

	for (unsigned int i = 0; i < th; i++)
		pthread_create(&threads[i], NULL, Prime, (void *)&td[i]);

//	--- --- --- --- --- --- --- ---

	pthread_exit(NULL);
//	Morte da Thread main

	return 0;
}
