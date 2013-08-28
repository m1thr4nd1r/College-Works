package br.com.ufba.roomsmanageradmin.bean;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

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
import br.com.ufba.roomsmanageradmin.model.Setor;
import br.com.ufba.roomsmanageradmin.model.Tipo;
import br.com.ufba.roomsmanageradmin.model.Usuario;

@ManagedBean
public class AcessoPessoaSetorBean implements Serializable{
	private String 				pessoaMatricula;
	private DataModel<Usuario> 	pessoa;
	private List 				setores;
	private String 				setor_id = "";
	
	public void save(){
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    List<Usuario> l = (List<Usuario>) session.createQuery("FROM Usuario WHERE numMatricula = "+Integer.valueOf(pessoaMatricula)).list();
	    session.close();	    
	    
	    Usuario pessoa = new Usuario();
	    for (Usuario usuario : l) {
	    	pessoa = usuario;
		}
	    
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

		    sf = Hibernate.getSessionFactory();
		    session = sf.openSession();
		    List <Acesso>lPessoa = (List<Acesso>) session.createQuery("FROM Acesso WHERE pessoa_id = "+pessoa.getId()+" AND setor_id = "+setor_id).list();
		    session.close();

		    Acesso acesso = null;
		    for (Acesso a : lPessoa) {
		    	acesso = a;
			}
		    
		    if(acesso == null)
		    {
				sf = Hibernate.getSessionFactory();
			    session = sf.openSession();
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
		    
		    FacesMessage msg = new FacesMessage("Acesso pessoa a setor adicionado com sucesso");  
		    FacesContext.getCurrentInstance().addMessage(null, msg);
		}
	    
	}
	
	/************** SETS e GETS ******************/
	public String getPessoaMatricula() {
		return pessoaMatricula;
	}
	
	public void setPessoaMatricula(String pessoaMatricula) {
		this.pessoaMatricula = pessoaMatricula;
	}
	
	public DataModel<Usuario> getPessoaModel() {
		return pessoa;
	}
	public void setPessoa(DataModel<Usuario> pessoaModel) {
		this.pessoa = pessoa;
	}
	
	public List<Setor> getSetores(){
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    this.setores = (List<Setor>) session.createQuery("FROM Setor").list();
	    session.close();
		return setores;
	}
	
	public String getSetor_id() {
		return setor_id;
	}
	public void setSetor_id(String setor_id) {
		this.setor_id = setor_id;
	}
	public DataModel<Usuario> getPessoa() {
		return pessoa;
	}
	public void setSetores(List setores) {
		this.setores = setores;
	}

}
