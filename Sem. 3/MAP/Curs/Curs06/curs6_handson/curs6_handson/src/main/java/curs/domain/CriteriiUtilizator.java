package curs.domain;

import java.util.function.Predicate;

/**
 * Search criteria for users. Each criterion is a Predicate&lt;Utilizator&gt;,
 * so criteria can be passed as parameters (e.g. to Repository.findAll(filter))
 * and composed with and / or / negate.
 * Utility class: only static methods, it cannot be instantiated.
 */
public final class CriteriiUtilizator {

    private CriteriiUtilizator() {
    }

    /**
     * the method returns a function (higher-order function); the lambda
     * captures the parameter prefix and uses it after the method has ended
     *
     * @param prefix - the beginning of the first name; must not be null
     * @return a criterion satisfied by the users whose first name starts with prefix
     */
    public static Predicate<Utilizator> prenumeleIncepeCu(String prefix) {
        return u -> u.getFirstName().startsWith(prefix);
    }

    /**
     *
     * @param nume - the last name searched for
     * @return a criterion satisfied by the users with the given last name
     */
    public static Predicate<Utilizator> areNumele(String nume) {
        return u -> u.getLastName().equals(nume);
    }

    /**
     *
     * @param n - the minimum number of friends
     * @return a criterion satisfied by the users with at least n friends
     */
    public static Predicate<Utilizator> areCelPutinPrieteni(int n) {
        return u -> u.getFriends().size() >= n;
    }

    /**
     * ordinary static method; it can be used as a Predicate&lt;Utilizator&gt;
     * through the method reference CriteriiUtilizator::faraPrieteni
     *
     * @param u - the user to be checked
     * @return true - if the user has no friends, false otherwise
     */
    public static boolean faraPrieteni(Utilizator u) {
        return u.getFriends().isEmpty();
    }
}
