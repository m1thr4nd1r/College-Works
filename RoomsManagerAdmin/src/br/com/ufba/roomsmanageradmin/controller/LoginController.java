package br.com.ufba.roomsmanageradmin.controller;

import java.io.*;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.swing.JOptionPane;

import br.com.ufba.roomsmanageradmin.model.Login;

public class LoginController extends HttpServlet{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private HttpSession session;
	
	public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException{
		PrintWriter out = response.getWriter();
		
		String user = request.getParameter("username");
		String senha = request.getParameter("senha");
		
		Login login = new Login(user,senha);
		session = request.getSession(true);
		
		if(login.validate()){
			session.setAttribute("logado", user);
		}
		else{
			JOptionPane.showMessageDialog(null, "Credenciais incorretas.");
		}
		
		out.println("<script>location.href='"+request.getRequestURL()+"/../index.jsp';</script>");
	}
	
	public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException{
		PrintWriter out = response.getWriter();
		session = request.getSession();
		int conf = JOptionPane.showConfirmDialog(null,"Deseja sair do sistema ?","RoomsManager",JOptionPane.YES_NO_OPTION,JOptionPane.QUESTION_MESSAGE);
		
		if(conf == 0){
			session.invalidate();
			out.println("<script>location.href='"+request.getRequestURL()+"/../index.jsp';</script>");
		}
		else{
			out.println("<script>window.history.back()</script>");
		}
		
	}
	
}
