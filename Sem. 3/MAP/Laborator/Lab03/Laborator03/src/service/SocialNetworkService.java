package service;

import domain.*;
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

    private final CommunityAnalyzer communityAnalyzer;

    private long nextUserId = 1;
    private long nextFriendshipId = 1;

    public SocialNetworkService(
            Repository<Long, User> userRepository,
            Repository<FriendshipId, Friendship> friendshipRepository,
            Validator<User> userValidator,
            Validator<Friendship> friendshipValidator,
            CommunityAnalyzer communityAnalyzer) {

        this.userRepository = Objects.requireNonNull(userRepository, "UserRepository cannot be null");
        this.friendshipRepository = Objects.requireNonNull(friendshipRepository, "FriendshipRepository cannot be null");

        this.userValidator = Objects.requireNonNull(userValidator, "UserValidator cannot be null");
        this.friendshipValidator = Objects.requireNonNull(friendshipValidator, "FriendshipValidator cannot be null");

        this.communityAnalyzer = Objects.requireNonNull(communityAnalyzer,"CommunityAnalyzer cannot be null");

        for (User user : userRepository.findAll()) {
            if (user.getId() >= nextUserId) {
                nextUserId = user.getId() + 1;
            }
        }
        for (Friendship friendship : friendshipRepository.findAll()) {
            if (friendship.getNumericId() >= nextFriendshipId) {
                nextFriendshipId = friendship.getNumericId() + 1;
            }
        }
    }

    public void addUser(String username, String firstName, String lastName) {
        String normalizedUsername = username == null ? null : username.trim();
        User user = new User(nextUserId, normalizedUsername, firstName, lastName);

        userValidator.validate(user);

        if (findUserByUsername(normalizedUsername) != null) {
            throw new ServiceException("Username already exists: " + normalizedUsername);
        }

        if (userRepository.save(user) != null) {
            throw new ServiceException(
                    "User already exists with id: " + nextUserId
            );
        }

        nextUserId++;
    }

    public void removeUser(Long id) {
        User user = requireUser(id);

        List<FriendshipId> friendshipsToDelete = new ArrayList<>();
        for (Friendship friendship : friendshipRepository.findAll()) {
            if (friendship.getFirstUsername().equalsIgnoreCase(user.getUsername())
                    || friendship.getSecondUsername().equalsIgnoreCase(user.getUsername())) {
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

    public void addFriendship(String firstUsername, String secondUsername) {
        User firstUser = requireUserByUsername(firstUsername);
        User secondUser = requireUserByUsername(secondUsername);

        Friendship friendship =
                new Friendship(nextFriendshipId, firstUser.getUsername(), secondUser.getUsername());

        friendshipValidator.validate(friendship);

        for (Friendship existing : friendshipRepository.findAll()) {
            boolean sameOrder = existing.getFirstUsername().equalsIgnoreCase(friendship.getFirstUsername())
                    && existing.getSecondUsername().equalsIgnoreCase(friendship.getSecondUsername());
            boolean reverseOrder = existing.getFirstUsername().equalsIgnoreCase(friendship.getSecondUsername())
                    && existing.getSecondUsername().equalsIgnoreCase(friendship.getFirstUsername());
            if (sameOrder || reverseOrder) {
                throw new ServiceException("Prietenia există deja.");
            }
        }

        if (friendshipRepository.save(friendship) != null) {
            throw new ServiceException("Prietenia există deja.");
        }
        nextFriendshipId++;
    }

    public void removeFriendship(Long id) {
        for (Friendship friendship : friendshipRepository.findAll()) {
            if (friendship.getNumericId().equals(id)) {
                friendshipRepository.delete(friendship.getId());
                return;
            }
        }
        throw new ServiceException("Prietenia nu există.");
    }

    public Iterable<Friendship> getFriendships() {
        return friendshipRepository.findAll();
    }


    private User findUserByUsername(String username) {
        if (username == null) {
            return null;
        }

        for (User user : userRepository.findAll()) {
            if (user.getUsername().equalsIgnoreCase(username.trim())) {
                return user;
            }
        }
        return null;
    }

    private User requireUserByUsername(String username) {
        User user = findUserByUsername(username);
        if (user == null) {
            throw new ServiceException("User with username " + username + " not found");
        }
        return user;
    }

    private User requireUser(Long id){
        User user = userRepository.findOne(id);
        if (user == null) {
            throw new ServiceException("User with id " + id + " not found");
        }

        return user;
    }

    private FriendshipGraph buildFriendshipGraph() {
        return new FriendshipGraph(
                userRepository.findAll(),
                friendshipRepository.findAll()
        );
    }

    public List<Community> getCommunities() {
        return communityAnalyzer.findCommunities(buildFriendshipGraph());
    }

    public int getCommunityCount() {
        return getCommunities().size();
    }

    public Community getMostSociableCommunity() {
        return communityAnalyzer.findMostSociableCommunity(buildFriendshipGraph()).orElseThrow(() ->
                new ServiceException("Nu exista comunitati in retea.")
        );
    }

}
