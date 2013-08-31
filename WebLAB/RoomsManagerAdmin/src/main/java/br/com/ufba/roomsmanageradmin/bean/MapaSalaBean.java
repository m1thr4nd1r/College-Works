package br.com.ufba.roomsmanageradmin.bean;

import java.io.Serializable;

import javax.faces.bean.ManagedBean;

import org.primefaces.model.DefaultTreeNode;
import org.primefaces.model.TreeNode;

import br.com.ufba.roomsmanageradmin.model.Pagina;

@ManagedBean
public class MapaSalaBean implements Serializable {  
  
    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private TreeNode root;

    public MapaSalaBean() {
    	
		root = new DefaultTreeNode("root", null);  
		
	    TreeNode sala = new DefaultTreeNode(new Pagina("Sala","-"), root);
	    TreeNode reserva = new DefaultTreeNode(new Pagina("Reserva", "-"), sala);
	    
	    new DefaultTreeNode("pagina",new Pagina("index.do"), sala);
	    new DefaultTreeNode("pagina",new Pagina("cadastro.do"), sala);
	    new DefaultTreeNode("pagina",new Pagina("lista.do"), sala);
	    
	    new DefaultTreeNode("pagina",new Pagina("index.do","reserva"), reserva);
	    new DefaultTreeNode("pagina",new Pagina("lista.do","reserva"),reserva);
	    
    }
    
    public TreeNode getRoot() {  
        return root;  
    }
    
}
