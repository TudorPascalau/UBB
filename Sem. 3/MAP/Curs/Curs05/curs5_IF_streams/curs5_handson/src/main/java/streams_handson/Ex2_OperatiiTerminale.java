package streams_handson;

import IF_handson.Student;

import java.util.List;

/**
 * Hands-on 2: operatii terminale simple: count, anyMatch / allMatch / noneMatch, reduce, max.
 */
public class Ex2_OperatiiTerminale {

    public static void main(String[] args) {
        List<Student> studenti = List.of(
                new Student(1, "Ana", 9.6),
                new Student(2, "Dan", 4.5),
                new Student(3, "Barbu", 10),
                new Student(4, "Bianca", 7.2));

        // TODO 1. count: numarati studentii promovati (media >= 5).
        //                                          -> promovati: 3

        // TODO 2. match: raspundeti cu true / false, cate un stream pentru fiecare:
        //   a) exista studenti restantieri (media < 5)?   (anyMatch)   -> true
        //   b) toti studentii au numele nevid?            (allMatch)   -> true
        //   c) niciun student nu are numele care incepe cu "Z"? (noneMatch) -> true

        // TODO 3. reduce: calculati suma mediilor (map pe medie, apoi reduce cu valoare initiala 0.0
        //         si o referinta la metoda pentru adunare). Afisati media generala = suma / numarul de studenti.
        //                                          -> media generala: 7.825

        // TODO 4. max: gasiti studentul cu cea mai mare medie (Comparator.comparing).
        //         Afisati-l doar daca exista (ifPresent).
        //                                          -> cel mai bun: Barbu(10.0)
        // Intrebare: de ce max intoarce Optional<Student> si nu direct Student?
    }
}
