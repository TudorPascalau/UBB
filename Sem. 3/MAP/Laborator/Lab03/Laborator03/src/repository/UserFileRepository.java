package repository;

import domain.User;

public class UserFileRepository extends AbstractFileRepository<Long, User> {

    public UserFileRepository(String fileName) {
        super(fileName);
        loadFromFile();
    }

    @Override
    protected User fromCsv(String line) {
        String[] fields = line.split(",", -1);

        if (fields.length != 4) {
            throw new IllegalArgumentException(
                    "Format asteptat: id,username,firstName,lastName"
            );
        }

        return new User(
                Long.parseLong(fields[0].trim()),
                fields[1],
                fields[2],
                fields[3]
        );
    }

    @Override
    protected String toCsv(User user) {
        requireSimpleCsvField(user.getUsername());
        requireSimpleCsvField(user.getFirstName());
        requireSimpleCsvField(user.getLastName());

        return user.getId() + ","
                + user.getUsername() + ","
                + user.getFirstName() + ","
                + user.getLastName();
    }

    private void requireSimpleCsvField(String value) {
        if (value.contains(",")
                || value.contains("\n")
                || value.contains("\r")
                || value.contains("\"")) {
            throw new RepositoryException("Formatul CSV simplificat nu permite virgule, ghilimele sau linii noi in campuri.");
        }
    }
}
