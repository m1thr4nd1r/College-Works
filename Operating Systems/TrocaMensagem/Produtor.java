import java.util.Date;
class Produtor implements Runnable {
  private Primitivas<Date> fila;
  private int id;
  
  static void dormir(int duracao) {
	  
      int tempo = (int) (duracao * Math.random() );
      try { Thread.sleep(tempo*1000); } catch (InterruptedException ie) {}
   }
  
  public Produtor( Primitivas<Date> fila, int id ) {
    this.fila = fila;
    this.id = id;
  }
  
  public void run() {
    Date message;
    while ( true ) {
      dormir(5);
      message = new Date();  // produz um item 
      System.out.println( "Produzido " + message + "(Produtor " + this.id + ")" );
      fila.send(message);   // adiciona no buffer
    }
  }
}
