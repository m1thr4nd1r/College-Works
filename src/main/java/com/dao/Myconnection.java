package com.dao;

import java.sql.*;

import javax.swing.JOptionPane;

public class Myconnection{

    private static Connection connection = null;
    private static String usuario = "b32066c6f7a258";
    private static String senha = "5ab3d940";
    private static String url = "jdbc:mysql://us-cdbr-east-04.cleardb.com:3306/heroku_e567d7139983552";

    public static Statement getStatement() throws SQLException
    {
        if(connection == null){
            try
            {
            	Class.forName("com.mysql.jdbc.Driver");        
                connection = DriverManager.getConnection(url, usuario, senha);
            } 
            catch(Exception e)
            {
            	JOptionPane.showMessageDialog(null,"FALHA NA CONEXÃƒO: "+e.toString()); 
            }
        }
        return connection.createStatement();
    }
    
    public Connection getConnection()
    {  
        try
        {  
            Class.forName("com.mysql.jdbc.Driver").newInstance();  
            Connection con = DriverManager.getConnection(url, usuario, senha);
            return con;  
        }  
        catch(Exception e)
        {  
            e.printStackTrace();  
        }

        return null;  
    }  
}