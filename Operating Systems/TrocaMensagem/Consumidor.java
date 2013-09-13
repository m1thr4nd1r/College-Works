import java.util.Date;
class Consumidor implements Runnable {
  private Primitivas<Date> fila;
  private int id;
  
  static void dormir(int duracao) {
	  
      int tempo = (int) (duracao * Math.random() );
      try { Thread.sleep(tempo*1000); } catch (InterruptedException ie) {}
   }
  
  public Consumidor( Primitivas<Date> fila, int id ) {
    this.fila = fila;
    this.id = id;
  }
  
  public void run() {
    Date message;
    while ( true ) { 
	  dormir(5);
      System.out.println( "Consumidor " + this.id + " tenta consumir" );
      message = fila.receive();  // consome um item do buffer
      if ( message != null )
        System.out.println( "Consumido " + message + "(Consumidor " + this.id + ")" );    
    }
  }
}
