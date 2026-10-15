import domain.Friendship;
import domain.FriendshipId;
import domain.User;
import repository.FriendshipFileRepository;
import repository.Repository;
import repository.UserFileRepository;
import service.SocialNetworkService;
import ui.UserInterface;
import validation.FriendshipValidator;
import validation.UserValidator;

public class Main {
    public static void main(String[] args) {
        Repository<Long, User> userRepository = new UserFileRepository("src/data/users.csv");
        Repository<FriendshipId, Friendship> friendshipRepository = new FriendshipFileRepository("src/data/friendships.csv");

        SocialNetworkService service = new SocialNetworkService(
                userRepository,
                friendshipRepository,
                new UserValidator(),
                new FriendshipValidator()
        );

        new UserInterface(service).run();

    }
}
