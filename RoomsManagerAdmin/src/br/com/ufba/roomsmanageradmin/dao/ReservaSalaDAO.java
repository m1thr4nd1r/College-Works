package br.com.ufba.roomsmanageradmin.dao;

import java.sql.SQLException;
import java.sql.Statement;
import br.com.ufba.roomsmanageradmin.model.ReservaSala;

public class ReservaSalaDAO {
	
	public void salva(ReservaSala reserva) throws SQLException{
		
		String sql = "INSERT INTO reserva_sala (sala_id,data_inicio,data_fim,horario_inicio,horario_termino,responsavel,reserva_para,evento_privado,email,telefone,obs)"+
					 "VALUES("+reserva.getSala_id()+",'"+reserva.getDataInicio()+"','"+reserva.getDataFim()+"','"+reserva.getHorarioInicio()+"','"+reserva.getHorarioTermino()+
					 "','"+reserva.getResponsavel()+"','"+reserva.getReservadoPara()+"','"+reserva.isEventoPrivado()+"','"+reserva.getEmail()+"','"+reserva.getTelefone()+"','"+reserva.getObservacao()+"')";
		Statement st = (Statement) Myconnection.getStatement();
		st.executeUpdate(sql);
		st.close();
		
	}
	
}
