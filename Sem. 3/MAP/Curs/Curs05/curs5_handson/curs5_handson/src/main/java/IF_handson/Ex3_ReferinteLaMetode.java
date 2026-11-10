package IF_handson;

/**
 * Hands-on 3: referinte la metode.
 * O referinta la metoda = o lambda care doar apeleaza o metoda existenta.
 * Pentru fiecare cerinta, scrieti in comentariu si lambda echivalenta.
 */
public class Ex3_ReferinteLaMetode {

    // TODO 1. Scrieti metoda statica bursier(Student s), care intoarce true daca studentul are media >= 9.



    public static void main(String[] args) {
        // TODO 2. Creati o lista cu new Student(1, "Ana", 9.6) si new Student(2, "Dan", 4.5).

        // TODO 3. Referinta la o METODA STATICA:
        //   Predicate<Student> eBursier, care foloseste metoda bursier.

        // TODO 4. Referinta la metoda unui OBIECT ANUME:
        //   Consumer<Object> afiseaza, care afiseaza valoarea primita (System.out).

        // TODO 5. Referinta la metoda unui OBIECT OARECARE de un anumit tip:
        //   Function<Student, String> nume, care intoarce numele studentului.

        // TODO 6. Referinta la CONSTRUCTOR:
        //   a) Supplier<List<Student>> listaNoua, care creeaza un ArrayList gol.
        //   b) Function<String, StringBuilder> sb, care creeaza un StringBuilder din sirul primit.

        // TODO 7. Folositi-le:
        //   a) Afisati toti studentii cu forEach si afiseaza.            -> Ana(9.6)  Dan(4.5)
        //   b) Afisati eBursier pentru primul student si nume pentru al doilea  -> true Dan
        //   c) Afisati listaNoua.get() si sb.apply("abc").reverse()      -> [] cba

        // TODO 8. Referinta la metoda unui OBIECT ANUME, cu elementul ca argument:
        //   Avem lista: List.of("a", "an", "ano", "anu", "mp", "anotimp", "anotimpuri").
        //   a) Definiti Predicate<String> prefixLambda, care verifica daca un cuvant este
        //      PREFIX al cuvantului "anotimp" (cu lambda).
        //   b) Definiti acelasi predicat, prefixDeAnotimp, cu o referinta la metoda.
        //   c) Afisati cuvintele din lista care trec testul (filter + toList), cu fiecare predicat.
        //                                                    -> [a, an, ano, anotimp]
        //   d) Afisati acum cuvintele care INCEP cu "an".    -> [an, ano, anu, anotimp, anotimpuri]
        //   Intrebare: de ce difera rezultatele de la c) si d)?
        //   Intrebare: de ce la d) nu putem scrie direct o referinta la metoda startsWith?
    }
}
