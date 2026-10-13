INSERT INTO Categorii(nume)
VALUES ('Elev'),
       ('Student'),
       ('Adult'),
       ('Pensionar'),
       ('VIP'),
       ('Insotitor'),
       ('Copil');

SELECT * FROM Categorii;

INSERT INTO Sectiuni(nume, descriere)
VALUES ('Shopping', 'Sectiune gift shops'),
       ('Rides', 'Sectiune rollecoastere'),
       ('Food', 'Sectiune mancare'),
       ('Info', 'Sectiune infopoint'),
       ('Nature', 'Sectiune parc aer liber'),
       ('Games', 'Sectiune minigames societate'),
       ('Arcade', 'Sectiune jocuri video');

SELECT * FROM Sectiuni;

INSERT INTO Vizitatori(nume, email, id_categorie)
VALUES ('Tudor' , 'tudor@gmail.com', 2),
       ('Dragos' , 'dragos@gmail.com', 3),
       ('Adi' , 'adi@gmail.com', 4),
       ('Stefan' , 'stefan@gmail.com', 1),
       ('Ana' , 'ana@gmail.com', 6),
       ('Diana' , 'diana@gmail.com', 7),
       ('Mircea' , 'mircea@gmail.com', 7);

SELECT * From Vizitatori;

INSERT INTO Atractii(nume, descriere, varsta_minima, id_sectiune)
VALUES ('Gift Shop', 'Loc pentru cumparat suveniruri', 5, 1),
       ('Japanese Arcade', 'Loc cu jocuri video japoneze retro', 10, 7),
       ('KFC', 'Fast food', 6, 3),
       ('Parc outdoors', 'Loc pentru stat in aer liber', 1, 5),
       ('Table de sah', 'Loc pentru jucat sah', 7, 6),
       ('Infopoint', 'Infopoint', 2, 4),
       ('Best Rollercoaster', 'Cel mai bun rollercoaster', 10, 3);

SELECT * FROM Atractii;

INSERT INTO Note(id_vizitator, id_atractie, nota)
VALUES (1, 2, 6.5),
       (3, 4, 7.5),
       (1, 4, 4.3),
       (4, 7, 8.9),
       (5, 5, 2.3),
       (2, 6, 10),
       (6, 1, 5.5);

SELECT * FROM Note;
