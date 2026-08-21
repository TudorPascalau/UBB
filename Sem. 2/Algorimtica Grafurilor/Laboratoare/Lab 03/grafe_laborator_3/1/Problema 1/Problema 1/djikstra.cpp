#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1e9;

int main() {
    int n, m, s;
    cin >> n >> m >> s;

    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        adj[x].push_back({ y, w });
        // adj[y].push_back({x, w}); // daca e neorientat
    }

    vector<int> dist(n, INF), parent(n, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[s] = 0;
    pq.push({ 0, s });

    while (!pq.empty()) {
        auto [d, x] = pq.top();
        pq.pop();

        if (d != dist[x]) continue; // ignoram intrarile vechi

        for (auto [y, w] : adj[x]) {
            if (dist[y] > dist[x] + w) {
                dist[y] = dist[x] + w;
                parent[y] = x;
                pq.push({ dist[y], y });
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) cout << "INF ";
        else cout << dist[i] << " ";
    }
    cout << "\n";
}