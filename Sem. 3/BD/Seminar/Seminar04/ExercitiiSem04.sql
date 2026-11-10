USE ParcDistractii;
GO

-- 1.1) Să se creeze o funcție scalară care primește ca parametru numele unei categorii și returnează codul acesteia. 
CREATE OR ALTER FUNCTION GetCategoryCode(@nume NVARCHAR(100))
RETURNS INT
AS
BEGIN
    IF(EXISTS(SELECT * FROM Categorii WHERE nume = @nume))
        RETURN (SELECT id_categorie FROM Categorii WHERE nume = @nume)
    RETURN NULL
END
GO

SELECT * FROM Categorii;
PRINT(dbo.GetCategoryCode('Elev'));
GO

-- 1.2) Creați o funcție de tip inline table valued care returnează toate înregistrările din tabelul Sectiuni al căror nume se termină cu o literă dată ca parametru de intrare și au cel puțin două caractere.
CREATE OR ALTER FUNCTION GetSectiuniByLastLetter(@litera NVARCHAR(1))
RETURNS TABLE AS
RETURN SELECT * FROM Sectiuni 
WHERE nume LIKE '%' + @litera AND LEN(nume) >= 2
GO

SELECT * FROM Sectiuni;
SELECT * FROM dbo.GetSectiuniByLastLetter('e');
GO

-- 2.1) Creați un view care afișează toate înregistrările din tabelul Categorii al căror nume este egal cu ‘pensionari’ sau ‘copii’.
CREATE OR ALTER VIEW vw_CategoriiPensionariCopii AS
SELECT nume FROM Categorii 
WHERE nume IN ('Pensionar', 'Copil')
GO

SELECT * FROM vw_CategoriiPensionariCopii;
GO

-- 2.2) Creați un view care afișează toate înregistrările din tabelul Sectiuni al căror nume începe cu litera G.
CREATE OR ALTER VIEW vw_SectiuniG AS
SELECT nume, descriere FROM Sectiuni 
WHERE nume LIKE 'G%'
GO

SELECT * FROM vw_SectiuniG;
GO

-- 2.3) Creați un view care care afișează numele vizitatorilor, nota și numele atracției.
CREATE OR ALTER VIEW vw_VizitatoriAtractii AS
SELECT v.nume AS NumeVizitator, n.nota AS Nota, a.nume AS NumeAtractie
FROM Vizitatori v
INNER JOIN Note n ON v.id_vizitator = n.id_vizitator
INNER JOIN Atractii a ON n.id_atractie = a.id_atractie
GO

SELECT * FROM Vizitatori;
SELECT * FROM vw_VizitatoriAtractii;
GO

-- exemplu trigger insert
CREATE TRIGGER IntroducereCategorie
ON Categorii
INSTEAD OF INSERT
AS
BEGIN
	RAISERROR('Momentan nu se pot insera date in acest tabel',16,1);
END;
GO

-- 3.1) Creați un trigger care împiedică execuția operațiilor de ștergere din tabelul Categorii și afișează un mesaj corespunzător. 
CREATE OR ALTER TRIGGER ImpiedicaStergereCategorii
ON Categorii
INSTEAD OF DELETE
AS
BEGIN
    RAISERROR('Ștergerea din tabelul Categorii nu este permisă.',16,1);
END;
GO

DROP TRIGGER ImpiedicaStergereCategorii;
GO

-- 3.2) Pentru baza de date creată la seminar, găsiți un scenariu de utilizare a unui trigger DML pentru operația de insert, update sau delete.
-- Creați și testați acest trigger.
-- Exemplu: Trigger care impiedica inserarea de vizitatori care sunt din categoria "Copil" în tabelul Vizitatori.
CREATE OR ALTER TRIGGER ImpiedicaInserareVizitatoriCopii
ON Vizitatori
INSTEAD OF INSERT
AS
BEGIN
    IF EXISTS (SELECT * FROM inserted i
               JOIN Categorii c ON i.id_categorie = c.id_categorie
               WHERE c.nume = 'Copil')
    BEGIN
        RAISERROR('Inserarea vizitatorilor din categoria "Copil" nu este permisă.', 16, 1);
        ROLLBACK TRANSACTION;
    END
    ELSE
    BEGIN
        INSERT INTO Vizitatori (nume, email, id_categorie)
        SELECT nume, email, id_categorie FROM inserted;
    END
END;
GO

DROP TRIGGER ImpiedicaInserareVizitatoriCopii;
GO
