--Exercitii selectare
--Ex. 1
SELECT * FROM Categorii
WHERE nume='Pensionar' OR nume='Copil';

--Ex. 2
SELECT * FROM Sectiuni
WHERE nume LIKE '[G]%';

--Ex. 3
SELECT * FROM Sectiuni
WHERE nume LIKE '%__s';


