package br.com.ufba.roomsmanageradmin.services;

import java.sql.SQLException;
import java.util.List;

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;

import org.hibernate.HibernateException;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;

// import br.com.ufba.roomsmanageradmin.dao.SalaDAO;
import br.com.ufba.roomsmanageradmin.model.Sala;
import br.com.ufba.roomsmanageradmin.dao.Hibernate;

@Path("/salas")
@Produces(MediaType.APPLICATION_JSON)
public class SalaService {
	
	@GET
	public String [][] get(){
		// SalaDAO dao = new SalaDAO();
		String [][] salas = null;
		List<Sala> lista;
		
		try {
			SessionFactory sf = Hibernate.getSessionFactory();
	    	Session session = sf.openSession();
	    	lista = (List<Sala>) session.createQuery("FROM Sala").list();
			salas = new String[lista.size()][2];			
			int i = 0;
			for (Sala sala : lista){
				salas[i][0] = sala.getNome();
				salas[i][1] = sala.getTipo();
				i++;
			}

		} catch (HibernateException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return salas;
	}
}
