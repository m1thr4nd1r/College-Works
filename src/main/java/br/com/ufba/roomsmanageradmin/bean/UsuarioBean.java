package br.com.ufba.roomsmanageradmin.bean;

import java.io.Serializable;
import java.text.ParseException;

import org.apache.tools.ant.taskdefs.Get.DownloadProgress;
import org.hibernate.HibernateException;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.primefaces.event.RowEditEvent;

import java.util.Iterator;
import java.util.List;

import javax.annotation.PostConstruct;
<<<<<<< HEAD
=======
import javax.faces.context.FacesContext;
import javax.faces.application.FacesMessage;
>>>>>>> d6e0eb113747dfe62d44e8de0d3f86e6d7d1ac80
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import javax.faces.bean.ViewScoped;
import javax.faces.event.*;
import javax.faces.model.DataModel;
import javax.faces.model.ListDataModel;
import javax.swing.JOptionPane;

import br.com.ufba.roomsmanageradmin.dao.Hibernate;
import br.com.ufba.roomsmanageradmin.model.Usuario;

@ManagedBean
@SessionScoped
public class UsuarioBean implements Serializable{
		
	private static final long serialVersionUID = 1L;
	
	private Usuario usuario = new Usuario();
	private DataModel<Usuario> usuarios;
	private int id;
	private String num_cadastro = "";
	
	@PostConstruct
	void UsuarioBean(){
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    List<Usuario> l = (List<Usuario>) session.createQuery("FROM Usuario").list();
	    usuarios = new ListDataModel(l);
	    session.close();
	}
	
	public Usuario getUsuario() {
		return usuario;
	}
	
	public void setUsuario(Usuario usuario) {
		this.usuario = usuario;
	}
<<<<<<< HEAD
	@PostConstruct
	void init(){
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    List<Usuario> l = (List<Usuario>) session.createQuery("FROM Usuario").list();
	    usuarios = new ListDataModel(l);
	    session.close();
	}

	public DataModel<Usuario> getUsuarios()
	{		    
	    return usuarios;
=======

	public DataModel<Usuario> getUsuarios()
	{
	    return this.usuarios;
	}
	
	public void setUsuarios(DataModel usuarios)
	{
		this.usuarios = usuarios;
>>>>>>> d6e0eb113747dfe62d44e8de0d3f86e6d7d1ac80
	}
	
	public String create(ActionEvent ae) throws ParseException
	{
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    Transaction tx = null;
	
	    System.out.println("Chego2");
	    
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
    
	public void update(RowEditEvent event)
	{
		SessionFactory sf = Hibernate.getSessionFactory();
		Session session = sf.openSession();
		Transaction tx = null;
		
		select();
			
		try{
			
			tx = session.beginTransaction();
//			FacesMessage msg = new FacesMessage("Usuário atualizado",""+((Usuario)event.getObject()).getNome());  
//			FacesContext.getCurrentInstance().addMessage(null, msg);
			
			session.update(this.usuario);
			session.flush();
			tx.commit(); 
		}catch (HibernateException e) {
			if (tx!=null) tx.rollback();
				e.printStackTrace(); 
		}finally {
			session.close(); 
		}
	}
	
	public void update(ValueChangeEvent e){
		JOptionPane.showMessageDialog(null,e.getNewValue().toString());
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

	public String getNum_cadastro() {
		return num_cadastro;
	}

	public void setNum_cadastro(String num_cadastro) {
		this.num_cadastro = num_cadastro;
	}
	
	
}