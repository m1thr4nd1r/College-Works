package br.com.ufba.roomsmanageradmin.controller;

import java.io.*;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.swing.JOptionPane;

import br.com.ufba.roomsmanageradmin.model.Login;

public class LoginController extends HttpServlet{
	
	private HttpSession session;
	
	public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException{
		PrintWriter out = response.getWriter();
		
		String user = request.getParameter("username");
		String senha = request.getParameter("senha");
		
		Login login = new Login(user,senha);
		session = request.getSession(true);
		
		if(login.validate()){
			session.setAttribute("nome", user);
			out.println("<script>location.href='site';</script>");
			return;
		}
		
		JOptionPane.showMessageDialog(null, "Credenciais incorretas.");
		out.println("<script>location.href='index.html';</script>");
	}
}
