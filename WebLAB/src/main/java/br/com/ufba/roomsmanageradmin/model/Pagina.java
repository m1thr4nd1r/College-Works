package br.com.ufba.roomsmanageradmin.model;

public class Pagina {

	private String titulo;
	private String path;
	
	public Pagina(){
		
	}

	public Pagina(String titulo) {
		this.titulo = titulo;
		this.path = titulo;
	}
	
	public Pagina(String titulo, String path) {
		super();
		this.titulo = titulo;
		this.path = path+"/"+titulo;
	}
	
	public String getTitulo() {
		return titulo;
	}
	public void setTitulo(String titulo) {
		this.titulo = titulo;
	}

	public String getPath() {
		return path;
	}

	public void setPath(String path) {
		this.path = path;
	}
}