<!DOCTYPE html>
<html>
   <head>
        <!-- <?php session_start() // Iniciando Sessão ?> -->
        <?php global $string_array; ?>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
            <title>Viajante Sem Destino</title>
        <link href="CSS.css" rel="stylesheet" type="text/css"> 
    </head> 
    
    <body>
        <script type="text/javascript" src="jquery-1.7.2.min.js" charset="utf-8"></script>
	 <!--<h1>Viajante Sem Destino!ABSOLUTE</h1>-->
        <div class="nav1">Viajante Sem Destino!</div>
        <marquee direction="right" scrolldelay="45" truespeed><h4><center>Bem-vindo!</center></font></h4></marquee>
     
	  <div class="data">
                  <?php date_default_timezone_set("America/Bahia"); ?>
		  <span class="dia"><?php echo date ("j")?></span>
		  <span class="mes"><?php echo date ("M")?></span>
		  <span class="ano"><?php echo date ("Y")?></span>
	  </div>        
		 
      <!-- <embed src="images/Round Table - Book End Bossa.mp3" width="70" height="25" autostart="false"> -->
       
    <DIV STYLE="position: absolute;left: 180px;height: 300px; width: 200px;">         
        
            <h4><FORM Method ="POST" Action ="index.php">
                    <font color = 'white'> Onde voce esta?
                    <br>
                    <input type='text' name='origem'
                    value='<?PHP echo isset($_POST['origem']) ? $_POST['origem'] : ''?>' />
                    <br>
                    <br>
                    Quanto pretende gastar?
                    <br>
                    <input type='number' name='valor'
                    value='<?PHP echo isset($_POST['valor']) ? $_POST['valor'] : ''?>' />
                    <br>
                    <br>
                    Quantos dias pretende ficar?
                    <br>
                    <input type='number' name='dias' 
                    value='<?PHP echo isset($_POST['dias']) ? $_POST['dias'] : ''?>' />
                    <br>                   
                    <input type='submit' value="I'm felling lucky" name="Enviar"/>
                </FORM>
            </h4>
    </DIV>
                        <?php
                        
                        global $origem;
                        global $valor;
                        global $flag_v, $flag_d;
                        $flag_v = false;
                        $flag_d = true;
                        
                        /*
                        echo "<form action = 'index.php' method = 'post'>
                        <font color = 'white'> Onde voce esta?
                        <br>
                        <input type='text' name='origem'/>
                        value='".isset($_POST['origem']) ? $_POST['origem'] : ''."'
                        <br>
                        <br>
                        Quanto pretende gastar?
                        <br>
                        <input type='number' name='valor'/>
                        <br>
                        <br>
                        Quantos dias pretende ficar?
                        <br>
                        <input type='number' name='dias'/>
                        <br>                   
                        <input type='submit' value='Enviar' name='Enviar'/>
                        <input type='reset' value='Apagar' name='Apagar'/>
                        </form>";
                        */
                        
                        if ((isset($_POST['origem'])) && ($_POST['origem'] != '')) // Se o campo local for setado e não estiver vazio
                            $origem = $_POST['origem']; // Salva o valor do campo local                              
                        else if (!(isset($_POST['origem'])) || ($_POST['origem'] == '')) // Se o campo local nao for setado ou estiver vazio
                            $origem = 'Salvador';
                        
                        
                        if (isset($_POST['dias'])) // Se o campo dias for setado...
                            if ($_POST['dias'] != '') // ...e não estiver vazio...
                                if ((int)$_POST['dias'] > 0) // ...e nao for negativo...
                                    $dias = (int)$_POST['dias']; // Salva o valor do campo dias
                                else 
                                {
                                    $flag_d = false; // Flag para inicializar a pesquisa
                                    echo "<br>";
                                    echo "*Informe um valor maior que 0 no campo 'Quantos dias pretende ficar?'";
                                }
                        else if ((!isset($_POST['dias'])) || ($_POST['dias'] == '')) // Se o campo dias nao for setado ou estiver vazio
                            $dias = 1;
                        
                        if (isset($_POST['valor'])) // Se o campo valor for setado...
                        {
                                echo "<br>";
                                if ($_POST['valor'] == '') //... e estiver vazio
                                    echo "*Preecha o campo 'Quanto pretende gastar?'";
                                else if ((float)$_POST['valor'] <= 0) //... ou se nao estiver vazio e for menor que 0
                                    echo "*Informe um valor maior que 0 no campo 'Quanto pretende gastar?'";
                                else if ((float)$_POST['valor'] > 1000000) //... ou se nao estiver vazio e for maior que $1.000.000 
                                    echo "*Informe um valor menor ou igual a 1000000 no campo 'Quanto pretende gastar?'";
                                else //... e nao estiver vazio nem for menor que 0
                                {
                                    $valor = (float)$_POST['valor']; // Salva o valor do campo valor
                                    $flag_v = true; // Flag para inicializar a pesquisa     
                                }
                        }
                    ?>
                   <img src="images/logoRodrigolisacomnome2.gif" width="405" height="380" alt="logo do site Viajante sem destino" id="imgpos" /> 
        
            <font color='white'>
        <?php 
            include_once 'controller.php';	
            if ($flag_v && $flag_d)
            {
                $cidades = array(); // Vetor com a lista de cidades (sem repeticao) e suas respectivas popularidades
                $cidades = null;
                $resultsA = array(); // Vetor com a lista de passagens e seus dados
                $resultsA = null;
                $resultsH = array(); // Vetor com a lista de hospedagens e seus dados
                $resultsH = null;
                start($valor,$origem,$dias,$resultsA,$resultsH,$cidades);
                if ($resultsA != null)
                {
                    for ($i = 0; $i < count($cidades); $i++)
                        $c[$i] = $cidades[$i][0];
                    $string_array = @implode("|", $c);
                
                    going($resultsA,$resultsH,$cidades,$dias);
                }
            }
            ?>
            </font>
        
		
       <center>
            <DIV id="footer">         
                <p> &copy; 2012 ANRV </p>
            </DIV>
       </center>

        <script type="text/javascript" charset="utf-8">
            $(document).ready
            ( 
                function()
                {
                    $($("form select")[0]).click
                    (
                        function()
                        {
                            var destino = document.formu0.list0.value;
                            var lista = "#listaP"+destino;
                            $(".listaP").hide();
                            $(".listaH").hide();
                            $(lista).toggle(1000)
                        }
                    );
                    $(".listaP select ").click
                    (
                        function()
                        {
                            var destino = document.formu0.list0.value;
                            var lista = "#listaH"+destino;
                            $(".listaH").hide();
                            $(lista).toggle(1000)
                        }
                    );
                    $(" .listaH select ").click(
                        function()
                        {
                            var array_produtos, string_array;
                            var destino = document.formu0.list0.value;
                            string_array = "<?php echo $string_array; ?>";
                            
                            array_produtos = string_array.split("|");
                            var cidade = array_produtos[destino];
                            
                            var r=confirm("Pressione OK, se o resultado da pesquisa lhe foi satisfatorio, ou cancelar, para voltar a pagina anterior");
                            if (r==true)
                            {
                                if (window.XMLHttpRequest)
                                {// code for IE7+, Firefox, Chrome, Opera, Safari
                                    xmlhttp=new XMLHttpRequest();
                                }
                                else
                                {// code for IE6, IE5
                                    xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
                                }                                

                                xmlhttp.open("POST","incpop.php?q="+cidade,false);
                                xmlhttp.send();
                                alert("Popularidade de " + cidade + " incrementada");
                            }
                        }
                    );
                }
            );
        </script>
    </body>
</html>							