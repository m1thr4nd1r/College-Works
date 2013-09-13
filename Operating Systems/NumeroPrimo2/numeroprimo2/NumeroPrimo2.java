/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package numeroprimo2;

import key.Keyboard;

/**
 *
 * @author Arlindo Junior
 */
public class NumeroPrimo2 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws Exception {
        // TODO code application logic here
               
        int i = 0;
        int numT = 0;
        
        
         // ler do teclado o numero a ser testado.
        
        
        numT = Keyboard.readInt(); // ler o numero de threads desejadas
       
        i = Keyboard.readInt();
        
        int i1 = 0;
        if (numT != 0)
            i1 = i/numT;
        
        
        primo[] p = new primo[numT]; // vetor de intervalos primos: Existe uma classe chamada primo que possui um metodo run que calcula primo.
        Thread[] t = new Thread[numT];
        
        for(int h = 0; h<numT;h++){   // distribui os intervalos para cada thread.
            p[h] = new primo(((i1 * h) + 1),i1 * (h+1));
            t[h] = new Thread(p[h]);
            p[h].setId("Thread "+(h+1)+": ");
        }
        
        for(int h = 0; h<numT;h++){
            t[h].start(); // Automaticamente é chamado o metodo run
        }
        
        
        
        

    }
}
