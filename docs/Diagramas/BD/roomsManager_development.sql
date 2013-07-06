SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL';

DROP SCHEMA IF EXISTS `roomsManager_development` ;
CREATE SCHEMA IF NOT EXISTS `roomsManager_development` DEFAULT CHARACTER SET latin1 ;
USE `roomsManager_development` ;

-- -----------------------------------------------------
-- Table `roomsManager_development`.`aluno`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `roomsManager_development`.`aluno` ;

CREATE  TABLE IF NOT EXISTS `roomsManager_development`.`aluno` (
  `id` INT(11) NOT NULL AUTO_INCREMENT ,
  `numMatricula` INT(11) NOT NULL ,
  `nome` VARCHAR(60) NOT NULL ,
  `curso` VARCHAR(60) NOT NULL ,
  PRIMARY KEY (`id`) ,
  UNIQUE INDEX `numMatricula_UNIQUE` (`numMatricula` ASC) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `roomsManager_development`.`sala`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `roomsManager_development`.`sala` ;

CREATE  TABLE IF NOT EXISTS `roomsManager_development`.`sala` (
  `id` INT(11) NOT NULL AUTO_INCREMENT ,
  `nome` VARCHAR(100) NOT NULL ,
  `quadro` BINARY(1) NOT NULL DEFAULT '0' ,
  `retroprojetor` BINARY(1) NOT NULL DEFAULT '0' ,
  `multimidia` BINARY(1) NOT NULL DEFAULT '0' ,
  `tipo` VARCHAR(60) NOT NULL COMMENT 'Laboratório OU Carteira' ,
  `ar_condicionado` BINARY(1) NOT NULL DEFAULT '0' ,
  `computadores` INT(11) NOT NULL DEFAULT '0' ,
  `capacidade` INT(11) NOT NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `roomsManager_development`.`grupo`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `roomsManager_development`.`grupo` ;

CREATE  TABLE IF NOT EXISTS `roomsManager_development`.`grupo` (
  `id` INT(11) NOT NULL AUTO_INCREMENT ,
  `nome` VARCHAR(60) NOT NULL ,
  `salao_ocupada_id` INT(11) NOT NULL ,
  `professor_responsavel` VARCHAR(60) NOT NULL ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_sala_id` (`salao_ocupada_id` ASC) ,
  CONSTRAINT `fk_sala_id`
    FOREIGN KEY (`salao_ocupada_id` )
    REFERENCES `roomsManager_development`.`sala` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `roomsManager_development`.`aluno_grupo`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `roomsManager_development`.`aluno_grupo` ;

CREATE  TABLE IF NOT EXISTS `roomsManager_development`.`aluno_grupo` (
  `grupo_id` INT(11) NOT NULL ,
  `aluno_id` INT(11) NOT NULL ,
  INDEX `fk_aluno_grupo_1` (`grupo_id` ASC) ,
  INDEX `fk_aluno_grupo_2` (`aluno_id` ASC) ,
  CONSTRAINT `fk_aluno_grupo_1`
    FOREIGN KEY (`grupo_id` )
    REFERENCES `roomsManager_development`.`grupo` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_aluno_grupo_2`
    FOREIGN KEY (`aluno_id` )
    REFERENCES `roomsManager_development`.`aluno` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `roomsManager_development`.`usuario`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `roomsManager_development`.`usuario` ;

CREATE  TABLE IF NOT EXISTS `roomsManager_development`.`usuario` (
  `id` INT(11) NOT NULL AUTO_INCREMENT ,
  `tipo` VARCHAR(45) NOT NULL COMMENT 'administrador ou funcionario' ,
  `email` VARCHAR(60) NOT NULL ,
  `nome` VARCHAR(100) NOT NULL ,
  `senha` VARCHAR(64) NOT NULL ,
  `num_cadastro` INT(20) NOT NULL ,
  PRIMARY KEY (`id`) ,
  UNIQUE INDEX `email_UNIQUE` (`email` ASC) ,
  UNIQUE INDEX `num_cadastro_UNIQUE` (`num_cadastro` ASC) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;



SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
