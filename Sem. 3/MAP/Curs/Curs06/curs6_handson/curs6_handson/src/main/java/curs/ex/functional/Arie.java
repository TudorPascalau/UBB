package curs.ex.functional;

/**
 * Computes the area of a geometric figure.
 * Own functional interface: one abstract method, any name we want.
 *
 * @param <E> - type of the figure
 */
@FunctionalInterface
public interface Arie<E> {

    /**
     *
     * @param figura - the figure whose area is computed
     * @return the area of the figure
     */
    double calculeaza(E figura);
}
