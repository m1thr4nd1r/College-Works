<%

HttpServletResponse res = (HttpServletResponse) response;   
String logado = (String)((HttpServletRequest)(request)).getSession().getAttribute("logado");

String [] str = request.getRequestURL().toString().split("/");
String url = "";
int tam = str.length;
int c = 0;

for(String s : str){
  if(c < (tam - 1)){
    url += s+"/";
  }
  c++;
}

%>

<ui:composition template="../template.xhtml"
  xmlns="http://www.w3.org/1999/xhtml"
  xmlns:ui="http://java.sun.com/jsf/facelets"
  xmlns:f="http://java.sun.com/jsf/core"
  xmlns:h="http://java.sun.com/jsf/html"
  xmlns:p="http://primefaces.org/ui" >

    <ui:define name="content">
      <section id="geral">
        <header id="topo_pagina">
          <div class="navbar navbar-inverse affix">
            <div class="navbar-inner2">
            <div class="container">
              <a class="brand" href="index.jsp">RoomsManager</a>
              <div class="nav-collapse collapse">
              <ul class="nav">
                <li class="">
                <a href="sala/index.do">Sala</a>
                </li>
                <li class="">
                <a href="usuario/index.do">Usuário</a>
                </li>
                <% if(logado != null){ %>
                  <li class="logout">
                    <a href="login?logout">
                      <img title="Sair do Sistema" src="<%= url %>images/logout.png" alt="Sair do Sistema" />
                    </a>
                  </li>
                <% } %>
              </ul>
              </div>
            </div>
            </div>
          </div>
          <div class="vAux"></div>
        </header>
        <div id="conteudo">
          <%
        if(logado==null){
        %>
            <form id="form_login" action="login" method="post">
            <div class="container-fluid offset5">
              <div class="span10">
                <div class="span10">
                  <label>Nome do Usu&aacute;rio</label>
                  <input name="username" type="text" id="usuario" value="" placeholder="Usu&aacute;rio"/>
                </div>
                <div class="span10">
                  <label>Senha</label>
                  <input name="senha" type="password" id="senha" value="" placeholder="Senha"/>
                </div>
              </div>
              <div class="span10">
                <input type="submit" value="Logar"/>
              </div>
                </div>
          </form>
        <% }else{%>
          <div class="logo_index">
            <h1>RoomsManagerAdmin</h1>
          </div>
        <% } %>
          </div>
        </section>
     </ui:define>
</ui:composition>