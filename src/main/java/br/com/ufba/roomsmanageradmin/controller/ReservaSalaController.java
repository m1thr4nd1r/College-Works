
package br.com.ufba.roomsmanageradmin.controller;

import java.awt.event.ActionEvent;
import java.io.Serializable;
import java.nio.channels.*;
import java.sql.SQLException;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.List;
import java.util.Locale;

import javax.annotation.PostConstruct;
import javax.faces.application.FacesMessage;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import javax.faces.context.FacesContext;
import javax.faces.model.ListDataModel;
import javax.swing.JOptionPane;

import org.hibernate.HibernateException;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.criterion.Restrictions;
import org.primefaces.event.*;
import org.primefaces.model.*;

import br.com.ufba.roomsmanageradmin.dao.Hibernate;
import br.com.ufba.roomsmanageradmin.model.ReservaSala;
import br.com.ufba.roomsmanageradmin.model.Sala;

@ManagedBean
@SessionScoped
public class ReservaSalaController implements Serializable{
	
	private ScheduleModel eventModel;  
    private ReservaSala reserva,selecionado;
    private ScheduleEvent event = new DefaultScheduleEvent();  
	private List<Sala> salas;
	private String sala_id;
	private String ptBrFormat = "dd/MM/yyyy", enFormat = "yyyy-MM-dd", horaFormat = "HH:mm";
	private String labelAction = "Salvar";
	
	@PostConstruct
	void init(){  
		
		eventModel = new DefaultScheduleModel();	
		reserva = new ReservaSala();
		selecionado = new ReservaSala();
		
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();

	    List<ReservaSala> l = (List<ReservaSala>) session.createQuery("FROM ReservaSala").list();
	    for (ReservaSala reservaSala : l) {

	    	Sala sala = reservaSala.getSala();
	    	
	    	if(!sala.getTipo().toLowerCase().equals("laboratorio") && (reservaSala.getStatus() != 2))
	    	{
	    	
		    	/** ADD 0 formula encontrado para solucionar o Problema com '.0' na data **/
		    	Date dataI = pularData(0,0,0,0,0,(Date)reservaSala.getDataInicio());
		    	Date horaI = pularData(0,0,0,0,0,(Date)reservaSala.getHorarioInicio());
		    	
		    	Date dataF = pularData(0,0,0,0,0,(Date)reservaSala.getDataFim());
		    	Date horaF = pularData(0,0,0,0,0,(Date)reservaSala.getHorarioTermino());
		    	
	//		    	JOptionPane.showMessageDialog(null, "M1 "+mergeDateHour(dataI,horaI)+"\n"+
	//		    										"M2 "+mergeDateHour(dataF,horaF)
	//		    										);
		    	
				reservaSala.setDataInicio(pularData(0,0,1900,0,0,mergeDateHour(dataI,horaI)));
		    	reservaSala.setDataFim(pularData(0,0,1900,0,0,mergeDateHour(dataF, horaF)));
		    	
		    	//JOptionPane.showMessageDialog(null,"data "+d);
		    	
		    	DefaultScheduleEvent evento = new DefaultScheduleEvent(sala.getNome()+" - "+reservaSala.getResponsavel()+" "+reservaSala.getReservadoPara(),reservaSala.getDataInicio(),reservaSala.getDataFim());
		    	evento.setId(reservaSala.getId()+"");
		    	evento.setData(reservaSala.getId());
		    	
	    		if(reservaSala.getStatus() == 1)
	    		{
		    		evento.setStyleClass("style1");
		    	}
		    	else
		    	{
		    		evento.setStyleClass("style2");
		    	}
	
	    		eventModel.addEvent(evento);
	    	}
	    	
		}
	    session.close();
	    
    }  
	
	/********************************************************/

    public void addEvent(){
		
    	Date date = pularData(1,0,0,0,0,event.getEndDate());
		reserva.setAceito(true);
		
		//1900
		Date hora = reserva.getHorarioInicio();
		reserva.setDataInicio(mergeDateHour(pularData(0,0,1900,0,0, event.getStartDate()), hora));
		hora = reserva.getHorarioTermino();
		reserva.setDataFim(mergeDateHour(pularData(0,0,1900,0,0,event.getEndDate()), hora));
		
		Sala sala = new Sala();
		sala.setId(Integer.parseInt(sala_id));
		reserva.setSala(sala);
		
		if(reserva.getHorarioTermino().toString().trim().isEmpty())
		{
			reserva.setDataFim(event.getEndDate());
		}
		
    	//JOptionPane.showMessageDialog(null,reserva.toString());
    	SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    Transaction tx = null;
	    JOptionPane.showMessageDialog(null,reserva);
		try{
			
	    	tx = session.beginTransaction();
	    	session.saveOrUpdate(reserva); 
	    	tx.commit();
	    	
	    	String msg = (labelAction.equals("Salvar")) ? "Reserva adicionada com sucesso!" : "Reserva atualizado com sucesso!";
	    	FacesMessage mesg = new FacesMessage(FacesMessage.SEVERITY_INFO, "Reserva de sala",msg);
    	    addMessage(mesg);
	    	
	    	List<Sala> l = (List<Sala>) session.createQuery("FROM Sala WHERE id = "+reserva.getSala().getId()).list();
    		for (Sala s : l) {
				sala = s;
			}
    		
	    	if(event.getId() == null){
	    		eventModel.addEvent(new DefaultScheduleEvent(sala.getNome()+" - "+reserva.getResponsavel()+" "+reserva.getReservadoPara(),reserva.getDataInicio(),reserva.getDataFim()));
	    	}else{  
	            eventModel.updateEvent(event);  
	    	}
	    	
	        this.event = new DefaultScheduleEvent();
	        this.reserva = new ReservaSala();
	        
    	}catch (HibernateException e) {
    		JOptionPane.showMessageDialog(null,e.getMessage());
    		if (tx!=null) tx.rollback();
	    	e.printStackTrace(); 
    	}finally {
	    	session.close();
	    }
	    
    }
    
    public void onEventSelect(SelectEvent selectEvent) {
    	this.event = (ScheduleEvent) selectEvent.getObject();
    	this.reserva = getReserva(this.event);
	    this.reserva.setDataInicio(dateToFormat(this.reserva.getDataInicio(),ptBrFormat));
	    this.reserva.setDataFim(dateToFormat(this.reserva.getDataFim(),ptBrFormat));
	    this.labelAction = "Atualizar";
	}  
      
    public void onDateSelect(SelectEvent selectEvent) {
    	Date d = (Date) selectEvent.getObject();
    	this.reserva.setDataInicio(dateToFormat(d,ptBrFormat));
		this.event = new DefaultScheduleEvent("Novo Evento", (Date) selectEvent.getObject(), (Date) selectEvent.getObject());
		this.labelAction = "Salvar";
    }  
      
    public void onEventMove(ScheduleEntryMoveEvent event){
    	this.event = event.getScheduleEvent();
    	this.selecionado = getReserva(this.event);
    	this.selecionado.setDataInicio(dateToFormat(this.event.getStartDate(),enFormat));
    	this.selecionado.setDataFim(dateToFormat(this.event.getEndDate(),enFormat));
    	updateReserva("Reserva movida com Sucesso!");
    }  
      
    public void onEventResize(ScheduleEntryResizeEvent event) {  
    	this.event = event.getScheduleEvent();
    	this.selecionado = getReserva(this.event);
    	this.selecionado.setDataInicio(dateToFormat(this.event.getStartDate(),enFormat));
    	this.selecionado.setDataFim(dateToFormat(this.event.getEndDate(),enFormat));
    	this.selecionado.setHorarioInicio(dateToFormat(this.event.getStartDate(),horaFormat));
    	this.selecionado.setHorarioTermino(dateToFormat(this.event.getEndDate(),horaFormat));
    	updateReserva("Período da reserva modificado com Sucesso!");
    }  
      
    private void addMessage(FacesMessage message) {  
        FacesContext.getCurrentInstance().addMessage(null, message);  
    }
    
    /********************** FUNÇÕES AUXILIARES ************************/
    
    private void updateReserva(String messagem){

    	SessionFactory sf = Hibernate.getSessionFactory();
		Session session = sf.openSession();
		Transaction tx = null;
		
		try{
			tx = session.beginTransaction();
			session.update(this.selecionado);
			session.flush();
			tx.commit();

	    	FacesMessage message = new FacesMessage(FacesMessage.SEVERITY_INFO, "Reserva de Sala",messagem);          
	        addMessage(message);  
		}catch (HibernateException e) {
			if (tx!=null) tx.rollback();
				e.printStackTrace();
				JOptionPane.showMessageDialog(null,e.getMessage());
		}finally {
			session.close(); 
		}
		
    }
    /**
     * 
     * @param event 
     * @return a Reserva de Sala no qual o event representa
     */
    private ReservaSala getReserva(ScheduleEvent event){

		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    ReservaSala res = new ReservaSala();
	    
	    try
	    {
	    	for (ReservaSala rs : (List<ReservaSala>) session.createQuery("FROM ReservaSala WHERE id = "+event.getData().toString()).list()){
				res = rs;
			};
	    }
	    catch (HibernateException e)
	    {
			// TODO: handle exception
	    	e.printStackTrace();
	    	JOptionPane.showMessageDialog(null,e.getMessage());
		}
	    session.close();
	    
	    return res;
	    
    }
    
    /**
     * 
     * @param dias quantidade de dias 
     * @param meses quantidade de meses
     * @param anos quantidade de anos
     * @param horas quantidade de horas
     * @param mins quantidade de minutos
     * @param data que se deseja acrescentar ou substrair as quantidades de dias, meses, anos, horas, minutos
     * @return data com o acrescentar ou substrair das quantidades de dias, meses, anos, horas, minutos
     */
    private Date pularData(int dias,int meses, int anos, int horas, int mins, Date data){
    	GregorianCalendar c = new GregorianCalendar();    	
    	c.setTime(data);
		c.add(Calendar.DATE, dias);
		c.add(Calendar.MONTH, meses);
		c.add(Calendar.YEAR, anos);
		c.add(Calendar.HOUR, horas);
		c.add(Calendar.MINUTE, mins);
		c.add(Calendar.SECOND,0);
		return c.getTime();
    }
    
    private Date mergeDateHour(Date data, Date hora){
    	GregorianCalendar cal = new GregorianCalendar();
    	cal.set(Calendar.YEAR, data.getYear());
    	cal.set(Calendar.MONTH, data.getMonth());
    	cal.set(Calendar.DATE, data.getDate());
    	cal.set(Calendar.HOUR_OF_DAY,hora.getHours());
    	cal.set(Calendar.MINUTE,hora.getMinutes());
    	cal.set(Calendar.SECOND,hora.getSeconds());
    	return cal.getTime();
	}
	    
	public Date dateToFormat(Date data, String format){
    	SimpleDateFormat sdf = new SimpleDateFormat(format);

    	String d =  sdf.format(data);
    	sdf = new SimpleDateFormat(format,Locale.US);
    	
    	try {
			data = sdf.parse(d);
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			JOptionPane.showMessageDialog(null, "ERROR: dateToFormat "+e.getMessage());
		}
    	
    	return data;
	}
	
	/********************** GETS e SETS ************************/
	
	public String getSala_id() {
		return sala_id;
	}
	
	public void setSala_id(String sala_id) {
		this.sala_id = sala_id;
	}
	
	public List<Sala> getSalas(){
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    this.salas = (List<Sala>) session.createQuery("FROM Sala WHERE tipo <> 'Laboratorio'").list();
	    session.close();
		return salas;
	}

    public ScheduleModel getEventModel() {  
        return eventModel;  
    }  
        
    public ScheduleEvent getEvent() {  
        return event;  
    }  
  
    public void setEvent(ScheduleEvent event) {  
        this.event = event;  
    } 

    public ReservaSala getReserva() {
		return reserva;
	}

	public void setReserva(ReservaSala reserva) {
		this.reserva = reserva;
	}

	public ReservaSala getSelecionado() {
		return selecionado;
	}

	public void setSelecionado(ReservaSala selecionado) {
		this.selecionado = selecionado;
	}

	public String getLabelAction() {
		return labelAction;
	}

	public void setLabelAction(String labelAction) {
		this.labelAction = labelAction;
	}

}
