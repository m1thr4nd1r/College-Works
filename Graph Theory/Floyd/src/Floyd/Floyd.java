package Floyd;

public class Floyd{
    
    private static Grafo grafo;
    private static float[][] adj;
    
    public static void initMatrixAdj(){
        adj = new float[grafo.numVertices()][grafo.numVertices()];
        
        for(int i = 0; i < grafo.numVertices(); i++){
            for(int j = 0; j < grafo.numVertices(); j++){
                if(i == j)
                    adj[i][j] = 0;
                else
                    adj[i][j] = Float.POSITIVE_INFINITY;
            }
        }
        
        float p;
        Vertice[] v;
        
        for(int i = 0; i < grafo.numArestas(); i++){
            p = grafo.getArestas().get(i).getPeso();
            v = grafo.getArestas().get(i).getVertices();
            
            if(v[0] != v[1]){
                adj[v[0].getIndex()][v[1].getIndex()] = p;
                adj[v[1].getIndex()][v[0].getIndex()] = p;
            }
        }         
    }
    
    public static void main(String[] args) {
        grafo = new Grafo();
        grafo.readVertices();
        grafo.readArestas();
        grafo.readPesos();
        
        initMatrixAdj();
        
        for(int k = 0; k < grafo.numVertices(); k++){
            for(int i = 0; i < grafo.numVertices(); i++){
                for(int j = 0; j < grafo.numVertices(); j++){
                    if(adj[i][j] > adj[i][k] + adj[k][j])
                        adj[i][j] = adj[i][k] + adj[k][j];
                }
            }
        }
        
        System.out.println("----------------");
        
        String out = "";
        
        for(int i = 0; i < grafo.numVertices(); i++)
            out += "\t" + grafo.getVertices().get(i).getSimbol();
        
        System.out.println(out);
        
        for(int i = 0; i < grafo.numVertices(); i++){
            out = grafo.getVertices().get(i).getSimbol() + "\t";
            for(int j = 0; j < grafo.numVertices(); j++){
                if(!Float.isInfinite(adj[i][j])){
                    out += adj[i][j] + "\t";
                }else{
                    out += "inf\t";
                }
            }
            System.out.println(out);
        }       
    }
}
