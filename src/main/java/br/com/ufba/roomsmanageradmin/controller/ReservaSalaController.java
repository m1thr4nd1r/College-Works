package br.com.ufba.roomsmanageradmin.controller;

import java.awt.event.ActionEvent;
import java.io.Serializable;
import java.nio.channels.SeekableByteChannel;
import java.sql.SQLException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.List;

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

import br.com.ufba.roomsmanageradmin.model.*;
import br.com.ufba.roomsmanageradmin.dao.*;

@ManagedBean
@SessionScoped
public class ReservaSalaController implements Serializable{
	
	private ScheduleModel eventModel;  
    private ReservaSala reserva,selecionado;
    private ScheduleEvent event = new DefaultScheduleEvent();  
	private List<Sala> salas;
	private String sala_id;
	
	@PostConstruct
	void init(){  
		
		eventModel = new DefaultScheduleModel();	
		reserva = new ReservaSala();
		selecionado = new ReservaSala();
		
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();

	    List<ReservaSala> l = (List<ReservaSala>) session.createQuery("FROM ReservaSala").list();
	    for (ReservaSala reservaSala : l) {
	    	
	    	Date dataI = (Date)reservaSala.getDataInicio();
	    	Date horaI = reservaSala.getHorarioInicio();
	    	/*
	    	 * BUG no Framework a data de fim não é incluída
	    	 */
	    	Date dataF = addDay(1,(Date)reservaSala.getDataFim());
	    	Date horaF = reservaSala.getHorarioTermino();
//	    	JOptionPane.showMessageDialog(null,"#"+dataI+"\n#"+dataF);
	    	
	    	Sala sala = reservaSala.getSala();
	    	SimpleDateFormat sdf = new SimpleDateFormat("dd/mm/yyyy");
	    	
	    	try {
				reservaSala.setDataInicio(mergeDateHour(sdf.parse(dataI.toString()),horaI));
		    	reservaSala.setDataFim(mergeDateHour(sdf.parse(dataF.toString()), horaF));
			} catch (ParseException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
	    	
	    	//JOptionPane.showMessageDialog(null,reservaSala.toString());
	    	DefaultScheduleEvent evento = new DefaultScheduleEvent(reservaSala.getId()+". "+sala.getNome()+" - "+reservaSala.getResponsavel()+" "+reservaSala.getReservadoPara(),reservaSala.getDataInicio(),reservaSala.getDataFim());
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

	/********************************************************/
    
	public void aceitaReserva(){
		JOptionPane.showMessageDialog(null,selecionado.getId());
    }
    
	public void recusaReserva(){
		JOptionPane.showMessageDialog(null,selecionado.getId());
    }
    
    public void addEvent(){
		
    	Date date = addDay(1,event.getEndDate());
		reserva.setAceito(true);
		Date hora = reserva.getHorarioInicio();
		//1900
		reserva.setDataInicio(mergeDateHour(addYear(1900, event.getStartDate()), hora));
		hora = reserva.getHorarioTermino();
		reserva.setDataFim(mergeDateHour(addYear(1900,event.getEndDate()), hora));
		
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
    	
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    ReservaSala res = new ReservaSala();
	    
	    try
	    {
	    	for (ReservaSala rs : (List<ReservaSala>) session.createQuery("FROM ReservaSala WHERE id = "+this.event.getData().toString()).list()){
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
	    this.selecionado = res;
    	//JOptionPane.showMessageDialog(null,"SELECT EVENT\n"+event+"\n#"+event.getId()+"\n"+res.toString());
    	
	}  
      
    public void onDateSelect(SelectEvent selectEvent) {  
		this.event = new DefaultScheduleEvent("Novo Evento", (Date) selectEvent.getObject(), (Date) selectEvent.getObject());
    }  
      
    public void onEventMove(ScheduleEntryMoveEvent event) {  
        FacesMessage message = new FacesMessage(FacesMessage.SEVERITY_INFO, "Event moved", "Day delta:" + event.getDayDelta() + ", Minute delta:" + event.getMinuteDelta());          
        addMessage(message);  
    }  
      
    public void onEventResize(ScheduleEntryResizeEvent event) {  
        FacesMessage message = new FacesMessage(FacesMessage.SEVERITY_INFO, "Event resized", "Day delta:" + event.getDayDelta() + ", Minute delta:" + event.getMinuteDelta());  
        addMessage(message);  
    }  
      
    private void addMessage(FacesMessage message) {  
        FacesContext.getCurrentInstance().addMessage(null, message);  
    }
    
    /********************************************************/
    
    private Date addDay(int dias,Date data){
    	GregorianCalendar c = new GregorianCalendar();    	
    	c.setTime(data);
		c.add(Calendar.DATE, dias);
		return c.getTime();
    }

    private Date addYear(int ano,Date data){
    	GregorianCalendar c = new GregorianCalendar();    	
    	c.setTime(data);
		c.add(Calendar.YEAR, ano);
		return c.getTime();
    }
    
	public String getData(String data){
		
		String dt = "";
		
		if(data != null && !data.isEmpty()){
			String [] str = data.split(" ");
			
			int mes = mesToInt(str[1].toLowerCase());
			
			String m = (mes < 10) ? "0"+mes : mes+"";
			dt += str[str.length-1]+"-"+m+"-"+str[2];
		}
		return dt;
	}
	
	public String getHora(String data){
		String h = "";
		
		if(data != null && !data.isEmpty()){
			String [] str = data.split(" ");
			
			h = str[3];
		}
		
		return h;
	}
	
	public int mesToInt(String mes){
		int m = -1;
		
		String [] meses = {"jan","feb","mar","apr","may","jun","jul","aug","sep","oct","nov","dec"};
		
		for(int i = 0; i < meses.length; i++) {
			if(meses[i].equals(mes)){
				return (i+1);
			}
		}
		
		return m;
	}

	private Date mergeDateHour(Date data, Date hora){

    	GregorianCalendar cal = new GregorianCalendar();
    	cal.set(Calendar.YEAR, data.getYear());
    	cal.set(Calendar.MONTH, data.getMonth());
    	cal.set(Calendar.DATE, data.getDate());
    	cal.set(Calendar.HOUR_OF_DAY,hora.getHours());
    	cal.set(Calendar.MINUTE,hora.getMinutes());
    	cal.set(Calendar.SECOND,hora.getSeconds());
    	JOptionPane.showMessageDialog(null,cal.getTime());
    	return cal.getTime();
    	
	}
	
}
