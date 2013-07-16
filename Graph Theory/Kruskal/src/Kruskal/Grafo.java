package Kruskal;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class Grafo {
    
    private ArrayList<Vertice> V = new ArrayList();
    private ArrayList<Aresta> A = new ArrayList();
    
    public Grafo(){}
    
    public Grafo(Vertice[] v, Aresta[] a){
        for(int i = 0; i < v.length && V.add(v[i]); i++);
        for(int i = 0; i < a.length && A.add(a[i]); i++);
    }
    
    public void Sort(){
       QuickSort(0, A.size() -1);
    }
    
    private void QuickSort(int begin, int end){
        int i, j;
        i = begin;
        j = end;
        
        Aresta pivo = A.get((i + j) / 2);
        
        while(i < j){
            while(A.get(i).getPeso() < pivo.getPeso()) i++;
            while(A.get(j).getPeso() > pivo.getPeso()) j--;
            
            if(i <= j){
                Aresta aux = A.get(i);
                A.set(i, A.get(j));
                A.set(j, aux);
                i++;
                j--;
            }
        }
        
        if(j > begin){
            QuickSort(begin, j);
        }
        
        if(i < end){
            QuickSort(i, end);
        }
    }
    
    /*GETS & SETS
     * ----------------------------*/
    
    public void addAresta(Aresta a){
        /*if((findVertice(a.getVertices()[0].getSimbol()) == null) ||
          (findVertice(a.getVertices()[1].getSimbol()) == null)){
            System.out.println("Vertice não achado");
            return;
        }*/
        
        A.add(a);
    }
    
    public int numVertices(){
        return V.size();
    }
    
    public int numArestas(){
        return A.size();
    }
    
    public ArrayList<Vertice> getVertices(){
        return V;
    }
    
    public ArrayList<Aresta> getArestas(){
        return A;
    }
    
    public Vertice findVertice(String simb){
        for(int i = 0; i < V.size(); i++){
            if(V.get(i).getSimbol().equals(simb))
                return V.get(i);
        }
        return null;
    }
    
    public Vertice findAresta(Vertice v1, Vertice v2){
        for(int i = 0; i < A.size(); i++){
            //Incomplete
        }        
        return null;
    }
    
    /*----------------------------*/
   
    @Override
    public String toString(){
        String out;
        
        out = "{";
        for(int i = 0; i < V.size() -1; i++)
            out += V.get(i).getSimbol() + ", ";
        out += V.get(V.size() -1).getSimbol() + "}\n";
        
        out += "{";
        for(int i = 0; i < A.size() -1; i++){
            out += A.get(i).toString() + ", ";
        }
        out += A.get(A.size() -1).toString() + ")}\n";
        
        out += "{";
        for(int i = 0; i < A.size() -1; i++)
            out += A.get(i).getPeso() + ", ";
        out += A.get(A.size() -1).getPeso() + "}";
        
        return out;
    }
    
    /*----------------------------*/
    
    public void readVertices(){
        String line = readLine();
        
        String[] v = line.split("( )*,( )*|\\{|\\}");
       
        for(int i = 0; i < v.length; i++){
            if(v[i].isEmpty() == false){
                V.add(new Vertice(v[i], V.size()));
            }
        }   
    }
    
    public void readArestas(){
        String[] a, v;
        String line;
        
        line = readLine();
        
        a = line.split("\\)( )*,( )*\\(|\\{( )*\\(|\\)( )*\\}");
        
        Vertice v1, v2;
        
        for(int i = 0; i < a.length; i++){
            if(!a[i].isEmpty()){
                v = a[i].split("( )*,( )*");
                
                if(v.length != 2){
                    System.out.println("Aresta (" + a[i] + ") mal formada");
                    continue;
                }
                
                v1 = findVertice(v[0]);
                v2 = findVertice(v[1]);
                
                if(v1 == null || v2 == null)
                    System.out.println("Aresta (" + a[i] + ") não pode ser criada");
                else
                    A.add(new Aresta(v1, v2));
            }
        } 
    }
    
    public void readPesos(){
        String[] p;
        String line;
        line = readLine();
        
        p = line.split("( )*,( )*|\\{|\\}");
        
        int k = 0;
        for(int i = 0; i < p.length; i++){
            if(!p[i].isEmpty() && k < A.size()){
                A.get(k).setPeso(Float.valueOf(p[i]));
                k++;
            }
        }
    }
    
    /* Componetes para leitura */
    
    private static BufferedReader buffer = new BufferedReader(new InputStreamReader(System.in));
    
    private static String readLine(){
        String b;
        try {
            b = buffer.readLine();
        } catch (IOException ex) {
            System.out.println("Erro inesperado: "+ex);
            return "";
        }
        return b;
    }
    /////
}
