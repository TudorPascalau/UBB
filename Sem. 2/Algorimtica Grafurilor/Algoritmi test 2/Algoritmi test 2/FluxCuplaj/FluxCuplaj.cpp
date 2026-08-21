#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct Edge {
    int to;
    int rev;
    int cap;
};

int N, M, E;
vector<vector<Edge>> adj;

void addEdge(int u, int v, int cap) {
    Edge direct{ v, (int)adj[v].size(), cap };
    Edge invers{ u, (int)adj[u].size(), 0 };

    adj[u].push_back(direct);
    adj[v].push_back(invers);
}

bool bfs(int source, int sink, vector<int>& parentNode, vector<int>& parentEdge) {
    fill(parentNode.begin(), parentNode.end(), -1);
    fill(parentEdge.begin(), parentEdge.end(), -1);

    queue<int> q;
    q.push(source);
    parentNode[source] = source;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < (int)adj[u].size(); i++) {
            Edge& e = adj[u][i];

            if (parentNode[e.to] == -1 && e.cap > 0) {
                parentNode[e.to] = u;
                parentEdge[e.to] = i;

                if (e.to == sink)
                    return true;

                q.push(e.to);
            }
        }
    }

    return false;
}

int edmondsKarp(int source, int sink) {
    int maxFlow = 0;

    int totalNodes = N + M + 2;

    vector<int> parentNode(totalNodes);
    vector<int> parentEdge(totalNodes);

    while (bfs(source, sink, parentNode, parentEdge)) {
        int pathFlow = INT_MAX;

        for (int v = sink; v != source; v = parentNode[v]) {
            int u = parentNode[v];
            int edgeIndex = parentEdge[v];

            pathFlow = min(pathFlow, adj[u][edgeIndex].cap);
        }

        for (int v = sink; v != source; v = parentNode[v]) {
            int u = parentNode[v];
            int edgeIndex = parentEdge[v];

            adj[u][edgeIndex].cap -= pathFlow;

            int reverseIndex = adj[u][edgeIndex].rev;
            adj[v][reverseIndex].cap += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main() {
    cin >> N >> M >> E;

    int source = 0;
    int sink = N + M + 1;
    int totalNodes = N + M + 2;

    adj.assign(totalNodes, {});

    for (int x = 1; x <= N; x++) {
        addEdge(source, x, 1);
    }

    for (int y = 1; y <= M; y++) {
        addEdge(N + y, sink, 1);
    }

    for (int i = 0; i < E; i++) {
        int x, y;
        cin >> x >> y;

        addEdge(x, N + y, 1);
    }

    cout << edmondsKarp(source, sink) << '\n';

    return 0;
}