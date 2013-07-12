package br.com.ufba.roomsmanageradmin.bean;

import java.io.Serializable;

import javax.faces.bean.ManagedBean;

import org.primefaces.model.DefaultTreeNode;
import org.primefaces.model.TreeNode;

import br.com.ufba.roomsmanageradmin.model.Pagina;

@ManagedBean
public class MapaUsuarioBean implements Serializable {  
  
    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private TreeNode root;

    public MapaUsuarioBean() {
    	
		root = new DefaultTreeNode("root", null);  
		  
	    TreeNode user = new DefaultTreeNode(new Pagina("Usuário","-"), root);
	    
	    new DefaultTreeNode("pagina",new Pagina("index.do"), user);
	    new DefaultTreeNode("pagina",new Pagina("create.do"), user);
	    new DefaultTreeNode("pagina",new Pagina("list.do"), user);
	    
    }
    
    public TreeNode getRoot() {  
        return root;  
    }
    
}
