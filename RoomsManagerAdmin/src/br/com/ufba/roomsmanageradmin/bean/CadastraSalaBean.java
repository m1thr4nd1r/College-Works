package br.com.ufba.roomsmanageradmin.bean;

import java.io.Serializable;
import java.sql.SQLException;

import javax.faces.bean.ManagedBean;
import javax.faces.bean.ViewScoped;

import br.com.ufba.roomsmanageradmin.dao.SalaDAO;
import br.com.ufba.roomsmanageradmin.model.Sala;

@ManagedBean
@ViewScoped
public class CadastraSalaBean implements Serializable{
	private static final long serialVersionUID = -6735027036534961738L;
	private Sala sala = new Sala();
	
	public void cadastra(){
		
		SalaDAO salaDAO = new SalaDAO();
		
		try {
			salaDAO.salva(sala);
		} catch (SQLException e) {
			System.out.println("#"+e.getMessage());
			e.printStackTrace();
		}
		
	}
	
	public Sala getSala(){
		return sala;
	}
}
