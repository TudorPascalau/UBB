package curs.ex.functional;

import java.util.List;

/**
 * Warm-up: the same behaviour written as anonymous class, lambda and method reference
 */
public class ArieDemo {

    /**
     * prints the area of every figure in the list; the way the area is computed
     * is received as a parameter
     *
     * @param figuri - the figures
     * @param arie   - the strategy that computes the area of one figure
     * @param <E>    - type of the figures
     */
    public static <E> void printArie(List<E> figuri, Arie<E> arie) {
        for (E f : figuri)
            System.out.printf("%s -> %.2f%n", f, arie.calculeaza(f));
    }

    /**
     *
     * @param args - command line arguments (not used)
     */
    public static void main(String[] args) {
        List<Cerc> cercuri = List.of(new Cerc(1), new Cerc(2));
        List<Patrat> patrate = List.of(new Patrat(3), new Patrat(4));

        // 1. clasa anonima: 6 linii pentru o singura formula
        Arie<Cerc> arieCercAnonima = new Arie<Cerc>() {
            @Override
            public double calculeaza(Cerc c) {
                return Math.PI * c.getRaza() * c.getRaza();
            }
        };
        printArie(cercuri, arieCercAnonima);

        // 2. lambda: doar parametrii si corpul
        Arie<Cerc> arieCercLambda = c -> Math.PI * c.getRaza() * c.getRaza();
        printArie(cercuri, arieCercLambda);

        // 3. referinta la o metoda statica existenta
        Arie<Cerc> arieCercRef = Cerc::arie;
        printArie(cercuri, arieCercRef);

        // aceeasi metoda printArie, alt tip de figura, alta formula
        printArie(patrate, p -> p.getLatura() * p.getLatura());
    }
}
