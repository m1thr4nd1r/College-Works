package br.com.ufba.roomsmanageradmin.model;

public class Area {
	private String nome;
	private int id;
	public String getNome() {
		return nome;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public Area(String nome, int id) {
		super();
		this.nome = nome;
		this.id = id;
	}
	public Area() {
		super();
	}
	
	
}
