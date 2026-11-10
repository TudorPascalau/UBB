-- Curs 6: baza de date a retelei de socializare (socialnetwork)
-- 1. In pgAdmin: Databases -> Create -> Database..., numele: socialnetwork
-- 2. Click dreapta pe baza socialnetwork -> Query Tool, deschideti acest fisier si rulati-l (F5).
-- Scriptul nu sterge nimic si poate fi rulat de mai multe ori.
-- id-ul utilizatorilor il genereaza baza de date (GENERATED ALWAYS AS IDENTITY),
-- de aceea nu dam id-uri in INSERT, iar prieteniile se leaga prin nume.

CREATE TABLE IF NOT EXISTS users (
    id         BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    first_name VARCHAR(50) NOT NULL,
    last_name  VARCHAR(50) NOT NULL
);

-- o prietenie (id1, id2) se salveaza o singura data, cu id1 < id2
CREATE TABLE IF NOT EXISTS friendships (
    id1 BIGINT REFERENCES users (id) ON DELETE CASCADE,
    id2 BIGINT REFERENCES users (id) ON DELETE CASCADE,
    PRIMARY KEY (id1, id2),
    CHECK (id1 < id2)
);

-- utilizatorii de test, adaugati doar daca nu exista deja (acelasi prenume si nume)
INSERT INTO users (first_name, last_name)
SELECT v.first_name, v.last_name
FROM (VALUES ('Ana', 'Pop'), ('Mihai', 'Ionescu'), ('Ioana', 'Marin'),
             ('Ion', 'Pop'), ('Irina', 'Pop'), ('Dan', 'Matei')) AS v(first_name, last_name)
WHERE NOT EXISTS (SELECT 1 FROM users u
                  WHERE u.first_name = v.first_name AND u.last_name = v.last_name);

-- prieteniile, date prin nume; id-urile se cauta in users, iar LEAST / GREATEST pun id-ul mai mic primul
INSERT INTO friendships (id1, id2)
SELECT LEAST(a.id, b.id), GREATEST(a.id, b.id)
FROM (VALUES ('Ana', 'Pop', 'Mihai', 'Ionescu'),
             ('Ana', 'Pop', 'Ioana', 'Marin'),
             ('Ana', 'Pop', 'Ion', 'Pop'),
             ('Mihai', 'Ionescu', 'Ioana', 'Marin'),
             ('Ion', 'Pop', 'Irina', 'Pop')) AS p(f1, l1, f2, l2)
JOIN users a ON a.first_name = p.f1 AND a.last_name = p.l1
JOIN users b ON b.first_name = p.f2 AND b.last_name = p.l2
ON CONFLICT DO NOTHING;

SELECT * FROM users ORDER BY id;
SELECT * FROM friendships ORDER BY id1, id2;
