USE LaboratorGestiuneJocuri;
GO

CREATE TABLE Users
(
    user_id INT IDENTITY(1,1),
    username NVARCHAR(50) NOT NULL,
    email NVARCHAR(254) NOT NULL,
    password_hash VARCHAR(255) NOT NULL,
    registered_at DATETIME2 NOT NULL DEFAULT (SYSDATETIME()),

    CONSTRAINT PK_Users PRIMARY KEY (user_id),
    CONSTRAINT UQ_Users_Username UNIQUE (username),
    CONSTRAINT UQ_Users_Email UNIQUE (email)
);
GO

CREATE TABLE Games
(
    game_id INT IDENTITY(1,1),
    title NVARCHAR(200) NOT NULL,
    description NVARCHAR(MAX) NULL,
    release_date DATE NULL,
    price DECIMAL(10,2) NOT NULL,

    CONSTRAINT PK_Games PRIMARY KEY (game_id),
    CONSTRAINT CK_Games_Price CHECK (price >= 0)
);
GO

CREATE TABLE Genres
(
    genre_id INT IDENTITY(1,1),
    name NVARCHAR(50) NOT NULL,

    CONSTRAINT PK_Genres PRIMARY KEY (genre_id),
    CONSTRAINT UQ_Genres_Name UNIQUE (name)
);
GO

CREATE TABLE Platforms
(
    platform_id INT IDENTITY(1,1),
    name NVARCHAR(50) NOT NULL,

    CONSTRAINT PK_Platforms PRIMARY KEY (platform_id),
    CONSTRAINT UQ_Platforms_Name UNIQUE (name)
);
GO

CREATE TABLE Companies
(
    company_id INT IDENTITY(1,1),
    name NVARCHAR(150) NOT NULL,
    country NVARCHAR(100) NULL,
    website NVARCHAR(500) NULL,

    CONSTRAINT PK_Companies PRIMARY KEY (company_id)
);
GO

CREATE TABLE Achievements
(
    achievement_id INT IDENTITY(1,1),
    game_id INT NOT NULL,
    name NVARCHAR(150) NOT NULL,
    description NVARCHAR(1000) NULL,

    CONSTRAINT PK_Achievements
        PRIMARY KEY (achievement_id),

    CONSTRAINT FK_Achievements_Games
        FOREIGN KEY (game_id)
        REFERENCES Games(game_id),

    CONSTRAINT UQ_Achievements_Game_Name
        UNIQUE (game_id, name)
);
GO

CREATE TABLE GameCompanies
(
    game_id INT NOT NULL,
    company_id INT NOT NULL,
    role VARCHAR(20) NOT NULL,

    CONSTRAINT PK_GameCompanies
        PRIMARY KEY (game_id, company_id),

    CONSTRAINT FK_GameCompanies_Games
        FOREIGN KEY (game_id)
        REFERENCES Games(game_id),

    CONSTRAINT FK_GameCompanies_Companies
        FOREIGN KEY (company_id)
        REFERENCES Companies(company_id),

    CONSTRAINT CK_GameCompanies_Role
        CHECK (role IN ('developer', 'publisher'))
);
GO

CREATE TABLE GameGenres
(
    game_id INT NOT NULL,
    genre_id INT NOT NULL,

    CONSTRAINT PK_GameGenres
        PRIMARY KEY (game_id, genre_id),

    CONSTRAINT FK_GameGenres_Games
        FOREIGN KEY (game_id)
        REFERENCES Games(game_id),

    CONSTRAINT FK_GameGenres_Genres
        FOREIGN KEY (genre_id)
        REFERENCES Genres(genre_id)
);
GO

CREATE TABLE UserAchievements
(
    user_id INT NOT NULL,
    achievement_id INT NOT NULL,
    unlocked_at DATETIME2 NOT NULL DEFAULT (SYSDATETIME()),

    CONSTRAINT PK_UserAchievements
        PRIMARY KEY (user_id, achievement_id),

    CONSTRAINT FK_UserAchievements_Users
        FOREIGN KEY (user_id)
        REFERENCES Users(user_id),

    CONSTRAINT FK_UserAchievements_Achievements
        FOREIGN KEY (achievement_id)
        REFERENCES Achievements(achievement_id)
);
GO

CREATE TABLE GamePlatforms
(
    game_id INT NOT NULL,
    platform_id INT NOT NULL,

    CONSTRAINT PK_GamePlatforms
        PRIMARY KEY (game_id, platform_id),

    CONSTRAINT FK_GamePlatforms_Games
        FOREIGN KEY (game_id)
        REFERENCES Games(game_id),

    CONSTRAINT FK_GamePlatforms_Platforms
        FOREIGN KEY (platform_id)
        REFERENCES Platforms(platform_id)
);
GO

CREATE TABLE Reviews
(
    review_id INT IDENTITY(1,1),
    user_id INT NOT NULL,
    game_id INT NOT NULL,
    rating INT NOT NULL,
    content NVARCHAR(2000) NULL,
    created_at DATETIME2 NOT NULL DEFAULT (SYSDATETIME()),

    CONSTRAINT PK_Reviews
        PRIMARY KEY (review_id),

    CONSTRAINT FK_Reviews_Users
        FOREIGN KEY (user_id)
        REFERENCES Users(user_id),

    CONSTRAINT FK_Reviews_Games
        FOREIGN KEY (game_id)
        REFERENCES Games(game_id),

    CONSTRAINT UQ_Reviews_User_Game
        UNIQUE (user_id, game_id),

    CONSTRAINT CK_Reviews_Rating
        CHECK (rating BETWEEN 1 AND 10)
);
GO

CREATE TABLE Orders
(
    order_id INT IDENTITY(1,1),
    user_id INT NOT NULL,
    ordered_at DATETIME2 NOT NULL DEFAULT (SYSDATETIME()),
    status VARCHAR(20) NOT NULL DEFAULT ('pending'),

    CONSTRAINT PK_Orders
        PRIMARY KEY (order_id),

    CONSTRAINT FK_Orders_Users
        FOREIGN KEY (user_id)
        REFERENCES Users(user_id),

    CONSTRAINT CK_Orders_Status
        CHECK (status IN ('pending', 'completed', 'cancelled'))
);
GO

CREATE TABLE OrderItems
(
    order_id INT NOT NULL,
    game_id INT NOT NULL,
    purchase_price DECIMAL(10,2) NOT NULL,

    CONSTRAINT PK_OrderItems
        PRIMARY KEY (order_id, game_id),

    CONSTRAINT FK_OrderItems_Orders
        FOREIGN KEY (order_id)
        REFERENCES Orders(order_id),

    CONSTRAINT FK_OrderItems_Games
        FOREIGN KEY (game_id)
        REFERENCES Games(game_id),

    CONSTRAINT CK_OrderItems_PurchasePrice
        CHECK (purchase_price >= 0)
);
GO

CREATE TABLE Collections
(
    collection_id INT IDENTITY(1,1),
    user_id INT NOT NULL,
    name NVARCHAR(100) NOT NULL,
    created_at DATETIME2 NOT NULL DEFAULT (SYSDATETIME()),

    CONSTRAINT PK_Collections
        PRIMARY KEY (collection_id),

    CONSTRAINT FK_Collections_Users
        FOREIGN KEY (user_id)
        REFERENCES Users(user_id),

    CONSTRAINT UQ_Collections_User_Name
        UNIQUE (user_id, name),

    CONSTRAINT UQ_Collections_Collection_User
        UNIQUE (collection_id, user_id)
);
GO

CREATE TABLE UserGames
(
    user_id INT NOT NULL,
    game_id INT NOT NULL,
    collection_id INT NOT NULL,
    added_at DATETIME2 NOT NULL DEFAULT (SYSDATETIME()),

    CONSTRAINT PK_UserGames
        PRIMARY KEY (user_id, game_id),

    CONSTRAINT FK_UserGames_Users
        FOREIGN KEY (user_id)
        REFERENCES Users(user_id),

    CONSTRAINT FK_UserGames_Games
        FOREIGN KEY (game_id)
        REFERENCES Games(game_id),

    CONSTRAINT FK_UserGames_Collections
        FOREIGN KEY (collection_id, user_id)
        REFERENCES Collections(collection_id, user_id)
);
GO

CREATE TABLE GameSessions
(
    session_id INT IDENTITY(1,1),
    user_id INT NOT NULL,
    game_id INT NOT NULL,
    started_at DATETIME2 NOT NULL DEFAULT (SYSDATETIME()),
    ended_at DATETIME2 NULL,

    CONSTRAINT PK_GameSessions
        PRIMARY KEY (session_id),

    CONSTRAINT FK_GameSessions_UserGames
        FOREIGN KEY (user_id, game_id)
        REFERENCES UserGames(user_id, game_id),

    CONSTRAINT CK_GameSessions_Dates
        CHECK (ended_at IS NULL OR ended_at >= started_at)
);
GO

CREATE TABLE Friendships
(
    user_id_1 INT NOT NULL,
    user_id_2 INT NOT NULL,
    requested_by INT NOT NULL,
    status VARCHAR(20) NOT NULL DEFAULT ('pending'),
    requested_at DATETIME2 NOT NULL DEFAULT (SYSDATETIME()),
    responded_at DATETIME2 NULL,

    CONSTRAINT PK_Friendships
        PRIMARY KEY (user_id_1, user_id_2),

    CONSTRAINT FK_Friendships_User1
        FOREIGN KEY (user_id_1)
        REFERENCES Users(user_id),

    CONSTRAINT FK_Friendships_User2
        FOREIGN KEY (user_id_2)
        REFERENCES Users(user_id),

    CONSTRAINT FK_Friendships_RequestedBy
        FOREIGN KEY (requested_by)
        REFERENCES Users(user_id),

    CONSTRAINT CK_Friendships_UserOrder
        CHECK (user_id_1 < user_id_2),

    CONSTRAINT CK_Friendships_RequestedBy
        CHECK (requested_by IN (user_id_1, user_id_2)),

    CONSTRAINT CK_Friendships_Status
        CHECK (status IN ('pending', 'accepted', 'rejected', 'cancelled')),

    CONSTRAINT CK_Friendships_Dates
        CHECK (responded_at IS NULL OR responded_at >= requested_at)
);
GO

