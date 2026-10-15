package domain;

public class User extends Entity<Long> {

    private final String username;
    private final String firstName;
    private final String lastName;

    public User(Long id, String username, String firstName, String lastName) {
        super(id);
        this.username = username;
        this.firstName = firstName;
        this.lastName = lastName;
    }

    public String getUsername() {
        return username;
    }

    public String getFirstName() {
        return firstName;
    }

    public String getLastName() {
        return lastName;
    }

    @Override
    public String toString() {
        return "User: " + getId() + ", username = " + username
                + ", firstName = " + firstName + ", lastName = " + lastName;
    }
}
