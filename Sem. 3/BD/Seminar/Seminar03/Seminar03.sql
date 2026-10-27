USE Blog224;
SELECT * FROM CuvinteCheie;
GO

--Crearea unei proceduri stocate
CREATE PROCEDURE AdaugaCuvantCheie @nume NVARCHAR(100)
AS
BEGIN
IF(EXISTS(SELECT * FROM CuvinteCheie WHERE nume = @nume))
	PRINT 'Acest cuvant cheie a fost deja adaugat in tabel!'
ELSE
	INSERT INTO CuvinteCheie(nume) VALUES(@nume)
END;
GO

--Apelarea procedurii stocate
EXEC AdaugaCuvantCheie N'Pumpkin';
SELECT * FROM CuvinteCheie;
GO

--Modificarea definitiei procedurii stocate
CREATE OR ALTER PROCEDURE AdaugaCuvantCheie @nume NVARCHAR(100)
AS
BEGIN
SET NOCOUNT ON;
IF(EXISTS(SELECT * FROM CuvinteCheie WHERE nume = @nume))
	PRINT 'Acest cuvant cheie a fost deja adaugat in tabel!'
ELSE
	INSERT INTO CuvinteCheie(nume) VALUES(@nume)
END;
GO

EXEC AdaugaCuvantCheie N'Cat';
SELECT * FROM CuvinteCheie;
GO

--Stergerea unei proceduri stocate
DROP PROCEDURE AdaugaCuvantCheie
