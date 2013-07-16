package depth;

import java.util.ArrayList;
import java.util.List;

public class Vertice {
    private String name;
    private List<Vertice> neighbours;
    private int[] weights;
    private boolean searched;

    public Vertice(String name) {
        this.name = name;
        this.searched = false;
        this.neighbours = new ArrayList<Vertice>();
    }
    
    public void initArray(int qnt)
    {
        this.weights = new int[qnt];
        for (int i = 0; i < qnt; i++) {
            this.weights[i] = Integer.MIN_VALUE;
        }
    }
    
    public void addNeighbours(Vertice v)
    {
        this.neighbours.add(v);
    }
    
    public String getName() {
        return name;
    }

    public List<Vertice> getNeighbours() {
        return neighbours;
    }

    public int[] getWeights() {
        return weights;
    }

    public void addWeights(int weigth)
    {
        for (int i = 0; i < this.weights.length; i++) {
            if (this.weights[i] == Integer.MIN_VALUE) {
                this.weights[i] = weigth;
                break;
            }
        }
    }
    
    public void setWeights(int[] weights) {
        this.weights = weights;
    }

    public boolean searched() {
        return searched;
    }

    public void setSearched(boolean searched) {
        this.searched = searched;
    }
    
}