package dijkstra;

public class Vertice {
    String caminho;
    char simb;
    double dist;
    
    public Vertice(char simb) {
        this.simb = simb;
        dist = Double.POSITIVE_INFINITY;
        caminho = "";
    }

    @Override
    public String toString() {
        return String.valueOf(simb);
    }
}
