package br.com.ufba.roomsmanageradmin.bean;

import java.io.Serializable;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

import javax.faces.bean.ManagedBean;
import javax.faces.bean.ViewScoped;
import javax.swing.JOptionPane;

import br.com.ufba.roomsmanageradmin.dao.Myconnection;
import br.com.ufba.roomsmanageradmin.dao.SalaDAO;
import br.com.ufba.roomsmanageradmin.dao.SetorDAO;
import br.com.ufba.roomsmanageradmin.model.*;


@ManagedBean
@ViewScoped
public class SetorBean implements Serializable {
	
	private Setor setor = new Setor();
	private List<Setor> setores;
	private String setor_id;
	
	
	public void cadastra(){
		SetorDAO SetorDAO = new SetorDAO();
		
		try {
			SetorDAO.salvar(setor);
		} catch (SQLException e) {
			System.out.println("#"+e.getMessage());
			e.printStackTrace();
		}
		
	}
	
	public void lista(){
		SetorDAO SetorDAO = new SetorDAO();
		
		try {
			setores = SetorDAO.getSetor();
		} catch (SQLException e) {
			System.out.println("#"+e.getMessage());
			e.printStackTrace();
		}
		
	}

	
	
	public Setor getSetor(){
		return setor;
	}
	
	public List<Setor> getSetores(){
		lista();
		return setores;
	}

	public String getSetor_id() {
		return setor_id;
	}

	public void setSetor_id(String setor_id) {
		this.setor_id = setor_id;
	}
	
    

}
