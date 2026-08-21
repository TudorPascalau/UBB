#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    int from, to, cost;
};

const int INF = 1e9;

int main() {
    int n, m, s;
    cin >> n >> m >> s;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].from >> edges[i].to >> edges[i].cost;
    }

    vector<int> dist(n, INF), parent(n, -1);
    dist[s] = 0;

    for (int i = 1; i <= n - 1; i++) {
        bool changed = false;
        for (const auto& e : edges) {
            if (dist[e.from] != INF && dist[e.to] > dist[e.from] + e.cost) {
                dist[e.to] = dist[e.from] + e.cost;
                parent[e.to] = e.from;
                changed = true;
            }
        }
        if (!changed) break;
    }

    bool negativeCycle = false;
    for (const auto& e : edges) {
        if (dist[e.from] != INF && dist[e.to] > dist[e.from] + e.cost) {
            negativeCycle = true;
            break;
        }
    }

    if (negativeCycle) {
        cout << "Exista circuit negativ accesibil din sursa\n";
    }
    else {
        for (int i = 0; i < n; i++) {
            if (dist[i] == INF) cout << "INF ";
            else cout << dist[i] << " ";
        }
        cout << "\n";
    }
}