#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TAM 60

int turn;
pthread_t proc1, proc2;
int saida;
int v_dados[TAM];

/*
  Insere dados inteiros aleatorios num vetor e o ordena em threads distintas.
*/

void *insere_dados(void *v_dados) {
  int i;
  int *dados = v_dados;

  srand(time(NULL));
  
  while (1) {
    while (turn != 0) {}

    for (i = 0; i < TAM; i++) {
      dados[i] = rand() % 100; 
      printf("%d\n", dados[i]);

      usleep(30000);
    }
    printf("\n");

    turn = 1;

    pthread_exit(NULL); 

  }

}

int compara(const void *a, const void *b) {
  return ( *(int*)a - *(int*)b );
}


void *ordena_dados(void *v_dados) {
  int i;
  int *dados = v_dados;

  while (1) {
    while (turn != 1) {}
    qsort(dados, TAM, sizeof(int), compara);
    
    for (i = 0; i < TAM; i++) {
      printf("%d ", dados[i]);
    }
    printf("\n");

    turn = 0;
    
    pthread_exit(NULL);
  }
}

int init() {
  turn = 0;

  if (pthread_create(&proc1, NULL, insere_dados, v_dados)) {
    fprintf(stderr, "Erro na criaçao da thread\n");
    return 1;
  }
  
  if (pthread_create(&proc2, NULL, ordena_dados, v_dados)) {
    fprintf(stderr, "Erro na criaçao da thread\n");
    return 2;
  }
  
  return 0;
}

int main() {

  saida = init();

  if (saida == 0) {
    saida = pthread_join(proc1, NULL); 
    saida = pthread_join(proc2, NULL); 
  }
  
  return 0;
}
