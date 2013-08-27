package br.com.ufba.roomsmanageradmin.model;

import java.io.Serializable;

@SuppressWarnings("serial")
public class Tipo implements Serializable{
	
	private String descricao;
	private int id;
	
	public Tipo(){
		
	}
	
	public Tipo(String descricao){
		this.descricao = descricao;
	}
	
	public Tipo(int id, String descricao){
		this.id = id;
		this.descricao = descricao;		
	}

	public String getDescricao() {
		return this.descricao;
	}

	public void setDescricao(String descricao) {
		this.descricao = descricao;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}
}