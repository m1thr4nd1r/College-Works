package br.com.ufba.roomsmanageradmin.bean;

import java.io.Serializable;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.List;

import javax.annotation.PostConstruct;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.ViewScoped;
import javax.faces.event.ActionEvent;
import javax.faces.model.ListDataModel;
import javax.swing.JOptionPane;

import org.hibernate.HibernateException;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;

import br.com.ufba.roomsmanageradmin.dao.Hibernate;
import br.com.ufba.roomsmanageradmin.dao.Myconnection;
import br.com.ufba.roomsmanageradmin.dao.SalaDAO;
import br.com.ufba.roomsmanageradmin.dao.SetorDAO;
import br.com.ufba.roomsmanageradmin.model.*;


@ManagedBean
@ViewScoped
public class SetorBean implements Serializable {
	
	private Setor setor = new Setor();
	private List<Setor> setores = new ArrayList<Setor>();
	private String setor_id;
	
	public String create(ActionEvent ae) throws ParseException
	{
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    Transaction tx = null;
	
	    
	    try{
	    	tx = session.beginTransaction();
	    	session.saveOrUpdate(setor); 
	    	tx.commit();
    	}catch (HibernateException e) {
    		if (tx!=null) tx.rollback();
	    	e.printStackTrace(); 
    	}finally {
	    	session.close();
	    }
	    return "list?faces-redirect=true";
    }
	
	@PostConstruct
	void iniciSetor(){
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    setores= (List<Setor>) session.createQuery("FROM Setor").list();
	    session.close();
	}	
	
	public Setor getSetor(){
		return setor;
	}
	
	public List<Setor> getSetores(){
		return setores;
	}

	public String getSetor_id() {
		return setor_id;
	}

	public void setSetor_id(String setor_id) {
		this.setor_id = setor_id;
	}
	
    

}
