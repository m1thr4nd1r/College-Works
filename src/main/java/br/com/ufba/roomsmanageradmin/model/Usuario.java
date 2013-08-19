package br.com.ufba.roomsmanageradmin.model;

public class Usuario {
	
	private int num_cadastro, id;
	private String nome, senha, email;
	private boolean tipo;
	
	public Usuario()
	{
//		this.nome = "";
//		this.senha = "";
//		this.email = "";
//		this.num_cadastro = 0;
//		this.id = 0;
//		this.tipo = false;
	}

	public Usuario(String email, String senha, String nome, int num_cadastro, boolean tipo)
	{
		this.email = email;
		this.senha = senha;
		this.nome = nome;
		this.num_cadastro = num_cadastro;
		this.tipo = tipo;
		this.id = 0;
	}
	
	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}
	
	
	public boolean getTipo() {
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
	
	@Override
	public String toString()
	{
		return this.num_cadastro+"";
	}
}
