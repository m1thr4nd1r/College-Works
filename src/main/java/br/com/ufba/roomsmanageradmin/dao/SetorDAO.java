package br.com.ufba.roomsmanageradmin.dao;

import java.sql.SQLException;
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

}
