#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

ifstream fin("in.txt");
ofstream fout("out.txt");

struct Edge {
    int to;
    int rev;
    int cap;
};

int V, E;
vector<vector<Edge>> adj;

void addEdge(int u, int v, int cap) {
    Edge direct{ v, (int)adj[v].size(), cap };
    Edge invers{ u, (int)adj[u].size(), 0 };

    adj[u].push_back(direct);
    adj[v].push_back(invers);
}

bool bfs(int s, int t, vector<int>& parentNode, vector<int>& parentEdge) {
    fill(parentNode.begin(), parentNode.end(), -1);
    fill(parentEdge.begin(), parentEdge.end(), -1);

    queue<int> q;
    q.push(s);
    parentNode[s] = s;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < (int)adj[u].size(); i++) {
            Edge& e = adj[u][i];

            if (parentNode[e.to] == -1 && e.cap > 0) {
                parentNode[e.to] = u;
                parentEdge[e.to] = i;

                if (e.to == t)
                    return true;

                q.push(e.to);
            }
        }
    }

    return false;
}

int edmondsKarp(int s, int t) {
    int maxFlow = 0;

    vector<int> parentNode(V + 1);
    vector<int> parentEdge(V + 1);

    while (bfs(s, t, parentNode, parentEdge)) {
        int pathFlow = INT_MAX;

        for (int v = t; v != s; v = parentNode[v]) {
            int u = parentNode[v];
            int edgeIndex = parentEdge[v];

            pathFlow = min(pathFlow, adj[u][edgeIndex].cap);
        }

        for (int v = t; v != s; v = parentNode[v]) {
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
    fin >> V >> E;

    // Pentru indexare de la 1:
    adj.assign(V + 1, {});

    // Pentru indexare de la 0, schimbă în:
    // adj.assign(V, {});

    for (int i = 0; i < E; i++) {
        int u, v, cap;
        fin >> u >> v >> cap;

        addEdge(u, v, cap);
    }

    int s, t;
    fin >> s >> t;

    fout << "Flux maxim: " << edmondsKarp(s, t) << '\n';

    return 0;
}