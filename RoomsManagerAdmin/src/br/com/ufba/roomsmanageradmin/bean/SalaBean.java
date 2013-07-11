package br.com.ufba.roomsmanageradmin.bean;

import java.io.Serializable;
import java.sql.SQLException;
import java.util.ArrayList;

import javax.faces.bean.ManagedBean;
import javax.faces.bean.ViewScoped;
import javax.swing.JOptionPane;

import org.eclipse.jdt.internal.compiler.ast.Literal;

import br.com.ufba.roomsmanageradmin.dao.SalaDAO;
import br.com.ufba.roomsmanageradmin.model.Sala;

@ManagedBean
@ViewScoped
public class SalaBean implements Serializable{
	private static final long serialVersionUID = -6735027036534961738L;
	private static ArrayList<Sala> listaSalas = new ArrayList<Sala>();
	private Sala sala = new Sala();
	
	public void cadastra(){
		
		SalaDAO salaDAO = new SalaDAO();
		
		try {
			salaDAO.salva(sala);
			lista();
		} catch (SQLException e) {
			System.out.println("#"+e.getMessage());
			e.printStackTrace();
		}
		
	}
	
	public void lista(){
		SalaDAO salaDAO = new SalaDAO();
		try{
			salaDAO.listaSala(listaSalas);
		}catch(SQLException e){
		
		}
		
	}
	
	
	public Sala getSala(){
		return sala;
	}
	
	public ArrayList<Sala> getListaSalas(){
		return listaSalas;
	}
}
