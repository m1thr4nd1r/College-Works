package dijkstra;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public abstract class Buffer {
    private static BufferedReader buffer = new BufferedReader(new InputStreamReader(System.in));
    private static String pesos;

    public static Vertice[] getVertices() {
        String b;
        Vertice V[];
        int i, v;
        
        try {
            b = buffer.readLine();
        } catch (IOException ex) {
            System.out.println("Erro inesperado: "+ex);
            return null;
        }
        
        for(i=0,v=0;i<b.length();i++)
            if(b.charAt(i)==',') v++;
        v++;
        
        V = new Vertice[v];
        
        for(v=0, i=0; i<b.length() && b.charAt(i)!='}' ; i++) {
            if(b.charAt(i)!='{' && b.charAt(i)!=',' && b.charAt(i)!=' ') 
                V[v++] = new Vertice(b.charAt(i));
        }
        
        return V;
    }
    
    public static double[][] getArestas(Vertice V[]) {
        String b;
        double c [][];
        int i, j, m;
        
        try {
            b = buffer.readLine();
            pesos = buffer.readLine();
        } catch (IOException ex) {
            System.out.println("Erro inesperado: "+ex);
            return null;
        }
        
        c = new double[V.length][V.length];
        
        for(i=0;i<V.length;i++)
            for(j=0;j<V.length;j++)
                if(i==j) c[i][j] = 0;
                else     c[i][j] = Double.POSITIVE_INFINITY;
        
        int v[] = new int[2];
        for(i=0, j=0; i<b.length()&& b.charAt(i)!='}';i++) {
            if(b.charAt(i)!='{' && b.charAt(i)!=' ' && b.charAt(i)!='('
                    && b.charAt(i)!=',' && b.charAt(i)!=')') {
                v[j++] = getIndex(V, b.charAt(i));

                if(j == 2) {
                    c[v[0]][v[1]] = c[v[1]][v[0]] = getPeso();
                    j = 0;
                }
            }
        }
        
        return c;
    }
    
    @SuppressWarnings("empty-statement")
    private static int getIndex(Vertice V[], char simb) {
        int v;
        for(v=0;v<V.length && V[v].simb != simb;v++);
        if(v == V.length) {
            System.out.printf("Erro durante a criação das arestas: o vertice "
                    + "%s não foi encontrado\n", simb);
            return -1;
        }
        return v;
    }
    
    @SuppressWarnings("empty-statement")
    private static double getPeso() {
        int i, j;
        double peso;
        for(i=0;i<pesos.length() && (pesos.charAt(i) == '{' || pesos.charAt(i) == ' '
                || pesos.charAt(i)==',');i++);
        for(j=i;j<pesos.length() && pesos.charAt(j)!='}' && pesos.charAt(j)!=',' 
                && pesos.charAt(j)!=' ';j++);
        
        peso = Double.parseDouble(String.valueOf(pesos.substring(i, j)));
        pesos = pesos.substring(j,pesos.length());
        return peso;
    }
    
    public static int getFonte() {
        String b;
        int fonte;
        try {
            b = buffer.readLine();
            fonte = Integer.parseInt(b);
        } catch (IOException ex) {
            System.out.println("Erro inesperado: "+ex);
            return -1;
        }
        return fonte-1;
    }
}