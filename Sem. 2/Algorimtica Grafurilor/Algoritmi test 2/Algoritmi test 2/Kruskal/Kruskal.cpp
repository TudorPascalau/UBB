#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, cost;
};

int V, E;
vector<int> parent, rang;

int findSet(int x) {
    if (parent[x] != x)
        parent[x] = findSet(parent[x]);

    return parent[x];
}

bool unionSet(int a, int b) {
    int rootA = findSet(a);
    int rootB = findSet(b);

    if (rootA == rootB)
        return false;

    if (rang[rootA] < rang[rootB])
        swap(rootA, rootB);

    parent[rootB] = rootA;

    if (rang[rootA] == rang[rootB])
        rang[rootA]++;

    return true;
}

int main() {
    cin >> V >> E;

    vector<Edge> edges;

    for (int i = 0; i < E; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;

        edges.push_back({ u, v, cost });
    }

    // Pentru indexare de la 1:
    parent.resize(V + 1);
    rang.resize(V + 1, 0);

    for (int i = 1; i <= V; i++)
        parent[i] = i;

    // Pentru indexare de la 0, schimbă blocul de mai sus în:
    /*
    parent.resize(V);
    rang.resize(V, 0);

    for (int i = 0; i < V; i++)
        parent[i] = i;
    */

    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.cost < b.cost;
        });

    vector<Edge> mst;
    int totalCost = 0;

    for (const auto& e : edges) {
        if (unionSet(e.u, e.v)) {
            mst.push_back(e);
            totalCost += e.cost;
        }
    }

    cout << "Cost MST: " << totalCost << '\n';
    cout << "Muchii MST:\n";

    for (const auto& e : mst) {
        cout << e.u << " " << e.v << " " << e.cost << '\n';
    }

    return 0;
}