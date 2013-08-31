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

import br.com.ufba.roomsmanageradmin.dao.*;
import br.com.ufba.roomsmanageradmin.model.*;

@Path("/laboratorios")
@Produces(MediaType.APPLICATION_JSON)
public class LabService {

	@GET
	public ControleAcesso [] get(){
		SalaDAO dao = new SalaDAO();
		ControleAcesso [] reservas = null;
		try {

			List <ControleAcesso>lista = (List<ControleAcesso>) dao.getLabsReservados();
			reservas = new ControleAcesso[lista.size()];
			int i = 0;
			for (ControleAcesso ctr : lista){
				reservas[i] = ctr;
				i++;
			}

		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return reservas;
	}
	
}