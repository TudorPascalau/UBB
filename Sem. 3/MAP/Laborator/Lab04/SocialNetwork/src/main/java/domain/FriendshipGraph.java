package domain;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

/**
 * An immutable view of users and their mutual friendships in graph format.
 */
public final class FriendshipGraph {
    private final Map<Long, Set<Long>> adjacency;

    /**
     * Creates a friendship graph.
     * @throws NullPointerException if either input is null or contains null
     * @param users users in the network
     * @param friendships friendships between network users
     * @throws IllegalArgumentException if a friendship references a user outside the network
     */
    public FriendshipGraph(Iterable<User> users, Iterable<Friendship> friendships) {
        Map<Long, Set<Long>> neighbors = new HashMap<>();

        for (User user : users) {
            neighbors.put(user.getId(), new HashSet<>());
        }

        for (Friendship friendship : friendships) {
            Long firstUserId = friendship.getFirstUserId();
            Long secondUserId = friendship.getSecondUserId();

            if (!neighbors.containsKey(firstUserId) || !neighbors.containsKey(secondUserId)) {
                throw new IllegalArgumentException("Friendship references a user outside the network");
            }

            neighbors.get(firstUserId).add(secondUserId);
            neighbors.get(secondUserId).add(firstUserId);
        }

        Map<Long, Set<Long>> immutableNeighbors = new HashMap<>();

        for (Map.Entry<Long, Set<Long>> entry : neighbors.entrySet()) {
            immutableNeighbors.put(entry.getKey(), Set.copyOf(entry.getValue()));
        }

        adjacency = Map.copyOf(immutableNeighbors);
    }

    /**
     * Returns the member identifiers.
     * @return an unmodifiable set of all user identifiers
     */
    public Set<Long> getUserIds() {
        return adjacency.keySet();
    }

    /**
     * Returns the identifiers of a user's friends.
     * @throws NullPointerException if userId is null
     * @param userId identifier of a user in the network
     * @return an unmodifiable set of friend identifiers, empty for a user without friends
     * @throws IllegalArgumentException if the user is absent
     */
    public Set<Long> getNeighbors(Long userId) {
        Set<Long> neighbors = adjacency.get(userId);

        if (neighbors == null) {
            throw new IllegalArgumentException("User does not exist in graph: " + userId);
        }

        return neighbors;
    }
}
