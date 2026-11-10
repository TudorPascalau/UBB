package db_handson;

/**
 * Hands-on 3: PreparedStatement si SQL injection.
 * Rezultatele asteptate (->) sunt pentru datele din sql/retea.sql; cu alte date difera.
 */
public class Ex3_PreparedStatement {

    // TODO 1. Scrieti metoda cautaPericulos(Connection c, String nume), care intoarce prenumele
    //         utilizatorilor cu numele dat, construind SQL-ul prin CONCATENARE:
    //         "SELECT first_name FROM users WHERE last_name = '" + nume + "'"

    // TODO 2. Scrieti metoda cauta(Connection c, String nume), cu acelasi rezultat,
    //         folosind un PreparedStatement cu parametrul ? (setString).

    public static void main(String[] args) {
        // TODO 3. Apelati ambele metode cu "Pop".               -> [Ana, Ion, Irina]  [Ana, Ion, Irina]
        //         Apelati ambele metode cu "x' OR '1'='1".      -> [Ana, Mihai, ... toti]  []
        // Intrebare: ce SQL s-a executat in cautaPericulos? De ce cauta nu are aceasta problema?

        // TODO 4. Cu un PreparedStatement, inserati utilizatorul (10, "Vlad", "Stan").
        //         Afisati rezultatul lui executeUpdate.          -> 1
        //         Rulati inca o data programul. Ce exceptie apare? De ce?

        // TODO 5. Stergeti utilizatorul cu id-ul 10 (DELETE cu parametru). Afisati randurile sterse. -> 1
        //         Verificati in pgAdmin continutul tabelei.
    }
}
