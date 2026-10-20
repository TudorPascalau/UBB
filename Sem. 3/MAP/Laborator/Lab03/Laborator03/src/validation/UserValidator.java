package validation;
import domain.User;

/**
 * Checks user identity and required text fields.
 */
public class UserValidator implements Validator<User> {
    /**
     * Creates the user validation strategy.
     */
    public UserValidator() {}
    /**
     * Checks entity validity.
     * @param user user to validate
     * @throws ValidationException if any user field is invalid
     */
    @Override public void validate(User user) {
        if (user == null) throw new ValidationException("User cannot be null");
        StringBuilder errors = new StringBuilder();
        if (user.getId() <= 0) errors.append("User ID must be positive. ");
        checkName(user.getFirstName(), "First name", errors);
        checkName(user.getLastName(), "Last name", errors);



        if (!errors.isEmpty()) throw new ValidationException(errors.toString().trim());
    }
    private void checkName(String name, String label, StringBuilder errors) {
        if (name == null || name.isBlank()) errors.append(label).append(" cannot be empty. ");
        else if (!name.matches("\\p{L}+")) {
            errors.append(label).append(" must contain only letters. ");
        }
    }
}
