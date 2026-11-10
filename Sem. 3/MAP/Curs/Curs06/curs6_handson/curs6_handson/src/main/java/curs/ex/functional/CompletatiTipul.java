package curs.ex.functional;

import curs.domain.Utilizator;

import java.util.ArrayList;
import java.util.List;
import java.util.function.BiFunction;
import java.util.function.BinaryOperator;
import java.util.function.Consumer;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.function.Supplier;
import java.util.function.ToIntFunction;
import java.util.function.UnaryOperator;

/**
 * Exercise: fill in the type of each variable (the solution is below; the file compiles).
 * Students receive the version with ____ instead of the types.
 */
public class CompletatiTipul {

    /**
     *
     * @param args - command line arguments (not used)
     */
    public static void main(String[] args) {
        Predicate<List<String>> ex1 = x -> "".equals(x.get(0));
        Consumer<Long> ex2 = (Long l) -> System.out.println(l);
        Function<String, Boolean> ex3 = s -> s.contains("a");      // sau Predicate<String>
        Supplier<List<String>> ex4 = () -> new ArrayList<>();       // sau ArrayList::new
        BinaryOperator<String> ex5 = String::concat;                // sau BiFunction<String, String, String>
        Function<Utilizator, String> ex6 = Utilizator::getFirstName;
        ToIntFunction<String> ex7 = String::length;                 // sau Function<String, Integer>
        UnaryOperator<String> ex8 = String::toUpperCase;            // sau Function<String, String>
        BiFunction<String, String, Utilizator> ex9 = Utilizator::new;

        System.out.println(ex1.test(List.of("", "a")));             // true
        ex2.accept(42L);                                             // 42
        System.out.println(ex3.apply("map"));                        // true
        System.out.println(ex4.get());                               // []
        System.out.println(ex5.apply("Java ", "8"));                 // Java 8
        System.out.println(ex6.apply(new Utilizator("Ana", "Pop"))); // Ana
        System.out.println(ex7.applyAsInt("lambda"));                // 6
        System.out.println(ex8.apply("map"));                        // MAP
        System.out.println(ex9.apply("Ion", "Pop"));                 // Utilizator{id=null, ...}
    }
}
