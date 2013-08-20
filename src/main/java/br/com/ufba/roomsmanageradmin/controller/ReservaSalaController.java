package br.com.ufba.roomsmanageradmin.controller;

import java.awt.event.ActionEvent;
import java.util.Calendar;
import java.util.Date;
import java.util.List;

import javax.annotation.PostConstruct;
import javax.faces.application.FacesMessage;
import javax.faces.bean.ManagedBean;
import javax.faces.context.FacesContext;
import javax.faces.model.ListDataModel;
import javax.swing.JOptionPane;

import org.hibernate.HibernateException;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.primefaces.event.*;
import org.primefaces.model.*;

import br.com.ufba.roomsmanageradmin.dao.Hibernate;
import br.com.ufba.roomsmanageradmin.model.ReservaSala;
import br.com.ufba.roomsmanageradmin.model.Sala;
import br.com.ufba.roomsmanageradmin.model.Usuario;

@ManagedBean
public class ReservaSalaController {
	
	private ScheduleModel eventModel;  
    
    private ScheduleEvent event = new DefaultScheduleEvent();  
  
	@PostConstruct
	void init(){  
		
		eventModel = new DefaultScheduleModel();
		
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();

	    List<ReservaSala> l = (List<ReservaSala>) session.createQuery("FROM ReservaSala").list();
	    for (ReservaSala reservaSala : l) {
	    	Date dataI = (Date)reservaSala.getDataInicio();
	    	Date dataF = (Date)reservaSala.getDataFim();
	    	Sala sala = reservaSala.getSala();
	    	if(!sala.getTipo().toLowerCase().equals("laboratorio")){
	    		eventModel.addEvent(new DefaultScheduleEvent(sala.getNome()+" - "+reservaSala.getResponsavel()+": "+reservaSala.getReservadoPara(),dataI,dataF));
	    	}
		}
	    session.close();
	    
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
      
    public void addEvent(){
    	JOptionPane.showMessageDialog(null,event.getId()+" title2: "+event.getTitle());
    	if(event.getId() == null)  
            eventModel.addEvent(event);  
        else  
            eventModel.updateEvent(event);  
          
        event = new DefaultScheduleEvent();  
    }  
    
    public void addEvent(ActionEvent actionEvent){
    	JOptionPane.showMessageDialog(null,event.getId()+" title: "+event.getTitle());
    	if(event.getId() == null)  
            eventModel.addEvent(event);  
        else  
            eventModel.updateEvent(event);  
          
        this.event = new DefaultScheduleEvent();
    }
    
    public void onEventSelect(SelectEvent selectEvent) {
    	JOptionPane.showMessageDialog(null,"SELECT EVENT "+((Date)selectEvent.getObject()));
    	this.event = (ScheduleEvent) selectEvent.getObject();
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
}
