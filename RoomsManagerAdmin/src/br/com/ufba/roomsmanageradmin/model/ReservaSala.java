package br.com.ufba.roomsmanageradmin.model;

import java.util.Date;

public class ReservaSala {
	private int sala_id;
	private Date dataInicio;
	private Date dataFim;
	private Date horarioInicio;
	private Date horarioTermino;
	private String responsavel;
	private String reservadoPara;
	private boolean eventoPrivado;
	private String email;
	private String telefone;
	private String observacao;
	
	public ReservaSala() {
		super();
	}

	public ReservaSala(int sala_id, Date dataInicio, Date dataFim,
			Date horarioInicio, Date horarioTermino, String responsavel,
			String reservadoPara, boolean eventoPrivado, String email,
			String telefone, String observacao) {
		super();
		this.sala_id = sala_id;
		this.dataInicio = dataInicio;
		this.dataFim = dataFim;
		this.horarioInicio = horarioInicio;
		this.horarioTermino = horarioTermino;
		this.responsavel = responsavel;
		this.reservadoPara = reservadoPara;
		this.eventoPrivado = eventoPrivado;
		this.email = email;
		this.telefone = telefone;
		this.observacao = observacao;
	}

	public int getSala_id() {
		return sala_id;
	}

	public void setSala_id(int sala_id) {
		this.sala_id = sala_id;
	}

	public Date getDataInicio() {
		return dataInicio;
	}

	public void setDataInicio(Date dataInicio) {
		this.dataInicio = dataInicio;
	}

	public Date getDataFim() {
		return dataFim;
	}

	public void setDataFim(Date dataFim) {
		this.dataFim = dataFim;
	}

	public Date getHorarioInicio() {
		return horarioInicio;
	}

	public void setHorarioInicio(Date horarioInicio) {
		this.horarioInicio = horarioInicio;
	}

	public Date getHorarioTermino() {
		return horarioTermino;
	}

	public void setHorarioTermino(Date horarioTermino) {
		this.horarioTermino = horarioTermino;
	}

	public String getResponsavel() {
		return responsavel;
	}

	public void setResponsavel(String responsavel) {
		this.responsavel = responsavel;
	}

	public String getReservadoPara() {
		return reservadoPara;
	}

	public void setReservadoPara(String reservadoPara) {
		this.reservadoPara = reservadoPara;
	}

	public boolean isEventoPrivado() {
		return eventoPrivado;
	}

	public void setEventoPrivado(boolean eventoPrivado) {
		this.eventoPrivado = eventoPrivado;
	}

	public String getEmail() {
		return email;
	}

	public void setEmail(String email) {
		this.email = email;
	}

	public String getTelefone() {
		return telefone;
	}

	public void setTelefone(String telefone) {
		this.telefone = telefone;
	}

	public String getObservacao() {
		return observacao;
	}

	public void setObservacao(String observacao) {
		this.observacao = observacao;
	}
	
}
