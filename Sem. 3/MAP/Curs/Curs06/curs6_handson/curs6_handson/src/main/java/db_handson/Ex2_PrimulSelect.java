package db_handson;

/**
 * Hands-on 2: interogare cu Statement si parcurgerea unui ResultSet.
 * Folositi clasa curs.domain.Utilizator.
 * Rezultatele asteptate (->) sunt pentru datele din sql/retea.sql; cu alte date difera.
 */
public class Ex2_PrimulSelect {

    public static void main(String[] args) {
        // TODO 1. Cu un Statement, executati "SELECT id, first_name, last_name FROM users".
        //         Parcurgeti ResultSet-ul cu while (rs.next()) si afisati fiecare rand.
        //                                                    -> 1 Ana Pop
        //                                                       2 Mihai Ionescu ...
        // Intrebare: pe ce rand este cursorul imediat dupa executeQuery?

        // TODO 2. Construiti lista utilizatori (List<Utilizator>) din randurile citite.

        // TODO 3. Cu un stream pe lista: prenumele celor cu numele Pop, sortate.
        //                                                    -> [Ana, Ion, Irina]

        // TODO 4. Obtineti acelasi rezultat direct din SQL (WHERE + ORDER BY), fara stream.
        //                                                    -> [Ana, Ion, Irina]
        // Intrebare: unde se face filtrarea la TODO 3 si unde la TODO 4?
        //            Care varianta este mai buna pentru un tabel cu un milion de randuri?
    }
}
