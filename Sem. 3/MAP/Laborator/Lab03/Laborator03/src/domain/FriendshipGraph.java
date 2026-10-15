package domain;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public final class FriendshipGraph {
    private final Map<String, Set<String>> adjacency;

    public FriendshipGraph(
            Iterable<User> users,
            Iterable<Friendship> friendships
    ) {
        Map<String, Set<String>> neighbors = new HashMap<>();

        for (User user : users) {
            neighbors.put(user.getUsername(), new HashSet<>());
        }

        for (Friendship friendship : friendships) {
            String firstUsername = friendship.getFirstUsername();
            String secondUsername = friendship.getSecondUsername();

            if (!neighbors.containsKey(firstUsername) || !neighbors.containsKey(secondUsername)) {
                throw new IllegalArgumentException("Friendship references a user outside the network");
            }

            neighbors.get(firstUsername).add(secondUsername);
            neighbors.get(secondUsername).add(firstUsername);
        }

        Map<String, Set<String>> immutableNeighbors = new HashMap<>();

        for (Map.Entry<String, Set<String>> entry : neighbors.entrySet()) {
            immutableNeighbors.put(
                    entry.getKey(),
                    Set.copyOf(entry.getValue())
            );
        }

        adjacency = Map.copyOf(immutableNeighbors);
    }

    public Set<String> getUsernames() {
        return adjacency.keySet();
    }

    public Set<String> getNeighbors(String username) {
        Set<String> neighbors = adjacency.get(username);

        if (neighbors == null) {
            throw new IllegalArgumentException("User does not exist in graph: " + username);
        }

        return neighbors;
    }
}
