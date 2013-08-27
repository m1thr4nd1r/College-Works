
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

import br.com.ufba.roomsmanageradmin.dao.*;
import br.com.ufba.roomsmanageradmin.model.*;

@ManagedBean
@SessionScoped
public class ReservaSalaController implements Serializable{
	
	private ScheduleModel eventModel;  
    private ReservaSala reserva,selecionado;
    private ScheduleEvent event = new DefaultScheduleEvent();  
	private List<Sala> salas;
	private String sala_id;
	private String ptBrFormat = "dd/MM/yyyy";
	
	@PostConstruct
	void init(){  
		
		eventModel = new DefaultScheduleModel();	
		reserva = new ReservaSala();
		selecionado = new ReservaSala();
		
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();

	    List<ReservaSala> l = (List<ReservaSala>) session.createQuery("FROM ReservaSala").list();
	    for (ReservaSala reservaSala : l) {
	    		
	    	/** ADD 0 formula encontrado para solucionar o Problema com '.0' na data **/
	    	Date dataI = pularDay(0,(Date)reservaSala.getDataInicio());
	    	Date horaI = pularDay(0,(Date)reservaSala.getHorarioInicio());
	    	
	    	Date dataF = pularDay(0,(Date)reservaSala.getDataFim());
	    	Date horaF = pularDay(0,(Date)reservaSala.getHorarioTermino());
	    	
//	    	JOptionPane.showMessageDialog(null,"#"+dataI+"\n#"+dataF);
	    	Sala sala = reservaSala.getSala();
	    	
//		    	JOptionPane.showMessageDialog(null, "M1 "+mergeDateHour(dataI,horaI)+"\n"+
//		    										"M2 "+mergeDateHour(dataF,horaF)
//		    										);
	    	
				reservaSala.setDataInicio(pularYear(1900,mergeDateHour(dataI,horaI)));
		    	reservaSala.setDataFim(pularYear(1900,mergeDateHour(dataF, horaF)));
	    	
	    	//JOptionPane.showMessageDialog(null,"data "+d);
	    	
	    	DefaultScheduleEvent evento = new DefaultScheduleEvent(sala.getNome()+" - "+reservaSala.getResponsavel()+" "+reservaSala.getReservadoPara(),reservaSala.getDataInicio(),reservaSala.getDataFim());
	    	evento.setId(reservaSala.getId()+"");
	    	evento.setData(reservaSala.getId());
	    	
    		if(!sala.getTipo().toLowerCase().equals("laboratorio") && reservaSala.isAceito())
    		{
	    		evento.setStyleClass("style1");
	    	}
	    	else
	    	{
	    		evento.setStyleClass("style2");
	    	}

    		eventModel.addEvent(evento);
    		
		}
	    session.close();
	    
    }  
	
	/********************************************************/

	public void aceitaReserva(){
		JOptionPane.showMessageDialog(null,"ACEITA");
    }

	public void recusaReserva(){
		JOptionPane.showMessageDialog(null,"RECUSA");
    }

    public void addEvent(){
		
    	Date date = pularDay(1,event.getEndDate());
		reserva.setAceito(true);
		Date hora = reserva.getHorarioInicio();
		//1900
		reserva.setDataInicio(mergeDateHour(pularYear(1900, event.getStartDate()), hora));
		hora = reserva.getHorarioTermino();
		reserva.setDataFim(mergeDateHour(pularYear(1900,event.getEndDate()), hora));
		
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
	    
		try{
	    	tx = session.beginTransaction();
	    	session.saveOrUpdate(reserva); 
	    	tx.commit();
	    	
	    	List<Sala> l = (List<Sala>) session.createQuery("FROM Sala WHERE id = "+reserva.getSala().getId()).list();
    		
	    	for (Sala s : l) {
				sala = s;
			}
    		
	    	if(event.getId() == null){
	    		eventModel.addEvent(new DefaultScheduleEvent(sala.getNome()+" - "+reserva.getResponsavel()+": "+reserva.getReservadoPara(),reserva.getDataInicio(),reserva.getDataFim()));
	    		FacesMessage message = new FacesMessage(FacesMessage.SEVERITY_INFO, "Reserva adicionada com sucesso!","Reserva adicionada com sucesso!");
	    	    addMessage(message);  
	    	}else{  
	            eventModel.updateEvent(event);  
	    	}
	    	
	        this.event = new DefaultScheduleEvent();
	        this.reserva = new ReservaSala();
	        
    	}catch (HibernateException e) {
    		if (tx!=null) tx.rollback();
	    	e.printStackTrace(); 
    	}finally {
	    	session.close();
	    }
	    
    }
    
    public void onEventSelect(SelectEvent selectEvent) {
    	this.event = (ScheduleEvent) selectEvent.getObject();
    	this.selecionado = getReserva(this.event);
	    this.selecionado.setDataInicio(dateToformat(this.selecionado.getDataInicio(),ptBrFormat));
	    this.selecionado.setDataFim(dateToformat(this.selecionado.getDataFim(),ptBrFormat));
	}  
      
    public void onDateSelect(SelectEvent selectEvent) {
    	Date d = (Date) selectEvent.getObject();
    	//JOptionPane.showMessageDialog(null,"#3 "+dateToformat(d,ptBrFormat));
    	this.reserva.setDataInicio(dateToformat(d,ptBrFormat));
		this.event = new DefaultScheduleEvent("Novo Evento", (Date) selectEvent.getObject(), (Date) selectEvent.getObject());
    }  
      
    public void onEventMove(ScheduleEntryMoveEvent event) {
    	this.event = event.getScheduleEvent();
    	this.selecionado = getReserva(this.event);
    	
    	JOptionPane.showMessageDialog(null,this.selecionado.getDataInicio());
    	
    	Date d = pularDay(event.getDayDelta(),this.selecionado.getDataInicio());
    	JOptionPane.showMessageDialog(null,d);
	    this.selecionado.setDataInicio(dateToformat(d,ptBrFormat));
	    
    	d = pularDay(event.getDayDelta(),this.selecionado.getDataFim());
    	JOptionPane.showMessageDialog(null,d);
    	this.selecionado.setDataFim(dateToformat(d,ptBrFormat));
	    
    	FacesMessage message = new FacesMessage(FacesMessage.SEVERITY_INFO, "Event moved", "Day delta:" + event.getDayDelta() + ", Minute delta:" + event.getMinuteDelta()+"<br/>"+this.selecionado);          
        addMessage(message);  
    }  
      
    public void onEventResize(ScheduleEntryResizeEvent event) {  
        FacesMessage message = new FacesMessage(FacesMessage.SEVERITY_INFO, "Event resized", "Day delta:" + event.getDayDelta() + ", Minute delta:" + event.getMinuteDelta());  
        addMessage(message);  
    }  
      
    private void addMessage(FacesMessage message) {  
        FacesContext.getCurrentInstance().addMessage(null, message);  
    }
    
    /********************** FUNÇÕES AUXILIARES ************************/
    
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
     * @param INT dias: quantidade de dias que se deseja pular (> 0: dias posteriores, < 0: dias anteriores);
     * @param DATE data: a data servida como parâmetro para pular os dias.
     * @return data com a quantidade de dias pulados.
     */
    private Date pularDay(int dias,Date data){
    	GregorianCalendar c = new GregorianCalendar();    	
    	c.setTime(data);
		c.add(Calendar.DATE, dias);
		return c.getTime();
    }

    /**
     * 
     * @param INT ano: quantidade de anos que se deseja pular (> 0: anos posteriores, < 0: anos anteriores);
     * @param DATE data: a data servida como parâmetro para pular os anos.
     * @return data com a quantidade de anos pulados.
     * 
     */
    private Date pularYear(int ano,Date data){
    	GregorianCalendar c = new GregorianCalendar();    	
    	c.setTime(data);
		c.add(Calendar.YEAR, ano);
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
	    
	public Date dateToformat(Date data, String format){
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
	    this.salas = (List<Sala>) session.createQuery("FROM Sala").list();
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

}
