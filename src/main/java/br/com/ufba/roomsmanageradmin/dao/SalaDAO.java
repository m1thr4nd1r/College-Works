package br.com.ufba.roomsmanageradmin.dao;

import java.util.*;
import java.sql.*;


import br.com.ufba.roomsmanageradmin.model.Sala;

public class SalaDAO {
	
	public void salva(Sala sala) throws SQLException{
		
		String sql = "INSERT INTO sala (nome,quadro,retroprojetor,multimidia,tipo,ar_condicionado,computadores,capacidade,setor_id)"+
					 "VALUES('"+sala.getNome()+"',"+sala.isQuadro()+","+sala.isRetroprojetor()+","+sala.isMultimidia()+",'"+sala.getTipo()+
					 "',"+sala.isArcondicionado()+","+sala.getComputadores()+","+sala.getCapacidade()+","+sala.getSetor_id()+")";
		Statement st = (Statement) Myconnection.getStatement();
		st.executeUpdate(sql);
		st.close();
		
	}
	
	public Sala getSalaById(int sala_id) throws SQLException{
		Sala sala = null;
		
		String consulta = "SELECT * FROM sala WHERE id = "+sala_id;
		
		Statement st = (Statement) Myconnection.getStatement();
		ResultSet rs = st.executeQuery(consulta);
		
		while(rs.next()){
			sala = new Sala(rs.getInt("id"),rs.getString("nome"), rs.getBoolean("quadro"), rs.getBoolean("retroprojetor"), rs.getBoolean("multimidia"), rs.getString("tipo"), rs.getBoolean("ar_condicionado"), rs.getInt("computadores"), rs.getInt("capacidade"), rs.getInt("setor_id"));
		}
		
		return sala;
	}
	
	public  ArrayList<Sala> lista() throws SQLException{
		ArrayList<Sala> salas = new ArrayList<Sala>();
		String consulta = "SELECT * FROM sala ";
		
		Statement st = (Statement) Myconnection.getStatement();
		ResultSet rs = st.executeQuery(consulta);
		
		while(rs.next()){
			salas.add(new Sala(rs.getInt("id"),rs.getString("nome"), rs.getBoolean("quadro"), rs.getBoolean("retroprojetor"), rs.getBoolean("multimidia"), rs.getString("tipo"), rs.getBoolean("ar_condicionado"), rs.getInt("computadores"), rs.getInt("capacidade"), rs.getInt("setor_id")));
		}
		
		return salas;
	}
	
	public List<Sala> getSalas() throws SQLException{
		List<Sala> salas = new ArrayList<Sala>();
		
		String consulta = "SELECT * FROM sala ";
		
		Statement st = (Statement) Myconnection.getStatement();
		ResultSet rs = st.executeQuery(consulta);
		
		while(rs.next()){
			salas.add(new Sala(rs.getInt("id"),rs.getString("nome"), rs.getBoolean("quadro"), rs.getBoolean("retroprojetor"), rs.getBoolean("multimidia"), rs.getString("tipo"), rs.getBoolean("ar_condicionado"), rs.getInt("computadores"), rs.getInt("capacidade"), rs.getInt("setor_id")));
		}
		
		return salas;
	}

}
