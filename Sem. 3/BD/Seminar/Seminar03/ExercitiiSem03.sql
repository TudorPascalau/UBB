USE ParcDistractii;
GO

--Ex 1.1
CREATE OR ALTER PROCEDURE AdaugaSectiune @nume VARCHAR(100), @descriere VARCHAR(500)
AS
BEGIN
SET NOCOUNT ON;
INSERT INTO Sectiuni(nume, descriere) VALUES (@nume, @descriere);
END;
GO

EXEC AdaugaSectiune 'Pet Zone', 'Zona pentru animale de companie';
SELECT * FROM Sectiuni;
GO

--Ex 1.2
CREATE OR ALTER PROCEDURE ActualizeazaEmailVizitator @id_vizitator INT, @emailNou VARCHAR(100)
AS
BEGIN
SET NOCOUNT ON;
UPDATE Vizitatori
SET email = @emailNou
WHERE id_vizitator = @id_vizitator;
END;
GO

EXEC ActualizeazaEmailVizitator 1, 'nou_email@gmail.com';
SELECT * FROM Vizitatori;
GO

-- Ex 1.3
-- Să se creeze o procedură stocată care returnează numele vizitatorului, adresa de email și numărul total de note pentru toți vizitatorii care au dat cel puțin o notă unei atracții.
CREATE OR ALTER PROCEDURE AfiseazaVizitatoriCuNote @nume VARCHAR(100) OUTPUT, @email VARCHAR(100) OUTPUT, @numarNote INT OUTPUT
AS
BEGIN
SET NOCOUNT ON;
SELECT @nume = v.nume, @email = v.email, @numarNote = COUNT(n.id_vizitator)
FROM Vizitatori v
JOIN Note n ON v.id_vizitator = n.id_vizitator
GROUP BY v.nume, v.email;
END;
GO

SELECT * FROM Note
SELECT * FROM Vizitatori
GO

DECLARE @nume VARCHAR(100), @email VARCHAR(100), @numarNote INT;
EXEC AfiseazaVizitatoriCuNote @nume = @nume OUTPUT, @email = @email OUTPUT, @numarNote = @numarNote OUTPUT;
SELECT @nume AS NumeVizitator, @email AS EmailVizitator, @numarNote AS NumarTotalNote;
GO

-- Ex 2.1
CREATE OR ALTER PROCEDURE AdaugaCategoria @nume VARCHAR(100)
AS
BEGIN
SET NOCOUNT ON;
IF(EXISTS(SELECT * FROM Categorii WHERE nume = @nume))
    PRINT 'Categoria exista deja.';
ELSE
    INSERT INTO Categorii(nume) VALUES (@nume);
END;
GO

SELECT * FROM Categorii;
EXEC AdaugaCategoria 'Familie';
EXEC AdaugaCategoria 'Copil';
GO

-- Ex 2.2
CREATE OR ALTER PROCEDURE AdaugaAtractie @nume VARCHAR(100), @descriere VARCHAR(500), @varsta_minima INT, @id_sectiune INT
AS
BEGIN
SET NOCOUNT ON;
IF(EXISTS(SELECT * FROM Atractii WHERE nume = @nume AND id_sectiune = @id_sectiune AND varsta_minima = @varsta_minima AND descriere = @descriere))
    PRINT 'Atractia exista deja.';
ELSE
    INSERT INTO Atractii(nume, descriere, varsta_minima, id_sectiune) VALUES (@nume, @descriere, @varsta_minima, @id_sectiune);
END;
GO

SELECT * FROM Atractii;
EXEC AdaugaAtractie 'Roller Coaster', 'Montagne russe cu viteza mare', 12, 3;
GO

-- Ex 2.3
CREATE OR ALTER PROCEDURE CodVizitatorDupaEmail @email VARCHAR(100), @codVizitator INT OUTPUT
AS
BEGIN
SET NOCOUNT ON;
IF(EXISTS(SELECT * FROM Vizitatori WHERE email = @email))
    SELECT @codVizitator = id_vizitator FROM Vizitatori WHERE email = @email;
ELSE
    PRINT 'Nu exista vizitator cu acest email.';
END;
GO

SELECT * FROM Vizitatori;

DECLARE @codVizitator INT;
SET @codVizitator = 0;
EXEC CodVizitatorDupaEmail '@gmail.com', @codVizitator OUTPUT;
IF(@codVizitator != 0)
    PRINT @codVizitator;
GO

-- Ex 3.1
-- Să se creeze o procedură stocată care șterge o atracție din tabelul Atractii. Procedura stocată va avea un singur parametru de intrare: numele atracției.
-- Înainte de ștergerea atracției, se va verifica dacă există note pentru acea atracție.
-- În cazul în care există note date acelei atracții, se va afișa pe ecran un mesaj corespunzător și nu se va șterge atracția respectivă.

CREATE OR ALTER PROCEDURE StergeAtractie @nume VARCHAR(100)
AS
BEGIN
SET NOCOUNT ON;
IF(EXISTS(SELECT * FROM Atractii a JOIN Note n ON a.id_atractie = n.id_atractie WHERE a.nume = @nume))
    PRINT 'Exista note pentru aceasta atractie. Nu se poate sterge.';
ELSE
    DELETE FROM Atractii WHERE nume = @nume;
END;
GO

SELECT * FROM Atractii;
EXEC StergeAtractie 'Roller Coaster';
EXEC StergeAtractie 'Best Rollercoaster';

GO

-- Ex 3.2
CREATE OR ALTER PROCEDURE AdaugaNota @id_vizitator INT, @id_atractie INT, @nota INT
AS
BEGIN
SET NOCOUNT ON;
IF(NOT EXISTS(SELECT * FROM Vizitatori WHERE id_vizitator = @id_vizitator))
    PRINT 'Nu exista vizitator cu acest ID.';
ELSE IF(NOT EXISTS(SELECT * FROM Atractii WHERE id_atractie = @id_atractie))
    PRINT 'Nu exista atractie cu acest ID.';
ELSE IF(@nota < 1 OR @nota > 10)
    PRINT 'Nota trebuie sa fie intre 1 si 10.';
ELSE
    INSERT INTO Note(id_vizitator, id_atractie, nota) VALUES (@id_vizitator, @id_atractie, @nota);
END;
GO

SELECT * FROM Note;
EXEC AdaugaNota 10, 1, 9;
EXEC AdaugaNota 1, 10, 8;
EXEC AdaugaNota 1, 1, 11;
GO

-- Ex 3.3
