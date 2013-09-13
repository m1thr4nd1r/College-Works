/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package produtoconsumidosemaforo;

/**
 *
 * @author Victor dos Santos
 */
public class Consumidor extends Thread {
   private ObjetoBuffer one_Buffer;
   private Semaforo s1,s2;

   // Construtores do Consumidor thread object
   public Consumidor( ObjetoBuffer data )
   {
      super( "Consumidor" );
      one_Buffer = data;
   }

   public Consumidor( ObjetoBuffer data, Semaforo sem1, Semaforo sem2 )
   {
      super( "Consumidor" );
      one_Buffer = data;
      s1 = sem1;
      s2 = sem2;
   }

   // Thread Consumidor lerah o buffer 10 vezes em intervalos aleatorios
   
   public void run()
   {
      int value, sum = 0;

      do {

         // dorme por um intervalo aleatorio
         try {
            Thread.sleep( (int) ( Math.random() * 3000 ) );
         }

         // Tratamento de excecao
         catch( InterruptedException exception ) {
            System.err.println( exception.toString() );
         }

         s2.P();  // bloqueio da thread consumidora
         value = one_Buffer.readBuffer();
         s1.V();  // liberacao do threads produtora
         sum += value;

      } while ( value != 10 );

      System.err.println(
         getName() + " terminou de consumir. Totalizou: " + soma);
   }
    
}
