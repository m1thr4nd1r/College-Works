SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL';

DROP SCHEMA IF EXISTS `roomsManager_development` ;
CREATE SCHEMA IF NOT EXISTS `roomsManager_development` DEFAULT CHARACTER SET latin1 ;
USE `roomsManager_development` ;

-- -----------------------------------------------------
-- Table `roomsManager_development`.`pessoa`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `roomsManager_development`.`pessoa` ;

CREATE  TABLE IF NOT EXISTS `roomsManager_development`.`pessoa` (
  `id` INT(11) NOT NULL AUTO_INCREMENT ,
  `numMatricula` INT(11) NOT NULL ,
  `nome` VARCHAR(60) NOT NULL ,
  `is_professor` TINYINT(1) NOT NULL DEFAULT FALSE ,
  PRIMARY KEY (`id`) ,
  UNIQUE INDEX `numMatricula_UNIQUE` (`numMatricula` ASC) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `roomsManager_development`.`grupo`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `roomsManager_development`.`grupo` ;

CREATE  TABLE IF NOT EXISTS `roomsManager_development`.`grupo` (
  `id` INT(11) NOT NULL AUTO_INCREMENT ,
  `nome` VARCHAR(60) NOT NULL ,
  `professor_responsavel` VARCHAR(60) NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `roomsManager_development`.`pessoa_has_grupo`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `roomsManager_development`.`pessoa_has_grupo` ;

CREATE  TABLE IF NOT EXISTS `roomsManager_development`.`pessoa_has_grupo` (
  `grupo_id` INT(11) NOT NULL ,
  `pessoa_id` INT(11) NOT NULL ,
  INDEX `fk_aluno_grupo_1` (`grupo_id` ASC) ,
  INDEX `fk_aluno_grupo_2` (`pessoa_id` ASC) ,
  CONSTRAINT `fk_aluno_grupo_1`
    FOREIGN KEY (`grupo_id` )
    REFERENCES `roomsManager_development`.`grupo` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_aluno_grupo_2`
    FOREIGN KEY (`pessoa_id` )
    REFERENCES `roomsManager_development`.`pessoa` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `roomsManager_development`.`sala`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `roomsManager_development`.`sala` ;

CREATE  TABLE IF NOT EXISTS `roomsManager_development`.`sala` (
  `id` INT(11) NOT NULL AUTO_INCREMENT ,
  `nome` VARCHAR(100) NOT NULL ,
  `quadro` TINYINT(1) NOT NULL DEFAULT FALSE ,
  `retroprojetor` TINYINT(1) NOT NULL DEFAULT FALSE ,
  `multimidia` TINYINT(1) NOT NULL DEFAULT FALSE ,
  `tipo` VARCHAR(60) NOT NULL COMMENT 'Laboratório OU Carteira' ,
  `ar_condicionado` TINYINT(1) NOT NULL DEFAULT FALSE ,
  `computadores` INT(11) NOT NULL DEFAULT '0' ,
  `capacidade` INT(11) NOT NULL ,
  PRIMARY KEY (`id`) )
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


-- -----------------------------------------------------
-- Table `roomsManager_development`.`solicitar_reserva`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `roomsManager_development`.`solicitar_reserva` ;

CREATE  TABLE IF NOT EXISTS `roomsManager_development`.`solicitar_reserva` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `sala_id` INT NOT NULL ,
  `data_inicio` DATE NOT NULL ,
  `data_fim` DATE NULL ,
  `horario_inicio` TIME NOT NULL ,
  `horario_termino` TIME NULL ,
  `responsavel` VARCHAR(45) NOT NULL ,
  `reserva_para` VARCHAR(45) NULL ,
  `evento_privado` TINYINT(1) NOT NULL ,
  `email` VARCHAR(45) NOT NULL ,
  `telefone` VARCHAR(45) NULL ,
  `obs` VARCHAR(45) NULL ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_solicitar_reserva_1_idx` (`sala_id` ASC) ,
  CONSTRAINT `fk_solicitar_reserva_1`
    FOREIGN KEY (`sala_id` )
    REFERENCES `roomsManager_development`.`sala` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `roomsManager_development`.`grupo_has_sala`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `roomsManager_development`.`grupo_has_sala` ;

CREATE  TABLE IF NOT EXISTS `roomsManager_development`.`grupo_has_sala` (
  `grupo_id` INT(11) NOT NULL ,
  `sala_id` INT(11) NOT NULL ,
  PRIMARY KEY (`grupo_id`, `sala_id`) ,
  INDEX `fk_grupo_has_sala_sala1_idx` (`sala_id` ASC) ,
  INDEX `fk_grupo_has_sala_grupo1_idx` (`grupo_id` ASC) ,
  CONSTRAINT `fk_grupo_has_sala_grupo1`
    FOREIGN KEY (`grupo_id` )
    REFERENCES `roomsManager_development`.`grupo` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_grupo_has_sala_sala1`
    FOREIGN KEY (`sala_id` )
    REFERENCES `roomsManager_development`.`sala` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `roomsManager_development`.`equipamento`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `roomsManager_development`.`equipamento` ;

CREATE  TABLE IF NOT EXISTS `roomsManager_development`.`equipamento` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `descricao` VARCHAR(45) NOT NULL ,
  `sala_id` INT(11) NULL ,
  `is_fixo` TINYINT(1) NOT NULL DEFAULT FALSE ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_equipamento_sala1` (`sala_id` ASC) ,
  CONSTRAINT `fk_equipamento_sala1`
    FOREIGN KEY (`sala_id` )
    REFERENCES `roomsManager_development`.`sala` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `roomsManager_development`.`solicitacao_equipamento`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `roomsManager_development`.`solicitacao_equipamento` ;

CREATE  TABLE IF NOT EXISTS `roomsManager_development`.`solicitacao_equipamento` (
  `equipamento_id` INT NOT NULL ,
  `pessoa_id` INT NOT NULL ,
  PRIMARY KEY (`equipamento_id`, `pessoa_id`) ,
  INDEX `fk_solicitacao_equipamento_1` (`pessoa_id` ASC) ,
  INDEX `fk_solicitacao_equipamento_2` (`equipamento_id` ASC) ,
  CONSTRAINT `fk_solicitacao_equipamento_1`
    FOREIGN KEY (`pessoa_id` )
    REFERENCES `roomsManager_development`.`pessoa` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_solicitacao_equipamento_2`
    FOREIGN KEY (`equipamento_id` )
    REFERENCES `roomsManager_development`.`equipamento` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;



SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
