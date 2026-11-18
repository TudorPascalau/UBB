Rețea de socializare - Laboratorul 5 - Persistență în PostgreSQL
==============================================================

Schema și ștergerea prieteniilor
-------------------------------
La ștergerea unui utilizator din aplicație, SocialNetworkService elimină explicit prieteniile asociate înainte de a șterge utilizatorul. \
Am păstrat acest flux comun deoarece și repository-urile FILE și MEMORY trebuie să elimine prieteniile. 
Dacă o operație de persistență eșuează, service-ul încearcă să refacă prieteniile deja șterse.

În PostgreSQL, ambele chei străine au și ON DELETE CASCADE. 
În fluxul obișnuit din aplicație, prieteniile au fost deja eliminate de service când se execută ștergerea utilizatorului. 
Cascada asigură aceeași regulă de integritate când utilizatorul este șters direct din PostgreSQL.

Generarea ID-ului de utilizator
------------------------------
users.id este BIGINT GENERATED ALWAYS AS IDENTITY. 
Service-ul folosește același apel save în toate modurile și furnizează inițial un ID local.
În DATABASE, acel ID este provizoriu. 
UserDbRepository inserează numai first_name și last_name, citește cheia generată cu getGeneratedKeys() și o setează pe obiectul User.


Operații JDBC și tratarea erorilor
---------------------------------
Repository-urile PostgreSQL primesc parametrii conexiunii de la factory și folosesc DriverManager.getConnection. 
Conexiunea, instrucțiunea pregătită și rezultatul interogării se închid prin try-with-resources.

Entitățile sunt validate înainte de save și update. 
Pentru update, executeUpdate() indică numărul de rânduri afectate. Dacă acesta este zero, metoda întoarce Optional.of(entity), adică entitatea propusă pentru un ID inexistent.
La succes, update întoarce Optional.empty(). 
Pentru delete, PostgreSQL returnează rândul șters prin DELETE ... RETURNING, iar repository-ul îl convertește în entitate. Dacă rândul lipsește, rezultatul este Optional.empty().

SQLException este împachetată în RepositoryException cu păstrarea cauzei.
Erorile de persistență sunt afișate ca mesaje în consolă, fără stack trace.

Parametrizarea interogărilor și demonstrația
-------------------------------------------
Valorile introduse în aplicație sunt transmise prin parametrii unui PreparedStatement. 
La inserarea unui utilizator, numele este legat prin setString și tratat de PostgreSQL ca valoare de tip text, chiar dacă are caractere care au semnificație în sintaxa SQL.
