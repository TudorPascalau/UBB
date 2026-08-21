#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct Edge {
    int to;
    int rev;
    int cap;
};

int V, E;
vector<vector<Edge>> adj;

void addEdge(int x, int y, int cap) {
    Edge direct{ y, (int)adj[y].size(), cap };
    Edge invers{ x, (int)adj[x].size(), 0 };

    adj[x].push_back(direct);
    adj[y].push_back(invers);
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

    // Problema are indexare de la 0.
    vector<int> parentNode(V);
    vector<int> parentEdge(V);

    while (bfs(source, sink, parentNode, parentEdge)) {
        int pathFlow = INT_MAX;

        for (int v = sink; v != source; v = parentNode[v]) {
            int u = parentNode[v];
            int idx = parentEdge[v];

            pathFlow = min(pathFlow, adj[u][idx].cap);
        }

        for (int v = sink; v != source; v = parentNode[v]) {
            int u = parentNode[v];
            int idx = parentEdge[v];

            adj[u][idx].cap -= pathFlow;

            int rev = adj[u][idx].rev;
            adj[v][rev].cap += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main() {
    ifstream fin("maxflow.in");
    ofstream fout("maxflow.out");

    fin >> V >> E;

    // Problema spune explicit: vârfurile sunt indexate de la 0.
    adj.assign(V, {});

    // Dacă ar fi indexare de la 1, ai schimba în:
    // adj.assign(V + 1, {});

    for (int i = 0; i < E; i++) {
        int x, y, c;
        fin >> x >> y >> c;

        addEdge(x, y, c);
    }

    int source = 0;
    int sink = V - 1;

    fout << edmondsKarp(source, sink) << '\n';

    return 0;
}