package br.com.ufba.roomsmanageradmin.bean;

import java.io.Serializable;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

import javax.annotation.PostConstruct;
import javax.faces.application.FacesMessage;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.ViewScoped;
import javax.faces.context.FacesContext;
import javax.faces.event.ActionEvent;
import javax.faces.model.DataModel;
import javax.faces.model.ListDataModel;
import javax.swing.JOptionPane;

import org.hibernate.HibernateException;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.primefaces.event.RowEditEvent;

import br.com.ufba.roomsmanageradmin.dao.Hibernate;
import br.com.ufba.roomsmanageradmin.model.Tipo;

@ManagedBean
@ViewScoped
public class TipoBean implements Serializable {
	
	private Tipo tipo = new Tipo();
	private DataModel<Tipo> tipos;

	@PostConstruct
	void init(){
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    List<Tipo> t = (List<Tipo>) session.createQuery("FROM Tipo").list();
	    tipos = new ListDataModel(t);
	    session.close();
	}	
	
	public String create(ActionEvent ae) throws ParseException
	{
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    Transaction tx = null;
		    
	    try{
	    	tx = session.beginTransaction();
	    	session.save(tipo); 
	    	tx.commit();
	    	FacesMessage message = new FacesMessage(FacesMessage.SEVERITY_INFO,"Tipo adicionado com sucesso!", "Sucesso!");
    	    FacesContext.getCurrentInstance().addMessage(null,message);    	    
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
		
		tipo = (Tipo) event.getObject();		
		
		try{
			tx = session.beginTransaction();
			session.update(tipo);
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
	    	session.delete(tipo); 
	    	tx.commit();
	    	List<Tipo> t = (List<Tipo>) session.createQuery("FROM Tipo").list();
		    tipos = new ListDataModel(t);
    	}catch (HibernateException e) {
    		if (tx!=null) tx.rollback();
	    	e.printStackTrace(); 
	    	JOptionPane.showMessageDialog(null, "Não foi possivel deletar "+ tipo.getDescricao()+".");
    	}finally {
	    	session.close();
	    }
    }
	
	public void select()
	{
        this.tipo = this.tipos.getRowData();
    }
	 
	public void onEdit(RowEditEvent event) {  
	       FacesMessage msg = new FacesMessage("Tipo editado", ((Tipo) event.getObject()).getDescricao());  
	       FacesContext.getCurrentInstance().addMessage(null, msg);  
	}  
	      
	public void onCancel(RowEditEvent event) {  
	    FacesMessage msg = new FacesMessage("Edição Cancelada", ((Tipo) event.getObject()).getDescricao());  
	    JOptionPane.showMessageDialog(null, "Edição cancelada");
	    FacesContext.getCurrentInstance().addMessage(null, msg);  
	}

	public Tipo getTipo(){
		return tipo;
	}

	public void setTipo(Tipo tipo){
		this.tipo = tipo;
	}
	
	public DataModel<Tipo> getTipos(){
		return tipos;
	}
}