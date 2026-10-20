package service;

import domain.*;
import repository.Repository;
import repository.RepositoryException;
import validation.Validator;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

/**
 * Coordinates network operations independently of the persistence backend.
 */
public class SocialNetworkService {
    private final Repository<Long, User> userRepository;
    private final Repository<FriendshipId, Friendship> friendshipRepository;
    private final Validator<User> userValidator;
    private final Validator<Friendship> friendshipValidator;
    private final CommunityAnalyzer communityAnalyzer;
    private long nextUserId = 1;

    /**
     * Creates a social network service.
     * @param userRepository user storage
     * @param friendshipRepository friendship storage
     * @param userValidator user validation strategy
     * @param friendshipValidator friendship validation strategy
     * @param communityAnalyzer graph analysis
     * @throws IllegalArgumentException if any dependency is null
     * @throws validation.ValidationException if loaded entities are invalid
     * @throws ServiceException if a loaded friendship references a missing user
     * @throws RepositoryException if storage cannot be accessed
     */
    public SocialNetworkService(Repository<Long, User> userRepository,
            Repository<FriendshipId, Friendship> friendshipRepository,
            Validator<User> userValidator, Validator<Friendship> friendshipValidator,
            CommunityAnalyzer communityAnalyzer) {
        if (userRepository == null || friendshipRepository == null || userValidator == null
                || friendshipValidator == null || communityAnalyzer == null)
            throw new IllegalArgumentException("Service dependencies cannot be null");

        this.userRepository = userRepository;
        this.friendshipRepository = friendshipRepository;
        this.userValidator = userValidator;
        this.friendshipValidator = friendshipValidator;
        this.communityAnalyzer = communityAnalyzer;

        validateLoadedData();

        for (User user : userRepository.findAll()) {
            if (user.getId() >= nextUserId) nextUserId = user.getId() + 1;
        }
    }
    /**
     * Adds a valid new user.
     * @param firstName given name
     * @param lastName family name
     * @throws validation.ValidationException if the user is invalid
     * @throws ServiceException if the generated ID already exists
     * @throws RepositoryException if persistence fails
     */
    public void addUser(String firstName, String lastName) {
        User user = new User(nextUserId, firstName, lastName);
        userValidator.validate(user);
        if (userRepository.save(user) != null)
            throw new ServiceException("User already exists with id " + nextUserId);
        nextUserId++;
    }
    /**
     * Removes the user and all incident friendships. Rollback is attempted on persistence failure.
     * @param id user ID
     * @throws IllegalArgumentException if id is null
     * @throws ServiceException if the user does not exist
     * @throws RepositoryException if persistence or rollback fails
     */
    public void removeUser(Long id) {
        ensureUserExists(id);
        List<Friendship> removed = new ArrayList<>();
        try {
            for (Friendship friendship : friendshipRepository.findAll()) {
                if (friendship.getFirstUserId().equals(id) || friendship.getSecondUserId().equals(id)) {
                    friendshipRepository.delete(friendship.getId());
                    removed.add(friendship);
                }
            }
            userRepository.delete(id);
        } catch (RepositoryException e) {
            // Recovery, not presentation: preserve references if the multi-file operation fails.
            for (Friendship friendship : removed) {
                try { friendshipRepository.save(friendship); }
                catch (RepositoryException recoveryError) { e.addSuppressed(recoveryError); }
            }
            if (e.getSuppressed().length > 0)
                throw new RepositoryException("Removal failed and rollback was incomplete; inspect both files", e);
            throw e;
        }
    }
    /**
     * Returns current users.
     * @return current users
     * @throws RepositoryException if storage fails
     */
    public Iterable<User> getUsers() { return userRepository.findAll(); }
    /**
     * Adds a friendship between existing users.
     * @param firstUserId first participant
     * @param secondUserId second participant
     * @throws IllegalArgumentException if either ID is null
     * @throws ServiceException if a user is absent or the friendship exists
     * @throws validation.ValidationException if the friendship is invalid
     * @throws RepositoryException if persistence fails
     */
    public void addFriendship(Long firstUserId, Long secondUserId) {
        Friendship friendship = new Friendship(firstUserId, secondUserId,
                LocalDateTime.now().withSecond(0).withNano(0));
        friendshipValidator.validate(friendship);
        ensureUserExists(firstUserId);
        ensureUserExists(secondUserId);
        if (friendshipRepository.save(friendship) != null)
            throw new ServiceException("Friendship already exists: " + friendship.getId());
    }
    /**
     * Removes a friendship by its participant IDs.
     * @param firstUserId first participant
     * @param secondUserId second participant
     * @throws IllegalArgumentException if either ID is null
     * @throws ServiceException if the friendship does not exist
     * @throws RepositoryException if persistence fails
     */
    public void removeFriendship(Long firstUserId, Long secondUserId) {
        if (friendshipRepository.delete(new FriendshipId(firstUserId, secondUserId)) == null)
            throw new ServiceException("Friendship does not exist");
    }
    /**
     * Returns current friendships.
     * @return current friendships
     * @throws RepositoryException if storage fails
     */
    public Iterable<Friendship> getFriendships() { return friendshipRepository.findAll(); }

    private void validateLoadedData() {
        for (User user : userRepository.findAll())
            userValidator.validate(user);

        for (Friendship friendship : friendshipRepository.findAll()) {
            friendshipValidator.validate(friendship);

            ensureUserExists(friendship.getFirstUserId());
            ensureUserExists(friendship.getSecondUserId());
        }
    }

    private void ensureUserExists(Long id) {
        User user = userRepository.findOne(id);
        if (user == null) throw new ServiceException("User with id " + id + " not found");
    }
    private FriendshipGraph buildFriendshipGraph() {
        return new FriendshipGraph(userRepository.findAll(), friendshipRepository.findAll());
    }
    /**
     * Finds communities in the network.
     * @return connected components
     * @throws RepositoryException if storage fails
     */
    public List<Community> getCommunities() {
        return communityAnalyzer.findCommunities(buildFriendshipGraph());
    }
    /**
     * Counts communities.
     * @return number of connected components
     * @throws RepositoryException if storage fails
     */
    public int getCommunityCount() { return getCommunities().size(); }
    /**
     * Finds the most sociable community.
     * @return the component with the longest simple path
     * @throws ServiceException if the network is empty
     * @throws RepositoryException if storage fails
     */
    public Community getMostSociableCommunity() {
        Optional<Community> result = communityAnalyzer.findMostSociableCommunity(buildFriendshipGraph());
        if (result.isEmpty()) throw new ServiceException("No communities found in the network.");
        return result.get();
    }
}
