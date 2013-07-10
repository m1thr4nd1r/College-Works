package br.com.ufba.roomsmanageradmin.dao;

import java.sql.SQLException;
import java.sql.Statement;
import br.com.ufba.roomsmanageradmin.model.Sala;

public class CadastraSalaDAO {
	
	public void salva(Sala sala) throws SQLException{
		
		String sql = "INSERT INTO sala (nome,quadro,retrojetor,multimidia,tipo,ar_condicionado,computadores,capacidade,setor_id)"+
					 "VALUES("+sala.getNome()+",'"+sala.isQuadro()+"','"+sala.isRetroprojetor()+"','"+sala.isMultimidia()+"','"+sala.getTipo()+
					 "','"+sala.isArcondicionado()+"','"+sala.getComputadores()+"','"+sala.getCapacidade()+"','"+sala.getSetor_id()+"')";
		Statement st = (Statement) Myconnection.getStatement();
		st.executeUpdate(sql);
		st.close();
		
	}
	
}
