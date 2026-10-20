package domain;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

/**
 * Immutable undirected graph keyed by user IDs.
 */
public final class FriendshipGraph {
    private final Map<Long, Set<Long>> adjacency;

    /**
     * Creates a friendship graph.
     * @param users graph vertices
     * @param friendships undirected edges
     * @throws IllegalArgumentException if an edge references an absent user
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
     * @return all vertex IDs
     */
    public Set<Long> getUserIds() {
        return adjacency.keySet();
    }

    /**
     * Returns adjacent vertex IDs.
     * @param userId vertex ID
     * @return adjacent vertex IDs
     * @throws IllegalArgumentException if the vertex is absent
     */
    public Set<Long> getNeighbors(Long userId) {
        Set<Long> neighbors = adjacency.get(userId);

        if (neighbors == null) {
            throw new IllegalArgumentException("User does not exist in graph: " + userId);
        }

        return neighbors;
    }
}
