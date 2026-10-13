CREATE DATABASE ParcDistractii;
GO

USE ParcDistractii;
GO

CREATE TABLE Categorii(
    id_categorie INT PRIMARY KEY IDENTITY(1,1),
    nume VARCHAR(100) NOT NULL
);

CREATE TABLE Vizitatori(
    id_vizitator INT PRIMARY KEY IDENTITY(1,1),
    nume VARCHAR(100) NOT NULL,
    email VARCHAR(100) NOT NULL,
    id_categorie INT NOT NULL,

    FOREIGN KEY(id_categorie) REFERENCES Categorii(id_categorie)
);

CREATE TABLE Sectiuni(
    id_sectiune INT PRIMARY KEY IDENTITY(1,1),
    nume VARCHAR(100) NOT NULL,
    descriere VARCHAR(500) NULL
);

CREATE TABLE Atractii(
    id_atractie INT PRIMARY KEY IDENTITY(1,1),
    nume VARCHAR(100) NOT NULL,
    descriere VARCHAR(500) NULL,
    varsta_minima INT NOT NULL,
    id_sectiune INT NOT NULL,

    FOREIGN KEY(id_sectiune) REFERENCES Sectiuni(id_sectiune),
    CHECK (varsta_minima >= 0)
);

CREATE TABLE Note(
    id_vizitator INT NOT NULL,
    id_atractie INT NOT NULL,
    nota FLOAT NULL,

    PRIMARY KEY (id_vizitator, id_atractie),
    FOREIGN KEY (id_vizitator) REFERENCES Vizitatori(id_vizitator),
    FOREIGN KEY (id_atractie) REFERENCES Atractii(id_atractie),

    CHECK(nota BETWEEN 1 AND 10)
);



