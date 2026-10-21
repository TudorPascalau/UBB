USE LaboratorGestiuneJocuri;
GO

SET XACT_ABORT ON;
BEGIN TRANSACTION;

-- 1. Users: IDs 1-10.
INSERT INTO Users (username, email, password_hash)
VALUES
    (N'tudor', N'tudor@example.com',
        CONVERT(VARCHAR(64), HASHBYTES('SHA2_256', 'PortalFan01!'), 2)),
    (N'andrew', N'andrew@example.com',
        CONVERT(VARCHAR(64), HASHBYTES('SHA2_256', 'DarkSouls02!'), 2)),
    (N'mary', N'mary@example.com',
        CONVERT(VARCHAR(64), HASHBYTES('SHA2_256', 'PuzzleMaster03!'), 2)),
    (N'helen', N'helen@example.com',
        CONVERT(VARCHAR(64), HASHBYTES('SHA2_256', 'SurvivalHorror04!'), 2)),
    (N'victor', N'victor@example.com',
        CONVERT(VARCHAR(64), HASHBYTES('SHA2_256', 'EldenLord05!'), 2)),
    (N'jane', N'jane@example.com',
        CONVERT(VARCHAR(64), HASHBYTES('SHA2_256', 'HalfLife06!'), 2)),
    (N'alex', N'alex@example.com',
        CONVERT(VARCHAR(64), HASHBYTES('SHA2_256', 'AshenOne07!'), 2)),
    (N'anna', N'anna@example.com',
        CONVERT(VARCHAR(64), HASHBYTES('SHA2_256', 'OpenWorld08!'), 2)),
    (N'michael', N'michael@example.com',
        CONVERT(VARCHAR(64), HASHBYTES('SHA2_256', 'ClassicGames09!'), 2)),
    (N'rachel', N'rachel@example.com',
        CONVERT(VARCHAR(64), HASHBYTES('SHA2_256', 'ResidentEvil10!'), 2));

-- 2. Games: IDs 1-8.
-- Prices and descriptions are sample data.
INSERT INTO Games (title, description, release_date, price)
VALUES
    (N'Portal',
     N'Solve puzzles using interconnected portals.',
     NULL, 9.99),
    (N'Portal 2',
     N'A puzzle adventure set in the Aperture Science laboratories.',
     NULL, 19.99),
    (N'Half-Life 2',
     N'A first-person science fiction adventure.',
     NULL, 9.99),
    (N'Resident Evil',
     N'Survive and explore a mysterious mansion.',
     NULL, 19.99),
    (N'Resident Evil 4',
     N'An action-packed survival horror adventure.',
     NULL, 39.99),
    (N'Dark Souls',
     N'Explore a dark fantasy world and overcome challenging enemies.',
     NULL, 39.99),
    (N'Dark Souls III',
     N'An action RPG featuring challenging boss battles.',
     NULL, 59.99),
    (N'Elden Ring',
     N'Explore a vast open world filled with fantasy creatures.',
     NULL, 59.99);

-- 3. Genres: IDs 1-6.
INSERT INTO Genres (name)
VALUES
    (N'Puzzle'),
    (N'Action'),
    (N'Adventure'),
    (N'Survival Horror'),
    (N'RPG'),
    (N'Open World');

-- 4. Platforms: IDs 1-3.
INSERT INTO Platforms (name)
VALUES
    (N'PC'),
    (N'PlayStation 4'),
    (N'Xbox One');

-- 5. Companies: IDs 1-4.
INSERT INTO Companies (name, country, website)
VALUES
    (N'Valve',        N'United States', NULL),
    (N'Capcom',       N'Japan',         NULL),
    (N'FromSoftware', N'Japan',         NULL),
    (N'Bandai Namco', N'Japan',         NULL);

-- 6. Game-company relationships.
-- The primary key permits only one role per game-company pair.
INSERT INTO GameCompanies (game_id, company_id, role)
VALUES
    (1, 1, 'developer'),
    (2, 1, 'developer'),
    (3, 1, 'developer'),
    (4, 2, 'developer'),
    (5, 2, 'developer'),
    (6, 3, 'developer'),
    (6, 4, 'publisher'),
    (7, 3, 'developer'),
    (7, 4, 'publisher'),
    (8, 3, 'developer'),
    (8, 4, 'publisher');

-- 7. Game-genre relationships.
INSERT INTO GameGenres (game_id, genre_id)
VALUES
    (1, 1), (1, 3),
    (2, 1), (2, 3),
    (3, 2), (3, 3),
    (4, 3), (4, 4),
    (5, 2), (5, 4),
    (6, 2), (6, 5),
    (7, 2), (7, 5),
    (8, 2), (8, 5), (8, 6);

-- 8. Game-platform relationships.
INSERT INTO GamePlatforms (game_id, platform_id)
VALUES
    (1, 1),
    (2, 1),
    (3, 1),
    (4, 1), (4, 2), (4, 3),
    (5, 1), (5, 2), (5, 3),
    (6, 1),
    (7, 1), (7, 2), (7, 3),
    (8, 1), (8, 2), (8, 3);

-- 9. Sample achievements: IDs 1-10.
INSERT INTO Achievements (game_id, name, description)
VALUES
    (1, N'First Portal',      N'Solve the first puzzle.'),
    (1, N'Experiment Over',   N'Complete the game.'),
    (2, N'Back to Testing',   N'Complete the first chapter.'),
    (3, N'Welcome',           N'Begin your adventure.'),
    (4, N'Survivor',          N'Survive the first encounter.'),
    (5, N'Mission Started',   N'Complete the first section.'),
    (6, N'First Bonfire',     N'Light your first bonfire.'),
    (6, N'First Victory',     N'Defeat the first boss.'),
    (7, N'Ash and Fire',      N'Defeat the first boss.'),
    (8, N'First Steps',       N'Discover your first resting place.');

-- 10. Collections: IDs 1-10.
INSERT INTO Collections (user_id, name)
VALUES
    (1,  N'Favorites'),
    (2,  N'To Finish'),
    (3,  N'Puzzle Games'),
    (4,  N'Horror Games'),
    (5,  N'Role-Playing Games'),
    (6,  N'My Library'),
    (7,  N'Action Games'),
    (8,  N'Exploration'),
    (9,  N'Classics'),
    (10, N'Favorites');

-- 11. Orders: IDs 1-10.
INSERT INTO Orders (user_id, ordered_at, status)
VALUES
    (1,  '2026-10-01T10:00:00', 'completed'),
    (2,  '2026-10-02T11:00:00', 'completed'),
    (3,  '2026-10-03T12:00:00', 'completed'),
    (4,  '2026-10-04T13:00:00', 'completed'),
    (5,  '2026-10-05T14:00:00', 'completed'),
    (6,  '2026-10-06T15:00:00', 'completed'),
    (7,  '2026-10-07T16:00:00', 'completed'),
    (8,  '2026-10-08T17:00:00', 'completed'),
    (9,  '2026-10-09T18:00:00', 'pending'),
    (10, '2026-10-10T19:00:00', 'cancelled');

-- 12. Order items.
INSERT INTO OrderItems (order_id, game_id, purchase_price)
VALUES
    (1, 1, 9.99),  (1, 2, 19.99),
    (2, 6, 39.99), (2, 7, 59.99),
    (3, 2, 19.99),
    (4, 4, 19.99), (4, 5, 39.99),
    (5, 8, 59.99),
    (6, 3, 9.99),
    (7, 7, 59.99),
    (8, 8, 59.99),
    (9, 1, 9.99),
    (10, 5, 39.99);

-- 13. User libraries.
-- Each collection belongs to the specified user.
-- Only completed orders add games to these sample libraries.
INSERT INTO UserGames (user_id, game_id, collection_id, added_at)
VALUES
    (1, 1, 1, '2026-10-01T10:05:00'),
    (1, 2, 1, '2026-10-01T10:05:00'),
    (2, 6, 2, '2026-10-02T11:05:00'),
    (2, 7, 2, '2026-10-02T11:05:00'),
    (3, 2, 3, '2026-10-03T12:05:00'),
    (4, 4, 4, '2026-10-04T13:05:00'),
    (4, 5, 4, '2026-10-04T13:05:00'),
    (5, 8, 5, '2026-10-05T14:05:00'),
    (6, 3, 6, '2026-10-06T15:05:00'),
    (7, 7, 7, '2026-10-07T16:05:00'),
    (8, 8, 8, '2026-10-08T17:05:00');

-- 14. Game sessions.
-- The final session is still in progress.
INSERT INTO GameSessions (user_id, game_id, started_at, ended_at)
VALUES
    (1, 1, '2026-10-11T10:00:00', '2026-10-11T11:30:00'),
    (1, 2, '2026-10-12T14:00:00', '2026-10-12T16:00:00'),
    (2, 6, '2026-10-11T18:00:00', '2026-10-11T20:00:00'),
    (2, 7, '2026-10-12T18:00:00', '2026-10-12T19:30:00'),
    (3, 2, '2026-10-13T09:00:00', '2026-10-13T10:00:00'),
    (4, 4, '2026-10-13T20:00:00', '2026-10-13T22:00:00'),
    (4, 5, '2026-10-14T19:00:00', '2026-10-14T21:00:00'),
    (5, 8, '2026-10-14T16:00:00', '2026-10-14T18:30:00'),
    (6, 3, '2026-10-15T10:00:00', '2026-10-15T12:00:00'),
    (7, 7, '2026-10-15T18:00:00', '2026-10-15T20:00:00'),
    (8, 8, '2026-10-21T08:00:00', NULL);

-- 15. Unlocked achievements.
INSERT INTO UserAchievements (user_id, achievement_id, unlocked_at)
VALUES
    (1, 1,  '2026-10-11T10:15:00'),
    (1, 3,  '2026-10-12T15:00:00'),
    (2, 7,  '2026-10-11T18:10:00'),
    (2, 8,  '2026-10-11T19:00:00'),
    (2, 9,  '2026-10-12T19:00:00'),
    (3, 3,  '2026-10-13T09:50:00'),
    (4, 5,  '2026-10-13T20:30:00'),
    (4, 6,  '2026-10-14T20:30:00'),
    (5, 10, '2026-10-14T16:15:00'),
    (6, 4,  '2026-10-15T10:10:00'),
    (7, 9,  '2026-10-15T19:00:00');

-- 16. Reviews.
INSERT INTO Reviews (user_id, game_id, rating, content, created_at)
VALUES
    (1, 1, 10, N'Inventive puzzles and an excellent atmosphere.',
     '2026-10-16T10:00:00'),
    (1, 2, 10, N'Varied puzzles and memorable dialogue.',
     '2026-10-16T10:10:00'),
    (2, 6, 9, N'Challenging but rewarding.',
     '2026-10-16T11:00:00'),
    (2, 7, 9, N'Intense combat and spectacular boss battles.',
     '2026-10-16T11:10:00'),
    (3, 2, 9, N'A great experience for puzzle fans.',
     '2026-10-16T12:00:00'),
    (4, 4, 8, N'A tense atmosphere and enjoyable exploration.',
     '2026-10-16T13:00:00'),
    (4, 5, 9, N'Engaging action from start to finish.',
     '2026-10-16T13:10:00'),
    (5, 8, 10, N'A vast world filled with discoveries.',
     '2026-10-16T14:00:00'),
    (6, 3, 9, N'A memorable science fiction adventure.',
     '2026-10-16T15:00:00'),
    (7, 7, 8, N'Challenging and entertaining.',
     '2026-10-16T16:00:00');

-- 17. Friendships.
-- user_id_1 < user_id_2.
-- requested_by must be one of the two users.
INSERT INTO Friendships
    (user_id_1, user_id_2, requested_by, status, requested_at, responded_at)
VALUES
    (1, 2, 1, 'accepted',
     '2026-10-10T10:00:00', '2026-10-10T11:00:00'),
    (1, 3, 3, 'accepted',
     '2026-10-11T10:00:00', '2026-10-11T12:00:00'),
    (2, 4, 2, 'pending',
     '2026-10-12T10:00:00', NULL),
    (3, 5, 5, 'rejected',
     '2026-10-13T10:00:00', '2026-10-13T11:00:00'),
    (4, 6, 4, 'accepted',
     '2026-10-14T10:00:00', '2026-10-14T12:00:00'),
    (5, 7, 7, 'cancelled',
     '2026-10-15T10:00:00', '2026-10-15T11:00:00'),
    (6, 8, 6, 'pending',
     '2026-10-16T10:00:00', NULL),
    (7, 9, 9, 'accepted',
     '2026-10-17T10:00:00', '2026-10-17T12:00:00'),
    (8, 10, 8, 'accepted',
     '2026-10-18T10:00:00', '2026-10-18T11:00:00');

COMMIT TRANSACTION;
GO