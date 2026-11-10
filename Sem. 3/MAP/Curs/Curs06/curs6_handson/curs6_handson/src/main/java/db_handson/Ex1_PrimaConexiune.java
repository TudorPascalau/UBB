package db_handson;

/**
 * Hands-on 1: prima conexiune JDBC.
 * JDBC = interfete din java.sql (Connection, Statement, ResultSet);
 * driverul PostgreSQL (dependenta din build.gradle.kts) le implementeaza.
 * Inainte: baza de date socialnetwork, cu tabela users (scriptul sql/retea.sql).
 */
public class Ex1_PrimaConexiune {

    public static void main(String[] args) {
        // TODO 1. Deschideti o conexiune cu DriverManager.getConnection(ConfigDb.URL, ConfigDb.USER, ConfigDb.PASSWORD),
        //         intr-un try-with-resources. Afisati numele si versiunea serverului
        //         (connection.getMetaData(): getDatabaseProductName, getDatabaseProductVersion).
        //                                                    -> PostgreSQL <versiunea instalata>
        // Intrebare: de ce try-with-resources? Ce se intampla daca nu inchidem conexiunea?

        // TODO 2. Prindeti SQLException si afisati mesajul ei.
        //         Schimbati temporar parola in config.properties si rulati din nou.
        //                                                    -> FATAL: password authentication failed ...
        // Intrebare: SQLException este checked sau unchecked? De unde stiti?

        // TODO 3. Opriti serviciul PostgreSQL (Services -> postgresql) si rulati din nou. Ce mesaj primiti?
    }
}
