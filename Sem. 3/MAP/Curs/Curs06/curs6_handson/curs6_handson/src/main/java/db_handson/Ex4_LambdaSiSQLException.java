package db_handson;

/**
 * Hands-on 4: lambda-uri cu cod JDBC.
 * Metodele JDBC arunca SQLException (checked), iar interfetele din java.util.function
 * nu declara exceptii. Solutia: o interfata functionala proprie, curs.repository.db.SqlFunction.
 * Rezultatele asteptate (->) sunt pentru datele din sql/retea.sql; cu alte date difera.
 */
public class Ex4_LambdaSiSQLException {

    // TODO 1. Scrieti metoda generica
    //             public static <T> List<T> interogheaza(String sql, SqlFunction<ResultSet, T> mapper)
    //         care deschide conexiunea, executa interogarea si transforma FIECARE rand cu mapper.
    //         SQLException se transforma in RepositoryException (unchecked).

    public static void main(String[] args) {
        // TODO 2. Scrieti:  Function<ResultSet, String> prenume = rs -> rs.getString("first_name");
        // Intrebare: de ce nu compileaza?
        //         Inlocuiti Function cu SqlFunction. Acum compileaza?

        // TODO 3. Folositi interogheaza cu "SELECT * FROM users ORDER BY id" si:
        //   a) mapper-ul prenume                                        -> [Ana, Mihai, Ioana, Ion, Irina, Dan]
        //   b) o lambda care intoarce "nume prenume"                    -> [Pop Ana, Ionescu Mihai, ...]
        //   c) o lambda cu bloc care construieste un Utilizator (cu id) -> [Utilizator{id=1, ...}, ...]

        // TODO 4. Cu un stream pe rezultatul de la c): numarul de utilizatori cu numele Pop.  -> 3
        // Intrebare: comparati interogheaza cu metoda executa din UtilizatorDbRepository.
        //            Ce parte se repeta mereu si ce parte primim ca parametru?
    }
}
