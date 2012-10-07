<?php
include_once 'buscaPassagens.php';
include_once 'buscaHospedagens.php';

function incrementarPopularidade($cidade)
{
    mysql_query("UPDATE `cidades` SET `popularidade` = `popularidade` + 1 WHERE `nome` = '$cidade'");
}

function conectaDB($nome,$usuario,$senha)
{
    if(!($id = mysql_connect("localhost",$usuario,$senha)))
            return false;
    // Seleciona o Banco de Dados
    else if(!($con= mysql_select_db($nome,$id)))
            return false;
    mysql_set_charset('UTF8', $id);
    return true;            
}

function fechaDB()
{
    mysql_close();
}
    
function start($preco,$origem,$dias,&$resultsA,&$resultsH,&$cidades)
{
    // Este arquivo conecta um banco de dados MySQL - Servidor = localhost
    //$dbname= "500820db2"; 
    //$usuario="500820";
    //$password="viajante"; 
    $dbname= "viajantesemdestino"; 
    $usuario="root";
    $password="";

    if (conectaDB($dbname,$usuario,$password))
    {
        $min1 = 1000000;
        $min2 = 1000000;
        
        $resultsA = buscaPassagens($preco/2,$origem,$cidades,$min1);
        if ($cidades != null)
        {
            if (($min1 == 1000000) && ($min2 == 1000000))
            {
                echo '<br /><br /><br /><br /><br /><br />';
                echo '<br /><br /><br /><br /><br /><br />';
                echo 'Quantia muito baixa informada.';
            }
            else
            {
            
            fechaDB();
            
            for ($i = 0; $i < count($cidades); $i++) 
                $resultsH[$i] = buscaHospedagens($cidades[$i][0], $preco/2, $dias,$min2);
            }
        }        
        else
        {
            echo '<br /><br /><br /><br /><br /><br />';
            echo '<br /><br /><br /><br /><br /><br />';
            echo '<br /> Cidade Origem nao cadastrada no banco de dados';
        }
    }
    else
        echo "Nao foi possivel estabelecer uma conexão com o gerenciador MySQL. Favor Contactar o Administrador.";
}

function going(&$resultsA,&$resultsH,&$cidades,$dias)
{
    /*
    echo 'Voce pode ir para os seguintes hoteis em ' . $dest . ':';
    for ($i = 0; $i < count($resultsH); $i++)
        echo '<br />' . 'Preco: ' . $resultsH[$i][0] . ' Nome: ' . $resultsH[$i][1] . ' Classificacao: ' . $resultsH[$i][2] . ' Endereco: ' . $resultsH[$i][3];
    */
    echo '<br /><br /><br /><br /><br /><br />';
    echo '<br /><br /><br /><br /><br /><br />';
    echo '<br />';
 
    if ($cidades != null)
    {
        echo '<div id="lista0">';
        echo '<p charset="utf-8">Voce pode ir para as </p>';
        echo '<p charset="utf-8"> seguintes cidades: <br>';
        echo '<form name="formu0" accept-charset="utf-8">';
        echo '<select size="16" name="list0">';
        for ($i = 0; $i < count($cidades); $i++)
            echo '<option value="'.($i).'">'.$cidades[$i][0].'</option>';
        echo '</p></select></br></form></div>';


        for ($i = 0; $i < count($cidades); $i++)
        {
            $k = 0;

            echo '<div id="listaP'.$i.'" class="listaP">';
            echo '<p charset="utf-8">Qual sera seu meio de transporte?<br>';
            echo '<form name="formuP'.$i.'" accept-charset="utf-8">';
            echo '<select size="6" name="listP'.$i.'">';
            echo '<option value="=-1">Nao utilizarei Transporte</option>';
            for ($j = 0; $j < count($resultsA); $j++)
                if ($resultsA[$j][0] == $cidades[$i][0])
                {
                    if(count($resultsA[$j])==6)
                        echo '<option value="'.($k).'">'.'Preco: R$'.$resultsA[$j][1].' || Tipo: Onibus || Classe: '.$resultsA[$j][2]. ' || Horarios: '.$resultsA[$j][3].' || Duracao: ' . $resultsA[$j][4] . ' || Compania: '.$resultsA[$j][5].'</option>';
                    else
                        echo '<option value="'.($k).'">'.'Preco: R$'.$resultsA[$j][1].' || Tipo: Avião || Ida (Saida/Chegada): '.$resultsA[$j][2].'/'.$resultsA[$j][3]. ' || Volta (Saida/Chegada): ' . $resultsA[$j][4] . '/' . $resultsA[$j][5] .' || Horarios: '.$resultsA[$j][3].' || Duracao: ' . $resultsA[$j][4] . ' || Compania: '.$resultsA[$j][5].'</option>';
                    $k++;
                }
            echo '</p></select></br></form></div>';

        }

        for ($i = 0; $i < count($cidades); $i++)
        {
            //if ($resultsH[$i] != null)
            //{
                $k = 0;
                echo '<div id="listaH'.$i.'" class="listaH">';
                echo '<p charset="utf-8">Qual sera seu hotel?<br>';
                echo '<form name="formuH'.$i.'" accept-charset="utf-8">';
                echo '<select size="6" name="listH'.$i.'">';
                echo '<option value="-1">Nao utilizarei Hospedagem</option>';

                for ($o = 0; $o < count($resultsH[$i]); $o++)
                {

                    echo '<option value="'.($k).'">'.'Diaria: R$'.$resultsH[$i][$o][0].' || Total: R$'.$resultsH[$i][$o][0]*$dias.' || Nome: '.$resultsH[$i][$o][1]. ' || Estrelas: ';
                    echo $resultsH[$i][$o][2];
                    //for ($j=0;$j < $resultsH[$i][$o][2];$j++)
                    //  echo '<img src= "/images/star_8bit>';
                    echo ' || Endereco: ' . $resultsH[$i][$o][3]. '</option>';
                    $k++;
                }
                echo '</p></select></br></form></div>';
            //}
        }
    }
    else
        echo 'Nao foram encontradas cidades que voce possa ir';

/*    
    echo '<div class="teste">';
    echo '<select size="6">';
    for ($j = 0; $j < count($cidades); $j++)
    if ($resultsH[$j] != null)
    {
        echo '<option value="'.($k).'">'.'Preco R$: '.$resultsH[$j][0]. 'Estrelas: '. $resultsH[$j][2] . '</option>';
        $k++;
    }
    echo '</select>';
    echo '</div>';
*/

    /*
    <!-- <center><font color='white'> <?php echo '<br />' . $pass1[$i-1]; ?> <!-- </center> -->
    <!-- <center><font color='white'> <?php echo 'Com pass2 <br />' . $pass2; ?> </center> -->
    <!-- <center><font color='white'> <?php echo '<br />' . 'Destino: ' . $pass[0] . ' | Preco: ' . $pass[1] . ' | Ida (Saida/Chegada): ' . $pass[2] . '/' . $pass[3] . ' | Volta (Saida/Chegada): ' . $pass[4] . '/' . $pass[5] . ' | Compania Aerea: ' . $pass[6]; ?> </center> -->
    <!-- <center><font color='white'> <?php echo '<br />' . 'Destino: ' . $results[$count][0] . ' | Preco: ' . $results[$count][1] . ' | Ida (Saida/Chegada): ' . $results[$count][2] . '/' . $results[$count][3] . ' | Volta (Saida/Chegada): ' . $results[$count][4] . '/' . $results[$count][5] . ' | Compania Aerea: ' . $results[$count][6] . ' | Count: ' . $count; ?> </center> -->
    */
}
?>
