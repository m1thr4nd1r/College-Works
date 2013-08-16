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
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
   "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
  <head>  
    <script type="text/javascript" src="js/padrao.js"></script>
        <title>RoomsManagerAdmin</title>
        <link href="css/comum.css" media="all" rel="stylesheet" type="text/css" />
        <link href="css/login.css" media="all" rel="stylesheet" type="text/css" />
    </head>
    <body>
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
              <a href="usuario/index.do">Usuario</a>
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
        <div class="login">
          <h1>Login</h1>
          <form action="login" method="post">          	
            <!--<div class="container-fluid offset5">
               <div class="span10">
                <div class="span10">
                  <label>Nome do Usu&aacute;rio</label>
                  <label>Usu&aacute;rio</label>- -->                  
                  <input name="username" id="user" type="text" value="" placeholder="Usu&aacute;rio"/>
              <!--  </div>
                <div class="span10">
                  <label>Senha</label>-->
                  <input name="senha" id="pass" type="password" value="" placeholder="Senha"/>
               <!--  </div>
              </div>
              <div class="span10"> -->
                <input class="btn btn-primary btn-block btn-larg" type="submit" value="Logar"/>
              <!--</div>
                </div>-->
          </form>
        </div>
        <% }else{%>
          <div class="logo_index">
            <h1>RoomsManagerAdmin</h1>
          </div>
        <% } %>
          </div>
          <jsp:include page="/footer.xhtml"/>
        </section>
    </body>
</html>