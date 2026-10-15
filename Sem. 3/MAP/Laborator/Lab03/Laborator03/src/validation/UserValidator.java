package validation;
import domain.User;

public class UserValidator implements Validator<User> {

    @Override
    public void validate(User user) {
        if (user == null) {
            throw new ValidationException("User cannot be null");
        }

        StringBuilder errorMessage = new StringBuilder();

        if (user.getUsername() == null || user.getUsername().isBlank()) {
            errorMessage.append("Username cannot be empty. ");
        }

        if(user.getFirstName() == null || user.getFirstName().isBlank()) {
            errorMessage.append("First name cannot be empty");
        }
        if(user.getLastName() == null || user.getLastName().isBlank()) {
            errorMessage.append("Last name cannot be empty");
        }

        if(!errorMessage.isEmpty()) {
            throw new ValidationException(errorMessage.toString());
        }
    }
}
