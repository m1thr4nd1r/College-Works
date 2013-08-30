package br.com.ufba.roomsmanageradmin.bean;

import java.awt.JobAttributes;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;

import javax.annotation.PostConstruct;
import javax.faces.application.FacesMessage;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import javax.faces.context.FacesContext;
import javax.faces.model.DataModel;
import javax.faces.model.ListDataModel;
import javax.swing.JOptionPane;

import org.hibernate.HibernateException;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.validator.internal.util.privilegedactions.GetConstructor;

import br.com.ufba.roomsmanageradmin.dao.Hibernate;
import br.com.ufba.roomsmanageradmin.model.Acesso;
import br.com.ufba.roomsmanageradmin.model.ControleAcesso;
import br.com.ufba.roomsmanageradmin.model.Sala;
import br.com.ufba.roomsmanageradmin.model.Setor;
import br.com.ufba.roomsmanageradmin.model.Tipo;
import br.com.ufba.roomsmanageradmin.model.Usuario;

@ManagedBean
@SessionScoped
public class AcessoPessoaSetorBean implements Serializable{
	private String 				 pessoaMatricula;
	private String 				 setor_id, sala_id;
	private List<Setor>			 setores;
	private List<Sala>			 salas,salasOcupadas,salasLivres;
	private List<ControleAcesso> cAcessos;
	
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
			
			Sala sala = getSalaById(sala_id);
			Usuario pessoa = getPessoaByMatricula();
			int setorId = sala.getSetor_id();
			Acesso acesso = getAcessoByPessoaSetor(pessoa, setorId+"");
			
			if(acesso != null)
			{
				SessionFactory sf = Hibernate.getSessionFactory();
			    Session session = sf.openSession();
			    Transaction tx = null;   
			    
			    try{
			    	tx = session.beginTransaction();
			    	Date atual = new Date(System.currentTimeMillis());
			    	session.saveOrUpdate(new ControleAcesso(pessoa,sala,atual,atual,criaData(atual.getYear(), atual.getMonth(), atual.getDay(),0,0,0),new Date(System.currentTimeMillis()))); 
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
	
	public void salvarDevolucao(){

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
			
			Sala sala = getSalaById(sala_id);
			Usuario pessoa = getPessoaByMatricula();
			ControleAcesso cAcesso = getControleAcessoByPessoaSala(pessoa.getId()+"",sala.getId()+"");
			
			if(cAcesso != null)
			{
				SessionFactory sf = Hibernate.getSessionFactory();
			    Session session = sf.openSession();
			    Transaction tx = null;   
			    
			    try{
			    	tx = session.beginTransaction();
			    	Date atual = new Date(System.currentTimeMillis());
			    	session.update(new ControleAcesso(pessoa,sala,cAcesso.getHoraEntrada(),cAcesso.getDataEntrada(),atual,atual)); 
			    	tx.commit();
		    	}catch (HibernateException e) {
		    		if (tx!=null) tx.rollback();
			    	e.printStackTrace(); 
			    	JOptionPane.showMessageDialog(null,e.getMessage());
		    	}finally {
			    	session.close();
			    	sala_id = "";
			    	pessoaMatricula = "";
			    	addMessage("Entrega realizada com sucesso!","");
			    }
			}
			else
			{
				addMessage("Num. de matricula ou Sala inválida","");
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
	
	/**
	 * 
	 * @param eChave int que representa se a sala está ocupada ou não. O - sala livre, 1 - sala ocupada 
	 * @return todas as salas ocupadas
	 */
	public List<Sala> getSalasAcesso(String eChave){
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    List<Sala> salas = null;
	    try{
			List<ControleAcesso> ctrl = (List<ControleAcesso>) session.createQuery("FROM ControleAcesso Where e_chave = "+eChave+" Order by data_entrada desc").list();
		    for (ControleAcesso ca: ctrl) {
		    	salas.add(ca.getSala());
			}
		}catch(HibernateException e){
			JOptionPane.showMessageDialog(null,e.getMessage());
		}
		finally{
		    session.close();
		}
		return salas;
	}
	
	public List<Sala> getSalasOcupadas(){
		this.salasOcupadas = getSalasAcesso("1");
		return (salasOcupadas != null) ? salasOcupadas : new ArrayList<Sala>();
	}

	public List<Sala> getSalasLivres(){
		this.salasLivres = new ArrayList<Sala>();
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    try{
	    	String query = "SELECT * FROM sala "+ 
							"WHERE id NOT IN ("+
							    "SELECT sala_id FROM controle_acesso "+
							    "WHERE e_chave = 1)";
	    	
	    	List<Sala> salas = (List<Sala>) session.createSQLQuery(query).list();
	    	this.salasLivres = salas;
		}catch(HibernateException e){
			JOptionPane.showMessageDialog(null,e.getMessage());
		}
		finally{
		    session.close();
		}
		return salasLivres;
	}

	public String getPessoaMatricula() {
		return pessoaMatricula;
	}
	
	public void setPessoaMatricula(String pessoaMatricula) {
		this.pessoaMatricula = pessoaMatricula;
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

	private int getSetorId(String sala_id){
		return ((Sala)getSalaById(sala_id)).getSetor_id();
	}
	
	private Sala getSalaById(String sala_id){
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    List <Sala>l = (List<Sala>) session.createQuery("FROM Sala WHERE id = "+sala_id).list();
	    session.close();
	    
	    Sala sala = null;
	    for (Sala a : l) {
	    	sala = a;
		}
	    
	    return sala;
	}
	
	private ControleAcesso getControleAcessoByPessoaSala(String pessoa_id, String sala_id){
		SessionFactory sf = Hibernate.getSessionFactory();
	    Session session = sf.openSession();
	    List <ControleAcesso>l = (List<ControleAcesso>) session.createQuery("FROM ControleAcesso WHERE sala_id = "+sala_id+" AND pessoa_id = "+pessoa_id).list();
	    session.close();
	    
	    ControleAcesso ctrl_acesso = null;
	    for (ControleAcesso ca : l) {
	    	ctrl_acesso = ca;
		}
	    
	    return ctrl_acesso;
	}
	
}
