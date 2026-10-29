-- Exercitii laborator 05 -> 3 proceduri

USE LaboratorGestiuneJocuri;
GO

CREATE OR ALTER PROCEDURE GetMaxPriceByGenre @Genre NVARCHAR(50), @MaxPrice DECIMAL(10, 2) OUTPUT
AS
BEGIN
    SELECT @MaxPrice = MAX(G.price)
    FROM Games G
    INNER JOIN GameGenres GG ON G.game_id = GG.game_id
    INNER JOIN Genres GE ON GG.genre_id = GE.genre_id
    WHERE GE.name = @Genre;
END
GO

DECLARE @MaxPrice DECIMAL(10, 2);
EXEC GetMaxPriceByGenre @Genre = 'Puzzle', @MaxPrice = @MaxPrice OUTPUT;
PRINT @MaxPrice;
GO

CREATE OR ALTER PROCEDURE GetGamesByPriceRange @MinPrice DECIMAL(10, 2), @MaxPrice DECIMAL(10, 2)
AS
BEGIN
    SELECT G.game_id, G.title, G.price
    FROM GAMES G
    WHERE G.price BETWEEN @MinPrice AND @MaxPrice;
END
GO

EXEC GetGamesByPriceRange @MinPrice = 20.00, @MaxPrice = 50.00;
GO

CREATE OR ALTER PROCEDURE GetGamesByDeveloper @DeveloperName NVARCHAR(100)
AS
BEGIN
    SELECT G.game_id, G.title, G.price
    FROM GAMES G
    INNER JOIN GameCompanies GC ON G.game_id = GC.game_id
    INNER JOIN Companies C ON GC.company_id = C.company_id
    WHERE GC.role = 'developer' AND C.name = @DeveloperName;
END
GO

EXEC GetGamesByDeveloper @DeveloperName = 'Valve';
GO
