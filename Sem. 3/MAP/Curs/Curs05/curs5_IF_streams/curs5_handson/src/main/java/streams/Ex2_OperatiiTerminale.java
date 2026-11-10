package streams;

import IF.Student;

import java.util.Comparator;
import java.util.List;
import java.util.Optional;

/**
 * Operatii terminale simple: count, anyMatch / allMatch / noneMatch, reduce, max.
 */
public class Ex2_OperatiiTerminale {

    /**
     *
     * @param args - command line arguments (not used)
     */
    public static void main(String[] args) {
        List<Student> studenti = List.of(
                new Student(1, "Ana", 9.6),
                new Student(2, "Dan", 4.5),
                new Student(3, "Barbu", 10),
                new Student(4, "Bianca", 7.2));

        // count: cate elemente au ramas
        long promovati = studenti.stream().filter(s -> s.getMedia() >= 5).count();
        System.out.println("promovati: " + promovati);

        // match: raspuns true / false
        System.out.println("exista restantieri: " + studenti.stream().anyMatch(s -> s.getMedia() < 5));
        System.out.println("toti au nume:       " + studenti.stream().allMatch(s -> !s.getNume().isEmpty()));
        System.out.println("nimeni cu Z:        " + studenti.stream().noneMatch(s -> s.getNume().startsWith("Z")));

        // reduce: combina elementele doua cate doua
        double sumaMedii = studenti.stream().map(Student::getMedia).reduce(0.0, Double::sum);
        System.out.println("media generala: " + sumaMedii / studenti.size());

        // max: rezultatul poate lipsi (lista vida), deci intoarce Optional
        Optional<Student> celMaiBun = studenti.stream().max(Comparator.comparing(Student::getMedia));
        celMaiBun.ifPresent(s -> System.out.println("cel mai bun: " + s));
    }
}
