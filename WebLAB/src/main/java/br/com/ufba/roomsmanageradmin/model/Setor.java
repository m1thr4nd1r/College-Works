package br.com.ufba.roomsmanageradmin.model;

import java.io.Serializable;

@SuppressWarnings("serial")
public class Setor implements Serializable{
	
	private String nome;
	private String email;
	private int id;
	
	public Setor(){
		
	}
	
	public Setor(String nome, String email){
		
		this.nome = nome;
		this.email = email;
		
	}
	
	public Setor(int id, String nome, String email){
		this.id = id;
		this.nome = nome;
		this.email = email;
		
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public String getEmail() {
		return email;
	}

	public void setEmail(String email) {
		this.email = email;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

}
