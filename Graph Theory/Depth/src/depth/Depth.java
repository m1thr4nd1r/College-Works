package depth;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Depth 
{
    public static List <Vertice> listaVertices = new ArrayList<Vertice>();
    
    private static String search(Vertice v)
    {
       String output = "";
       if (!v.searched())
       {
           v.setSearched(true);
           List <Vertice> neighbours = v.getNeighbours();
           for (int i = 0; i < neighbours.size(); i++) 
           {
               output += "Saindo de " + v.getName() + " Para " + neighbours.get(i).getName() + "\n";
               output += search(neighbours.get(i));
           }
           listaVertices.add(v);
       }
       return output;
    }
   
    private static String depth(List<Vertice> v) 
    {
        String output = "";
        
        Random generator = new Random();
 
        int begin = generator.nextInt(v.size());
        
        output = search(v.get(begin));
        v.remove(begin);
        
        for (int i = 0; i < v.size(); i++) 
        {
            output+= search(v.get(i));
            v.remove(i);
        }
    
        return  output;
    }
    
    public static List<Vertice> getVertices(String input)
    {
        int pos = 0;
        List<Vertice> v = new ArrayList<Vertice>();
        
        while (pos != -1)
        {
            int temp = input.indexOf(',',pos);
            if (temp == -1) 
            {
                temp = input.length()-1;
                v.add(new Vertice(input.substring(pos+1,temp)));
                pos = -1;
            }
            else
            {
                v.add(new Vertice(input.substring(pos+1,temp)));
                pos = temp + 1;
            }
        }
        
        for (int i = 0; i < v.size(); i++)
            v.get(i).initArray(v.size());
        
        return v;
    }    
    
    public static List<Vertice> getVerticesWeights(List<Vertice> v, String input, String weights)
    {
        int count = 0;
        int pos = 0;
        
        while (pos != -1)
        {
            int temp = input.indexOf(',',pos);
            if (temp == -1)
            {
                pos = -1;
            }
            else
            {
                String begin = input.substring(pos+2,temp);
                pos = input.indexOf(')',temp);
                String end = input.substring(temp+2,pos);
                Vertice b = null;
                Vertice e = null;
                for (int i = 0; i < v.size(); i++)
                {
                
                    if (v.get(i).getName().equals(begin))
                        b = v.get(i);
                    else if (v.get(i).getName().equals(end))
                        e = v.get(i);

                    if ((b != null) && (e != null))
                    {
                        b.addNeighbours(e);
//                        e.addNeighbours(b);
                        
                        temp = weights.indexOf(',',count);
                        if (temp == -1)
                            temp = weights.length()-1;
                        b.addWeights(Integer.decode(weights.substring(count+1,temp)));
//                        e.addWeights(Integer.decode(weights.substring(count+1,temp)));
                        count = temp + 1;
                        break;
                    }
                }
                pos += 2;
            }
        }
        
        return v;
    }
    
    public static void main(String[] args) {
//        - A primeira linha contém o conjunto dos vértices;
//        - A segunda linha contém o conjunto das arestas;
//        - A terceira linha contém o conjunto do peso das arestas;
//        - A quarta linha contém um número natural intervalo [1, |V|] que indica a posição do vértice fonte u no conjunto dos vértices;
//        Exemplo do conteúdo da entrada:
//        {a, b, c, d}
//        {(a, b), (a, c), (b, d), (c, d)}
//        {10, 13, 5, 23}
        
//      input = Vertices
//      String input = Keyboard.readString();
        String input = Keyboard.readString();
        
        List<Vertice> v = getVertices(input);
        
//      input = Edges
//      input = Keyboard.readString();
        input = Keyboard.readString();
//      String weights = Keyboard.readString();
        String weights = Keyboard.readString();
        
        v = getVerticesWeights(v,input,weights);
        
        String saida = depth(v);
        System.out.println(saida);
        int i;
        for(i = 0;i<listaVertices.size();i++)
        {
            System.out.println(listaVertices.get(i).getName());
        }
        
    }
    
}