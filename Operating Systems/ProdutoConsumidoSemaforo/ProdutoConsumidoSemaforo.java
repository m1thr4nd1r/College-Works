/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package produtoconsumidosemaforo;

/**
 *
 * @author Victor dos Santos
 */
public class ProdutoConsumidoSemaforo {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        ObjetoBuffer oneBuffer = new ObjetoBuffer();
      Semaforo     s1       = new Semaforo(1);  // semaforo do produtor
      Semaforo     s2       = new Semaforo(0);  // semaforo do consumidor

      // criacao das threads
      Produtor oneProducer =  new Produtor( oneBuffer,s1,s2 );
      Consumidor oneConsumer = new Consumidor( oneBuffer,s1,s2);

      // start threads
      oneProducer.start();
      oneConsumer.start();
    }
}
