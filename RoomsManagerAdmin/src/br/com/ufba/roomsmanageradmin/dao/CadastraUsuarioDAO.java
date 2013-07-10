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
		usuario.getNome()+"','"+usuario.getSenha()+"','"+usuario.getEmail()+"','"+usuario.getNum_cadastro()+"','"+usuario.isAdmin()+"')";
		Statement st = (Statement) Myconnection.getStatement();
		st.executeUpdate(sql);
		st.close();
	}
	
//	public List getUsuarios() throws SQLException{
//		List <Usuario> lista = new ArrayList<Usuario>();
//		
//		String consulta = "SELECT * FROM reserva_sala";
//		
//		Statement st = (Statement) Myconnection.getStatement();
//		ResultSet rs = st.executeQuery(consulta);
//		
//		while(rs.next()){
//			ReservaSala reserva = new ReservaSala(rs.getInt("sala_id"),rs.getString("data_inicio"),rs.getString("data_fim"),rs.getString("horario_inicio"),rs.getString("horario_termino"), rs.getString("responsavel"), rs.getString("reserva_para"),rs.getBoolean("evento_privado"),rs.getString("email"), rs.getString("telefone"),rs.getString("obs"));
//			lista.add(reserva);
//		}
//		
//		st.close();
//		
//		return lista;
//	}
}