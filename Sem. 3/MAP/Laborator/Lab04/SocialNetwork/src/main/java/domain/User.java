package domain;

/**
 * A user identified by an immutable numeric ID.
 */
public class User extends Entity<Long> {
    private final String firstName;
    private final String lastName;

    /**
     * Creates a user.
     * @param id user ID
     * @param firstName given name
     * @param lastName family name
     * @throws IllegalArgumentException if the ID is null
     */
    public User(Long id, String firstName, String lastName) {
        super(id);
        this.firstName = firstName;
        this.lastName = lastName;
    }
    /**
     * Returns the given name.
     * @return the given name
     */
    public String getFirstName() { return firstName; }
    /**
     * Returns the family name.
     * @return the family name
     */
    public String getLastName() { return lastName; }
    /**
     * Returns a readable description.
     * @return a readable description
     */
    @Override public String toString() {
        return "User: " + getId() + ", " + firstName + " " + lastName;
    }
}
