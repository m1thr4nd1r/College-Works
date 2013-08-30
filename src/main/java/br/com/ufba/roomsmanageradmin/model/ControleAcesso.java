package br.com.ufba.roomsmanageradmin.model;

import java.io.Serializable;
import java.util.Date;

public class ControleAcesso implements Serializable {
	private int 	id;
	private Usuario pessoa; 
	private Sala 	sala;
	private Date 	horaEntrada, dataEntrada, horaSaida, dataSaida;
	private boolean eChave;
	
	public ControleAcesso() {
		super();
	}

	public ControleAcesso(Sala sala, Date horaEntrada, Date dataEntrada,
			Date horaSaida, Date dataSaida, boolean eChave) {
		super();
		this.sala = sala;
		this.horaEntrada = horaEntrada;
		this.dataEntrada = dataEntrada;
		this.horaSaida = horaSaida;
		this.dataSaida = dataSaida;
		this.eChave = eChave;
	}

	public ControleAcesso(int id, Usuario pessoa, Sala sala, Date horaEntrada,
			Date dataEntrada, Date horaSaida, Date dataSaida, boolean eChave) {
		super();
		this.id = id;
		this.pessoa = pessoa;
		this.sala = sala;
		this.horaEntrada = horaEntrada;
		this.dataEntrada = dataEntrada;
		this.horaSaida = horaSaida;
		this.dataSaida = dataSaida;
		this.eChave = eChave;
	}
	public ControleAcesso(Usuario pessoa, Sala sala, Date horaEntrada,
			Date dataEntrada, Date horaSaida, Date dataSaida, boolean eChave) {
		super();
		this.pessoa = pessoa;
		this.sala = sala;
		this.horaEntrada = horaEntrada;
		this.dataEntrada = dataEntrada;
		this.horaSaida = horaSaida;
		this.dataSaida = dataSaida;
		this.eChave = eChave;
	}
	public ControleAcesso(Usuario pessoa, Sala sala, Date horaEntrada,
			Date dataEntrada, Date horaSaida, Date dataSaida) {
		super();
		this.pessoa = pessoa;
		this.sala = sala;
		this.horaEntrada = horaEntrada;
		this.dataEntrada = dataEntrada;
		this.horaSaida = horaSaida;
		this.dataSaida = dataSaida;
	}
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public Usuario getPessoa() {
		return pessoa;
	}
	public void setPessoa(Usuario pessoa) {
		this.pessoa = pessoa;
	}
	public Sala getSala() {
		return sala;
	}
	public void setSala(Sala sala) {
		this.sala = sala;
	}
	public Date getHoraEntrada() {
		return horaEntrada;
	}
	public void setHoraEntrada(Date horaEntrada) {
		this.horaEntrada = horaEntrada;
	}
	public Date getDataEntrada() {
		return dataEntrada;
	}
	public void setDataEntrada(Date dataEntrada) {
		this.dataEntrada = dataEntrada;
	}
	public Date getHoraSaida() {
		return horaSaida;
	}
	public void setHoraSaida(Date horaSaida) {
		this.horaSaida = horaSaida;
	}
	public Date getDataSaida() {
		return dataSaida;
	}
	public void setDataSaida(Date dataSaida) {
		this.dataSaida = dataSaida;
	}
	public boolean iseChave() {
		return eChave;
	}
	public void seteChave(boolean eChave) {
		this.eChave = eChave;
	}
	
	@Override
	public String toString(){
		return  "ID: "+this.id+"\n"+
				"DEntrada: "+this.dataEntrada+"\n"+
				"DSaida: "+this.dataSaida+"\n"+
				"HEntrada: "+this.horaEntrada+"\n"+
				"HSaida: "+this.horaSaida+"\n"+
				"Pessoa: "+this.pessoa+"\n"+
				"Sala: "+this.sala+"\n"+
				"Chave Entregue: "+this.eChave;
	}
}
