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
import com.dao.UsuarioDAO;

@ManagedBean
public class UsuarioBean implements Serializable{
		
	private Usuario usuario = new Usuario();
	private UsuarioDAO userDAO = new UsuarioDAO();
	private List usuarios; 
	private String url;
		
	public Usuario getUsuario() {
		return usuario;
	}
	
	public void setUsuario(Usuario usuario) {
		this.usuario = usuario;
	}

	public List getUsuarios()
	{
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
        try {
            userDAO.salva(usuario);
            return "index";
        } catch (SQLException e) {
    		System.out.println("ERRO: "+e.getMessage());
            e.printStackTrace();
        }
	    return "reserva";
	}

	public String viewLink()
    {
        this.usuario = new Usuario();
        this.usuario.setEmail(url);
        return "view?" + this.url + "?faces-redirect=true";
	}
    
    public String updateLink()
    {
        this.usuario = new Usuario();
        this.usuario.setEmail(url);
        return "update?" + this.url + "?faces-redirect=true";
	}
    
    public void deletar()
    {
        System.out.println("Vai deletar no futuro");
    }
}