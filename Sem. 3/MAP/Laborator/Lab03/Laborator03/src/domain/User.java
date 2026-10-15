package domain;

public class User extends Entity<Long> {

    private final String username;
    private String firstName;
    private String lastName;

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

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    @Override
    public String toString() {
        return "User{id=" + getId() + ", username=" + username
                + ", firstName=" + firstName + ", lastName=" + lastName + '}';
    }
}
