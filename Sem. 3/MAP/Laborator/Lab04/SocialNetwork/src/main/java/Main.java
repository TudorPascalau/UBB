import ui.UserInterface;
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
            RepositoryFactory factory = ConfigLoader.loadFactory("src/main/resources/config.properties");
            UserValidator userValidator = new UserValidator();
            FriendshipValidator friendshipValidator = new FriendshipValidator();
            SocialNetworkService service = new SocialNetworkService(
                    factory.createUserRepository(userValidator),
                    factory.createFriendshipRepository(friendshipValidator),
                    userValidator, friendshipValidator, new CommunityAnalyzer());
            ui = new UserInterface(service);
        } catch (IOException e) {
            System.out.println("Unable to read src/main/resources/config.properties: " + e.getMessage());
            return;
        } catch (UnsupportedOperationException e) {
            System.out.println("Unable to start the application: DATABASE persistence is not implemented yet.");
            return;
        } catch (RepositoryException | ValidationException | ServiceException | IllegalArgumentException e) {
            System.out.println("Unable to start the application: " + e.getMessage());
            return;
        }
        ui.run();
    }

}
