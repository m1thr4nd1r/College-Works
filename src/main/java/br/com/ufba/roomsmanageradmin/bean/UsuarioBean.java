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
import javax.faces.model.DataModel;
import javax.faces.model.ListDataModel;

import br.com.ufba.roomsmanageradmin.dao.Hibernate;
import br.com.ufba.roomsmanageradmin.model.Usuario;
import br.com.ufba.roomsmanageradmin.dao.UsuarioDAO;

@ManagedBean
public class UsuarioBean implements Serializable{
		
	private static final long serialVersionUID = 1L;
	
	private Usuario usuario = new Usuario();
	private DataModel<Usuario> usuarios;
	private int id;
		
	public Usuario getUsuario() {
		return usuario;
	}
	
	public void setUsuario(Usuario usuario) {
		this.usuario = usuario;
	}

	public DataModel<Usuario> getUsuarios()
	{
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    List<Usuario> l = (List<Usuario>) session.createQuery("FROM Usuario").list();
	    usuarios = new ListDataModel(l);
	    session.close();
		    
	    return usuarios;
	}
	
	public String create(ActionEvent ae) throws ParseException
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
    
	public String update()
	{
		SessionFactory sf = Hibernate.getSessionFactory();
		Session session = sf.openSession();
		Transaction tx = null;
		
		try{
			tx = session.beginTransaction();
			session.update(usuario); 
			tx.commit();
			session.flush();
		}catch (HibernateException e) {
			if (tx!=null) tx.rollback();
				e.printStackTrace(); 
		}finally {
		session.close(); 
		}
		
		return "list?faces-redirect=true"; 
	}

	public String delete()
    {
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    Transaction tx = null;
	
	    select();
	    
	    try{
	    	tx = session.beginTransaction();
	    	session.delete(usuario); 
	    	tx.commit();
    	}catch (HibernateException e) {
    		if (tx!=null) tx.rollback();
	    	e.printStackTrace(); 
    	}finally {
	    	session.close();
	    }
	    
	    return "list?faces-redirect=true";
    }
	
	public void select()
	{
        this.usuario = this.usuarios.getRowData();
    }
}