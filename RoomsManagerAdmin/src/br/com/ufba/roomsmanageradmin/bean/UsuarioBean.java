package br.com.ufba.roomsmanageradmin.bean;

import java.io.Serializable;
import java.sql.SQLException;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.List;

import javax.faces.bean.ManagedBean;
import javax.faces.event.ActionEvent;
import javax.swing.JOptionPane;

import br.com.ufba.roomsmanageradmin.dao.CadastraUsuarioDAO;
import br.com.ufba.roomsmanageradmin.model.Usuario;

@ManagedBean
public class UsuarioBean implements Serializable{
		
	private CadastraUsuarioDAO userDAO = new CadastraUsuarioDAO();
	private Usuario usuario = new Usuario();
	private List usuarios; 
		
	public Usuario getUsuario() {
		return usuario;
	}

	public void setUsuario(Usuario usuario) {
		this.usuario = usuario;
	}

	public List getUsuarios(){
		
		try {
			this.usuarios = userDAO.getUsuarios();
		} catch (SQLException e) {
			JOptionPane.showMessageDialog(null,"GETUSERS ERRO: "+e.getMessage());
			e.printStackTrace();
		}
		 
		return this.usuarios;
	}
	
	public String salvar(ActionEvent ae) throws ParseException
	{
		try	{
				userDAO.salva(usuario);
				
				return "index";
			
			} catch (SQLException e) {
				System.out.println("ERRO: "+e.getMessage());
				e.printStackTrace();
			}
		
		return "reserva";
	}
}