package br.com.ufba.roomsmanageradmin.model;

import java.io.Serializable;


@SuppressWarnings("serial")
public class Sala implements Serializable{
	
	private int id;
	private String  nome;
	private boolean quadro;
	private boolean	retroprojetor;
	private boolean multimidia;
	private String 	tipo;
	private boolean arcondicionado;
	private int 	computadores;
	private int 	capacidade;
	private int 	setor_id;
	
	public Sala(){
	
	}
	
	public Sala(String nome, boolean quadro, boolean retroprojetor,
			boolean multimidia, String tipo, boolean arcondicionado,
			int computadores, int capacidade, int setor_id) {
		super();
		this.nome = nome;
		this.quadro = quadro;
		this.retroprojetor = retroprojetor;
		this.multimidia = multimidia;
		this.tipo = tipo;
		this.arcondicionado = arcondicionado;
		this.computadores = computadores;
		this.capacidade = capacidade;
		this.setor_id = 1;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public boolean isQuadro() {
		return quadro;
	}
	public void setQuadro(boolean quadro) {
		this.quadro = quadro;
	}
	public int getSetor_id() {
		return setor_id;
	}
	public void setSetor_id(int setor_id) {
		this.setor_id = setor_id;
	}
	public String getNome() {
		return nome;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}
	public boolean isRetroprojetor() {
		return retroprojetor;
	}
	public void setRetroprojetor(boolean retroprojetor) {
		this.retroprojetor = retroprojetor;
	}
	public boolean isMultimidia() {
		return multimidia;
	}
	public void setMultimidia(boolean multimidia) {
		this.multimidia = multimidia;
	}
	public String getTipo() {
		return tipo;
	}
	public void setTipo(String tipo) {
		this.tipo = tipo;
	}
	public boolean isArcondicionado() {
		return arcondicionado;
	}
	public void setArcondicionado(boolean arcondicionado) {
		this.arcondicionado = arcondicionado;
	}
	public int getComputadores() {
		return computadores;
	}
	public void setComputadores(int computadores) {
		this.computadores = computadores;
	}
	public int getCapacidade() {
		return capacidade;
	}
	public void setCapacidade(int capacidade) {
		this.capacidade = capacidade;
	}
	
	

}
