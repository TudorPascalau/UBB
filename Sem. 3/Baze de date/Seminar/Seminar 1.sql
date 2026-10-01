--crearea bazei de date Blog224
CREATE DATABASE Blog224;
GO
USE Blog224;

CREATE TABLE Utilizatori
(cod_u INT PRIMARY KEY IDENTITY(1,1),
nume_utilizator VARCHAR(100),
email VARCHAR(100) UNIQUE,
parola VARCHAR(200)
);

CREATE TABLE Postari
(cod_p INT PRIMARY KEY IDENTITY,
titlu VARCHAR(300) NOT NULL,
continut VARCHAR(MAX), 
data_postarii DATETIME,
cod_u INT FOREIGN KEY REFERENCES Utilizatori(cod_u)
);

CREATE TABLE Comentarii
(cod_c INT PRIMARY KEY IDENTITY,
continut VARCHAR(500),
data_comentariului DATETIME,
cod_u INT FOREIGN KEY REFERENCES Utilizatori(cod_u),
cod_p INT FOREIGN KEY REFERENCES Postari(cod_p)
);

CREATE TABLE CuvinteCheie
(cod_cc INT PRIMARY KEY IDENTITY,
nume NVARCHAR(100)
);

--crearea tabelului de legatura
CREATE TABLE PostariCuvinteCheie
(cod_p INT FOREIGN KEY REFERENCES Postari(cod_p),
cod_cc INT FOREIGN KEY REFERENCES CuvinteCheie(cod_cc),
CONSTRAINT pk_PostariCuvinteCheie PRIMARY KEY(cod_p, cod_cc)
);