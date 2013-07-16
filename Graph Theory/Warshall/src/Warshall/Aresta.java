package Warshall;

public class Aresta {
    private Vertice v1, v2;
    private float peso;
    
    public Aresta(Vertice v1, Vertice v2, float peso){
        this.v1 = v1;
        this.v2 = v2;
        this.peso = peso;
    }
    
    public Aresta(Vertice v1, Vertice v2){
        this(v1, v2, 0);
    }
    
    public void setPeso(float peso){
        this.peso = peso;
    }
    
    public float getPeso(){
        return peso;
    }
    
    public Vertice[] getVertices(){
        return new Vertice[]{v1, v2};
    }
    
    @Override
    public String toString(){
        return "(" + v1.getSimbol() + " " + v2.getSimbol() + ")";
    }
}
