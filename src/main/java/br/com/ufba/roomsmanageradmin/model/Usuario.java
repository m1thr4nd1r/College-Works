package br.com.ufba.roomsmanageradmin.model;

public class Usuario {
	
	private int num_matricula, id, tipo_id;
	private String nome, senha, email;
	
	public Usuario()
	{
	}

	public Usuario(String email, String senha, String nome, int num_matricula, int tipo_id)
	{
		this.email = email;
		this.senha = senha;
		this.nome = nome;
		this.num_matricula = num_matricula;
		this.tipo_id = tipo_id;
		this.id = 0;
	}
	
	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
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
		
	public int getNum_matricula() {
		return num_matricula;
	}

	public void setNum_matricula(int num_matricula) {
		this.num_matricula = num_matricula;
	}

	public int getTipo_id() {
		return tipo_id;
	}

	public void setTipo_id(int tipo_id) {
		this.tipo_id = tipo_id;
	}

	@Override
	public String toString()
	{
		return  "ID: "+this.id+"\n"+
				"NUM. CADASTRO: "+this.num_matricula+"\n"+
				"EMAIL: "+this.email+"\n"+
				"NOME: "+this.nome;
	}
}
