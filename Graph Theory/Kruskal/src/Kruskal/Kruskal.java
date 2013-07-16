package Kruskal;

public class Kruskal {
    private static Grafo entrada, saida;
    private static int[] id, grau;
    
    private static void init(){
        id = new int[entrada.numVertices()];
        grau = new int[entrada.numVertices()];
        
        for(int i = 0; i < entrada.numVertices(); i++){
            id[i] = i;
            grau[i] = i;
        }
    }
    
    private static int find(int index){
        int i = index;
        
        while(i != id[i]){
            i = id[i];
        }
        
        return i;
    }
    
    private static void union(Aresta a){
        Vertice[] v = a.getVertices();
        if(v[0] == v[1]) return;
        
        int i, j;
        i = find(v[0].getIndex());
        j = find(v[1].getIndex());
        
        if (grau[i] < grau[j]) { 
            id[i] = j; 
            grau[j] += grau[i]; 
        } else { 
            id[j] = i; 
            grau[i] += grau[j]; 
        }
        
        saida.addAresta(a);
    }
    
    public static void main(String[] args) {        
        entrada = new Grafo();
        
        entrada.readVertices();
        entrada.readArestas();
        entrada.readPesos();
        
        entrada.Sort();
        
        Vertice[] temp = new Vertice[entrada.getVertices().size()];
        saida = new Grafo(entrada.getVertices().toArray(temp), 
                         new Aresta[0]);
        
        init();
        
        for(int i = 0; i < entrada.numArestas(); i++){
            Vertice[] v = entrada.getArestas().get(i).getVertices();
            if(find(v[0].getIndex()) != find(v[1].getIndex())){
               union(entrada.getArestas().get(i));
            }
        }
        
        System.out.println("--------------");
        System.out.println(saida);
    }
}
