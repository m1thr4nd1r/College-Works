package br.com.ufba.roomsmanageradmin.model;

import java.io.Serializable;

public class Acesso implements Serializable{
	private int id;
	private int pessoa_id;
	private int setor_id;
	
	public Acesso() {
		super();
	}
	
	public Acesso(int id, int pessoa_id, int setor_id) {
		super();
		this.id = id;
		this.pessoa_id = pessoa_id;
		this.setor_id = setor_id;
	}

	public Acesso(int pessoa_id, int setor_id) {
		super();
		this.pessoa_id = pessoa_id;
		this.setor_id = setor_id;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public int getPessoa_id() {
		return pessoa_id;
	}

	public void setPessoa_id(int pessoa_id) {
		this.pessoa_id = pessoa_id;
	}

	public int getSetor_id() {
		return setor_id;
	}

	public void setSetor_id(int setor_id) {
		this.setor_id = setor_id;
	}
	
	@Override
	public String toString(){
		return  "ID: "+this.id+"\n"+
				"SETOR_ID: "+this.setor_id+"\n"+
				"PESSOA_ID: "+this.pessoa_id;
	}
		
}
