package br.com.ufba.roomsmanageradmin.bean;

import java.io.Serializable;
import java.sql.SQLException;
import java.text.ParseException;
import java.util.*;

import javax.faces.bean.*;
import javax.faces.event.*;
import javax.swing.JOptionPane;

import br.com.ufba.roomsmanageradmin.dao.ReservaSalaDAO;
import br.com.ufba.roomsmanageradmin.dao.SalaDAO;
import br.com.ufba.roomsmanageradmin.model.ReservaSala;
import br.com.ufba.roomsmanageradmin.model.Sala;



@ManagedBean
public class ReservaSalaBean implements Serializable{

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private ReservaSalaDAO rsDAO = new ReservaSalaDAO();
	private ReservaSala reserva = new ReservaSala();
	private List<ReservaSala> reservas;
	private List<Sala> salas;
	private String sala_id;
	
	public String salva(ActionEvent ae) throws ParseException{
		
		try {
			
			String dataInicio = getData(reserva.getDataInicio().toString());
			
			String dataFim = null;
			
			if(reserva.getDataFim() != null){
				dataFim = getData(reserva.getDataFim().toString());
			}
			
			if(dataFim == null || dataFim.isEmpty()){
				dataFim = dataInicio;
			}
			
			String HorarioInicio = getHora(reserva.getHorarioInicio().toString());
			String HorarioTermino = getHora(reserva.getHorarioTermino().toString());
			System.out.println("$$"+sala_id);
			ReservaSala res = new ReservaSala(Integer.parseInt(sala_id),dataInicio,dataFim,HorarioInicio,HorarioTermino,reserva.getResponsavel(),reserva.getReservadoPara(),reserva.isEventoPrivado(),reserva.getEmail(),reserva.getTelefone(),reserva.getObservacao());
			rsDAO.salva(res);
			
			JOptionPane.showMessageDialog(null,"Cadastrado efetuado com Sucesso!");
			return "reservaSalaSucesso?faces-redirect=true";
			
		} catch (SQLException e) {
			System.out.println("ERRO: "+e.getMessage());
			e.printStackTrace();
		}
		
		return "reservaSalaFailed";
	}
	
	public String getSala_id() {
		return sala_id;
	}
	
	public void setSala_id(String sala_id) {
		this.sala_id = sala_id;
	}

	public List<ReservaSala> getReservas(){
		
		try {
			this.reservas = rsDAO.getReservas();
		} catch (SQLException e) {
			JOptionPane.showMessageDialog(null,"GETRESERVAS ERRO: "+e.getMessage());
			e.printStackTrace();
		}
		 
		return this.reservas;
	}
	
	public List<Sala> getSalas(){
		SalaDAO dao = new SalaDAO();
		try {
			salas = dao.getSalas();
		} catch (SQLException e) {
			JOptionPane.showMessageDialog(null,"GETRESERVAS GETSALAS ERRO: "+e.getMessage());
			e.printStackTrace();
		}
		return salas;
	}
	
	public ReservaSala getReserva(){
		return reserva;
	}
	
	/**
	 * 
	 * @param data
	 * @return a data no formato do banco 
	 */
	public String getData(String data){
		
		String dt = "";
		
		if(data != null && !data.isEmpty()){
			String [] str = data.split(" ");
			
			int mes = mesToInt(str[1].toLowerCase());
			
			String m = (mes < 10) ? "0"+mes : mes+"";
			dt += str[str.length-1]+"-"+m+"-"+str[2];
		}
		return dt;
	}
	
	public String getHora(String data){
		String h = "";
		
		if(data != null && !data.isEmpty()){
			String [] str = data.split(" ");
			
			h = str[3];
		}
		
		return h;
	}
	
	public int mesToInt(String mes){
		int m = -1;
		
		String [] meses = {"jan","feb","mar","apr","may","jun","jul","aug","sep","oct","nov","dec"};
		
		for(int i = 0; i < meses.length; i++) {
			if(meses[i].equals(mes)){
				return (i+1);
			}
		}
		
		return m;
	}
	
}
