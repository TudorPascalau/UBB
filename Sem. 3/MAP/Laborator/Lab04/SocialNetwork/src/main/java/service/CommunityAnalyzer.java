package service;

import domain.Community;
import domain.FriendshipGraph;

import java.util.*;

/**
 * Identifies and analyzes friendship communities.
 */
public final class CommunityAnalyzer {
    /**
     * Creates a community analyzer.
     */
    public CommunityAnalyzer() {}

    /**
     * Finds maximal groups in which every user is connected to every other by friendships.
     * @param graph network graph
     * @return an unmodifiable list of communities, including isolated users; empty for an empty network
     * @throws NullPointerException if graph is null
     */
    public List<Community> findCommunities(FriendshipGraph graph) {
        Objects.requireNonNull(graph, "Graph cannot be null");

        Set<Long> visited = new HashSet<>();

        List<Community> communities = graph.getUserIds().stream()
                .collect(
                        ArrayList<Community>::new,
                        (result, userId) -> {
                            if (!visited.contains(userId)) {
                                Set<Long> members =
                                        collectComponent(graph, userId, visited);

                                result.add(new Community(members));
                            }
                        },
                        (left, right) -> left.addAll(right));

        return List.copyOf(communities);
    }

    // DFS with stack
    private Set<Long> collectComponent(
            FriendshipGraph graph,
            Long startUserId,
            Set<Long> visited) {

        Set<Long> members = new HashSet<>();
        visitComponent(graph, startUserId, visited, members);
        return members;
    }

    /**
     * Visits the users reachable from the supplied user.
     *
     * @param graph network graph
     * @param userId user to visit
     * @param visited identifiers already visited across components
     * @param members identifiers collected for the current component
     */
    private void visitComponent(
            FriendshipGraph graph,
            Long userId,
            Set<Long> visited,
            Set<Long> members) {

        if (!visited.add(userId)) {
            return;
        }

        members.add(userId);

        graph.getNeighbors(userId).stream()
                .filter(neighbor -> !visited.contains(neighbor))
                .forEach(neighbor -> visitComponent(graph, neighbor, visited, members));
    }

    /**
     * Finds the community with the longest chain of friendships without repeated users.
     * @param graph network graph
     * @return a community with a longest such chain (any in case of a tie), or empty for an empty network
     * @throws NullPointerException if graph is null
     */
    public Optional<Community> findMostSociableCommunity(
            FriendshipGraph graph) {

        return findCommunities(graph).stream()
                .map(community ->
                        new AbstractMap.SimpleImmutableEntry<>(
                                community,
                                longestPathLength(graph, community)))
                .max(Comparator.comparingInt(
                        (Map.Entry<Community, Integer> entry) ->
                                entry.getValue()))
                .map(Map.Entry::getKey);
    }

    private int longestPathLength(FriendshipGraph graph, Community community) {
        int maximumLength = 0;
        Set<Long> currentPath = new HashSet<>();

        for (Long userId : community.getUserIds()) {
            int length = longestPathFrom(graph, userId, currentPath);

            maximumLength = Math.max(maximumLength, length);

            // Max size = n - 1
            if (maximumLength == community.size() - 1) {
                break;
            }
        }

        return maximumLength;
    }

    // DFS backtracking
    private int longestPathFrom(FriendshipGraph graph, Long currentUserId, Set<Long> currentPath) {
        currentPath.add(currentUserId);
        int maximumLength = 0;

        for (Long neighbor : graph.getNeighbors(currentUserId)) {
            if (!currentPath.contains(neighbor)) {
                int length = 1 + longestPathFrom(graph, neighbor, currentPath);

                maximumLength = Math.max(maximumLength, length);
            }
        }

        currentPath.remove(currentUserId);
        return maximumLength;
    }
}
