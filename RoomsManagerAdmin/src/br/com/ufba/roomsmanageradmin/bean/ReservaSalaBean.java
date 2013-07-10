package br.com.ufba.roomsmanageradmin.bean;

import java.io.Serializable;
import java.sql.SQLException;
import java.util.*;

import javax.faces.bean.*;
import javax.faces.event.*;
import org.primefaces.event.*;

import br.com.ufba.roomsmanageradmin.dao.ReservaSalaDAO;
import br.com.ufba.roomsmanageradmin.model.Area;
import br.com.ufba.roomsmanageradmin.model.ReservaSala;



@ManagedBean
public class ReservaSalaBean implements Serializable{
	
	private ReservaSala reserva;
	private Area area;
	
	public void salva(ActionEvent ae){
		ReservaSalaDAO rsDAO = new ReservaSalaDAO();
		
		try {
			rsDAO.salva(reserva);
		} catch (SQLException e) {
			System.out.println("#"+e.getMessage());
			e.printStackTrace();
		}
	}
	
	public ReservaSala getReserva(){
		return reserva;
	}
	
	public List getSala(){
		List<Area> l = new ArrayList<Area>();
		l.add(new Area("Dept. de Computação",1));
		return l;
	}
	
	public Area getArea(){
		return area;
	}
}
