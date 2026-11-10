package db_handson;

/**
 * Hands-on 5: tabela friendships(id1, id2), stream-uri si repository-ul din baza de date.
 * Folositi metoda interogheaza din Ex4_LambdaSiSQLException.
 * Rezultatele asteptate (->) sunt pentru datele din sql/retea.sql; cu alte date difera.
 */
public class Ex5_PrieteniiCuStreamuri {

    public static void main(String[] args) {
        // TODO 1. Incarcati toate prieteniile din tabela friendships (ORDER BY id1, id2) intr-o List<long[]>: fiecare rand devine new long[]{id1, id2}.
        //                                                    -> 5 prietenii

        // TODO 2. Cu un stream pe lista: id-urile prietenilor lui Ana (id 1).
        //         Atentie: Ana poate fi pe pozitia id1 sau id2.  -> [2, 3, 4]

        // TODO 3. Creati repo = new UtilizatorDbRepository(new UtilizatorValidator(), ConfigDb.URL, ConfigDb.USER, ConfigDb.PASSWORD).
        //         Transformati id-urile de la TODO 2 in prenume: map(repo::findOne), apoi flatMap(Optional::stream).
        //                                                    -> [Mihai, Ioana, Ion]
        // Intrebare: cate interogari SQL s-au executat? Cum ar arata un singur SELECT cu JOIN?

        // TODO 4. Numarul de prieteni pentru fiecare id: din fiecare pereche obtineti ambele id-uri
        //         (flatMap pe LongStream.of(p) / Stream.of), apoi groupingBy + counting.
        //                                                    -> {1=3, 2=2, 3=2, 4=2, 5=1}
        // Intrebare: de ce Dan (id 6) nu apare? Cum ati scrie acelasi raport in SQL (GROUP BY)?
    }
}
