package br.com.ufba.roomsmanageradmin.controller;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.swing.JOptionPane;

import br.com.ufba.roomsmanageradmin.model.Login;

public class SiteController  extends HttpServlet{
	
	private HttpSession session;
	
	public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException{
		PrintWriter out = response.getWriter();
		
		session = request.getSession();
		String nome = (String) session.getAttribute("nome");
		
		if(nome.isEmpty()){
			out.println("<script>location.href='index.html';</script>");
		}
		
		out.println("<script>location.href='sala/reserva/lista.do';</script>");
	}

}
