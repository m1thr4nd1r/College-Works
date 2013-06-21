package com.dao;

import java.sql.Connection;  
import java.sql.DriverManager;  
 
public class Conexao {    
   
	private static Conexao instance;
	private Connection con;

	public Connection getCon() {
		return con;
	}

	public void setCon(Connection con) {
		this.con = con;
	}

	private Conexao() {
		this.execute();
	}

	public static Conexao getInstance() {
	    if (instance == null)
	         instance = new Conexao();
	    return instance;
	}
	
	
    private Connection execute() {  
        try {  
        	/** Configuração para banco de dados MySQL
        	 * 
        	 *	String url = "jdbc:mysql://localhost:3306/roomsmanager";
        	 *
        	 *	Configuração para banco de dados PostgreSQL
        	 **/
            String url = "jdbc:postgresql://localhost:5432/roomsmanager";  
            String usuario = "postgres";  
            String senha = "123";  
  
            Class.forName("org.postgresql.Driver");           
  
            this.setCon(DriverManager.getConnection(url, usuario, senha));  
  
            System.out.println("Conexão realizada com sucesso.");      
            
             
        } catch (Exception e) {  
             e.printStackTrace();  
        }
        
		return con;  
    }  
}  


