-- phpMyAdmin SQL Dump
-- version 3.2.1
-- http://www.phpmyadmin.net
--
-- Servidor: localhost
-- Tempo de Geração: Jun 02, 2012 as 07:47 AM
-- Versão do Servidor: 5.1.37
-- Versão do PHP: 5.2.10

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

--
-- Banco de Dados: `viajantesemdestino`
--

-- --------------------------------------------------------

--
-- Estrutura da tabela `passagens`
--

CREATE TABLE IF NOT EXISTS `passagens` (
  `id_passagens` int(11) NOT NULL AUTO_INCREMENT,
  `cidade_origem` int(40) NOT NULL DEFAULT '23',
  `cidade_destino` int(40) NOT NULL,
  `tipo` varchar(15) NOT NULL DEFAULT 'onibus',
  `empresa` varchar(40) NOT NULL,
  `classe` varchar(30) NOT NULL,
  `preco` varchar(10) NOT NULL,
  `horarios` varchar(50) NOT NULL,
  `duracao` varchar(10) NOT NULL,
  `link` varchar(60) NOT NULL,
  PRIMARY KEY (`id_passagens`),
  KEY `cidade_destino` (`cidade_destino`),
  KEY `cidade_origem` (`cidade_origem`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=55 ;

--
-- Extraindo dados da tabela `passagens`
--

INSERT INTO `passagens` (`id_passagens`, `cidade_origem`, `cidade_destino`, `tipo`, `empresa`, `classe`, `preco`, `horarios`, `duracao`, `link`) VALUES
(1, 23, 7, 'onibus', 'Aguia Branca', 'Semi-leito', '26.30', '21:30', '1h30min', 'www.aguiabranca.com.br'),
(2, 23, 7, 'onibus', 'Camurujipe', 'Semi-leito', '25.77', '07:20 - 20;30', '1h30min', 'www.camurujipe.com.br'),
(3, 23, 7, 'onibus', 'Camurujipe', 'Leito', '35.63', '23:50', '1h30min', 'www.camurujipe.com.br'),
(4, 23, 3, 'onibus', 'Aguia Branca', 'Convenc c/ ar', '75.31', '05:30', '9h05min', 'https://www.aguiabranca.com.br/'),
(5, 23, 3, 'onibus', 'Aguia Branca', 'Double Leito', '163.95', '19:15', '7h35min', 'https://www.aguiabranca.com.br/'),
(6, 23, 3, 'onibus', 'Aguia Branca', 'Semi-leito', '101.63', '20:00', '8h', 'https://www.aguiabranca.com.br/'),
(7, 23, 28, 'onibus', 'Aguia Branca', 'Convencional', '44.21', '06:20', '11h45min', 'https://www.aguiabranca.com.br/'),
(8, 23, 22, 'onibus', 'Aguia Branca', 'Convencional', '8.68', '06:20', '15min', 'https://www.aguiabranca.com.br/'),
(9, 23, 4, 'onibus', 'Aguia Branca', 'Semi-leito', '115.02', '22:47', '9h', 'https://www.aguiabranca.com.br/'),
(10, 23, 5, 'onibus', 'Aguia Branca', 'Convencional', '57.35', '22:47', '7h25min', 'https://www.aguiabranca.com.br/'),
(11, 23, 26, 'onibus', 'Aguia Branca', 'Convencional', '30.18', '22:43', '3h15min', 'https://www.aguiabranca.com.br/'),
(12, 23, 26, 'onibus', 'Aguia Branca', 'Convenc c/ ar', '33.75', '13:40', '3h1min', 'https://www.aguiabranca.com.br/'),
(13, 23, 6, 'onibus', 'Aguia Branca', 'Convenc c/ ar', '93.51', '05:30', '11h40min', 'https://www.aguiabranca.com.br/'),
(14, 23, 6, 'onibus', 'Aguia Branca', 'Double Leito', '203.75', '19:15', '9h45min', 'https://www.aguiabranca.com.br/'),
(15, 23, 6, 'onibus', 'Aguia Branca', 'Double Plus', '126.23', '19:15', '10h10min', 'https://www.aguiabranca.com.br/'),
(16, 23, 6, 'onibus', 'Aguia Branca', 'Semi-leito', '126.23', '20:00', '11h25min', 'https://www.aguiabranca.com.br/'),
(17, 23, 8, 'onibus', 'Aguia Branca', 'Convenc c/ ar', '42.96', '05:30-13:40', '5h05min', 'https://www.aguiabranca.com.br/'),
(18, 23, 8, 'onibus', 'Aguia Branca', 'Double Leito', '69.82', '09:00', '4h55min', 'https://www.aguiabranca.com.br/'),
(19, 23, 8, 'onibus', 'Aguia Branca', 'Double Plus', '57.88', '09:00', '4h55min', 'https://www.aguiabranca.com.br/'),
(20, 23, 8, 'onibus', 'Aguia Branca', 'Convencional', '38.41', '22:47', '4h35min', 'https://www.aguiabranca.com.br/'),
(21, 23, 8, 'onibus', 'Aguia Branca', 'Semi-leito', '57.88', '12:45-22:45', '4h35min', 'https://www.aguiabranca.com.br/'),
(22, 23, 9, 'onibus', 'Aguia Branca', 'Convencional', '17.40', '06:20-22:43', '1h50min', 'https://www.aguiabranca.com.br/'),
(23, 23, 9, 'onibus', 'Aguia Branca', 'Convenc c/ ar', '19.40', '13:40', '1h35min', 'https://www.aguiabranca.com.br/'),
(24, 23, 12, 'onibus', 'Aguia Branca', 'Double Leito', '109.90', '09:00', '7h45min', 'https://www.aguiabranca.com.br/'),
(25, 23, 12, 'onibus', 'Aguia Branca', 'Double Leito', '139.90', '22:44', '7h05min', 'https://www.aguiabranca.com.br/'),
(26, 23, 12, 'onibus', 'Aguia Branca', 'Double Plus', '79.90', '09:00', '7h45min', 'https://www.aguiabranca.com.br/'),
(27, 23, 12, 'onibus', 'Aguia Branca', 'Double Plus', '85.00', '22:44', '7h05min', 'https://www.aguiabranca.com.br/'),
(28, 23, 12, 'onibus', 'Aguia Branca', 'Semi-leito', '79.90', '12:45', '7h50min', 'https://www.aguiabranca.com.br/'),
(29, 23, 12, 'onibus', 'Aguia Branca', 'Semi-leito', '88.54', '22:45', '7h10min', 'https://www.aguiabranca.com.br/'),
(30, 23, 10, 'onibus', 'Aguia Branca', 'Double Plus', '93.03', '20:00', '7h30min', 'https://www.aguiabranca.com.br/'),
(31, 23, 10, 'onibus', 'Aguia Branca', 'Double Leito', '150.05', '20:00', '7h30min', 'https://www.aguiabranca.com.br/'),
(32, 23, 11, 'onibus', 'Aguia Branca', 'Convec c/ ar', '74.73', '20:00', '10h05min', 'https://www.aguiabranca.com.br/'),
(33, 23, 13, 'onibus', 'Aguia Branca', 'Convencional', '27.40', '05:40-08:00-20:01', '3h20min', 'https://www.aguiabranca.com.br/'),
(34, 23, 13, 'onibus', 'Aguia Branca', 'Convenc c/ ar', '30.65', '10:15-20:00', '2h45min', 'https://www.aguiabranca.com.br/'),
(35, 23, 13, 'onibus', 'Aguia Branca', 'Semi-leito', '41.29', '12:30-21:35', '3h20min', 'https://www.aguiabranca.com.br/'),
(36, 23, 19, 'onibus', 'Aguia Branca', 'Convenc c/ ar', '75.17', '06:30', '9h45min', 'https://www.aguiabranca.com.br/'),
(37, 23, 14, 'onibus', 'Aguia Branca', 'Convenc c/ ar', '63.18', '05:30 ? 13:40', '7h50min', 'https://www.aguiabranca.com.br/'),
(38, 23, 14, 'onibus', 'Aguia Branca', 'Semi-leito', '74.79', '09:00 - 12:45', '7h50min', 'https://www.aguiabranca.com.br/'),
(39, 23, 14, 'onibus', 'Aguia Branca', 'Double Leito', '130.93', '22:44', '7h50min', 'https://www.aguiabranca.com.br/'),
(40, 23, 15, 'onibus', 'Aguia Branca', 'Executivo', '80.33', '22:00', '7h35min', 'https://www.aguiabranca.com.br/'),
(41, 23, 16, 'onibus', 'Aguia Branca', 'Double plus', '176.04', '19:15', '9h40min', 'https://www.aguiabranca.com.br/'),
(42, 23, 16, 'onibus', 'Aguia Branca', 'Double leito', '284.29', '19:15', '9h40min', 'https://www.aguiabranca.com.br/'),
(43, 23, 17, 'onibus', 'Aguia Branca', 'Convenc c/ ar', '57.11', '10:15 ? 20:00', '7h30min', 'https://www.aguiabranca.com.br/'),
(44, 23, 17, 'onibus', 'Aguia Branca', 'Semi-leito', '77.02', '12:30 ? 21:35', '6h10min', 'https://www.aguiabranca.com.br/'),
(45, 23, 17, 'onibus', 'Aguia Branca', 'Convencional', '51.04', '20:00', '7h', 'https://www.aguiabranca.com.br/'),
(46, 23, 18, 'onibus', 'Aguia Branca', 'Convencional', '59.67', '20:30', '7h', 'https://www.aguiabranca.com.br/'),
(47, 23, 18, 'onibus', 'Aguia Branca', 'Executivo', '62.89', '22:00', '7h', 'https://www.aguiabranca.com.br/'),
(48, 23, 21, 'onibus', 'Aguia Branca', 'Semi-leito', '138.73', '20:00', '11h15min', 'https://www.aguiabranca.com.br/'),
(49, 23, 24, 'onibus', 'Aguia Branca', 'Convencional', '46.40', '13:00 ? 20:00', '6h30min', 'https://www.aguiabranca.com.br/'),
(50, 23, 25, 'onibus', 'Aguia Branca', 'Convenc c/ ar', '116.61', '05:30', '2h45min', 'https://www.aguiabranca.com.br/'),
(51, 23, 25, 'onibus', 'Aguia Branca', 'Double Plus', '157.48', '19:15', '12h', 'https://www.aguiabranca.com.br/'),
(52, 23, 25, 'onibus', 'Aguia Branca', 'Double Leito', '254.29', '19:15', '12h', 'https://www.aguiabranca.com.br/'),
(53, 23, 26, 'onibus', 'Aguia Branca', 'Convencional', '34.80', '06:20', '4h', 'https://www.aguiabranca.com.br/'),
(54, 7, 23, 'onibus', 'Aguia Branca', 'Semi-leito', '26.30', '21:30', '1h30min', 'www.aguiabranca.com.br'),
(55, 7, 23, 'onibus', 'Camurujipe', 'Semi-leito', '25.77', '07:20 - 20;30', '1h30min', 'www.camurujipe.com.br'),
(56, 7, 23, 'onibus', 'Camurujipe', 'Leito', '35.63', '23:50', '1h30min', 'www.camurujipe.com.br'),
(57, 3, 23, 'onibus', 'Aguia Branca', 'Convenc c/ ar', '75.31', '05:30', '9h05min', 'https://www.aguiabranca.com.br/'),
(58, 3, 23, 'onibus', 'Aguia Branca', 'Double Leito', '163.95', '19:15', '7h35min', 'https://www.aguiabranca.com.br/'),
(59, 3, 23, 'onibus', 'Aguia Branca', 'Semi-leito', '101.63', '20:00', '8h', 'https://www.aguiabranca.com.br/'),
(60, 28, 23, 'onibus', 'Aguia Branca', 'Convencional', '44.21', '06:20', '11h45min', 'https://www.aguiabranca.com.br/'),
(61, 22, 23, 'onibus', 'Aguia Branca', 'Convencional', '8.68', '06:20', '15min', 'https://www.aguiabranca.com.br/'),
(62, 4, 23, 'onibus', 'Aguia Branca', 'Semi-leito', '115.02', '22:47', '9h', 'https://www.aguiabranca.com.br/'),
(63, 5, 23, 'onibus', 'Aguia Branca', 'Convencional', '57.35', '22:47', '7h25min', 'https://www.aguiabranca.com.br/'),
(64, 26, 23, 'onibus', 'Aguia Branca', 'Convencional', '30.18', '22:43', '3h15min', 'https://www.aguiabranca.com.br/'),
(65, 26, 23, 'onibus', 'Aguia Branca', 'Convenc c/ ar', '33.75', '13:40', '3h1min', 'https://www.aguiabranca.com.br/'),
(66, 6, 23, 'onibus', 'Aguia Branca', 'Convenc c/ ar', '93.51', '05:30', '11h40min', 'https://www.aguiabranca.com.br/'),
(67, 6, 23, 'onibus', 'Aguia Branca', 'Double Leito', '203.75', '19:15', '9h45min', 'https://www.aguiabranca.com.br/'),
(68, 6, 23, 'onibus', 'Aguia Branca', 'Double Plus', '126.23', '19:15', '10h10min', 'https://www.aguiabranca.com.br/'),
(69, 6, 23, 'onibus', 'Aguia Branca', 'Semi-leito', '126.23', '20:00', '11h25min', 'https://www.aguiabranca.com.br/'),
(70, 8, 23, 'onibus', 'Aguia Branca', 'Convenc c/ ar', '42.96', '05:30-13:40', '5h05min', 'https://www.aguiabranca.com.br/'),
(71, 8, 23, 'onibus', 'Aguia Branca', 'Double Leito', '69.82', '09:00', '4h55min', 'https://www.aguiabranca.com.br/'),
(72, 8, 23, 'onibus', 'Aguia Branca', 'Double Plus', '57.88', '09:00', '4h55min', 'https://www.aguiabranca.com.br/'),
(73, 8, 23, 'onibus', 'Aguia Branca', 'Convencional', '38.41', '22:47', '4h35min', 'https://www.aguiabranca.com.br/'),
(74, 8, 23, 'onibus', 'Aguia Branca', 'Semi-leito', '57.88', '12:45-22:45', '4h35min', 'https://www.aguiabranca.com.br/'),
(75, 9, 23, 'onibus', 'Aguia Branca', 'Convencional', '17.40', '06:20-22:43', '1h50min', 'https://www.aguiabranca.com.br/'),
(76, 9, 23, 'onibus', 'Aguia Branca', 'Convenc c/ ar', '19.40', '13:40', '1h35min', 'https://www.aguiabranca.com.br/'),
(77, 12, 23, 'onibus', 'Aguia Branca', 'Double Leito', '109.90', '09:00', '7h45min', 'https://www.aguiabranca.com.br/'),
(78, 12, 23, 'onibus', 'Aguia Branca', 'Double Leito', '139.90', '22:44', '7h05min', 'https://www.aguiabranca.com.br/'),
(79, 12, 23, 'onibus', 'Aguia Branca', 'Double Plus', '79.90', '09:00', '7h45min', 'https://www.aguiabranca.com.br/'),
(80, 12, 23, 'onibus', 'Aguia Branca', 'Double Plus', '85.00', '22:44', '7h05min', 'https://www.aguiabranca.com.br/'),
(81, 12, 23, 'onibus', 'Aguia Branca', 'Semi-leito', '79.90', '12:45', '7h50min', 'https://www.aguiabranca.com.br/'),
(82, 12, 23, 'onibus', 'Aguia Branca', 'Semi-leito', '88.54', '22:45', '7h10min', 'https://www.aguiabranca.com.br/'),
(83, 10, 23, 'onibus', 'Aguia Branca', 'Double Plus', '93.03', '20:00', '7h30min', 'https://www.aguiabranca.com.br/'),
(84, 10, 23, 'onibus', 'Aguia Branca', 'Double Leito', '150.05', '20:00', '7h30min', 'https://www.aguiabranca.com.br/'),
(85, 11, 23, 'onibus', 'Aguia Branca', 'Convec c/ ar', '74.73', '20:00', '10h05min', 'https://www.aguiabranca.com.br/'),
(86, 13, 23, 'onibus', 'Aguia Branca', 'Convencional', '27.40', '05:40-08:00-20:01', '3h20min', 'https://www.aguiabranca.com.br/'),
(87, 13, 23, 'onibus', 'Aguia Branca', 'Convenc c/ ar', '30.65', '10:15-20:00', '2h45min', 'https://www.aguiabranca.com.br/'),
(88, 13, 23, 'onibus', 'Aguia Branca', 'Semi-leito', '41.29', '12:30-21:35', '3h20min', 'https://www.aguiabranca.com.br/'),
(89, 19, 23, 'onibus', 'Aguia Branca', 'Convenc c/ ar', '75.17', '06:30', '9h45min', 'https://www.aguiabranca.com.br/'),
(90, 14, 23, 'onibus', 'Aguia Branca', 'Convenc c/ ar', '63.18', '05:30 ? 13:40', '7h50min', 'https://www.aguiabranca.com.br/'),
(91, 14, 23, 'onibus', 'Aguia Branca', 'Semi-leito', '74.79', '09:00 - 12:45', '7h50min', 'https://www.aguiabranca.com.br/'),
(92, 14, 23, 'onibus', 'Aguia Branca', 'Double Leito', '130.93', '22:44', '7h50min', 'https://www.aguiabranca.com.br/'),
(93, 15, 23, 'onibus', 'Aguia Branca', 'Executivo', '80.33', '22:00', '7h35min', 'https://www.aguiabranca.com.br/'),
(94, 16, 23, 'onibus', 'Aguia Branca', 'Double plus', '176.04', '19:15', '9h40min', 'https://www.aguiabranca.com.br/'),
(95, 16, 23, 'onibus', 'Aguia Branca', 'Double leito', '284.29', '19:15', '9h40min', 'https://www.aguiabranca.com.br/'),
(96, 17, 23, 'onibus', 'Aguia Branca', 'Convenc c/ ar', '57.11', '10:15 ? 20:00', '7h30min', 'https://www.aguiabranca.com.br/'),
(97, 17, 23, 'onibus', 'Aguia Branca', 'Semi-leito', '77.02', '12:30 ? 21:35', '6h10min', 'https://www.aguiabranca.com.br/'),
(98, 17, 23, 'onibus', 'Aguia Branca', 'Convencional', '51.04', '20:00', '7h', 'https://www.aguiabranca.com.br/'),
(99, 18, 23, 'onibus', 'Aguia Branca', 'Convencional', '59.67', '20:30', '7h', 'https://www.aguiabranca.com.br/'),
(100, 18, 23, 'onibus', 'Aguia Branca', 'Executivo', '62.89', '22:00', '7h', 'https://www.aguiabranca.com.br/'),
(101, 21, 23, 'onibus', 'Aguia Branca', 'Semi-leito', '138.73', '20:00', '11h15min', 'https://www.aguiabranca.com.br/'),
(102, 24, 23, 'onibus', 'Aguia Branca', 'Convencional', '46.40', '13:00 ? 20:00', '6h30min', 'https://www.aguiabranca.com.br/'),
(103, 25, 23, 'onibus', 'Aguia Branca', 'Convenc c/ ar', '116.61', '05:30', '2h45min', 'https://www.aguiabranca.com.br/'),
(104, 25, 23, 'onibus', 'Aguia Branca', 'Double Plus', '157.48', '19:15', '12h', 'https://www.aguiabranca.com.br/'),
(105, 25, 23, 'onibus', 'Aguia Branca', 'Double Leito', '254.29', '19:15', '12h', 'https://www.aguiabranca.com.br/'),
(106, 26, 23, 'onibus', 'Aguia Branca', 'Convencional', '34.80', '06:20', '4h', 'https://www.aguiabranca.com.br/'),
(107, 29, 23, 'onibus', 'Aguia Branca', 'Convencional', '12.10', '11:45', '1h25min', 'https://www.aguiabranca.com.br/'),
(108, 23, 29, 'onibus', 'Aguia Branca', 'Convencional', '12.10', '06:20', '1h25min', 'https://www.aguiabranca.com.br/'),
(109, 12, 6, 'onibus', 'Aguia Branca', 'Convencional', '37.63', '07:20', '4h50min', 'https://www.aguiabranca.com.br/'),
(110, 12, 6, 'onibus', 'Aguia Branca', 'Executivo', '54.07', '16:00', '4h40min', 'https://www.aguiabranca.com.br/'),
(111, 12, 7, 'onibus', 'Aguia Branca', 'Convencional', '55.13', '07:00', '7h05min', 'https://www.aguiabranca.com.br/'),
(112, 12, 4, 'onibus', 'Aguia Branca', 'Semi-leito', '29.06', '05:55', '1h45min', 'https://www.aguiabranca.com.br/'),
(113, 12, 4, 'onibus', 'Aguia Branca', 'Convencional', '19.26', '06:00', '1h45min', 'https://www.aguiabranca.com.br/'),
(114, 12, 8, 'onibus', 'Aguia Branca', 'Convencional', '22.39', '22:00', '3h', 'https://www.aguiabranca.com.br/'),
(115, 12, 14, 'onibus', 'Aguia Branca', 'Convencional', '5.57', '07:20', '50min', 'https://www.aguiabranca.com.br/'),
(116, 12, 14, 'onibus', 'Cidade do Sol', 'Convencional', '6.53', '06:15 - 07:15', '50min', 'http://www.viacaocidadesol.com.br/'),
(117, 12, 25, 'onibus', 'Aguia Branca', 'Convencional', '61.88', '07:20', '08h05min', 'https://www.aguiabranca.com.br/'),
(118, 12, 25, 'onibus', 'Aguia Branca', 'Executivo', '88.92', '16:00', '07h15min', 'https://www.aguiabranca.com.br/');


--
-- Restrições para as tabelas dumpadas
--

--
-- Restrições para a tabela `passagens`
--
ALTER TABLE `passagens`
  ADD CONSTRAINT `passagens_ibfk_4` FOREIGN KEY (`cidade_origem`) REFERENCES `cidades` (`id`),
  ADD CONSTRAINT `passagens_ibfk_1` FOREIGN KEY (`cidade_destino`) REFERENCES `cidades` (`id`),
  ADD CONSTRAINT `passagens_ibfk_2` FOREIGN KEY (`cidade_destino`) REFERENCES `cidades` (`id`),
  ADD CONSTRAINT `passagens_ibfk_3` FOREIGN KEY (`cidade_destino`) REFERENCES `cidades` (`id`);
