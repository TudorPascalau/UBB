#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <iomanip>
using namespace std;

struct Edge {
    int to;
    int rev;
    int cap;
};

int N, M;
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

    vector<int> parentNode(N + 1);
    vector<int> parentEdge(N + 1);

    while (bfs(s, t, parentNode, parentEdge)) {
        int pathFlow = INT_MAX;

        for (int v = t; v != s; v = parentNode[v]) {
            int u = parentNode[v];
            int idx = parentEdge[v];

            pathFlow = min(pathFlow, adj[u][idx].cap);
        }

        for (int v = t; v != s; v = parentNode[v]) {
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
    ifstream fin("flux.in");
    ofstream fout("flux.out");

    fin >> N >> M;
    adj.assign(N + 1, {});

    for (int i = 0; i < M; i++) {
        int x, y, c;
        fin >> x >> y >> c;

        addEdge(x, y, c);
    }

    int sursa = 1;
    int destinatie = N;

    fout << fixed << setprecision(3) << (double)edmondsKarp(sursa, destinatie);

    return 0;
}