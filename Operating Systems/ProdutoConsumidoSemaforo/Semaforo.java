/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package produtoconsumidosemaforo;

/**
 *
 * @author Victor dos Santos
 */
final class Semaforo {

  private int value;	//valor do semaforo
  private int waiting = 0;	//quantidade de processos bloqueados por UM DETERMINADO semaforo

  public Semaforo (int i) { //construtor: inicia o semaforo adequadamente
		value = i ;
  } //fim do construtor

  synchronized void P() { //ou DOWN()
    if ( value > 0 ) //verifica o valor do semaforo
			value--; //se semaforo maior que zero, decrementa o valor do do semaforo
    else {
			waiting++;	//senao, incrementa o numero de threads suspensas
			try { wait(); } catch (InterruptedException e) { }; //senao o processo que executou a operacao P (ou DOWN) e' suspenso
			waiting--;
		};	//fim do else/if
  } //fim do metodo P()

  synchronized void V() { //ou UP()
		if (waiting > 0) //se tem processo na fila de espera
			notify(); //tira processo da fila de espera
		else 	 
			value++;	//senao, incrementa o valor do semaforo
  } //fim do metodo V()

} //fim da classe Semaforo