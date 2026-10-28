import ui.UserInterface;
import application.ApplicationInitializationException;
import repository.RepositoryException;
import config.ConfigLoader;
import repository.factory.RepositoryFactory;
import service.ServiceException;
import service.SocialNetworkService;
import service.CommunityAnalyzer;
import validation.UserValidator;
import validation.FriendshipValidator;
import validation.ValidationException;
import java.io.IOException;

/**
 * Application entry point.
 */
public final class Main {
    /**
     * Prevents instantiation of the application entry point.
     */
    private Main() {}

    /**
     * Starts the application and reports expected initialization failures.
     * @param args unused command-line arguments
     */
    public static void main(String[] args) {
        UserInterface ui;
        try {
            ui = initializeApplication();
        }
        catch (ApplicationInitializationException e) {
            System.out.println(e.getMessage());
            return;
        }
        ui.run();
    }

    /**
     * Builds repositories, validates loaded data and assembles the user interface.
     * @return the initialized user interface
     * @throws ApplicationInitializationException if configuration, persistence or initial validation fails
     */
    private static UserInterface initializeApplication() {
        try {
            UserValidator userValidator = new UserValidator();
            FriendshipValidator friendshipValidator = new FriendshipValidator();
            RepositoryFactory factory = new RepositoryFactory(
                    ConfigLoader.load("src/main/resources/config.properties"));

            SocialNetworkService service = new SocialNetworkService(
                    factory.createUserRepository(userValidator),
                    factory.createFriendshipRepository(friendshipValidator),
                    new CommunityAnalyzer());

            return new UserInterface(service);
        }
        catch (IOException e) {
            throw new ApplicationInitializationException(
                    "Unable to read src/main/resources/config.properties: " + e.getMessage(), e);
        }
        catch (UnsupportedOperationException e) {
            throw new ApplicationInitializationException(
                    "Unable to start the application: DATABASE persistence is not implemented yet.", e);
        }
        catch (RepositoryException | ValidationException | ServiceException | IllegalArgumentException e) {
            throw new ApplicationInitializationException(
                    "Unable to start the application: " + e.getMessage(), e);
        }
    }

}
