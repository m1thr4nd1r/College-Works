<?php

include_once 'parser.php';

function buscaPassagensAviao($preco,$origem,&$min)
{
    $results = array();
   
    /*
    $aux =  0;
    date_default_timezone_set("America/Bahia");
    if (((int)date('H') > 17) || ((int)date('H') < 1)) // Caso seja mais que 17 horas, nao é possivel comprar passagem de aviao para o dia seguinte
        $aux++;
    $tomorrow = date ("Y-m") . "-" . (date ("d") + $aux); // Usando a funçao para pegar o dia de amanha
    $datomorrow = date ("Y-m") . "-" . (date ("d") + $aux+1); // Usando a funcao para pegar o dia depois de amanha

    //$link = "http://www.decolar.com/shop/flights/search/roundtrip/" . $local . "/" . $dest . "/" . $tomorrow . "/" . $datomorrow . "/1/0/0";
    */
    
    $query = "SELECT codigo_aeroporto FROM cidades WHERE `nome` = '$origem'"; // Buscando no Banco de Dados o codigo do aeroporto de acordo com a cidade
    $res = mysql_query($query) or die("query die: ".  mysql_error());
    $origem = mysql_result($res,0);

    $query = "SELECT * FROM cidades WHERE `codigo_aeroporto` !=  '' AND `codigo_aeroporto` !=  '$origem' "; // Buscando no Banco de Dados os codigos de aeroportos restantes
    $res = mysql_query($query) or die("query die: ".  mysql_error());
    while ($city = mysql_fetch_array($res))
    {
        $html = null;
        $dest = $city['codigo_aeroporto'];
        $link = $origem . "-" . $dest . '.htm'; // Adiciona todas as informacoes necessarias ao link
        $html = loadHTML($link);
        /* O preco mais barato... o site da decolar fornece a tabela com os menores pre&#65533;os encontrados */
        if(($html != null) && ($html != false))
        {
            $element = procuraPassagensAviao($html); // Acha o bloco de passagens no site da decolar
            if($element != null) 
            {
                $query = "SELECT nome FROM cidades WHERE `codigo_aeroporto` = '$dest'"; // Buscando no Banco de Dados o nome da cidade de acordo com o codigo do aeroporto
                $result = mysql_query($query) or die("query die: ".  mysql_error());
                $dest = mysql_result($result,0);

                trataPassagemAviao($element,$dest,$preco,$results,$min);
                clearHTML($html);
            }    
        }
    }
    return $results;
}

function armazenaCidades($results)
{
    $j = 0;
    $count = count($results);
    $cidades = array(); // Criando o array que ter&#65533; o nome das cidades que o usuario poder&#65533; ir
    for ($i = 0; $i < $count; $i++)
        if (($i == 0) || (($i > 0) && ($results[$i][0] != $results[$i-1][0])))
        {
            $aux = $results[$i][0];
            $cidades[$j][0] = $results[$i][0]; // Salva o nome de cada cidade listada pelas passagens de avi&#65533;o
            $query = "SELECT popularidade FROM cidades WHERE nome = '$aux'";
            $res = mysql_query($query) or die("query die: ".  mysql_error());
            $cidades[$j][1] = mysql_result($res, 0);
            //echo 'Cidade: ' . $cidades[$j] . '<br />';  
            $j++;
        }
    return $cidades;
}

function buscaPassagensOnibus($preco, $origem, &$cidades, &$results, &$min)
{
    $j = count($cidades);
    $query = "SELECT passagens.*,c.nome,c.popularidade FROM  passagens, cidades c, cidades e WHERE c.id = passagens.cidade_destino AND passagens.cidade_origem =  e.id AND e.nome = '$origem' AND passagens.preco <= $preco/2 ORDER BY popularidade DESC";
    // Buscando no Banco de Dados o destino da passagem de acordo com metade do pre&#65533;o (para passagem de ida e volta)
    //$query = "SELECT * FROM passagens WHERE `origem` = '$origem' AND `preco` <= $preco/2"; 
    $res = mysql_query($query) or die("query die: ".  mysql_error());
    while ($city = mysql_fetch_array($res)) // Pegando a primeira coluna da resposta a pesquisa realizada
    {
        if ($city['preco'] <= $min)
            $min = $city['preco'];
        
        $flag_c = true; // Inicializando o flag dos nomes das cidades
        $pop = $city['popularidade']; // Pegando o campo de popularidade da cidade
        
        $k = count($results);
        $results[$k][0] = $city['nome']; // Pegando o campo destino do resultado
        $results[$k][1] = $city['preco'] * 2;
        $results[$k][2] = $city['classe'];
        $results[$k][3] = $city['horarios'];
        $results[$k][4] = $city['duracao'];
        $results[$k][5] = $city['empresa'];
        
        for ($i = 0; $i < $j; $i++)
            if ($results[$k][0] == $cidades[$i][0]) // Compara se o resultado da busca &#65533; igual a algum dos nomes das cidades ja armazenados previamente
            {
                $flag_c = false;
                break;
            }
        if ($flag_c) // Se nao existirem cidades anteriores com o mesmo nome...
        {
            $cidades[$j][0] = $results[$k][0]; // Adiciona essa cidade ao vetor com o nome das cidades que o usuario pode ir
            $cidades[$j][1] = $pop; // Adiciona a popularidade da cidade ao vetor
            //echo 'Cidade2: ' . $cidades[$j] . '<br />';
            $j++;
        }
    }  
}

function buscaPassagens($preco, $origem, &$cidades, &$min)
{
	$results = array(); // matriz com os dados das passagens de aviao
        $results = null;
        $codigo = null; // String com o codigo do aeroporto da cidade (se houver)
        
        $origem = trim($origem); // Remove espaços em branco do fim e inicio da string
        $query = "SELECT codigo_aeroporto  FROM `cidades` WHERE `nome` = '$origem'"; 
        $res = mysql_query($query); //or die("query die: " .  mysql_error());
        if (mysql_num_rows($res) != 0)
        {
            $codigo = mysql_result($res,0); // Pega o codigo do aeroporoto da cidade de origem
            
            if ($codigo != null) // Se o codigo for nulo entao a cidade possui um aeroporto, logo é realizada a busca de passagens aereas
            {
                $results = buscaPassagensAviao ($preco,$origem,$min);
                $cidades = armazenaCidades($results);
            }

            buscaPassagensOnibus($preco, $origem, $cidades, $results, $min);   

            if ($results != null)
            {
                $pop = array();
                foreach ($cidades as $c) 
                    $pop[] = $c[1];
                array_multisort($pop, SORT_DESC, $cidades); // Arrumando o vetor de acordo com a popularidade em ordem decrescente
            }
        }
        return $results;
}                
?>