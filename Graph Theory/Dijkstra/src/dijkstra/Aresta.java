package dijkstra;

public class Aresta {
    Vertice v1, v2;
    double peso;
    
    public Aresta(Vertice v1, Vertice v2, double peso) {
        this.v1 = v1;
        this.v2 = v2;
        this.peso = peso;
    }

    @Override
    public String toString() {
        String s = "(";
        s = s.concat(v1.toString());
        s = s.concat(", ");
        s = s.concat(v2.toString());
        s = s.concat(")");
        return s;
    }
}