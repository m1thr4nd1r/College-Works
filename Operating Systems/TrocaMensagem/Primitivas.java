import java.util.Vector;

public class Primitivas<E> {
	
  private Vector<E> fila;
  
  public Primitivas() {
    fila = new Vector<E>();
  }
  
  public void send( E item ) {
    fila.addElement( item );	// adiciona ao fim da fila
  }
  
  public E receive() {
    if ( fila.size() == 0 )
      return null;
    else		// remove do inicio da fila
      return fila.remove( 0 );
  }
}
