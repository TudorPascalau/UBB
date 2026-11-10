USE LaboratorGestiuneJocuri;
GO

-- Materialized / Indexed View
CREATE VIEW dbo.V_RPGGames
WITH SCHEMABINDING
AS
SELECT G.game_id, G.title
FROM dbo.Games G
INNER JOIN dbo.GameGenres GG ON G.game_id = GG.game_id
INNER JOIN dbo.Genres GN ON GG.genre_id = GN.genre_id
WHERE GN.name = 'RPG';
GO

CREATE UNIQUE CLUSTERED INDEX IX_V_RPGGames ON dbo.V_RPGGames(game_id);
GO

SELECT * FROM dbo.V_RPGGames
WITH (NOEXPAND);
GO

-- Non-Materialized View
CREATE VIEW dbo.V_RPGGames_NonMaterialized
AS
SELECT G.game_id, G.title
FROM dbo.Games G
INNER JOIN dbo.GameGenres GG ON G.game_id = GG.game_id
INNER JOIN dbo.Genres GN ON GG.genre_id = GN.genre_id
WHERE GN.name = 'RPG';
GO

SELECT * FROM dbo.V_RPGGames_NonMaterialized
--WITH (NOEXPAND);
GO
