package streams_handson;

import java.util.List;

/**
 * Hands-on 1: primul stream.
 * Pipeline: sursa -> operatii intermediare (filter, map, sorted) -> operatie terminala.
 */
public class Ex1_PrimulStream {

    public static void main(String[] args) {
        List<String> cuvinte = List.of("ddd2", "aaa2", "bbb1", "aaa1", "ccc1", "aaa3");

        // TODO 1. FARA stream (cu for): construiti lista rezultatFor cu cuvintele care incep cu "a",
        //         transformate in majuscule si sortate. Afisati-o.
        //                                                    -> for:    [AAA1, AAA2, AAA3]

        // TODO 2. CU stream: obtineti acelasi rezultat in lista rezultatStream,
        //         folosind filter, map, sorted si toList. Afisati-o.
        //                                                    -> stream: [AAA1, AAA2, AAA3]
        // Intrebare: care operatii sunt intermediare si care este terminala?

        // TODO 3. Cu un stream, afisati cuvintele care incep cu "b", folosind forEach
        //         si o referinta la metoda.                  -> bbb1

        // TODO 4. Afisati lista cuvinte dupa toate prelucrarile.
        //                                                    -> sursa:  [ddd2, aaa2, bbb1, aaa1, ccc1, aaa3]
        // Intrebare: s-a modificat sursa? De ce?
    }
}
