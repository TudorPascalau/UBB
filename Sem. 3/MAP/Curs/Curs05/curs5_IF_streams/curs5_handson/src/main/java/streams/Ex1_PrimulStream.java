package streams;

import java.util.ArrayList;
import java.util.List;

/**
 *  stream-urile nu fac programul mai rapid, fac codul mai scurt, mai clar și mai sigur
 * Primul stream: aceeasi prelucrare scrisa cu for si cu stream.
 * Pipeline: sursa -> operatii intermediare (filter, map, sorted) -> operatie terminala.
 */
public class Ex1_PrimulStream {

    /**
     *
     * @param args - command line arguments (not used)
     */
    public static void main(String[] args) {
        List<String> cuvinte = List.of("ddd2", "aaa2", "bbb1", "aaa1", "ccc1", "aaa3");

        // cu for: cuvintele care incep cu "a", cu majuscule, sortate
        List<String> rezultatFor = new ArrayList<>();
        for (String c : cuvinte)
            if (c.startsWith("a"))
                rezultatFor.add(c.toUpperCase());
        rezultatFor.sort(null);
        System.out.println("for:    " + rezultatFor);

        // cu stream: spunem CE vrem, nu CUM se parcurge
        List<String> rezultatStream = cuvinte.stream()
                .filter(c -> c.startsWith("a"))     // intermediara: pastreaza unele elemente
                .map(String::toUpperCase)           // intermediara: transforma fiecare element
                .sorted()                           // intermediara: ordoneaza
                .toList();                          // terminala: produce rezultatul
        System.out.println("stream: " + rezultatStream);

        // forEach este tot o operatie terminala
        cuvinte.stream()
                .filter(c -> c.startsWith("b"))
                .forEach(System.out::println);

        // stream-ul nu modifica sursa
        System.out.println("sursa:  " + cuvinte);
    }
}
