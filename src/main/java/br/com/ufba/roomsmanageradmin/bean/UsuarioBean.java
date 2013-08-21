package br.com.ufba.roomsmanageradmin.bean;

import java.io.Serializable;
import java.text.ParseException;

import org.hibernate.HibernateException;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.primefaces.event.RowEditEvent;

import java.util.List;

import javax.annotation.PostConstruct;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.ViewScoped;
import javax.faces.event.ActionEvent;
import javax.faces.model.DataModel;
import javax.faces.model.ListDataModel;

import br.com.ufba.roomsmanageradmin.dao.Hibernate;
import br.com.ufba.roomsmanageradmin.model.Usuario;

@ManagedBean
public class UsuarioBean implements Serializable{
		
	private static final long serialVersionUID = 1L;
	
	private Usuario usuario = new Usuario();
	private DataModel<Usuario> usuarios;
	private String tipo;
		
	public Usuario getUsuario() {
		return usuario;
	}
	
	public void setUsuario(Usuario usuario) {
		this.usuario = usuario;
	}
	@PostConstruct
	public void UsuarioBean(){
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    List<Usuario> l = (List<Usuario>) session.createQuery("FROM Usuario").list();
	    usuarios = new ListDataModel(l);
	    session.close();
	}

	public DataModel<Usuario> getUsuarios()
	{
		return usuarios;
	}
	
	public String create(ActionEvent ae) throws ParseException
	{
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    Transaction tx = null;
	    
	    usuario.setTipo_id(usuario.getTipo_id()+1);
	    
	    try{
	    	tx = session.beginTransaction();
	    	session.saveOrUpdate(usuario); 
	    	tx.commit();
    	}catch (HibernateException e) {
    		if (tx!=null) tx.rollback();
	    	e.printStackTrace(); 
    	}finally {
	    	session.close();
	    }
	    return "list?faces-redirect=true";
    }
    
	public String update(RowEditEvent event) throws ParseException
	{
		SessionFactory sf = Hibernate.getSessionFactory();
		Session session = sf.openSession();
		Transaction tx = null;
		
		select();
		
		try{
			tx = session.beginTransaction();
			session.update(usuario);
			session.flush();
			tx.commit(); 
		}catch (HibernateException e) {
			if (tx!=null) tx.rollback();
				e.printStackTrace(); 
		}finally {
		session.close(); 
		}
		
		return "list"; 
	}

	public void delete()
    {
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    Transaction tx = null;
	
	    select();
	    
	    try{
	    	tx = session.beginTransaction();
	    	session.delete(usuario); 
	    	tx.commit();
	    	List<Usuario> l = (List<Usuario>) session.createQuery("FROM Usuario").list();
		    usuarios = new ListDataModel(l);
    	}catch (HibernateException e) {
    		if (tx!=null) tx.rollback();
	    	e.printStackTrace(); 
    	}finally {
	    	session.close();
	    }
    }
	
	public void select()
	{
        this.usuario = this.usuarios.getRowData();
    }
}