package br.com.ufba.roomsmanageradmin.bean;

import java.io.Serializable;
import java.sql.SQLException;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

import javax.annotation.PostConstruct;
import javax.faces.application.FacesMessage;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.ViewScoped;
import javax.faces.context.FacesContext;
import javax.swing.JOptionPane;
import java.util.UUID;

import javax.faces.application.FacesMessage;
import javax.faces.context.FacesContext;
import javax.faces.event.ActionEvent;
import javax.faces.model.DataModel;
import javax.faces.model.ListDataModel;

import org.primefaces.event.RowEditEvent;

import org.eclipse.jdt.internal.compiler.ast.Literal;
import org.hibernate.HibernateException;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.primefaces.event.RowEditEvent;


import br.com.ufba.roomsmanageradmin.dao.Hibernate;
import br.com.ufba.roomsmanageradmin.dao.SalaDAO;
import br.com.ufba.roomsmanageradmin.dao.SetorDAO;
import br.com.ufba.roomsmanageradmin.model.Sala;
import br.com.ufba.roomsmanageradmin.model.Setor;
import br.com.ufba.roomsmanageradmin.model.Usuario;

@ManagedBean
public class SalaBean implements Serializable{
	private static final long serialVersionUID = -6735027036534961738L;
	private static ArrayList<Sala> listaSalas = new ArrayList<Sala>();
	private ArrayList<Setor> listaSetor = new ArrayList<Setor>();
	private DataModel<Sala> sal;
	private Sala sala = new Sala();
	private String setor_id;
	
	public String getSetor_id() {
		return setor_id;
	}

	public void setSetor_id(String setor_id) {
		this.setor_id = setor_id;
	}
	
	@PostConstruct
	public void SalaBean(){
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    listaSalas = (ArrayList<Sala>) session.createQuery("FROM Sala").list();	
	    listaSetor = (ArrayList<Setor>) session.createQuery("FROM Setor").list();	
	    session.close();
	}
	
	public String create(ActionEvent ae) throws ParseException
	{
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    Transaction tx = null;
	
	    
	    try{
	    	tx = session.beginTransaction();
	    	sala.setSetor_id(Integer.valueOf(setor_id));
	    	session.saveOrUpdate(sala); 
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
		
		sala = (Sala) event.getObject();
		
		sala.setSetor_id(Integer.valueOf(setor_id));
		
		try{
			tx = session.beginTransaction();
			session.update(sala);
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
	    	session.delete(sala);
	    	tx.commit();
//	    	listaSalas = (ArrayList<Sala>) session.createQuery("FROM Sala").list();
//	    	 sal = new ListDataModel(listaSalas);	    	
    	}catch (HibernateException e) {
    		if (tx!=null) tx.rollback();
	    	e.printStackTrace(); 
    	}finally {
	    	session.close();
	    }
    }
	
	public void select()
	{
        this.sala = this.sal.getRowData();
//        JOptionPane.showMessageDialog(null, sala.getNome());
    }
	 private String getRandomModel() {  
	        return UUID.randomUUID().toString().substring(0, 8);  
	 }
	 
	 public void onEdit(RowEditEvent event) {  
	        FacesMessage msg = new FacesMessage("Sala editada", ((Sala) event.getObject()).getNome());  
	        Sala sala = (Sala) event.getObject();
	        //Sala user = Facade.find(use.getId()); 
	        System.out.print(sala.getNome()+" "+sala.getSetorNome()+"\n");
	        FacesContext.getCurrentInstance().addMessage(null, msg);  
	}  
	      
    public void onCancel(RowEditEvent event) {  
        FacesMessage msg = new FacesMessage("Edição Cancelada", ((Sala) event.getObject()).getNome());  
        JOptionPane.showMessageDialog(null, "Edição cancelada");
        FacesContext.getCurrentInstance().addMessage(null, msg);  
    }  
	
	
	public Sala getSala(){
		return sala;
	}
		
	
	public ArrayList<Sala> getListaSalas(){
		for(Sala auxSala : listaSalas){
			for(Setor auxSetor : listaSetor){
				if(auxSala.getSetor_id() == auxSetor.getId()){
					auxSala.setSetorNome(auxSetor.getNome());
				}
			}
		}
		return listaSalas;
	}

	public DataModel<Sala> getSal(){		    
	    return sal;
	}
	public ArrayList<Setor> getListaSetor(){
		return listaSetor;
	}
}
