USE LaboratorGestiuneJocuri;
GO

-- 1.Afișează titlul și prețul jocurilor care costă între 15 și 45, inclusiv.
SELECT G.title, G.price
FROM Games G
WHERE 15 <= G.price AND G.price <= 45;

-- 2.Afișează jocurile al căror titlu începe cu „Resident” sau conține „Souls”.
SELECT G.title
FROM GAMES G
WHERE G.title LIKE 'Resident%' OR G.title LIKE '%Souls%';

-- 3.Afișează numele și țara companiilor care nu au un website completat.
SELECT C.name, C.country
FROM Companies C
WHERE C.website IS NULL;

-- 4.Afișează identificatorul utilizatorului, identificatorul jocului și momentul începerii pentru sesiunile de joc încă neîncheiate.
SELECT GS.user_id, GS.game_id, GS.started_at
FROM GameSessions GS
WHERE GS.ended_at IS NULL;

-- 5. Afișează titlul, prețul și numele dezvoltatorului pentru jocurile dezvoltate de companii din Japonia. Ia în considerare numai asocierile cu rolul developer.
SELECT G.title, G.price, C.name AS developer_name
FROM Games G
INNER JOIN GameCompanies GC on G.game_id = GC.game_id
INNER JOIN Companies C on GC.company_id = C.company_id
WHERE C.country = 'Japan';

-- 6. Afișează, fără duplicate, titlurile jocurilor din genul „Action” disponibile pe „Linux”.
SELECT DISTINCT G.title
FROM Games G
INNER JOIN GameGenres GG ON G.game_id = GG.game_id
INNER JOIN Genres GE ON GG.genre_id = GE.genre_id
INNER JOIN GamePlatforms GP ON GG.game_id = GP.game_id
INNER JOIN Platforms P ON P.platform_id = GP.platform_id
WHERE GE.name = 'ACTION' AND P.name = 'Linux';

-- 7. Afișează utilizatorul, numele colecției și titlul jocului pentru jocurile din bibliotecă ce aparțin genului „Adventure”.
SELECT U.username, C.name, G.title
FROM Genres GE
INNER JOIN GameGenres GG ON GE.genre_id = GG.genre_id
INNER JOIN Games G ON GG.game_id = G.game_id 
INNER JOIN UserGames UG ON G.game_id = UG.game_id
INNER JOIN Collections C ON UG.collection_id = C.collection_id
INNER JOIN Users U ON C.user_id = U.user_id
WHERE GE.name = 'Adventure';

-- 8. Afișează utilizatorul, jocul, nota și conținutul recenziilor acordate jocurilor dezvoltate de „FromSoftware”
SELECT U.username, G.title, R.rating, R.content
FROM Companies C
INNER JOIN GameCompanies GC ON C.company_id = GC.company_id
INNER JOIN Games G ON GC.game_id = G.game_id
INNER JOIN Reviews R ON G.game_id = R.game_id
INNER JOIN Users U ON R.user_id = U.user_id
WHERE GC.role = 'developer' AND C.name = 'FromSoftware';

-- 9.Afișează utilizatorul, numele realizării și titlul jocului pentru realizările deblocate în intervalul 11–14 octombrie 2026, inclusiv.
SELECT U.username, A.name, G.title
FROM UserAchievements UA
INNER JOIN Users U ON UA.user_id = U.user_id
INNER JOIN Achievements A ON UA.achievement_id = A.achievement_id
INNER JOIN Games G on A.game_id = G.game_id
WHERE UA.unlocked_at BETWEEN '2026-10-11 00:00:00' AND '2026-10-14 00:00:00'

-- 10.Afișează, fără duplicate, utilizatorii care au cumpărat cel puțin un joc din genul „RPG” printr-o comandă finalizată.
SELECT DISTINCT U.username
FROM Orders O
INNER JOIN Users U ON O.user_id = U.user_id
INNER JOIN OrderItems OI ON O.order_id = OI.order_id
INNER JOIN GameGenres GG ON OI.game_id = GG.game_id
INNER JOIN Genres GE ON GG.genre_id = GE.genre_id
WHERE O.status = 'completed' AND GE.name = 'RPG';

-- 11. Afișează toate jocurile împreună cu notele primite și numele autorilor recenziilor. Include și jocurile fără recenzii.
SELECT G.title, R.rating, U.username
FROM Games G
LEFT OUTER JOIN UserGames UG ON G.game_id = UG.game_id
LEFT OUTER JOIN Users U ON UG.user_id = U.user_id
LEFT OUTER JOIN Reviews R ON U.user_id = R.user_id

-- 12. Pentru fiecare platformă, afișează numele și numărul de jocuri disponibile. Include platformele fără jocuri.
SELECT P.name, COUNT(GP.game_id) AS game_count
FROM GamePlatforms GP
LEFT OUTER JOIN Platforms P ON GP.platform_id = P.platform_id
GROUP BY P.name;

-- 13. Pentru fiecare dezvoltator care are cel puțin două jocuri asociate, afișează numele și prețul mediu al jocurilor dezvoltate de acesta.
SELECT C.name, AVG(G.price) AS average_price
FROM GameCompanies GC
INNER JOIN Companies C ON GC.company_id = C.company_id
INNER JOIN Games G ON GC.game_id = G.game_id
GROUP BY C.name
HAVING COUNT(GC.game_id) >= 2;

-- 14. Afișează genurile care conțin cel puțin două jocuri cu prețul strict mai mare de 30. Pentru fiecare gen, afișează numele și numărul jocurilor care respectă condiția.
SELECT GE.name, COUNT(GG.game_id) AS game_count
FROM Genres GE
INNER JOIN GameGenres GG ON GE.genre_id = GG.genre_id
INNER JOIN Games G ON GG.game_id = G.game_id
WHERE G.price > 30
GROUP BY GE.name
HAVING COUNT(GE.genre_id) > 2;
