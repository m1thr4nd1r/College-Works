import java.util.Date;

public class TrocaMensagem {
  public static void main( String[] args ) {
    
	// cria a fila de mensagens
    Primitivas<Date> fila = new Primitivas<Date>();
    
    int qnt = 5;
    
    Thread produtor[] = new Thread[qnt];
    Thread consumidor[] = new Thread[qnt];
    
    for (int i = 0; i < qnt; i++)
    {
	    // cria o(s) produtor(es) e consumidor(es)
	    produtor[i] = new Thread( new Produtor(fila, i+1) );
	    consumidor[i] = new Thread( new Consumidor(fila, i+1) );
    }
    
    for (int i = 0; i < qnt; i++)
    {
    	// starta as threads
	    produtor[i].start();
	    consumidor[i].start();
    }
  }
}