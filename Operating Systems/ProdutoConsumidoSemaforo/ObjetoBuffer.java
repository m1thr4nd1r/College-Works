/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package produtoconsumidosemaforo;

/**
 *
 * @author Victor dos Santos
 */
public class ObjetoBuffer {
    private int memory;

   // metodo de escrita de dados na memoria
   public void writeBuffer( int value )
   {
      System.err.println( Thread.currentThread().getName() +
         " produzindo o valor: " + value );

      this.memory = value;
   }

   // metodo de leitura de dados na memoria
   public int readBuffer()
   {
      System.err.println( Thread.currentThread().getName() +
         " consumindo o valor: " + this.memory );

      return this.memory;
   }
    
}
