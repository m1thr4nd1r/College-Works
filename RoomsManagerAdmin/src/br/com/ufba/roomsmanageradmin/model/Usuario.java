package br.com.ufba.roomsmanageradmin.model;

public class Usuario {
	
	private int num_cadastro;
	private String nome, senha, email;
	private boolean tipo;
	
	public Usuario()
	{
		this.nome = "";
		this.senha = "";
		this.email = "";
		this.tipo = false;
	}

	public Usuario(String email, String senha, String nome, int num_cadastro, boolean tipo)
	{
		this.email = email;
		this.senha = senha;
		this.nome = nome;
		this.num_cadastro = num_cadastro;
		this.tipo = tipo;
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
	
	public String isAdmin()
	{
		if (this.tipo)
			return "Administrador";
		return	"Funcionario"; 
	}
}
