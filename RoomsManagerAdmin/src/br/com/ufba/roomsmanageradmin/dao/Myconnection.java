package br.com.ufba.roomsmanageradmin.dao;

import java.sql.*;

import javax.swing.JOptionPane;
/**
 *
 */ 
public class Myconnection{

    private static Connection connection = null;
    
    public static Statement getStatement() throws SQLException
    {
    	 System.out.println("Chegou!");
        if(connection == null){
            String url = "jdbc:mysql://localhost:3306/roomsManager_development";
            String usuario = "root";  
            String senha   = "123456";  
            try
            {
            	Class.forName("com.mysql.jdbc.Driver");        
                connection = DriverManager.getConnection(url, usuario, senha);
                System.out.println("Conectado!");
            } 
            catch(Exception e){
            	JOptionPane.showMessageDialog(null,"FALHA NA CONEXÃO: "+e.toString()); 
            }
        }
        return connection.createStatement();
    }
    
    public Connection getConnection(){  
       try{  
          Class.forName("com.mysql.jdbc.Driver").newInstance();  
          String driver = "jdbc:mysql://localhost:3306/roomsManager_development";  
          Connection con = DriverManager.getConnection(driver,"root","123");   
          return con;  
        }  
        catch(Exception e){  
            e.printStackTrace();  
        }  
        return null;  
    }  
    
}
