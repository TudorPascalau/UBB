USE Blog224;
GO

SELECT * From CuvinteCheie
GO

-- crearea unei functii scalare --
CREATE FUNCTION VerificaCuvantCheie(@nume VARCHAR(100))
RETURNS BIT
AS
BEGIN
    IF(EXISTS(SELECT * FROM CuvinteCheie WHERE nume = @nume))
        RETURN 1
    RETURN 0
END
GO

-- apelul functiei scalare --
PRINT(dbo.VerificaCuvantCheie('Pumpkin'));
PRINT(dbo.VerificaCuvantCheie('Milkshake'));
GO

-- modificarea functiei scalare --
ALTER FUNCTION VerificaCuvantCheie(@nume VARCHAR(100))
RETURNS VARCHAR(50)
AS
BEGIN
    IF(EXISTS(SELECT * FROM CuvinteCheie WHERE nume = @nume))
        RETURN 'Exista acest cuvant cheie'
    RETURN 'Nu exista acest cuvant cheie'
END
GO

PRINT(dbo.VerificaCuvantCheie('Pumpkin'));
PRINT(dbo.VerificaCuvantCheie('Milkshake'));
GO


-- stergerea functiei scalare --
DROP FUNCTION dbo.VerificaCuvantCheie
GO

-- functie inline table-valued --
CREATE OR ALTER FUNCTION ReturneazaPostari(@data_postarii DATETIME)
RETURNS TABLE AS
RETURN SELECT titlu, continut, data_postarii FROM Postari
WHERE data_postarii > @data_postarii
GO

INSERT INTO Postari(titlu, continut, data_postarii) VALUES
    ('postare1', 'continut1', '2000-02-03 12:12:12'),
    ('postare2', 'continut2', '1999-02-03 12:12:12');
GO

-- apelul functiei inline table-valued --
SELECT * FROM dbo.ReturneazaPostari('2000-02-02 12:12:12')
GO

-- crearea unui view --
CREATE OR ALTER VIEW vw_Postari AS
SELECT titlu, data_postarii FROM Postari
WHERE titlu LIKE 'p%'
GO

-- interogarea view-ului --
SELECT * FROM vw_Postari
GO

-- stergerea view-ului --
DROP VIEW vw_Postari
GO
