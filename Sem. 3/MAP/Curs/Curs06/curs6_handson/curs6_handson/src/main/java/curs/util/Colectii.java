package curs.util;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.function.BinaryOperator;
import java.util.function.Function;
import java.util.stream.StreamSupport;

/**
 * Generic helper methods that receive behaviour as parameters (functional interfaces).
 * Seminar 5 wrote them with loops; curs 5 rewrites them with the Stream API:
 * the signatures stay the same, except reduce, which returns Optional instead of null.
 */
public final class Colectii {

    private Colectii() {
    }

    /**
     * copies the elements of an Iterable into a new list
     * (e.g. the result of Repository.findAll())
     *
     * @param elemente - the elements to be copied; must not be null
     * @param <E>      - type of the elements
     * @return a new, modifiable list with the same elements, in the same order
     */
    public static <E> List<E> catreLista(Iterable<E> elemente) {
        List<E> rezultat = new ArrayList<>();
        elemente.forEach(rezultat::add);      // referinta la metoda unui obiect anume
        return rezultat;
    }

    /**
     * applies a function to every element (the "map" operation)
     *
     * @param elemente - the elements to be transformed; must not be null
     * @param f        - the transformation applied to each element; must not be null
     * @param <T>      - type of the elements
     * @param <R>      - type of the results
     * @return the list of results, in the order of the elements
     */
    public static <T, R> List<R> transforma(Iterable<T> elemente, Function<T, R> f) {
        return StreamSupport.stream(elemente.spliterator(), false)
                .map(f)
                .toList();
    }

    /**
     * combines all the elements, two by two, with an operator (the "reduce" operation)
     *
     * @param elemente - the elements to be combined; must not be null
     * @param op       - the operator that combines two elements into one; must not be null
     * @param <E>      - type of the elements
     * @return an Optional with the result of the combination
     * or Optional.empty() - if there are no elements
     */
    public static <E> Optional<E> reduce(Iterable<E> elemente, BinaryOperator<E> op) {
        return StreamSupport.stream(elemente.spliterator(), false)
                .reduce(op);
    }
}
