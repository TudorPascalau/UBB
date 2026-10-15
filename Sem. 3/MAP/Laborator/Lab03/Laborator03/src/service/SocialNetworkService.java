package service;

import domain.Friendship;
import domain.FriendshipId;
import domain.User;
import repository.Repository;
import validation.Validator;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class SocialNetworkService {

    private final Repository<Long, User> userRepository;
    private final Repository<FriendshipId, Friendship> friendshipRepository;

    private final Validator<User> userValidator;
    private final Validator<Friendship> friendshipValidator;

    private long nextUserId = 1;

    public SocialNetworkService(
            Repository<Long, User> userRepository,
            Repository<FriendshipId, Friendship> friendshipRepository,
            Validator<User> userValidator,
            Validator<Friendship> friendshipValidator) {

        this.userRepository = Objects.requireNonNull(userRepository, "UserRepository cannot be null");
        this.friendshipRepository = Objects.requireNonNull(friendshipRepository, "FriendshipRepository cannot be null");

        this.userValidator = Objects.requireNonNull(userValidator, "UserValidator cannot be null");
        this.friendshipValidator = Objects.requireNonNull(friendshipValidator, "FriendshipValidator cannot be null");

        for (User user : userRepository.findAll()) {
            if (user.getId() >= nextUserId) {
                nextUserId = user.getId() + 1;
            }
        }
    }

    public void addUser(String firstName, String lastName) {
        User user = new User(nextUserId, firstName, lastName);

        userValidator.validate(user);

        if (userRepository.save(user) != null) {
            throw new ServiceException(
                    "User already exists with id: " + nextUserId
            );
        }

        nextUserId++;
    }

    public void removeUser(Long id) {
        requireUser(id);

        List<FriendshipId> friendshipsToDelete = new ArrayList<>();
        for (Friendship friendship : friendshipRepository.findAll()) {
            if (friendship.getFirstUserId().equals(id)
                    || friendship.getSecondUserId().equals(id)) {
                friendshipsToDelete.add(friendship.getId());
            }
        }

        for(FriendshipId friendshipId : friendshipsToDelete) {
            friendshipRepository.delete(friendshipId);
        }

        userRepository.delete(id);
    }

    public Iterable<User> getUsers() {
        return userRepository.findAll();
    }

    public void addFriendship(Long firstUserId, Long secondUserId) {
        requireUser(firstUserId);
        requireUser(secondUserId);

        Friendship friendship =
                new Friendship(firstUserId, secondUserId);

        friendshipValidator.validate(friendship);

        if (friendshipRepository.save(friendship) != null) {
            throw new ServiceException("Prietenia există deja.");
        }
    }

    public void removeFriendship(Long firstUserId, Long secondUserId) {
        requireUser(firstUserId);
        requireUser(secondUserId);

        FriendshipId friendshipId = new FriendshipId(firstUserId, secondUserId);

        if (friendshipRepository.delete(friendshipId) == null) {
            throw new ServiceException("Prietenia nu există.");
        }
    }

    public Iterable<Friendship> getFriendships() {
        return friendshipRepository.findAll();
    }


    private User requireUser(Long id){
        User user = userRepository.findOne(id);
        if (user == null) {
            throw new ServiceException("User with id " + id + " not found");
        }

        return user;
    }

}
