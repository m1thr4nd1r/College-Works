package br.com.ufba.roomsmanageradmin.dao;

import java.util.*;
import java.util.logging.SimpleFormatter;
import java.io.Serializable;
import java.sql.*;
import java.text.*;
import br.com.ufba.roomsmanageradmin.model.*;

public class ReservaSalaDAO implements Serializable{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	@SuppressWarnings("deprecation")
	public void salva(ReservaSala reserva) throws SQLException, ParseException{
		
		int m = reserva.getDataInicio().getMonth()+1;
		int d = reserva.getDataInicio().getDate();
		
		String mes = (m) < 10 ? "0"+m : ""+m;
		String dia = (d) < 10 ? "0"+d : ""+d;
		
		String data1 = reserva.getDataInicio().getYear()+1900+"-"+mes+"-"+dia;

		m = reserva.getDataFim().getMonth()+1;
		d = reserva.getDataFim().getDate();
		
		mes = (m) < 10 ? "0"+m : ""+m;
		dia = (d) < 10 ? "0"+d : ""+d;
		
		String data2 = reserva.getDataFim().getYear()+1900+"-"+mes+"-"+dia;

		String h1 = (reserva.getHorarioInicio().getHours() < 10) ? "0"+reserva.getHorarioInicio().getHours() : reserva.getHorarioInicio().getHours()+"";
		String m1 = (reserva.getHorarioInicio().getMinutes() < 10) ? "0"+reserva.getHorarioInicio().getMinutes() : reserva.getHorarioInicio().getMinutes()+"";
		String horario1 = h1+":"+m1+":00";
		
		String h2 = (reserva.getHorarioTermino().getHours() < 10) ? "0"+reserva.getHorarioTermino().getHours() : reserva.getHorarioTermino().getHours()+"";
		String m2 = (reserva.getHorarioTermino().getMinutes() < 10) ? "0"+reserva.getHorarioTermino().getMinutes() : reserva.getHorarioTermino().getMinutes()+"";
		String horario2 = h2+":"+m2+":00";

		String sql = "INSERT INTO reserva_sala (sala_id,data_inicio,data_fim,horario_inicio,horario_termino,responsavel,reserva_para,evento_privado,email,telefone,obs,aceito)"+
					 "VALUES("+reserva.getSala().getId()+",'"+data1+"','"+data2+"','"+horario1+"','"+horario2+
					 "','"+reserva.getResponsavel()+"','"+reserva.getReservadoPara()+"',"+reserva.isEventoPrivado()+",'"+reserva.getEmail()+"','"+reserva.getTelefone()+"','"+reserva.getObservacao()+"',1)";
		
		//System.out.println(sql);
		Statement st = (Statement) Myconnection.getStatement();
		st.executeUpdate(sql);
		st.close();
		
	}
	
	public List<ReservaSala> getReservas() throws SQLException{
		List <ReservaSala> lista = new ArrayList<ReservaSala>();
		
		String consulta = "SELECT * FROM reserva_sala";
		
		Statement st = (Statement) Myconnection.getStatement();
		ResultSet rs = st.executeQuery(consulta);
		
		while(rs.next()){
			ReservaSala reserva = new ReservaSala(rs.getInt("sala_id"),rs.getDate("data_inicio"),rs.getDate("data_fim"),rs.getTime("horario_inicio"),rs.getTime("horario_termino"), rs.getString("responsavel"), rs.getString("reserva_para"),rs.getBoolean("evento_privado"),rs.getString("email"), rs.getString("telefone"),rs.getString("obs"),rs.getBoolean("aceito"));
			lista.add(reserva);
		}
		
		st.close();
		
		return lista;
	}
	
}
