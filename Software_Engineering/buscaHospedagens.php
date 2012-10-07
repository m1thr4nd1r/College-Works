<?php

include_once 'parser.php';

function buscaHospedagens($dest,$valor,$dias,&$min)
{
    // http://www.hotelscombined.pt/Aracaju?languageCode=PB&currencyCode=BRL
    // http://www.hotelscombined.pt/Search.aspx?search=Ilheus&sttype=1&languageCode=PB&brandId=null&currencyCode=BRL&useStored=false
    // http://www.hotelscombined.pt/PB/City/Ilheus_1.htm
    
    $results = array(); // matriz com os dados das hospedagens
    $results = null;
    
    $dest = str_replace(' ','_',$dest); // Troca espaços por _
    $link = $dest . '_1.htm'; // Adiciona todas as informacoes necessarias ao link
    $html = loadHTML($link);

    if (($html != null) && ($html != false))
    {
        $element = procuraHospedagens($html);
        if ($element != null)
        {
            trataHospedagem($element,$valor,$dias,$results,1,$min);
            //echo "|". $results[count($results)-1][2] ."|<br />";
            clearHTML($html);
        }
    }
    
    $link = $dest . '_2.htm'; // Adiciona todas as informacoes necessarias ao link
    $html = loadHTML($link);
    
    if (($html != null) && ($html != false))
    {
        $element = procuraHospedagensD($html);
        if ($element != null)
        {
            trataHospedagem($element,$valor,$dias,$results,2,$min);
            clearHTML($html);
        }
    }
    
    if ($results != null)
    {
        $price = array();
        foreach ($results as $r) 
            $price[] = $r[0];
        array_multisort($price, SORT_ASC, $results); // Arrumando o vetor de acordo com o preço, de forma crescente
    }
    
    return $results;
}
?>