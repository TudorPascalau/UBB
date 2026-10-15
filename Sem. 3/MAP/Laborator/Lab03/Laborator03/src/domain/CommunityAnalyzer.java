package domain;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.HashSet;
import java.util.List;
import java.util.Objects;
import java.util.Optional;
import java.util.Set;

public final class CommunityAnalyzer {

    public List<Community> findCommunities(FriendshipGraph graph) {
        Objects.requireNonNull(graph, "Graph cannot be null");

        Set<String> visited = new HashSet<>();
        List<Community> communities = new ArrayList<>();

        for (String username : graph.getUsernames()) {
            if (!visited.contains(username)) {
                Set<String> members = collectComponent(graph, username, visited);

                communities.add(new Community(members));
            }
        }

        return List.copyOf(communities);
    }

    private Set<String> collectComponent(FriendshipGraph graph, String startUsername, Set<String> visited) {
        Set<String> members = new HashSet<>();
        Deque<String> stack = new ArrayDeque<>();

        visited.add(startUsername);
        stack.push(startUsername);

        while (!stack.isEmpty()) {
            String currentUsername = stack.pop();
            members.add(currentUsername);

            for (String neighbor : graph.getNeighbors(currentUsername)) {
                if (visited.add(neighbor)) {
                    stack.push(neighbor);
                }
            }
        }

        return members;
    }

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
        Set<String> currentPath = new HashSet<>();

        for (String username : community.getUsernames()) {
            int length = longestPathFrom(
                    graph,
                    username,
                    currentPath
            );

            maximumLength = Math.max(maximumLength, length);

            // Simple path cant be larger than max members - 1
            if (maximumLength == community.size() - 1) {
                break;
            }
        }

        return maximumLength;
    }

    private int longestPathFrom(FriendshipGraph graph, String currentUsername, Set<String> currentPath) {
        currentPath.add(currentUsername);
        int maximumLength = 0;

        for (String neighbor : graph.getNeighbors(currentUsername)) {
            if (!currentPath.contains(neighbor)) {
                int length = 1 + longestPathFrom(
                        graph,
                        neighbor,
                        currentPath
                );

                maximumLength = Math.max(maximumLength, length);
            }
        }

        currentPath.remove(currentUsername);
        return maximumLength;
    }
}
