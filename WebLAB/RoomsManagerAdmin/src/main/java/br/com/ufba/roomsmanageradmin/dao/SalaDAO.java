package br.com.ufba.roomsmanageradmin.dao;

import java.util.*;
import java.sql.*;


import br.com.ufba.roomsmanageradmin.model.ControleAcesso;
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
		
		String consulta = "SELECT * FROM sala";
		
		Statement st = (Statement) Myconnection.getStatement();
		ResultSet rs = st.executeQuery(consulta);
		
		while(rs.next()){
			salas.add(new Sala(rs.getInt("id"),rs.getString("nome"), rs.getBoolean("quadro"), rs.getBoolean("retroprojetor"), rs.getBoolean("multimidia"), rs.getString("tipo"), rs.getBoolean("ar_condicionado"), rs.getInt("computadores"), rs.getInt("capacidade"), rs.getInt("setor_id")));
		}
		
		return salas;
	}
	
	public List<ControleAcesso> getLabsReservados() throws SQLException{
		List<ControleAcesso> ctr = new ArrayList<ControleAcesso>();
		
		String query = "SELECT c.*, s.nome FROM controle_acesso AS c INNER JOIN sala AS s ON s.id = c.sala_id WHERE s.tipo = 'laboratorio' ORDER BY hora_entrada desc";
		
		Statement st = (Statement) Myconnection.getStatement();
		ResultSet rs = st.executeQuery(query);
		
		while(rs.next()){
			Sala s = new Sala(rs.getInt("sala_id"),rs.getString("nome"));
			boolean naLista = false;
			for(ControleAcesso ca : ctr){
				Sala aux = ca.getSala();
				if(!naLista){
					naLista = (s.getId() == aux.getId());
				}
			}
			if(!naLista){
				ctr.add(new ControleAcesso(s,rs.getDate("hora_entrada"),rs.getDate("data_entrada"),rs.getDate("hora_saida"),rs.getDate("data_saida"),rs.getBoolean("e_chave")));
			}
		}
		
		return ctr;
	}
	
}
