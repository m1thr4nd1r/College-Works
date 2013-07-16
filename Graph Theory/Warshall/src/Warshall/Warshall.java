package Warshall;

public class Warshall {
    
    private static Grafo grafo;
    private static boolean[][] adj;
    
    public static void initMatrixAdj(){
        adj = new boolean[grafo.numVertices()][grafo.numVertices()];
        
        for(int i = 0; i < grafo.numVertices(); i++){
            adj[i][i] = true;
        }
        
        Vertice[] v;
        for(int i = 0; i < grafo.numArestas(); i++){
            v = grafo.getArestas().get(i).getVertices();
            
            if(v[0].getIndex() <= v[1].getIndex()){
                adj[v[0].getIndex()][v[1].getIndex()] = true;
            }else{
                adj[v[1].getIndex()][v[0].getIndex()] = true;
            }
        }         
    }
    
    public static void main(String[] args) {
        grafo = new Grafo();
        grafo.readVertices();
        grafo.readArestas();
        
        initMatrixAdj();
        
        for(int k = 0; k < grafo.numVertices(); k++){
            for(int i = 0; i < grafo.numVertices(); i++){
                if(adj[i][k] || adj[k][i]){
                    for(int j = i; j < grafo.numVertices(); j++){
                        if(adj[k][j] || adj[j][k]){
                            adj[i][j] = true;
                        }
                    }
                }
            }
        }
        
        String out;
        for(int i = 0; i < grafo.numVertices(); i++){
            out = grafo.getVertices().get(i).getSimbol() + " ==> ";
            for(int j = 0; j < grafo.numVertices(); j++){
                if(i <= j){  
                    if(adj[i][j])
                        out += grafo.getVertices().get(j).getSimbol() + " ";
                }else{
                    if(adj[j][i])
                        out += grafo.getVertices().get(j).getSimbol() + " ";
                }
            }
            
            System.out.println(out);
        }
    }
}
