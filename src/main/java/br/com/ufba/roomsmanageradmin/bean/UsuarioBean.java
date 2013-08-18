package br.com.ufba.roomsmanageradmin.bean;

import java.io.Serializable;
import java.text.ParseException;

import org.hibernate.HibernateException;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;

import java.util.List;

import javax.faces.bean.ManagedBean;
import javax.faces.event.ActionEvent;

import br.com.ufba.roomsmanageradmin.dao.Hibernate;
import br.com.ufba.roomsmanageradmin.model.Usuario;
import br.com.ufba.roomsmanageradmin.dao.UsuarioDAO;

@ManagedBean
public class UsuarioBean implements Serializable{
		
	private static final long serialVersionUID = 1L;
	
	private Usuario usuario = new Usuario();
	private List<Usuario> usuarios = null; 
	private String url;
		
	public Usuario getUsuario() {
		return usuario;
	}
	
	public void setUsuario(Usuario usuario) {
		this.usuario = usuario;
	}

	public List<Usuario> getUsuarios()
	{
		SessionFactory sf = Hibernate.getSessionFactory();
	    
    	Session session = sf.openSession();
	    	
	    usuarios = (List<Usuario>) session.createQuery("FROM Usuario").list();
	    session.close();
		    
	    return usuarios;
	}
	
	public String salvar(ActionEvent ae) throws ParseException
	{
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    Transaction tx = null;
	
	    try{
	    	tx = session.beginTransaction();
	    	session.save(usuario); 
	    	tx.commit();
    	}catch (HibernateException e) {
    		if (tx!=null) tx.rollback();
	    	e.printStackTrace(); 
    	}finally {
	    	session.close();
	    }
	    return "list?faces-redirect=true";
    }

	public String viewLink()
    {
        this.usuario = new Usuario();
        this.usuario.setEmail(url);
        return "view?" + this.url + "?faces-redirect=true";
	}
    
    public String updateLink()
    {
        this.usuario = new Usuario();
        this.usuario.setEmail(url);
        return "update?" + this.url + "?faces-redirect=true";
	}
    
    public void deletar()
    {
        System.out.println("Vai deletar no futuro");
    }
}