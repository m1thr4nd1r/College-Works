package br.com.ufba.roomsmanageradmin.model;

import javax.faces.application.FacesMessage;

public class Login {
	
	private String usuario;
	private String senha;

	public String getUsuario() {
		return usuario;
	}

	public void setUsuario(String usuario) {
		this.usuario = usuario;
	}

	public String getSenha() {
		return senha;
	}

	public void setSenha(String senha) {
		this.senha = senha;
	}

	public Login(String usuario, String senha) {
		super();
		this.usuario = usuario;
		this.senha = senha;
	}

	public Login() {
		super();
	}
	
	public boolean validate(){
        if(usuario != null  && usuario.equals("admin") && senha != null  && senha.equals("admin")) {  
            return true;
        }
        return false;
	}
	
	public String toString(){
		return usuario;
	}
}