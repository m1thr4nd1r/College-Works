package br.com.ufba.roomsmanageradmin.bean;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;

import javax.annotation.PostConstruct;
import javax.faces.application.FacesMessage;
import javax.faces.bean.ManagedBean;
import javax.faces.context.FacesContext;
import javax.faces.model.DataModel;
import javax.faces.model.ListDataModel;
import javax.swing.JOptionPane;

import org.hibernate.HibernateException;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;

import br.com.ufba.roomsmanageradmin.dao.Hibernate;
import br.com.ufba.roomsmanageradmin.model.Acesso;
import br.com.ufba.roomsmanageradmin.model.ControleAcesso;
import br.com.ufba.roomsmanageradmin.model.Sala;
import br.com.ufba.roomsmanageradmin.model.Setor;
import br.com.ufba.roomsmanageradmin.model.Tipo;
import br.com.ufba.roomsmanageradmin.model.Usuario;

@ManagedBean
public class AcessoPessoaSetorBean implements Serializable{
	private String 				pessoaMatricula;
	private List<Setor>			setores;
	private List<Sala>			salas;
	private String 				setor_id, sala_id;
	
	@PostConstruct
	void init(){
		this.setores = getSetores();
		this.salas = getSalas();
	}
	
	public void save(){
		
		Usuario pessoa = getPessoaByMatricula();
	    int id = 0;
	    
		try{
			id = Integer.valueOf(setor_id);
		}
		catch(Exception e)
		{
			JOptionPane.showMessageDialog(null,e.getMessage());
		}
		finally 
		{

		    Acesso acesso = getAcessoByPessoaSetor(pessoa,this.setor_id);
		    
		    if(acesso == null)
		    {
		    	SessionFactory sf = Hibernate.getSessionFactory();
			    Session session = sf.openSession();
			    Transaction tx = null;   
			    
			    try{
			    	tx = session.beginTransaction();
			    	session.saveOrUpdate(new Acesso(pessoa.getId(),id)); 
			    	tx.commit();
		    	}catch (HibernateException e) {
		    		if (tx!=null) tx.rollback();
			    	e.printStackTrace(); 
			    	JOptionPane.showMessageDialog(null,e.getMessage());
		    	}finally {
			    	session.close();
			    	setor_id = "";
			    }
			    
		    }
		    pessoaMatricula = "";
		    addMessage("Acesso pessoa a setor adicionado com sucesso","");
		    
		}
	    
	}
	
	public void salvarControle(){
		
		int id = 0;
	    
		try{
			id = Integer.valueOf(sala_id);
		}
		catch(Exception e)
		{
			JOptionPane.showMessageDialog(null,e.getMessage());
		}
		finally 
		{
			
			int setorId = getSetorId(id+"");
			Usuario pessoa = getPessoaByMatricula();
			Acesso acesso = getAcessoByPessoaSetor(pessoa, setorId+"");
			
			if(acesso != null)
			{
				SessionFactory sf = Hibernate.getSessionFactory();
			    Session session = sf.openSession();
			    Transaction tx = null;   
			    
			    try{
			    	tx = session.beginTransaction();
			    	Date atual = new Date(System.currentTimeMillis());
			    	session.saveOrUpdate(new ControleAcesso(pessoa.getId(),id,atual,atual,criaData(atual.getYear(), atual.getMonth(), atual.getDay(),0,0,0),new Date(System.currentTimeMillis()))); 
			    	tx.commit();
		    	}catch (HibernateException e) {
		    		if (tx!=null) tx.rollback();
			    	e.printStackTrace(); 
			    	JOptionPane.showMessageDialog(null,e.getMessage());
		    	}finally {
			    	session.close();
			    	sala_id = "";
			    	pessoaMatricula = "";
			    	addMessage("Permissão de acesso adicionada com sucesso!","");
			    }
			}
			else
			{
				addMessage("Pessoa não tem permissão de acesso a sala selecionada","");
			}
			
		}
		
	}
	
	/*********************************************/
	
	private Usuario getPessoaByMatricula(){
		
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    List<Usuario> l = (List<Usuario>) session.createQuery("FROM Usuario WHERE numMatricula = "+Integer.valueOf(pessoaMatricula)).list();
	    session.close();	    
	    
	    Usuario pessoa = new Usuario();
	    for (Usuario usuario : l) {
	    	pessoa = usuario;
		}
	    
	    return pessoa;
	}
	
	private Acesso getAcessoByPessoaSetor(Usuario pessoa,String setor_id){

		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    List <Acesso>lPessoa = (List<Acesso>) session.createQuery("FROM Acesso WHERE pessoa_id = "+pessoa.getId()+" AND setor_id = "+setor_id).list();
	    session.close();

	    Acesso acesso = null;
	    for (Acesso a : lPessoa) {
	    	acesso = a;
		}
	    
	    return acesso;
	}
	
	private int getSetorId(String sala_id){
		
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    List <Sala>l = (List<Sala>) session.createQuery("FROM Sala WHERE id = "+sala_id).list();
	    session.close();

	    int setor_id = -1;
	    for (Sala a : l) {
	    	setor_id = a.getSetor_id();
		}
	    
	    return setor_id;
	    
	}
	
	private void addMessage(String string,String texto){
		FacesMessage msg = new FacesMessage(string,texto);  
		FacesContext.getCurrentInstance().addMessage(null, msg);
	}
	
	private Date criaData(int ano, int mes, int dia, int hora, int minuto, int segundo){
		Calendar c = Calendar.getInstance();
		c.set(ano,mes,dia,hora,minuto,segundo);
		return c.getTime();
	}
	/************** SETS e GETS ******************/
	public String getPessoaMatricula() {
		return pessoaMatricula;
	}
	
	public void setPessoaMatricula(String pessoaMatricula) {
		this.pessoaMatricula = pessoaMatricula;
	}
	
	public List<Setor> getSetores(){
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    this.setores = (List<Setor>) session.createQuery("FROM Setor").list();
	    session.close();
		return setores;
	}
	
	public List<Sala> getSalas(){
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    this.salas = (List<Sala>) session.createQuery("FROM Sala").list();
	    session.close();
		return salas;
	}
	
	public String getSetor_id() {
		return setor_id;
	}
	public void setSetor_id(String setor_id) {
		this.setor_id = setor_id;
	}
	
	public void setSetores(List<Setor> setores) {
		this.setores = setores;
	}

	public String getSala_id() {
		return sala_id;
	}

	public void setSala_id(String sala_id) {
		this.sala_id = sala_id;
	}

}
