delimiter $$

CREATE TABLE `club` (
  `clubName` varchar(45) NOT NULL,
  `location` varchar(45) NOT NULL,
  `league` varchar(45) NOT NULL,
  PRIMARY KEY (`clubName`),
  KEY `playsIn_idx` (`league`),
  CONSTRAINT `playsIn` FOREIGN KEY (`league`) REFERENCES `league` (`leagueName`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1$$

delimiter $$

CREATE TABLE `contract` (
  `contractID` int(11) NOT NULL,
  `startDate` date NOT NULL,
  `endDate` date NOT NULL,
  `salary` int(11) NOT NULL,
  PRIMARY KEY (`contractID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1$$

delimiter $$

CREATE TABLE `fixture` (
  `date` date NOT NULL,
  `time` time NOT NULL,
  `homeTeam` varchar(45) NOT NULL,
  `awayTeam` varchar(45) NOT NULL,
  `match_ID` varchar(45) NOT NULL,
  PRIMARY KEY (`match_ID`),
  KEY `teamPlayingAtHome_idx` (`homeTeam`),
  KEY `awayTeamSelected_idx` (`awayTeam`),
  CONSTRAINT `awayTeamSelected` FOREIGN KEY (`awayTeam`) REFERENCES `club` (`clubName`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `homeTeamSelected` FOREIGN KEY (`homeTeam`) REFERENCES `club` (`clubName`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1$$

delimiter $$

CREATE TABLE `league` (
  `leagueName` varchar(45) NOT NULL,
  `location` varchar(3) NOT NULL,
  PRIMARY KEY (`leagueName`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1$$

delimiter $$

CREATE TABLE `player` (
  `player_ID` int(11) NOT NULL,
  `firstName` varchar(45) NOT NULL,
  `lastName` varchar(45) NOT NULL,
  `age` int(11) NOT NULL,
  `position` varchar(45) NOT NULL,
  `club` varchar(45) NOT NULL,
  `contract_Id` int(11) NOT NULL,
  PRIMARY KEY (`player_ID`),
  KEY `playsFor_idx` (`club`),
  KEY `signedContract_idx` (`contract_Id`),
  CONSTRAINT `playsForClub` FOREIGN KEY (`club`) REFERENCES `club` (`clubName`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `signedContract` FOREIGN KEY (`contract_Id`) REFERENCES `contract` (`contractID`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1$$

delimiter $$

CREATE TABLE `stadium` (
  `stadiumName` varchar(45) NOT NULL,
  `location` varchar(45) NOT NULL,
  `capacity` int(11) NOT NULL,
  `club` varchar(45) NOT NULL,
  PRIMARY KEY (`stadiumName`),
  KEY `homeGround_idx` (`club`),
  CONSTRAINT `homeGroundTo` FOREIGN KEY (`club`) REFERENCES `club` (`clubName`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1$$

delimiter $$

CREATE TABLE `staff` (
  `staff_ID` int(11) NOT NULL,
  `firstName` varchar(45) NOT NULL,
  `lastName` varchar(45) NOT NULL,
  `position` varchar(45) NOT NULL,
  `age` int(11) NOT NULL,
  `club` varchar(45) NOT NULL,
  `contract_Identifier` int(11) NOT NULL,
  PRIMARY KEY (`staff_ID`),
  KEY `worksFor_idx` (`club`),
  KEY `putPenToPaperFor_idx` (`contract_Identifier`),
  CONSTRAINT `employedBy` FOREIGN KEY (`club`) REFERENCES `club` (`clubName`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `putPenToPaperFor` FOREIGN KEY (`contract_Identifier`) REFERENCES `contract` (`contractID`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1$$

delimiter $$

CREATE TABLE `youthacademy` (
  `academyID` int(11) NOT NULL,
  `location` varchar(45) NOT NULL,
  `associatedClub` varchar(45) NOT NULL,
  PRIMARY KEY (`academyID`),
  KEY `developPlayersIn_idx` (`associatedClub`),
  CONSTRAINT `developedBy` FOREIGN KEY (`associatedClub`) REFERENCES `club` (`clubName`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1$$













