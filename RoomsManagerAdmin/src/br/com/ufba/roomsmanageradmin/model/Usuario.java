package br.com.ufba.roomsmanageradmin.model;

public class Usuario {
	
	private int num_cadastro;
	private String nome, senha, email, user;
	private boolean tipo;
	
	public Usuario()
	{
		this.nome = "";
		this.senha = "";
		this.email = "";
		this.user = "";
		this.tipo = false;
	}

	public boolean isAdmin() {
		return tipo;
	}

	public void setTipo(boolean tipo) {
		this.tipo = tipo;
	}

	public String getEmail() {
		return email;
	}

	public void setEmail(String email) {
		this.email = email;
	}

	public String getUser() {
		return user;
	}

	public void setUser(String user) {
		this.user = user;
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

	public int getNum_cadastro() {
		return num_cadastro;
	}

	public void setNum_cadastro(int num_cadastro) {
		this.num_cadastro = num_cadastro;
	}
	
	public boolean save()
	{
		System.out.println("Guardou " + this.nome + " no Banco");
		
		return true;
	}
}
