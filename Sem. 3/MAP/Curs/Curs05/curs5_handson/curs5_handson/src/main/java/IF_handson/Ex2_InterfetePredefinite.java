package IF_handson;

import java.util.function.Function;
import java.util.function.Predicate;

/**
 * Hands-on 2: interfetele functionale predefinite din java.util.function.
 * Folositi clasa Student din acest pachet.
 */
public class Ex2_InterfetePredefinite {

    public static void main(String[] args) {
        Student ana = new Student(1, "Ana", 9.6);
        Student dan = new Student(2, "Dan", 4.5);

        // TODO 1. Predicate<T>: T -> boolean   test
        //   a) Definiti predicatul promovat: studentul are media >= 5.
        //   b) Definiti predicatul incepeCuA: numele studentului incepe cu "A".
        //   c) Afisati promovat pentru ana si dan                  -> true false
        //   d) Combinati promovat si incepeCuA (and) pentru ana     -> true
        //   e) Negati promovat (negate) si testati pentru dan       -> true


        // TODO 2. Function<T, R>: T -> R  apply
        //   a) Definiti functia lungime: String -> Integer, intoarce lungimea sirului (cu lambda).
        //   b) Definiti functia numar: String -> Integer, transforma sirul in numar (cu referinta la metoda).
        //   c) Afisati lungime.apply("lambda") si numar.apply("12")  -> 6 12
        //   d) Folositi andThen ca sa ridicati la patrat rezultatul lui numar pentru "12"  -> 144



        // TODO 3. Consumer<T>: T -> void  (face ceva cu valoarea)  accept
        //   Definiti consumerul afiseaza, care afiseaza "Consumer: " + student. Apelati-l pentru ana.

        // TODO 4. Supplier<T>: () -> T (produce o valoare, fara argumente) get
        //   a) Definiti un Supplier<LocalDate> azi, care da data curenta (referinta la metoda).
        //   b) Definiti un Supplier<List<String>> listaNoua, care creeaza un ArrayList gol (referinta la constructor).
        //   c) Afisati rezultatele celor doi supplieri.

        // TODO 5. UnaryOperator<T>: T -> T si BinaryOperator<T>: (T, T) -> T
        //   a) Definiti UnaryOperator<String> majuscule, care transforma sirul in majuscule.
        //   b) Definiti BinaryOperator<Integer> suma, care aduna doua numere.
        //   c) Afisati majuscule.apply("ana") si suma.apply(2, 3)  -> ANA 5

        // TODO 6. Comparator<T>: (T, T) -> int
        //   a) Creati o lista modificabila cu ana, dan si new Student(3, "Barbu", 10).
        //   b) Sortati lista dupa nume, cu o lambda.                    -> [Ana(9.6), Barbu(10.0), Dan(4.5)]
        //   c) Sortati lista descrescator dupa medie, cu Comparator.comparing(...).reversed()
        //                                                               -> [Barbu(10.0), Ana(9.6), Dan(4.5)]
    }
}
