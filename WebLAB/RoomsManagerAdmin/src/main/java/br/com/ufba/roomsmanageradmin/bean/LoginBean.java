package br.com.ufba.roomsmanageradmin.bean;

import javax.faces.application.FacesMessage;
import javax.faces.bean.ManagedBean;
import javax.faces.context.FacesContext;
import javax.faces.event.ActionEvent;

import org.primefaces.context.RequestContext;

import br.com.ufba.roomsmanageradmin.model.Login;

@ManagedBean
public class LoginBean{
	
	private Login login;
	
	public void logado(ActionEvent actionEvent){
		
		RequestContext context = RequestContext.getCurrentInstance();  
        FacesMessage msg = null;  
        boolean loggedIn = false;  
        System.out.println(login.getUsuario()); 
        
        if(login.validate()){  
            loggedIn = true;  
            msg = new FacesMessage(FacesMessage.SEVERITY_INFO, "Bem Vindo", login.getUsuario());
        } else {  
            loggedIn = false;  
            msg = new FacesMessage(FacesMessage.SEVERITY_WARN, "Login ERROR", "Login ou senha inválidas.");  
        }  
          
        FacesContext.getCurrentInstance().addMessage(null, msg);  
        context.addCallbackParam("loggedIn", loggedIn);
        
	}
	
	public Login getLogin(){
		return this.login;
	}
	
}