/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package produtoconsumidosemaforo;

/**
 *
 * @author Victor dos Santos
 */
public class Producer extends Thread {
   private  ObjetoBuffer o_Buffer;
   private  Semaforo s1,s2;

   // construtores da Thread Produtor
   public Produtor( ObjetoBuffer data )
   {
      super( "Produtor" );
      o_Buffer = data;
   }

   public Produtor( ObjetoBuffer data, Semaforo sem1, Semaforo sem2 )
   {
      super( "Produtor" );
      o_Buffer = data;
      s1 = sem1;
      s2 = sem2;
   }

   // Thread do Produtor escreverah 10 vezes no buffer em intervalos de tempo aleatorios 
   
   public void run()
   {
      for ( int i = 1; i <= 10; i++ ) {

         // dorme por um tempo aleatorio
         try {
            Thread.sleep( ( int ) ( Math.random() * 3000 ) );
         }

         // tratamento de excecao
         catch( InterruptedException exception ) {
            System.err.println( exception.toString() );
         }

         // chama metodo do objeto buffer 
         
         s1.P();         
         o_Buffer.writeBuffer( i );
         s2.V();
      }

      System.err.println(getName() + " terminou de produzir");
   }
}
