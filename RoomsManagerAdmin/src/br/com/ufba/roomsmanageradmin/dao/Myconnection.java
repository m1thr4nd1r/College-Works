/*
 * Classe respons�vel pelo gerenciamento da conex�o com Banco
 * 
 */
package br.com.ufba.roomsmanageradmin.dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
/**
 *
 */ 
public class Myconnection{

    private static Connection connection = null;
    
    public static Statement getStatement() throws SQLException
    {
        
        if(connection == null){
            String url = "jdbc:mysql://localhost:3306/roomsManager_development";
            String usuario = "root";  
            String senha = "123";  
            try
            {
                Class.forName("com.mysql.jdbc.Driver");
//                Class.forName("org.postgresql.Driver");           
                connection = DriverManager.getConnection(url, usuario, senha);
            } 
            catch(Exception e){}
        }
        return connection.createStatement();
    }
    
    public Connection getConnection(){  
       try{  
          Class.forName("com.mysql.jdbc.Driver").newInstance();  
          String driver = "jdbc:mysql://localhost:3306/proufba";  
          Connection con = DriverManager.getConnection(driver,"root","123");   
          return con;  
        }  
        catch(Exception e){  
            e.printStackTrace();  
        }  
        return null;  
    }  
    
}
