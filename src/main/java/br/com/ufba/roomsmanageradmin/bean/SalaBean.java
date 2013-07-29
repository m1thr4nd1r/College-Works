package br.com.ufba.roomsmanageradmin.bean;

import java.io.Serializable;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.UUID;

import javax.faces.application.FacesMessage;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.ViewScoped;
import javax.faces.context.FacesContext;
import javax.swing.JOptionPane;
import java.util.UUID;

import javax.faces.application.FacesMessage;
import javax.faces.context.FacesContext;
import org.primefaces.event.RowEditEvent;

import org.eclipse.jdt.internal.compiler.ast.Literal;
import org.primefaces.event.RowEditEvent;

import br.com.ufba.roomsmanageradmin.dao.SalaDAO;
import br.com.ufba.roomsmanageradmin.model.Sala;

@ManagedBean
@ViewScoped
public class SalaBean implements Serializable{
	private static final long serialVersionUID = -6735027036534961738L;
	private static ArrayList<Sala> listaSalas = new ArrayList<Sala>();
	private Sala sala = new Sala();
	
	public String cadastra(){
		
		SalaDAO salaDAO = new SalaDAO();
		
		try {
			salaDAO.salva(sala);
			JOptionPane.showMessageDialog(null, "Sala cadastrada com sucesso.");
			return "cadastra.do?faces-redirect=true";
		} catch (SQLException e) {
			System.out.println("#"+e.getMessage());
			e.printStackTrace();
		}
		return "cadastra.do?faces-redirect=true";
	}
	
	public void lista(){
		SalaDAO salaDAO = new SalaDAO();
		try{
			listaSalas = salaDAO.lista();
		}catch(SQLException e){
		
		}
		
	}
	 
	 private String getRandomModel() {  
	        return UUID.randomUUID().toString().substring(0, 8);  
	    } 
	 public void onEdit(RowEditEvent event) {  
	        FacesMessage msg = new FacesMessage("Sala sala editada", ((Sala) event.getObject()).getModel());  
	  
	        FacesContext.getCurrentInstance().addMessage(null, msg);  
	    }  
	      
	    public void onCancel(RowEditEvent event) {  
	        FacesMessage msg = new FacesMessage("Edição Cancelada", ((Sala) event.getObject()).getModel());  
	  
	        FacesContext.getCurrentInstance().addMessage(null, msg);  
	    }  
	
	
	public Sala getSala(){
		return sala;
	}
	
	public ArrayList<Sala> getListaSalas(){
		lista();
		return listaSalas;
	}
}
