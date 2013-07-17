package br.com.ufba.roomsmanageradmin.bean;

import java.io.Serializable;
import java.sql.SQLException;
import java.util.List;

import javax.faces.bean.ManagedBean;
import javax.faces.bean.ViewScoped;

import br.com.ufba.roomsmanageradmin.dao.SetorDAO;
import br.com.ufba.roomsmanageradmin.model.*;


@ManagedBean
@ViewScoped
public class SetorBean implements Serializable {
	
	private Setor setor = new Setor();
	
	
	public void cadastra(){
		//System.out.println("INSERT INTO sala (nome,email)"+"" +
			//	"VALUES("+setor.getNome()+",'"+setor.getEmail()+"')");
		SetorDAO SetorDAO = new SetorDAO();
		
		try {
			SetorDAO.salvar(setor);
		} catch (SQLException e) {
			System.out.println("#"+e.getMessage());
			e.printStackTrace();
		}
		
	}
	
	public Setor getSetor(){
		return setor;
	}

}
