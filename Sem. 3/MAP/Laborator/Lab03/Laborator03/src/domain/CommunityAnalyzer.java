package domain;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.HashSet;
import java.util.List;
import java.util.Objects;
import java.util.Optional;
import java.util.Set;

/**
 * Finds connected components and longest simple paths using explicit loops.
 */
public final class CommunityAnalyzer {
    /**
     * Creates a graph analyzer.
     */
    public CommunityAnalyzer() {}

    /**
     * Finds all connected components.
     * @param graph network graph
     * @return connected components
     * @throws NullPointerException if graph is null
     */
    public List<Community> findCommunities(FriendshipGraph graph) {
        Objects.requireNonNull(graph, "Graph cannot be null");

        Set<Long> visited = new HashSet<>();
        List<Community> communities = new ArrayList<>();

        for (Long userId : graph.getUserIds()) {
            if (!visited.contains(userId)) {
                Set<Long> members = collectComponent(graph, userId, visited);

                communities.add(new Community(members));
            }
        }

        return List.copyOf(communities);
    }

    private Set<Long> collectComponent(FriendshipGraph graph, Long startUserId, Set<Long> visited) {
        Set<Long> members = new HashSet<>();
        Deque<Long> stack = new ArrayDeque<>();

        visited.add(startUserId);
        stack.push(startUserId);

        while (!stack.isEmpty()) {
            Long currentUserId = stack.pop();
            members.add(currentUserId);

            for (Long neighbor : graph.getNeighbors(currentUserId)) {
                if (visited.add(neighbor)) {
                    stack.push(neighbor);
                }
            }
        }

        return members;
    }

    /**
     * Finds the component with the longest simple path.
     * @param graph network graph
     * @return the component with the longest simple path, or empty for an empty graph
     * @throws NullPointerException if graph is null
     */
    public Optional<Community> findMostSociableCommunity(FriendshipGraph graph) {
        List<Community> communities = findCommunities(graph);

        Community mostSociable = null;
        int maximumLength = -1;

        for (Community community : communities) {
            int length = longestPathLength(graph, community);

            if (length > maximumLength) {
                maximumLength = length;
                mostSociable = community;
            }
        }

        return Optional.ofNullable(mostSociable);
    }

    private int longestPathLength(FriendshipGraph graph, Community community) {
        int maximumLength = 0;
        Set<Long> currentPath = new HashSet<>();

        for (Long userId : community.getUserIds()) {
            int length = longestPathFrom(graph, userId, currentPath);

            maximumLength = Math.max(maximumLength, length);

            // Simple path cant be larger than max members - 1
            if (maximumLength == community.size() - 1) {
                break;
            }
        }

        return maximumLength;
    }

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
