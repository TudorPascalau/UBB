package service;

import domain.*;
import repository.Repository;
import repository.RepositoryException;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import static util.StreamHelper.stream;

/**
 * Coordinates network operations independently of the persistence backend.
 */
public class SocialNetworkService {
    private final Repository<Long, User> userRepository;
    private final Repository<FriendshipId, Friendship> friendshipRepository;
    private final CommunityAnalyzer communityAnalyzer;
    private long nextUserId;

    /**
     * Creates a social network service.
     * @param userRepository user storage
     * @param friendshipRepository friendship storage
     * @param communityAnalyzer graph analysis
     * @throws IllegalArgumentException if any dependency is null
     * @throws ServiceException if a loaded friendship references a missing user
     * @throws RepositoryException if storage cannot be accessed
     */
    public SocialNetworkService(Repository<Long, User> userRepository,
            Repository<FriendshipId, Friendship> friendshipRepository,
            CommunityAnalyzer communityAnalyzer) {
        if (userRepository == null || friendshipRepository == null || communityAnalyzer == null)
            throw new IllegalArgumentException("Service dependencies cannot be null");

        this.userRepository = userRepository;
        this.friendshipRepository = friendshipRepository;
        this.communityAnalyzer = communityAnalyzer;

        validateLoadedRelationships();

        nextUserId = stream(userRepository.findAll())
                .mapToLong(User::getId)
                .max()
                .orElse(0L) + 1;
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
        if (userRepository.save(user).isPresent()) {
            throw new ServiceException("User already exists with id " + nextUserId);
        }
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

        List<Friendship> incidentFriendships = incidentFriendships(id).toList();

        List<Friendship> removed = new ArrayList<>();

        try {
            incidentFriendships.forEach(friendship -> {
                friendshipRepository.delete(friendship.getId());

                // Track only deletions that completed successfully.
                removed.add(friendship);
            });

            userRepository.delete(id);
        }
        catch (RepositoryException e) {
            removed.forEach(friendship -> {
                try {
                    friendshipRepository.save(friendship);
                }
                catch (RepositoryException recoveryError) {
                    e.addSuppressed(recoveryError);
                }
            });

            if (e.getSuppressed().length > 0) {
                throw new RepositoryException("Removal failed and rollback was incomplete; inspect both files", e);
            }

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
     * Finds users matching the supplied condition.
     * @param filter condition used to select users
     * @return matching users; empty if none match
     * @throws IllegalArgumentException if filter is null
     * @throws RepositoryException if persistence fails
     */
    public List<User> findUsers(Predicate<User> filter) {
        return userRepository.findAll(filter);
    }

    /**
     * Returns users sorted using the supplied comparator.
     *
     * @param comparator ordering applied to users
     * @return a sorted, unmodifiable list; empty if no users exist
     * @throws IllegalArgumentException if comparator is null
     * @throws RepositoryException if persistence fails
     */
    public List<User> getSortedUsers(Comparator<User> comparator) {
        if (comparator == null) {
            throw new IllegalArgumentException("Comparator cannot be null");
        }

        return stream(userRepository.findAll())
                .sorted(comparator)
                .toList();
    }

    /**
     * Returns the friends of an existing user.
     *
     * @param userId identifier of the user whose friends are requested
     * @return the user's friends, or an empty list if the user has none
     * @throws IllegalArgumentException if userId is null
     * @throws ServiceException if the user or a referenced friend does not exist
     * @throws RepositoryException if storage cannot be accessed
     */
    public List<User> getFriends(Long userId) {
        ensureUserExists(userId);

        return incidentFriendships(userId)
                .map(friendship -> friendship.getFirstUserId().equals(userId)
                        ? friendship.getSecondUserId()
                        : friendship.getFirstUserId())
                .map(this::ensureUserExists)
                .collect(Collectors.toList());
    }

    private Stream<Friendship> incidentFriendships(Long userId) {
        return stream(friendshipRepository.findAll())
                .filter(friendship -> friendship.getFirstUserId().equals(userId)
                        || friendship.getSecondUserId().equals(userId));
    }

    private User ensureUserExists(Long id) {
        return userRepository.findOne(id).orElseThrow(() ->
                new ServiceException("User with id " + id + " not found"));
    }

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
        ensureUserExists(firstUserId);
        ensureUserExists(secondUserId);
        if (friendshipRepository.save(friendship).isPresent()) {
            throw new ServiceException("Friendship already exists: " + friendship.getId());
        }
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
        friendshipRepository.delete(new FriendshipId(firstUserId, secondUserId)).orElseThrow(() ->
                        new ServiceException("Friendship does not exist"));
    }
    /**
     * Returns current friendships.
     * @return current friendships
     * @throws RepositoryException if storage fails
     */
    public Iterable<Friendship> getFriendships() { return friendshipRepository.findAll(); }

    private void validateLoadedRelationships() {
        stream(friendshipRepository.findAll()).flatMap(friendship -> java.util.stream.Stream.of(
                        friendship.getFirstUserId(), friendship.getSecondUserId())).forEach(this::ensureUserExists);
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
        return communityAnalyzer.findMostSociableCommunity(buildFriendshipGraph()).
                orElseThrow(() -> new ServiceException("No communities found in the network."));
    }
}
