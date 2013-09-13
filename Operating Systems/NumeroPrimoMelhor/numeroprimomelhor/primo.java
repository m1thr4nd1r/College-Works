/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package numeroprimomelhor;





/**
 *
 * @author Arlindo Junior
 */
public class primo implements Runnable{
    
    private int ini;
    private int fin;
    private String id;
    
    public primo(int ini, int fin){
        this.ini = ini;
        this.fin = fin;
    
    }
    
    public void setId(String id){
        this.id = id;
    }
    
    public String getId(){
        return id;
    }
    
   public void run() { // metodo padrão de Runnable...
       
       
        int atual;  
        int primo;  
  
        for(int i = ini; i <= fin; i++){  
            primo = 0;  
            atual = i;  
            //verifica se é primo  
            for(int j = 1; j <= Math.sqrt(atual) ; j++){  
                if(atual%j==0 && atual != 1){  
                    primo = primo + 1;  
                }  
            }  
            //só é primo se for divisivel por 1 e ele mesmo  
            if(primo==1){  
                System.out.println(id + atual);  
            }  
        }
    } 
    
    
}
