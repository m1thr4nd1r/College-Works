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

@ManagedBean (name = "UsuarioBean")
public class UsuarioBean implements Serializable{
		
	private Usuario usuario = new Usuario();
	private List usuarios; 
	private boolean tipo;
		
	public Usuario getUsuario() {
		return usuario;
	}
	
	public void setTipo(boolean tipo)
	{
		this.tipo = tipo;
	}
	
	public boolean getTipo()
	{
		return tipo;
	}

	public void setUsuario(Usuario usuario) {
		this.usuario = usuario;
	}

	public List getUsuarios(){
		 
		return this.usuarios;
	}
	
	public String salvar(ActionEvent ae) throws ParseException
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
		return "create";
	}
}