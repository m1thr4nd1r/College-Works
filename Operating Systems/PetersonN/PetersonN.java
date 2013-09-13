/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package peterson;

/**
 *
 * @author Arlindo Junior
 */
public class PetersonN implements Runnable{
    static int N = 10; // n processos
    private static int ultimo[] = new int[N];
    private static int estagio[] = new int[N + 1];
    private int id;
    
    /*
     A idéia básica é que cada processo deve passar por n-1 estágios antes de poder entrar na sua região crítica. 
     Um processo avança um estágio sempre que:
        (a) ele está na frente de todos os demais (ninguém está em um estágio maior ou igual ao dele) ou
        (b) chega outro processo no estágio em que ele está (ele deixa de ser o último no seu estágio atual).
     */
    
    /* Há processos N de 1 a N. Portanto, precisamos de um array volta com tamanho N - 1 
     * e precisamos de um vetor estágios com tamanho N. No entanto, eu declarei a ultimo e 
     * o vetor de estagio com tamanhos N e N + 1, respectivamente. Mas equivale a N - 1 e N
     * Pois nunca acesso a possição 0.
     */
    
  public static void main(String[] args) {
      
      for(int h = 1; h <= N; h++){     // inicializando o vetor estagio == inicialmente, todos os elementos estão zerados.
          estagio[h] = 0;
      }
      
      Thread[] t = new Thread[N]; // Valor de N -> querendo mudar é só alterar N lah em cima.
      
      for(int h = 1; h <= N ;h++){  
        new Thread(new PetersonN(h), "Thread - "+h+"").start();  // Criando a thread e inicializando. 
      }

    }

	public PetersonN(int i) {
        id = i; // id do processo.
    }   
   
 
  
void EntrarNaRegiao(int process) // algoritmo de peterson 
{
  int i, j;

  for (i = 1; i <= N - 1; i++) { 
    estagio[process] = i; // estágio atual de process
    ultimo[i] = process; // indica qual é o último processo que chegou ao estágio
    for (j = 1; j <= N; j++) {
      if (j == process)
        continue;
      while (estagio[j] >= i  && ultimo[i] == process){ //Enquanto um processo está executando (ou tentando entrar) na região crítica, os estágios funcionam como "barreiras".
          System.out.println("[" + process + "] "+" - Esperando..."); // enquanto não for autorizado fica no loop esperando
      }
    }
  }
  System.out.println("[" + process + "] - Entrei" ); // indica que entrou na região
  
  SairDaRegiao(process);
}

void SairDaRegiao(int process)
{
  estagio[process] = 0; 
  
}

    @Override
 public void run() { // quando inicializo a thread ela invoca automaticamente esse metodo.
     
     EntrarNaRegiao(id);
 }
}
