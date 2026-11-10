package IF;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.function.Supplier;

/**
 * Referinta la metoda = o lambda care doar apeleaza o metoda existenta.
 * Cele patru tipuri, fiecare cu lambda echivalenta.
 */
public class Ex3_ReferinteLaMetode {

    // TODO 1. Scrieti metoda statica bursier(Student s), care intoarce true daca studentul are media >= 9.
    /**
     *
     * @param s - the student
     * @return true - if the student has an average of at least 9
     */
    static boolean bursier(Student s) {
        return s.getMedia() >= 9;
    }

    /**
     *
     * @param args - command line arguments (not used)
     */
    public static void main(String[] args) {
        // TODO 2. Creati o lista cu new Student(1, "Ana", 9.6) si new Student(2, "Dan", 4.5).
        List<Student> studenti = List.of(new Student(1, "Ana", 9.6), new Student(2, "Dan", 4.5));

        // TODO 3. Referinta la o METODA STATICA:
        //   Predicate<Student> eBursier, care foloseste metoda bursier.
        // lambda echivalenta: s -> Ex3_ReferinteLaMetode.bursier(s)
        Predicate<Student> eBursier = Ex3_ReferinteLaMetode::bursier;

        // TODO 4. Referinta la metoda unui OBIECT ANUME:
        //   Consumer<Object> afiseaza, care afiseaza valoarea primita (System.out).
        // lambda echivalenta: x -> System.out.println(x)
        Consumer<Object> afiseaza = System.out::println;

        // TODO 5. Referinta la metoda unui OBIECT OARECARE de un anumit tip:
        //   Function<Student, String> nume, care intoarce numele studentului.
        // lambda echivalenta: s -> s.getNume()
        Function<Student, String> nume = Student::getNume;

        // TODO 6. Referinta la CONSTRUCTOR:
        //   a) Supplier<List<Student>> listaNoua, care creeaza un ArrayList gol.
        //   b) Function<String, StringBuilder> sb, care creeaza un StringBuilder din sirul primit.
        // lambda echivalenta: () -> new ArrayList<>(),  s -> new StringBuilder(s)
        Supplier<List<Student>> listaNoua = ArrayList::new;
        Function<String, StringBuilder> sb = StringBuilder::new;

        // TODO 7. Folositi-le:
        //   a) Afisati toti studentii cu forEach si afiseaza.            -> Ana(9.6)  Dan(4.5)
        //   b) Afisati eBursier pentru primul student si nume pentru al doilea  -> true Dan
        //   c) Afisati listaNoua.get() si sb.apply("abc").reverse()      -> [] cba
        studenti.forEach(afiseaza);
        System.out.println(eBursier.test(studenti.get(0)) + " " + nume.apply(studenti.get(1)));
        System.out.println(listaNoua.get() + " " + sb.apply("abc").reverse());

        // TODO 8. Referinta la metoda unui OBIECT ANUME, cu elementul ca argument:
        //   Avem lista: List.of("a", "an", "ano", "anu", "mp", "anotimp", "anotimpuri").
        List<String> cuvinte = List.of("a", "an", "ano", "anu", "mp", "anotimp", "anotimpuri");

        //   a) Definiti Predicate<String> prefixLambda, care verifica daca un cuvant este
        //      PREFIX al cuvantului "anotimp" (cu lambda).
        Predicate<String> prefixLambda = s -> "anotimp".startsWith(s);

        //   b) Definiti acelasi predicat, prefixDeAnotimp, cu o referinta la metoda.
        Predicate<String> prefixDeAnotimp = "anotimp"::startsWith;

        //   c) Afisati cuvintele din lista care trec testul (filter + toList), cu fiecare predicat.
        //                                                    -> [a, an, ano, anotimp]
        System.out.println(cuvinte.stream().filter(prefixLambda).toList());
        System.out.println(cuvinte.stream().filter(prefixDeAnotimp).toList());

        //   d) Afisati acum cuvintele care INCEP cu "an".    -> [an, ano, anu, anotimp, anotimpuri]
        System.out.println(cuvinte.stream().filter(s -> s.startsWith("an")).toList());

        //   Intrebare: de ce difera rezultatele de la c) si d)?
        //   Intrebare: de ce la d) nu putem scrie direct o referinta la metoda startsWith?
    }
}
