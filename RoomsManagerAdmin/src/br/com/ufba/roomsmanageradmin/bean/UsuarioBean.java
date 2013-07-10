package br.com.ufba.roomsmanageradmin.bean;

import java.io.Serializable;
import java.sql.SQLException;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.List;

import javax.faces.bean.ManagedBean;
import javax.faces.event.ActionEvent;

import br.com.ufba.roomsmanageradmin.dao.CadastraUsuarioDAO;
import br.com.ufba.roomsmanageradmin.model.Usuario;

@ManagedBean
public class UsuarioBean implements Serializable{
		
	private CadastraUsuarioDAO userDAO = new CadastraUsuarioDAO();
	private String nome, senha, email, username, num_cadastro, tipo;
	private Usuario user = new Usuario();
//	private static List<Usuario> usuarios =  new ArrayList<Usuario>(); 	
	
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
	
//	public static List<Usuario> getUsuarios() {
//		return usuarios;
//	}

	public String create()
	{
		Usuario user = new Usuario();
		
		user.setEmail(this.email);
		user.setNome(this.nome);
		user.setSenha(this.senha);
		user.setUser(this.username);
		user.setNum_cadastro(Integer.valueOf(this.num_cadastro));
		user.setTipo((this.tipo == "1")? true : false);
		
//		usuarios.add(user);
		
		System.out.println(this.nome + "Cadastrado");
		
		return "list?faces-redirect=true";
	}
	
	public String salvar(ActionEvent ae) throws ParseException
	{
		try	{
				Usuario user = new Usuario();
				
				user.setEmail(this.email);
				user.setNome(this.nome);
				user.setSenha(this.senha);
				user.setUser(this.username);
				user.setNum_cadastro(Integer.valueOf(this.num_cadastro));
				user.setTipo((this.tipo == "1")? true : false);
				
				userDAO.salva(user);
				
				return "index";
			
			} catch (SQLException e) {
				System.out.println("ERRO: "+e.getMessage());
				e.printStackTrace();
			}
		
		return "reserva";
	}
}