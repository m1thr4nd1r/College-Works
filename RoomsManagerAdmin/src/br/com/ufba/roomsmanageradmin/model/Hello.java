package br.com.ufba.roomsmanageradmin.model;

import javax.annotation.PostConstruct;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.RequestScoped;
 
@RequestScoped
@ManagedBean
public class Hello {
    
    @PostConstruct
    public void init(){
        System.out.println(" Bean executado! ");
    }
     
    public String getMessage(){
        return "Eu não sou mais Java. Meu nome agora é JSF!";
    }
 
}
