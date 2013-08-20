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
	private Sala sala = new Sala();
	private String setor_id;
	
	public String getSetor_id() {
		return setor_id;
	}

	public void setSetor_id(String setor_id) {
		this.setor_id = setor_id;
	}
	
	@PostConstruct
	void init(){
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    listaSalas = (ArrayList<Sala>) session.createQuery("FROM Sala").list();	    
	    session.close();
	}
	
	public String create(ActionEvent ae) throws ParseException
	{
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    Transaction tx = null;
	
	    System.out.println("Chego2");
	    
	    try{
	    	tx = session.beginTransaction();
	    	sala.setSetor_id(4);
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

	/*public String cadastra(){
		
		SalaDAO salaDAO = new SalaDAO();
		
		try {
			
			sala.setSetor_id(Integer.parseInt(setor_id));
			salaDAO.salva(sala);
			JOptionPane.showMessageDialog(null, "Sala cadastrada com sucesso. ");
			return "cadastra.do?faces-redirect=true";
		} catch (SQLException e) {
			System.out.println("#"+e.getMessage());
			e.printStackTrace();
		}
		return "cadastra.do?faces-redirect=true";
	}
	*/
//	public void lista(){
//		SalaDAO salaDAO = new SalaDAO();
//		SetorDAO setorDAO = new SetorDAO();
//		try{
//			listaSalas = salaDAO.lista();
//			listaSetor = setorDAO.getSetor();
//			for(Sala auxSala :listaSalas){
//				for(Setor auxSetor :listaSetor){
//					if(auxSala.getSetor_id() == auxSetor.getId()){
//						auxSala.setSetorNome(auxSetor.getNome());
//					}
//				}
//			}
//		}catch(SQLException e){
//		
//		}
//		
//	}
	 
	 private String getRandomModel() {  
	        return UUID.randomUUID().toString().substring(0, 8);  
	 }
	 
	 public void onEdit(RowEditEvent event) {  
	        FacesMessage msg = new FacesMessage("Sala editada", ((Sala) event.getObject()).getNome());  
	        Sala sala = (Sala) event.getObject();
//	        Sala user = Facade.find(use.getId()); 
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
		return listaSalas;
	}

	
	public ArrayList<Setor> getListaSetor(){
		return listaSetor;
	}
}
