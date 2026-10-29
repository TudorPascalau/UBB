package service;

import domain.User;
import java.util.function.Predicate;

/**
 * Provides reusable user search criteria.
 */
public final class UserCriteria {
    private UserCriteria() {}

    /**
     * Creates a case-insensitive last-name criterion.
     * @param lastName last name to match
     * @return a predicate matching the supplied last name
     * @throws IllegalArgumentException if lastName is null or blank
     */
    public static Predicate<User> lastNameEquals(String lastName) {
        if (lastName == null || lastName.isBlank()) {
            throw new IllegalArgumentException("Last name cannot be empty");
        }

        return user -> lastName.equalsIgnoreCase(user.getLastName());
    }

    /**
     * Creates a case-insensitive first-name criterion.
     * @param firstName first name to match
     * @return a predicate matching the supplied first name
     * @throws IllegalArgumentException if firstName is null or blank
     */
    public static Predicate<User> firstNameEquals(String firstName) {
        if (firstName == null || firstName.isBlank()) {
            throw new IllegalArgumentException("First name cannot be empty");
        }

        return user -> firstName.equalsIgnoreCase(user.getFirstName());
    }
}
