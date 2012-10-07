<?php

include_once 'simple_html_dom.php';

/* Funcao nao mais utilizada para achar o destino dado uma html da decolar com passagens de aviao
function achaDestino($element,$i)
{
    $dest = null;
    $dest = $element->find('li[class=airport]',1+$i*4); // Acha o destino de cada passagem
    $dest = $dest->plaintext; // Convertendo de HTML DOM para string
    $dest = trim($dest); // Removendo espacos em branco do inicio e final da string criada
    return $dest;
}
*/

function clearHTML(&$html) // Funcao para limpar os dados html (e liberar memoria)
{
    $html->clear(); 
    unset($html);
}

function loadHTML($link) // Carrega o HTML contido em $link 
{
    return @file_get_html($link); // (o @ evita que warnings sejam dados)
}

function procuraHospedagens($html) // Procura o bloco que contem as hospedagens no html do hotels combined
{
    return  $html->find('div[class=resultsHolder]',0);
}

function procuraHospedagensD($html) // Procura o bloco que contem as hospedagens no html da decolar
{
    return $html->find('ul[class=hotelResults]',0);
}

function procuraEnderecoHospedagem($element,$i) // Procura o endereço da hospedagem no html da hotels combined
{
    return $element->find('dd[class=hc_sri_addr]',$i)->plaintext;
}

function procuraEnderecoHospedagemD($element,$i) // Procura o endereço da hospedagem no html da decolar
{
    return $element->find('span[class=hotelAddress]',$i)->plaintext;
}

function procuraPassagensAviao($html) // Procura o bloco de passagens no site da decolar
{
    return $html->find('div[class=clusters]',0); 
}

function procuraPrecoHospedagem($element,$i) // Procura o preço da hospedagem no html do hotels combined
{
    return $element->find('dd[class=hc_sri_price]',$i);
}

function procuraPrecoHospedagemD($element,$i) // Procura o preço da hospedagem no html da decolar
{
    return $element->find('span[class=localHotelPrice]',$i);
}

function validaPrecoHospedagem($price) // Valida o preço da hospedagem encontrado no html do hotels combined
{
    $price = $price->plaintext; // Converte o preço da hospedagem em string
    $price = (int)strrchr($price,' '); // Remove todos os caracteres ate o ultimo espaço da string e entao converte-o em inteiro
    return $price;
}

function validaPrecoHospedagemD($price) // Valida o preço da hospedagem encontrado no html da decolar
{
    return validaPrecoAviao($price); // Chama a funcao de validação de preço do aviao, pois os dois tem o mesmo principio
}

function procuraPrecoAviao($element, $i) // Procurando o preço de uma passagem de aviao no html da decolar
{
    return $element->find('span[class=amount]',$i); // Extraindo o preço da passagem
}

function validaPrecoAviao($price) // Validando o preco da passagem de aviao da decolar
{
    $price = $price->plaintext; // Convertendo de HTML DOM para string
    $price = trim($price); // Removendo espaços em branco do inicio e final da string criada
    $price = str_replace('.','',$price); // Trocando virgula por ponto
    $price = (int) $price; // Convertendo de string para int
    return $price;
}

function procuraNomeHospedagem($element,$i) // Procura o nome da hospedagem no html do hotels combined
{
    return $element->find('a[class=hc_sri_hotel]',$i)->plaintext;
}

function procuraNomeHospedagemD($element,$i) // Procura o nome da hospedagem no html do decolar
{
    return ucwords(trim($element->find('a[class=hotelNameLink]',$i)->plaintext)); // Encontra o nome do hotel, converte-o em string, elimina os espaços em branco...
                                                                                  // e entao torna a primeira letra de todas as palavras maiusculas
}

function procuraCompaniaAerea($element,$i)
{
    $company = $element->find('li[class=name]',$i*2); // Extraindo o nome da compania aerea
    $company = $company->plaintext; // Convertendo de HTML DOM para String
    $company = trim($company); // Removendo espacos em branco do inicio e final da string criada
    return $company;
}

function procuraClassificacaoHospedagem($element,$i) // Procura a classificacao (estrelas) de um hotel do html do hotels combined
{
    $aux = $element->find('span[class=hc_sri_rating]',$i); // Encontra a seção com as estrelas (possui uma imagem para representar uma estrela)
    return count($aux->find('img')); // Retorna todas as imagens no elemento aux e entao conta o tamanho deste vetor retornado
}

function procuraClassificacaoHospedagemD($element,$i) // Procura a classificacao (estrelas) de um hotel do html do decolar
{
    $aux = $element->find('h3[class=hotelName]',$i); // Encontra a seção pai
    $aux = $aux->lastChild(); // Pega o ultimo filho do pai (onde se encontra a classificacao da hospedagem (tambem em estrelas))
    $aux = $aux->getAttribute('class'); // Pega o atributo class, na forma de string
    $aux = substr($aux, strlen($aux)-1, 1); // Pega a substring que começa na ultima posição da string e tem somente um byte de tamanho
    $aux = (int)$aux;
    return $aux;
}

function procuraHorarioSaidaIda($element,$j)
{
    $departure_leave = $element->find('strong[class=hour]',$j); // Pegando Horario de Saida do voo de ida
    $departure_leave = $departure_leave->plaintext; // Convertendo de HTML DOM para String
    $departure_leave = trim($departure_leave); // Removendo espacos em branco do inicio e final da string criada
    return $departure_leave;
}

function procuraHorarioChegadaIda($element,$j)
{
    $departure_arrive = $element->find('strong[class=hour]',$j); // Pegando horario de Chegada do voo de ida
    $departure_arrive = $departure_arrive->plaintext; // Convertendo de HTML DOM para String
    $departure_arrive = trim($departure_arrive); // Removendo espacos em branco do inicio e final da string criada
    return $departure_arrive;
}   

function procuraHorarioSaidaVolta($element,$j)
{
    $arrival_leave = $element->find('strong[class=hour]',$j); // Pegando Horario de Saida do voo de volta
    $arrival_leave = $arrival_leave->plaintext; // Convertendo de HTML DOM para String
    $arrival_leave = trim($arrival_leave); // Removendo espacos em branco do inicio e final da string criada
    return $arrival_leave;
}
        
function procuraHorarioChegadaVolta($element,$j)
{
    $arrival_arrive = $element->find('strong[class=hour]',$j); // Pegando Horario de Chegada do voo de volta
    $arrival_arrive = $arrival_arrive->plaintext; // Convertendo de HTML DOM para String
    $arrival_arrive = trim($arrival_arrive); // Removendo espacos em branco do inicio e final da string criada
    return $arrival_arrive;
}

function trataHospedagem($element,$preco,$dias,&$results,$flag,&$min)
{
    $i = 0;
    $pass = array(); // Array temporario com todas as informaçoes de uma hospedagem
    $pass = null;
    
    if ($flag == 1)
    {
        $price = procuraPrecoHospedagem($element, $i);
        if ($price != null)
            $price = validaPrecoHospedagem ($price);
        if ($price*$dias <= $preco)
        {
            do
            {
                if ($price*$dias < $min) 
                    $min = $price*$dias;
                $pass[0] = $price;
                $pass[1] = procuraNomeHospedagem($element, $i);
                $pass[2] = procuraClassificacaoHospedagem($element, $i);
                $pass[3] = procuraEnderecoHospedagem($element, $i);
                $results[count($results)] = $pass;
                //echo "|". $results[count($results)-1][2] ."|<br />";
                $i++;

                $price = procuraPrecoHospedagem($element,$i);
                if ($price != null)
                    $price = validaPrecoHospedagem($price);

            } while (($price != null) && ($price*$dias <= $preco));
        }
    }
    else if ($flag == 2)
    {
        $price = procuraPrecoHospedagemD($element,$i);
        if ($price != null)
            $price = validaPrecoHospedagemD ($price);
        if ($price*$dias <= $preco)
        {
            do
            {
                if ($price*$dias < $min) 
                    $min = $price*$dias;
                $pass[0] = $price;
                $pass[1] = procuraNomeHospedagemD($element, $i);
                $pass[2] = procuraClassificacaoHospedagemD($element, $i);
                $pass[3] = procuraEnderecoHospedagemD($element, $i);
                $results[count($results)] = $pass;
                $i++;

                $price = procuraPrecoHospedagemD($element,$i);
                if ($price != null)
                    $price = validaPrecoHospedagemD($price);

            } while (($price != null) && ($price*$dias <= $preco));
        }
    }
}

function trataPassagemAviao($element,$dest,$preco,&$results,&$min)
{
    $i = 0;
    $j = 0;
    $pass = array(); // Array temporario com todas as informaçoes de uma passagen de aviao
    $pass = null;
    $price = procuraPrecoAviao($element,$i);
    if ($price != null)
        $price = validaPrecoAviao($price);
    if ($price <= $preco)
    {
        do
        {
            if ($price < $min) 
                $min = $price;
            $pass[0] = $dest;
            $pass[1] = $price;
            
            if ($element != null)
            {                 
                $pass[2] = procuraHorarioSaidaIda($element,$j++);
                $pass[3] = procuraHorarioChegadaIda ($element, $j++); 
                $pass[4] = procuraHorarioSaidaVolta ($element, $j++);
                $pass[5] = procuraHorarioChegadaVolta ($element, $j++);
            }
            
            $pass[6] = procuraCompaniaAerea($element,$i);   
             
            $results[count($results)] = $pass;
            $i++;

            $price = procuraPrecoAviao($element,$i);
            if ($price != null)
                $price = validaPrecoAviao($price);

        } while (($price != null) && ($price <= $preco));
    }
}
?>
