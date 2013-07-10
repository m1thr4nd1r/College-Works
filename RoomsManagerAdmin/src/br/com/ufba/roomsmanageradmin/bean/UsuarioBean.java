package br.com.ufba.roomsmanageradmin.bean;

import java.util.ArrayList;
import java.util.List;

import javax.faces.application.FacesMessage;
import javax.faces.bean.ManagedBean;
import javax.faces.context.FacesContext;
import javax.faces.event.ActionEvent;

import br.com.ufba.roomsmanageradmin.model.Usuario;

@ManagedBean
public class UsuarioBean {
	
	private String nome, senha, email, username, num_cadastro, tipo;
	private static List<Usuario> users =  new ArrayList<Usuario>(); 	
	
	public String getTipo() {
		return tipo;
	}

	public void setTipo(String tipo) {
		this.tipo = tipo;
	}

	public String getEmail() {
		return email;
	}

	public void setEmail(String email) {
		this.email = email;
	}

	public String getUsername() {
		return username;
	}

	public void setUsername(String username) {
		this.username = username;
	}

	public String getSenha() {
		return senha;
	}

	public void setSenha(String senha) {
		this.senha = senha;
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public String getNum_cadastro() {
		return num_cadastro;
	}

	public void setNum_cadastro(String num_cadastro) {
		this.num_cadastro = num_cadastro;
	}
	
	public static List<Usuario> getUsers() {
		return users;
	}

	public void create(ActionEvent actionEvent)
	{
		Usuario user = new Usuario();
		
		user.setEmail(this.email);
		user.setNome(this.nome);
		user.setSenha(this.senha);
		user.setUser(this.username);
		user.setNum_cadastro(Integer.valueOf(this.num_cadastro));
		user.setTipo((this.tipo == "1")? true : false);
		
		users.add(user);
		
//		FacesContext context = FacesContext.getCurrentInstance();
//		
//		if (user.save())
//		    context.addMessage(null, new FacesMessage("Successful", this.nome + " cadastrado com Sucesso"));
//		else
//			context.addMessage(null, new FacesMessage("Successful", this.nome + " nao cadastrado"));
	}
}
