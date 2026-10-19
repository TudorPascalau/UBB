package home;

import domain.User;
import domain.validators.UserValidator;
import repository.Repository;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

/**
 * Separate entry point for requirements 4-6; the existing Main stays unchanged.
 * Add src/main/resources to the runtime classpath (or mark it as Resources Root).
 * Run from the Seminar04 project directory so data/users.txt can be found.
 */
public class Main {
    public static void main(String[] args) {
        cerinta4();
    }

    /**
     * Requirement 6: loads a classpath resource and always closes its stream.
     * Missing resources and read errors retain their original cause.
     */
    public static Properties incarcaConfiguratie(String resursa) {
        try (InputStream input = Main.class.getResourceAsStream(resursa)) {
            if (input == null)
                throw new FileNotFoundException("Resursa nu exista in classpath: " + resursa);
            Properties properties = new Properties();
            properties.load(input);
            return properties;
        } catch (IOException | IllegalArgumentException e) {
            throw new RuntimeException("Nu se poate incarca configuratia: " + resursa, e);
        }
    }

    /**
     * Change only repository.type in config.properties between FILE, MEMORY and DATABASE.
     * DATABASE intentionally propagates UnsupportedOperationException from findAll().
     */
    public static void cerinta4() {
        Properties properties = incarcaConfiguratie("/config.properties");
        RepositoryFactory factory = new RepositoryFactory(properties);
        Repository<Long, User> repository = factory.createUserRepository(new UserValidator());
        System.out.println("Repository creat: " + repository.getClass().getName());
        System.out.println("Utilizatori: " + repository.findAll());
    }
}
