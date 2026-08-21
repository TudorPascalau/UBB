#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct Edge {
    int to;
    int cost;
};

int main() {
    int V, E;
    cin >> V >> E;

    // Pentru indexare de la 1:
    vector<vector<Edge>> adj(V + 1);

    // Pentru indexare de la 0, schimbă în:
    // vector<vector<Edge>> adj(V);

    for (int i = 0; i < E; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;

        adj[u].push_back({ v, cost });
        adj[v].push_back({ u, cost });
    }

    int start;
    cin >> start;

    // Pentru indexare de la 1:
    vector<int> key(V + 1, INT_MAX);
    vector<int> parent(V + 1, -1);
    vector<bool> inMST(V + 1, false);

    // Pentru indexare de la 0, schimbă în:
    /*
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);
    */

    priority_queue<pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>> pq;

    key[start] = 0;
    pq.push({ 0, start });

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u])
            continue;

        inMST[u] = true;

        for (auto e : adj[u]) {
            int v = e.to;
            int cost = e.cost;

            if (!inMST[v] && cost < key[v]) {
                key[v] = cost;
                parent[v] = u;
                pq.push({ key[v], v });
            }
        }
    }

    int totalCost = 0;

    cout << "Muchii MST:\n";

    // Pentru indexare de la 1:
    for (int v = 1; v <= V; v++) {
        if (v != start && parent[v] != -1) {
            cout << parent[v] << " " << v << " " << key[v] << '\n';
            totalCost += key[v];
        }
    }

    // Pentru indexare de la 0, schimbă for-ul de mai sus în:
    /*
    for (int v = 0; v < V; v++) {
        if (v != start && parent[v] != -1) {
            cout << parent[v] << " " << v << " " << key[v] << '\n';
            totalCost += key[v];
        }
    }
    */

    cout << "Cost MST: " << totalCost << '\n';

    return 0;
}