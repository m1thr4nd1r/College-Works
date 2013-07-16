package prim;

import java.util.Random;

public class Prim 
{
    public static void print(String start, String end, int weight)
    {
        System.out.println("Aresta: " + start + "&" + end + " Com Peso: " + weight);
    }
    
    public static void printWay(int start, int avoid, int[][]result, String vertices)
    // Avoid para evitar que uma aresta seja impressa duas vezes
    {
        String s;
        String e;
        
        for (int i = 0; i < result.length; i++) 
        {
            if ((i != avoid) && (result[start][i] != 0))
            {
                int pos = 0;
        
                for (int j = 0; j < start; j++)
                    pos = (vertices.indexOf('|',pos)) + 1;
                
                int j = vertices.indexOf('|',pos+1);
                
                if (j == -1) 
                    s = vertices.substring(pos);
                else 
                    s = vertices.substring(pos,j);
                
                pos = 0;

                for (j = 0; j < i; j++)
                    pos = (vertices.indexOf('|',pos)) + 1;
                
                j = vertices.indexOf('|',pos+1);
                
                if (j == -1)
                    e = vertices.substring(pos);
                else 
                    e = vertices.substring(pos,j);
                
                print(s,e,result[start][i]);
                printWay(i,start,result, vertices);
            }
        }
    }
    
    public static int prim(int matrix[][], int result[][])
    {
        int [] inTree;
        int [] outTree;
        
        inTree = new int[matrix.length];
        outTree = new int [matrix.length];
        
        Random generator = new Random();
 
        int begin = generator.nextInt(matrix.length);
        
        for (int i = 0; i < matrix.length; i++) {
            outTree[i] = i;
        }
        
        outTree[begin] = -1;
        inTree[0] = begin;
        
        Boolean flag;
        int count = 0;
        
        while (count < matrix.length - 1)
        {
            int pos = -1;
            int element = -1;
            int lesser = Integer.MAX_VALUE;
            for (int z = 0; z < count + 1; z++)
            // Loop dentro da lista de simbolos que ja estao na arvore
            {
                for (int i = 0; i < matrix.length; i++) 
                // Loop dentro de uma aresta tendo um dos vertices na arvore geradora
                {
                    flag = true;
                    for (int j = 0; j < count + 1; j++) 
                    // Loop para verificar se o vertice escolhido se encontra na lista de vertices
                    // ainda nao presentes na arvore geradora
                    {
                        if (inTree[j] == i) {
                            flag = false;
                        }
                    }
                    if ((flag) && (matrix[inTree[z]][i] != 0) && (matrix[inTree[z]][i] < lesser))
                    // Verifica se o valor escolhido é diferente de zero e menor que o menor valor encontrado ate o momento
                    {
                        lesser = matrix[inTree[z]][i];
                        pos = i;
                        element = inTree[z];
                    }
                }
            }
        
            result[element][pos] = lesser;
            result[pos][element] = lesser;
            inTree[count + 1] = pos;
            outTree[pos] = -1;
            count++;
        }
        
        return begin;
    }
    
    public static int[][] test()
    {
        int[][] matrix = {
//           A  B  C  D  E  F  G
//            {0, 3, 4},
//            {3, 0, 5},
//            {4, 5, 0},
            {0, 7, 0, 5, 0, 0, 0},
            {7, 0, 8, 9, 7, 0, 0},
            {0, 8, 0, 0, 5, 0, 0},
            {5, 9, 0, 0, 15, 6, 0},
            {0, 7, 5, 15, 0, 8, 9},
            {0, 0, 0, 6, 8, 0, 11},
            {0, 0, 0, 0, 9, 11, 0}
        };
        return matrix;
    }
    
    private static String getVertices(String input) 
    {
//        {a, b, c, d}
        input = input.replace(", ", "|");
        input = input.substring(1,input.length() -1);
        input+= '|';
        
        return input;
    }
    
    public static String getEdges(String input)
    {
//        {(a, b), (a, c), (b, d), (c, d)}
        input = input.substring(1,input.length() -2);
        input = input.replace("(","");
        input = input.replace("), ","-");
        input = input.replace(", ","*");
        input = input.replace("-","|");
        input = input.replace("*"," ");
        input += '|';
        
        return input;
    }
    
    private static String addWeight(String edges, String input) 
    {
//        {10, 13, 5, 23}
        int pos = 0;
        int p = 0;
        boolean flag = false;
        
        while (!flag)
        {
            int temp = input.indexOf(',',p);
            
            if (temp == -1)
            {
                temp = input.length()-1;
                flag = true;
            }
            
            pos = edges.indexOf('|',pos);
            
            String o = edges.substring(0,pos);
            String n = edges.substring(0,pos) + " " + input.substring(p+1,temp);
            
            edges = edges.replace(o,n);
            
            pos += input.substring(p,temp).length() + 2;
            p = temp + 1;
        }
        
        return edges;
    }
    
    public static String changeEdges(String vertices, String edges)
    {
        int pos = 0;
        int size = 0;
        
        while (pos != -1)
        {
            size++;
            int temp = vertices.indexOf('|', pos);
            if (temp != -1)
            {
                String old = vertices.substring(pos, temp);
                String n = Integer.toString(size-1);
                edges = edges.replace(old,n);
                pos = temp + 1;
            }
            else {
                pos = -1;
            }
        }
        
        return edges + Integer.toString(size-1);
    }
    
    public static int[][] createMatrix(String edges, int[][] matrix)
    {
        int pos = 0;
        
        while (pos != -1)
        {
            int temp = edges.indexOf('|', pos);
            if (temp != -1)
            {
                 int first = edges.indexOf(' ',pos);
                 int last = edges.indexOf(' ',first+1);
                 String v1 = edges.substring(pos,first);
                 String v2 = edges.substring(first+1,last);
                 String weight = edges.substring(last+1, temp);
                 
                 matrix[Integer.decode(v1)][Integer.decode(v2)] = Integer.decode(weight);
                 matrix[Integer.decode(v2)][Integer.decode(v1)] = Integer.decode(weight);
                 
                 pos = temp + 1;
            }
            else {
                pos = -1;
            }
        }
        
        return matrix;
    }
    
    public static int maxWeight(String input)
    {
        int pos = 0;
        int sum = 0;
        
        while (pos != -1)
        {
           int temp = input.indexOf(',',pos);
           
           if (temp == -1)
           {
               temp = input.length() - 1;
               sum += Integer.decode(input.substring(pos+1,temp));
               pos = -1;
           }
           else
           {
               sum += Integer.decode(input.substring(pos+1,temp));
               pos = temp + 1;
           }
        }
        return sum;
    }
    
    public static boolean isConected(int[][] matrix)
    {
        boolean flag = false;
        
        for (int i = 0; i < matrix.length; i++)
        {
            flag = false;
            for (int j = 0; j < matrix.length; j++)
                if (matrix[i][j] != 0)
                {
                    flag = true;
                    break;
                }
        }
        
        return flag;
    }
    
    public static void main(String[] args) 
    {
//        - A primeira linha contém o conjunto dos vértices;
//        - A segunda linha contém o conjunto das arestas;
//        - A terceira linha contém o conjunto do peso das arestas;
//        - A quarta linha contém um número natural intervalo [1, |V|] que indica a posição do vértice fonte u no conjunto dos vértices;
//        Exemplo do conteúdo da entrada:
//        {a, b, c, d}
//        {(a, b), (a, c), (b, d), (c, d)}
//        {10, 13, 5, 23}
        
//        matrix = test();
//        vertices += "Um|Dois|Tres|Quatro|Cinco|Seis|Sete";
//        vertices += "A|B|C|D|E|F|G";
        
        String input = Keyboard.readString();

        String vertices = getVertices(input);
        
        input = Keyboard.readString();
        
        String edges = getEdges(input);
        
        input = Keyboard.readString();
        
        int total = maxWeight(input);
        
        edges = addWeight(edges,input);
        
        edges = changeEdges(vertices, edges);
        
        input = edges.substring(edges.lastIndexOf('|')+1,edges.length());
        
        int size = Integer.decode(input);
        
        edges = edges.substring(0,edges.lastIndexOf('|')+1);
//        
        int[][] matrix = new int[size][size];
//        
        matrix = createMatrix(edges,matrix);
        
//        if (isConected(matrix))
//        {
            int[][] result = new int[matrix.length][matrix.length];

            int start = prim(matrix,result);

            System.out.println("\n" + "Árvore geradora minima: ");

            printWay(start,-1,result,vertices);
            
            System.out.println("Peso da árvore geradora maxima (todos as arestas): " + total);
//        }
//        else
//            System.out.println("O grafo não é conexo");
    }
}