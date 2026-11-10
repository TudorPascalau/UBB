USE LaboratorGestiuneJocuri;
GO

CREATE TABLE versionTable
(
    version INT NOT NULL,

    CONSTRAINT CK_versionTable_Version
        CHECK (version BETWEEN 1 AND 6)
);
GO

INSERT INTO versionTable (version)
VALUES (1);
GO

CREATE TABLE procedureTable
(
    initial_version INT NOT NULL,
    final_version INT NOT NULL,
    procedure_name VARCHAR(128) NOT NULL,

    CONSTRAINT PK_procedureTable
        PRIMARY KEY (initial_version, final_version)
);
GO

INSERT INTO procedureTable
    (initial_version, final_version, procedure_name)
VALUES
    (1, 2, 'Up1_ChangePasswordHashToNvarchar'),
    (2, 1, 'Down1_RestorePasswordHashVarchar'),

    (2, 3, 'Up2_AddGamePriceDefault'),
    (3, 2, 'Down2_DropGamePriceDefault'),

    (3, 4, 'Up3_CreateWishlistItems'),
    (4, 3, 'Down3_DropWishlistItems'),

    (4, 5, 'Up4_AddSystemRequirements'),
    (5, 4, 'Down4_DropSystemRequirements'),

    (5, 6, 'Up5_AddReviewsUserGamesForeignKey'),
    (6, 5, 'Down5_DropReviewsUserGamesForeignKey');
GO

-- Versiunea 1: modificarea tipului unei coloane

CREATE OR ALTER PROCEDURE Up1_ChangePasswordHashToNvarchar
AS
BEGIN
    ALTER TABLE Users
    ALTER COLUMN password_hash NVARCHAR(255) NOT NULL;
END;
GO

CREATE OR ALTER PROCEDURE Down1_RestorePasswordHashVarchar
AS
BEGIN
    ALTER TABLE Users
    ALTER COLUMN password_hash VARCHAR(255) NOT NULL;
END;
GO


-- Versiunea 2: adaugarea unei constrangeri DEFAULT

CREATE OR ALTER PROCEDURE Up2_AddGamePriceDefault
AS
BEGIN
    ALTER TABLE Games
    ADD CONSTRAINT DF_Games_Price DEFAULT (0) FOR price;
END;
GO

CREATE OR ALTER PROCEDURE Down2_DropGamePriceDefault
AS
BEGIN
    ALTER TABLE Games
    DROP CONSTRAINT DF_Games_Price;
END;
GO


-- Versiunea 3: crearea unei tabele

CREATE OR ALTER PROCEDURE Up3_CreateWishlistItems
AS
BEGIN
    CREATE TABLE WishlistItems
    (
        user_id INT NOT NULL,
        game_id INT NOT NULL,
        added_at DATETIME2 NOT NULL
        CONSTRAINT DF_WishlistItems_AddedAt
            DEFAULT (SYSDATETIME()),

        CONSTRAINT PK_WishlistItems
            PRIMARY KEY (user_id, game_id),

        CONSTRAINT FK_WishlistItems_Games
            FOREIGN KEY (game_id)
            REFERENCES Games(game_id),

        CONSTRAINT FK_WishlistItems_Users
            FOREIGN KEY (user_id)
            REFERENCES Users(user_id)
    );
END;
GO

CREATE OR ALTER PROCEDURE Down3_DropWishlistItems
AS
BEGIN
    DROP TABLE IF EXISTS WishlistItems;
END;
GO


-- Versiunea 4: adaugarea unei coloane

CREATE OR ALTER PROCEDURE Up4_AddSystemRequirements
AS
BEGIN
    ALTER TABLE Games
    ADD system_requirements NVARCHAR(2000) NULL;
END;
GO

CREATE OR ALTER PROCEDURE Down4_DropSystemRequirements
AS
BEGIN
    ALTER TABLE Games
    DROP COLUMN system_requirements;
END;
GO


-- Versiunea 5: adaugarea unei chei straine

CREATE OR ALTER PROCEDURE Up5_AddReviewsUserGamesForeignKey
AS
BEGIN
    ALTER TABLE Reviews WITH CHECK
    ADD CONSTRAINT FK_Reviews_UserGames
        FOREIGN KEY (user_id, game_id)
        REFERENCES UserGames(user_id, game_id);
END;
GO

CREATE OR ALTER PROCEDURE Down5_DropReviewsUserGamesForeignKey
AS
BEGIN
    ALTER TABLE Reviews
    DROP CONSTRAINT FK_Reviews_UserGames;
END;
GO

-- Procedura schimbare versiune

CREATE OR ALTER PROCEDURE goToVersion @newVersion INT
AS
BEGIN
    DECLARE @current_version INT;
    DECLARE @procedureName VARCHAR(128);

    SELECT @current_version = version
    FROM versionTable;

    IF @newVersion IS NULL OR @newVersion < 1 OR @newVersion > 6
    BEGIN
        PRINT 'Versiune invalida! Alege o versiune intre 1 si 6.';
        RETURN;
    END;

    IF @newVersion = @current_version
    BEGIN
        PRINT 'Baza de date este deja la versiunea ceruta!';
        RETURN;
    END;

    WHILE @current_version > @newVersion
    BEGIN
        SELECT @procedureName = procedure_name
        FROM procedureTable
        WHERE initial_version = @current_version
            AND final_version = @current_version - 1;

        PRINT ('Executing ' + @procedureName);

        BEGIN TRY
            EXEC @procedureName;
        END TRY
        BEGIN CATCH
            THROW;
        END CATCH;

        SET @current_version = @current_version - 1;

        UPDATE versionTable
        SET version = @current_version;
    END;

    WHILE @current_version < @newVersion
    BEGIN
        SELECT @procedureName = procedure_name
        FROM procedureTable
        WHERE initial_version = @current_version
          AND final_version = @current_version + 1;

        PRINT ('Executing ' + @procedureName);

        BEGIN TRY
            EXEC @procedureName;
        END TRY
        BEGIN CATCH
            THROW;
        END CATCH;

        SET @current_version = @current_version + 1;

        UPDATE versionTable
        SET version = @current_version;
    END;
END;
GO
