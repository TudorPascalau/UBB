USE LaboratorGestiuneJocuri;
GO

--1. Jocuri care costa cel mult 20 unitati monetare
SELECT G.game_id, G.title, G.price FROM GAMES G
WHERE G.price <= 20;

--2. Jocuri RPG si preturile lor
SELECT G.game_id, G.title, GE.name AS genre, G.price
FROM GAMES G
INNER JOIN GameGenres GG ON G.game_id = GG.game_id
INNER JOIN Genres GE ON GG.genre_id = GE.genre_id
WHERE GE.name = 'RPG';

--3. Jocuri disponibile pe Linux
SELECT G.game_id, G.title, P.name AS platform
FROM Games G
INNER JOIN GamePlatforms GP on G.game_id = GP.game_id
INNER JOIN Platforms P on GP.platform_id = P.platform_id
WHERE P.name = 'Linux';

--4. Jocuri dezvoltate de Valve
SELECT G.game_id, G.title, C.name AS company
FROM Games G
INNER JOIN GameCompanies GC on G.game_id = GC.game_id
INNER JOIN Companies C on GC.company_id = C.company_id
WHERE C.name = 'Valve';

--5. Recenziile cu note de cel putin 9, impreună cu autorul si jocul
SELECT R.review_id, R.rating, R.content, U.username AS author, G.title AS game
FROM Reviews R
INNER JOIN Users U on R.user_id = U.user_id
INNER JOIN Games G on R.game_id = G.game_id
WHERE R.rating >= 9;

--6. Genurile distincte din biblioteca utilizatorului 'tudor'
SELECT DISTINCT GE.name AS genre
FROM Users U
INNER JOIN UserGames UG on U.user_id = UG.user_id
INNER JOIN Games G on UG.game_id = G.game_id
INNER JOIN GameGenres GG on G.game_id = GG.game_id
INNER JOIN Genres GE on GG.genre_id = GE.genre_id
WHERE U.username = 'tudor';

--7. Utilizatorii care au cumparat cel putin un joc din seria Dark Souls, prin comenzi finalizate
SELECT DISTINCT U.username
FROM Users U
INNER JOIN Orders O on U.user_id = O.user_id
INNER JOIN OrderItems OG on O.order_id = OG.order_id
INNER JOIN Games G on OG.game_id = G.game_id
WHERE G.title LIKE '%Dark Souls%' AND O.status = 'completed';

--8. Numarul de jocuri din fiecare colectie (inclusiv colectiile goale)
SELECT U.username, C.name AS collection_name, COUNT(UG.game_id) AS game_count
FROM Users U
INNER JOIN Collections C ON U.user_id = C.user_id
LEFT JOIN UserGames UG ON C.collection_id = UG.collection_id AND C.user_id = UG.user_id
GROUP BY U.user_id, U.username, C.collection_id, C.name;

--9. Jocurile care au cel putin doua recenzii, cu media notelor
SELECT G.game_id, G.title, AVG(R.rating) AS average_rating
FROM Games G
INNER JOIN Reviews R on G.game_id = R.game_id
GROUP BY G.game_id, G.title
HAVING COUNT(R.review_id) >= 2;

--10. Utilizatorii care au cheltuit peste 50 in comenzi finalizate
SELECT U.username, SUM(OG.purchase_price) AS total_spent
FROM Users U
INNER JOIN Orders O on U.user_id = O.user_id
INNER JOIN OrderItems OG on O.order_id = OG.order_id
WHERE O.status = 'completed'
GROUP BY U.user_id, U.username
HAVING SUM(OG.purchase_price) >= 50
