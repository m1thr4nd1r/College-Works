package dijkstra;

import java.util.ArrayList;

public class Dijkstra {
    
    public static void main(String args[]) {
        ArrayList<Integer> N;
        Vertice V[];
        double c[][];
        int u, v, w;
        
        if(args.length > 0) {
            printHelp();
            System.exit(1);
        }
        V = Buffer.getVertices();
        N = setEnumVertices(V);
        c = Buffer.getArestas(V);
        u = Buffer.getFonte();
        printGrafo(V, c);
        
        //Inicializa a distância entre os vértices e o caminho entre eles
        for(v=0;v<V.length;v++) {
            V[v].dist = c[u][v];
            if(u != v && V[v].dist != Double.POSITIVE_INFINITY)
                V[v].caminho = V[u].toString().concat(V[v].toString());    
        }
        
        N.remove(u);

        while(!N.isEmpty()) {
            w = 0;
            for(v=1;v<N.size();v++)
                if(V[N.get(v)].dist<V[N.get(w)].dist)  w = v;
            for(v=0;v<N.size();v++)
                if(V[N.get(w)].dist+c[N.get(w)][N.get(v)] < V[N.get(v)].dist) {
                    V[N.get(v)].dist = V[N.get(w)].dist+c[N.get(w)][N.get(v)];
                    V[N.get(v)].caminho = V[N.get(w)].caminho
                            .concat(V[N.get(v)].toString());
                }
            N.remove(w);
        }
        printPesos(V, u);
    }
    
    public static ArrayList<Integer> setEnumVertices(Vertice V[]) {
        ArrayList<Integer> N = new ArrayList<Integer>();
        for(int i=0;i<V.length;i++)
            N.add(i);
        return N;
    }
    
    public static void printGrafo(Vertice V[], double c[][]) {
        System.out.println("G = (V, E)");
        System.out.print("V = {");
        for(int i=0;i<V.length;i++) {
            System.out.printf("%c", V[i].simb);
            if(i<V.length-1)
                System.out.print(", ");
        }
        System.out.println("}");
        
        ArrayList<Aresta> arestas = new ArrayList<Aresta>();
        String virg = "";
        System.out.print("E = {");
        for(int i=0;i<V.length;i++) {  
            for(int j=i+1;j<V.length;j++) {
                if(c[i][j] != Double.POSITIVE_INFINITY) {
                    System.out.print(virg);
                    arestas.add(new Aresta(V[i], V[j], c[i][j]));
                    System.out.print(arestas.get(arestas.size()-1));
                    virg = ", ";
                }
            }
        }
        System.out.println("}");
        System.out.println("p: E -> R");
        for(int i=0;i<arestas.size();i++) {
            System.out.printf("\tp%s = %7.2f\n", arestas.get(i),arestas.get(i).peso);
        }        
    }
    
    public static void printPesos(Vertice V[], int u) {
        System.out.printf("\nCAMINHO DE CUSTO MINIMO ENTRE O VERTICE \"%c\" E "
                + "OS DEMAIS VERTICES:\n", V[u].simb);

        System.out.printf("\t%s     %7s     %s\n", "VERTICE", "CUSTO", "CAMINHO");
        
        for(int v=0; v<V.length; v++)
            if(u != v)
                System.out.printf("\t%4c     %10.2f     %s\n", V[v].simb, V[v].dist, V[v].caminho);
    }
    
    public static void printHelp() {
        System.out.println(
            "\n\n\tHELP\n\n" + 
            "Este programa exemplifica o algoritmo de Djikstra, que encontra " + 
            "o caminho de custo mínimo entre um determinado vertice \"u\" e outro " + 
            "vertice \"v\" qualquer num grafo G(V, E).\n" + 
            "Para funcionar corretamente a entrada deve cumprir necessáriamente " + 
            "os seguintes requisitos:\n" + 
            "    - A primeira linha da entrada deve conter o conjunto dos vertices;\n" +
            "    - A segunda linha deve conter o conjunto das arestas;\n" +
            "    - A terceira linha deve conter o conjunto dos pesos das arestas;\n" +
            "    - A quarta linha deve conter um numero natural no intervalo [1, |V|] "+
            " que indica a posicao do vertice origem \"u\" no conjunto dos vertices;\n" +
            "\n" +
            "Exemplo do conteudo da entrada:\n" +
            "{a, b, c, d}\n" +
            "{(a, b), (a, c), (b, d), (c, d)}\n" +
            "{10, 13, 5, 23}\n" +
            "1\n"
        );
    }
}