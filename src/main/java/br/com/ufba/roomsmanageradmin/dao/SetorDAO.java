package br.com.ufba.roomsmanageradmin.dao;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import br.com.ufba.roomsmanageradmin.model.Setor;
import com.mysql.jdbc.Statement;


public class SetorDAO {
	
	public void salvar(Setor setor) throws SQLException{
			
			String sql = "INSERT INTO setor (nome,email)"+
						 "VALUES('"+setor.getNome()+"','"+setor.getEmail()+"')";
			Statement st = (Statement) Myconnection.getStatement();
			st.executeUpdate(sql);
			st.close();
			
	}
	
	
	public ArrayList<Setor> getSetor() throws SQLException{
		
		ArrayList<Setor> setores = new ArrayList<Setor>();
		
		String consulta = "SELECT * FROM setor ";
		
		Statement st = (Statement) Myconnection.getStatement();
		ResultSet rs = st.executeQuery(consulta);
		
		while(rs.next()){
			setores.add(new Setor(rs.getInt("id"), rs.getString("nome"), rs.getString("email")));
		}
		return setores;
	}
		
}
