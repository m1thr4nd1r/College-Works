package br.com.ufba.roomsmanageradmin.model;

import java.io.Serializable;
import java.util.Date;

public class ControleAcesso implements Serializable {
	private int id;
	private int pessoaId, salaId;
	private Date horaEntrada, dataEntrada, horaSaida, dataSaida;
	public ControleAcesso(int id, int pessoaId, int salaId, Date horaEntrada,
			Date dataEntrada, Date horaSaida, Date dataSaida) {
		super();
		this.id = id;
		this.pessoaId = pessoaId;
		this.salaId = salaId;
		this.horaEntrada = horaEntrada;
		this.dataEntrada = dataEntrada;
		this.horaSaida = horaSaida;
		this.dataSaida = dataSaida;
	}
	public ControleAcesso(int pessoaId, int salaId, Date horaEntrada,
			Date dataEntrada, Date horaSaida, Date dataSaida) {
		super();
		this.pessoaId = pessoaId;
		this.salaId = salaId;
		this.horaEntrada = horaEntrada;
		this.dataEntrada = dataEntrada;
		this.horaSaida = horaSaida;
		this.dataSaida = dataSaida;
	}
	public ControleAcesso() {
		super();
	}
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public int getPessoaId() {
		return pessoaId;
	}
	public void setPessoaId(int pessoaId) {
		this.pessoaId = pessoaId;
	}
	public int getSalaId() {
		return salaId;
	}
	public void setSalaId(int salaId) {
		this.salaId = salaId;
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
	
	
}
