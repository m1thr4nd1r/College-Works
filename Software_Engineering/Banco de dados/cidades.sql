-- phpMyAdmin SQL Dump
-- version 3.2.1
-- http://www.phpmyadmin.net
--
-- Servidor: localhost
-- Tempo de Geração: Jun 02, 2012 as 07:48 AM
-- Versão do Servidor: 5.1.37
-- Versão do PHP: 5.2.10

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

--
-- Banco de Dados: `viajantesemdestino`
--

-- --------------------------------------------------------

--
-- Estrutura da tabela `cidades`
--

CREATE TABLE IF NOT EXISTS `cidades` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nome` longtext NOT NULL,
  `uf` varchar(20) NOT NULL DEFAULT 'Bahia',
  `codigo_aeroporto` tinytext NOT NULL,
  `popularidade` int(50) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=30 ;

--
-- Extraindo dados da tabela `cidades`
--

INSERT INTO `cidades` (`id`, `nome`, `uf`, `codigo_aeroporto`, `popularidade`) VALUES
(1, 'Barreiras', 'Bahia', 'BRA', 0),
(2, 'Bom Jesus da Lapa', 'Bahia', 'LAZ', 0),
(3, 'Camacam', 'Bahia', '', 0),
(4, 'Canavieiras', 'Bahia', '', 0),
(5, 'Coaraci', 'Bahia', '', 0),
(6, 'Eunápolis', 'Bahia', '', 0),
(7, 'Feira de Santana', 'Bahia', 'FEC', 0),
(8, 'Gandu', 'Bahia', '', 0),
(9, 'Gov. Mangabeira', 'Bahia', '', 0),
(10, 'Ibicaraí', 'Bahia', '', 0),
(11, 'Ibipeba', 'Bahia', '', 0),
(12, 'Ihéus', 'Bahia', 'IOS', 0),
(13, 'Ipirá', 'Bahia', '', 0),
(14, 'Itabuna', 'Bahia', '', 0),
(15, 'Itambé', 'Bahia', '', 0),
(16, 'Itanhém', 'Bahia', '', 0),
(17, 'Morro do Chapéu', 'Bahia', '', 0),
(18, 'Poções', 'Bahia', '', 0),
(19, 'Pontal', 'Bahia', '', 0),
(20, 'Paulo Afonso', 'Bahia', 'PAV', 0),
(21, 'Porto Seguro', 'Bahia', 'BPS', 0),
(22, 'Santo Amaro', 'Bahia', '', 0),
(23, 'Salvador', 'Bahia', 'SSA', 0),
(24, 'Tapiramutá', 'Bahia', '', 0),
(25, 'Teixeira de Freitas', 'Bahia', '', 0),
(26, 'Valença', 'Bahia', 'VAL', 0),
(27, 'Vitória da Conquista', 'Bahia', 'VDC', 0),
(28, 'Camamu', 'Bahia', '', 0),
(29, 'Amelia Rodrigues', 'Bahia', '', 0);
