#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n, m, s;
    cin >> n >> m >> s;

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        // adj[y].push_back(x); // daca e neorientat
    }

    vector<int> dist(n, -1), parent(n, -1);
    queue<int> q;

    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int x = q.front();
        q.pop();

        for (int y : adj[x]) {
            if (dist[y] == -1) {
                dist[y] = dist[x] + 1;
                parent[y] = x;
                q.push(y);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << "nod " << i << ", dist = " << dist[i]
            << ", parent = " << parent[i] << "\n";
    }
}