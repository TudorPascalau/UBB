--adaugarea datelor in tabel
INSERT INTO Utilizatori (nume_utilizator, email, parola)
VALUES ('bob', 'bob@gmail.com', '12wea32dfawfe'),
       ('tom', 'tom@gmail.com', '1289hd0nqu0cn');

--citirea datelor din tabel
SELECT * FROM Utilizatori;
SELECT cod_u, nume_utilizator, email, parola FROM Utilizatori;
SELECT nume_utilizator, email FROM Utilizatori;
SELECT nume_utilizator AS utilizator, email FROM Utilizatori;
SELECT email, nume_utilizator FROM Utilizatori;

--actualizarea datelor din tabel
UPDATE Utilizatori SET nume_utilizator='bobt'
UPDATE Utilizatori SET nume_utilizator='tom'
WHERE cod_u=2;
UPDATE Utilizatori SET nume_utilizator='tomt',
                       email='tom_t@gmail.com'
WHERE cod_u=2;

--stergerea datelor din tabel
DELETE FROM Utilizatori WHERE cod_u=2;
DELETE FROM Utilizatori;

INSERT INTO Utilizatori (nume_utilizator, email, parola)
VALUES ('bob', 'bob@gmail.com', '12wea32dfawfe'),
       ('tom', 'tom@gmail.com', '1289hd0nqu0cn');

SELECT * FROM Utilizatori
WHERE nume_utilizator='tom';
