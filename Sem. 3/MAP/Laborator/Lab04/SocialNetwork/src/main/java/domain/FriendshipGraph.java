package domain;

import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import static util.StreamHelper.stream;

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
    public FriendshipGraph(
            Iterable<User> users,
            Iterable<Friendship> friendships) {

        Set<Long> userIds = stream(users)
                .map(User::getId)
                .collect(Collectors.toSet());

        List<Friendship> friendshipList = stream(friendships).toList();

        friendshipList.forEach(friendship -> {
            if (!userIds.contains(friendship.getFirstUserId())
                    || !userIds.contains(friendship.getSecondUserId())) {

                throw new IllegalArgumentException(
                        "Friendship references a user outside the network");
            }
        });

        Map<Long, Set<Long>> neighbors = friendshipList.stream()
                .flatMap(friendship -> Stream.of(
                        Map.entry(
                                friendship.getFirstUserId(),
                                friendship.getSecondUserId()),
                        Map.entry(
                                friendship.getSecondUserId(),
                                friendship.getFirstUserId())))
                .collect(Collectors.groupingBy(
                        entry -> entry.getKey(),
                        Collectors.mapping(
                                entry -> entry.getValue(),
                                Collectors.toSet())));

        Map<Long, Set<Long>> immutableNeighbors = userIds.stream()
                .collect(Collectors.toMap(
                        id -> id,
                        id -> Set.copyOf(
                                neighbors.getOrDefault(id, Set.of()))));

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
