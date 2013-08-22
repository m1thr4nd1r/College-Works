package br.com.ufba.roomsmanageradmin.services;

import java.sql.SQLException;
import java.util.*;

import javax.swing.JOptionPane;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;

import org.hibernate.HibernateException;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;

// import br.com.ufba.roomsmanageradmin.dao.ReservaSalaDAO;
import br.com.ufba.roomsmanageradmin.dao.Hibernate;
import br.com.ufba.roomsmanageradmin.model.Sala;
import br.com.ufba.roomsmanageradmin.model.ReservaSala;

@Path("/reservas/{data}")
@Produces(MediaType.APPLICATION_JSON)
public class ReservaSalaService {

	@GET
	public ReservaSala [] get(@PathParam("data") String data){
		// ReservaSalaDAO dao = new ReservaSalaDAO();
		ReservaSala [] reservas = null;
		try {
			// List lista = dao.getReservas(data);
			SessionFactory sf = Hibernate.getSessionFactory();
	    	Session session = sf.openSession();

	    	List<ReservaSala> lista = (List<ReservaSala>) session.createQuery("FROM ReservaSala").list();
			reservas = new ReservaSala[lista.size()];
			int i = 0;
			for (ReservaSala reserva : (List<ReservaSala>) session.createQuery("FROM ReservaSala").list()) {
				reservas[i] = reserva;
				i++;
			}
		} catch (HibernateException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return reservas;
	}
}