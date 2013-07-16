package Warshall;

public class Vertice{
    private int index;
    private String simb;
    
    public Vertice(String simb, int index){
        this.simb = simb;
        this.index = index;
    }
    
    public String getSimbol(){
        return simb;
    }
    
    public int getIndex(){
        return index;
    }
}
