package br.com.ufba.roomsmanageradmin.dao;

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
        // TODO code application logic here      	
        try {  
  
//            String url = "jdbc:postgresql://localhost:5432/";
            String url = "jdbc:mysql://localhost:3306/proufba";  
            String usuario = "postgres";  
            String senha = "123";  
  
//            Class.forName("org.postgresql.Driver");           
            Class.forName("com.mysql.jdbc.Driver").newInstance();  
            this.setCon(DriverManager.getConnection(url, usuario, senha));  
  
            System.out.println("Conexão realizada com sucesso.");      
            
             
        } catch (Exception e) {  
             e.printStackTrace();  
        }
        
		return con;  
    }  
}  


