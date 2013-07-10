package br.com.ufba.roomsmanageradmin.dao;

import java.io.Serializable;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.List;

import br.com.ufba.roomsmanageradmin.model.ReservaSala;
import br.com.ufba.roomsmanageradmin.model.Usuario;

public class CadastraUsuarioDAO implements Serializable {

	private static final long serialVersionUID = 1L;

	public void salva(Usuario usuario) throws SQLException, ParseException
	{
		String sql;
		sql = "INSERT INTO usuario (nome,senha,email,num_cadastro,tipo)" + "VALUES('" +
		usuario.getNome()+"','"+usuario.getSenha()+"','"+usuario.getEmail()+"','"+usuario.getNum_cadastro()+"','"+usuario.getTipo()+"')";
		Statement st = (Statement) Myconnection.getStatement();
		st.executeUpdate(sql);
		st.close();
	}
	
	public List getUsuarios() throws SQLException{
		List <Usuario> lista = new ArrayList<Usuario>();
		
		String consulta = "SELECT * FROM usuario";
		
		Statement st = (Statement) Myconnection.getStatement();
		ResultSet rs = st.executeQuery(consulta);
		
		while(rs.next())
		{
			Usuario user = new Usuario(rs.getString("email"),rs.getString("senha"), rs.getString("nome"), rs.getInt("num_cadastro"), rs.getBoolean("tipo"));
			lista.add(user);
		}
		
		st.close();
		
		return lista;
	}
}