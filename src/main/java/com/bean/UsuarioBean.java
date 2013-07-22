package com.bean;

import java.io.Serializable;
import java.sql.SQLException;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.List;

import javax.faces.bean.ManagedBean;
import javax.faces.event.ActionEvent;
import javax.swing.JOptionPane;

import com.model.Usuario;

@ManagedBean
public class UsuarioBean implements Serializable{
		
	private Usuario usuario = new Usuario();
	private List usuarios; 
		
	public Usuario getUsuario() {
		return usuario;
	}

	public void setUsuario(Usuario usuario) {
		this.usuario = usuario;
	}

	public List getUsuarios(){
		 
		return this.usuarios;
	}
	
	public String salvar(ActionEvent ae) throws ParseException
//	public String salvar()
	{
//		try	{
//				userDAO.salva(usuario);
//				
//				return "index";
//			
//			} catch (SQLException e) {
//				System.out.println("ERRO: "+e.getMessage());
//				e.printStackTrace();
//			}
//		
		return "reserva";
	}
}