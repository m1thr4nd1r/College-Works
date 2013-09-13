import java.util.ArrayList;

public class ProdutorConsumidor {

	static final int MAX = 10; //tamanho maximo do buffer
	static final int NConsumidores = 10;
	static final int MProdutores = 1;
	
	static Monitor monitor = new Monitor(); //instancia um monitor
	static ArrayList<Produtor> ListaProdutores = new ArrayList<Produtor>();
	static ArrayList<Consumidor> ListaConsumidores = new ArrayList<Consumidor>();
	
	public static void main(String[] args) {
		for(int i=0; i<MProdutores; i++)
		{
			Produtor produtor = new  Produtor(i+1); //instancia uma thread produtor
			ListaProdutores.add(produtor);
		}
		for(int i=0; i<NConsumidores; i++)
		{
			Consumidor consumidor = new  Consumidor(i+1); //instancia uma thread consumidor
			ListaConsumidores.add(consumidor);
		}
		//inicia as threads
		for(Produtor p : ListaProdutores)
			p.start();
		for(Consumidor c : ListaConsumidores)
			c.start();
	}
	
	
	static class Produtor extends Thread {
		int IdProdutor;
		Produtor(int aiNumero)
		{
			this.IdProdutor = aiNumero;
		}
		
		public void run() {
			int liItem;
			while(true) {
				liItem = ProduzItem(); //produz o item
				monitor.insert(liItem, IdProdutor);
			}
		}
		
		private int ProduzItem() {
			System.out.println("O Produtor "+IdProdutor+" produziu um item, mas ainda nao esta no buffer");
			return 1;
		}

	}
	
	static class Consumidor extends Thread {
		int IdConsumidor;
		Consumidor(int aiNumero)
		{
			this.IdConsumidor = aiNumero;
		}
		public void run() {
			int liItem;
			while(true) {
				liItem = monitor.remove(IdConsumidor); //consome o item
				ConsomeItem(liItem); 
			}
		}
		
		private void ConsomeItem(int ioItem) {
			System.out.println("Fim do while do Consumidor "+IdConsumidor);	//aqui ficaria uma funcao de consumir que depende da implementacao	
		}
	}
	
	static class Monitor {

		private int buffer[] = new int[MAX]; //o 20 eh pra ser MAX
		private int count = 0, lo = 0, hi = 0; //contadores e indices
		//lo aponta para o lugar do buffer que contem o proximo item a ser buscado
		//hi eh o proximo lugar onde o item sera colocado
		
		public synchronized void insert(int aiItem, int aiIdProdutor) {
			System.out.println("O Produtor "+aiIdProdutor+" está no monitor para tentar colocar um item no Buffer");
			while (count == MAX) //se o buffer estiver cheio, durma
			{	
				System.out.println("O Buffer está cheio. O Produtor "+aiIdProdutor+" dorme");
				durma();
				System.out.println("O Produtor "+aiIdProdutor+" acordou");
			}
			buffer[hi] = aiItem; //insere um item no buffer
			hi = (hi+1) % MAX; //lugar para colocar o proximo item
			count++;		  //mais um item no buffer
			System.out.println("Foi inserido um item no buffer pelo Produtor "+aiIdProdutor);
			if(count==1) //se o consumidor estiver dormindo, acorde-o
			{
				System.out.println("É enviado um sinal para tentar acordar os Consumidores!");
				notifyAll();
			}
			imprimeBuffer();
		}
		
		public synchronized int remove(int aiIdConsumidor) {
			int liItem;
			System.out.println("O Consumidor "+aiIdConsumidor+" está no monitor para tentar remover um item do Buffer");
			while (count == 0)
			{//se o buffer estiver vazio durma
				System.out.println("O Buffer esta vazio. O Consumidor "+aiIdConsumidor+" dorme");
				durma();
				System.out.println("O Consumidor "+aiIdConsumidor+" acordou");
			}
			liItem = buffer [lo]; //busca um item no buffer
			buffer[lo]=0;
			lo = (lo+1) % MAX;  //lugar de onde buscar o proximo item
			count--;		//um item a menos no buffer
			System.out.println("Foi removido um item do buffer pelo Consumidor "+aiIdConsumidor);
			if(count == MAX - 1)	//se o produtor estiver dormindo, acorde-o
			{
				System.out.println("É enviado um sinal para tentar acordar os Produtores!");
				notifyAll();
			}
			imprimeBuffer();
			return liItem;
		}
		
		private void durma() {
			try {
				wait();
			}
			catch(InterruptedException exc) {};		
		}
		
		private void imprimeBuffer() {
			System.out.print("Buffer:[ ");
			for(int i : buffer)
				System.out.print(i+" ");
			System.out.print("]");
			System.out.println();
		}
	}

}
