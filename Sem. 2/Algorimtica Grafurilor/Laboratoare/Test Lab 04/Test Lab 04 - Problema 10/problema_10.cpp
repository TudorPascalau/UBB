#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
#include <iomanip>
#include <algorithm>

using std::cout;
using std::cin;

using namespace std;

float distEuclidiana(pair<int, int> a, pair<int, int> b) {
    float dx = a.first - b.first;
    float dy = a.second - b.second;
    return sqrt(dx * dx + dy * dy);
}

int main() {
    ifstream fin("in.txt");

    int n, m;
    fin >> n >> m;

    vector<pair<int, int>> coord(n + 1);
    for (int i = 1; i <= n; i++) {
        fin >> coord[i].first >> coord[i].second;
    }

    vector<vector<pair<int, float>>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int x, y;
        fin >> x >> y;

        float cost = distEuclidiana(coord[x], coord[y]);
        adj[x].push_back({ y, cost });  
    }

    int S, F;
    cin >> S >> F;

    const float INF = 1e18;
    vector<float> dist(n + 1, INF);
    vector<int> parent(n + 1, -1);

    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> pq;

    dist[S] = 0;
    pq.push({ 0, S });

    while (!pq.empty()) {
        double d = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (d > dist[node]) {
            continue;
        }

        for (const auto& edge : adj[node]) {
            int neigh = edge.first;
            double cost = edge.second;

            if (dist[node] + cost < dist[neigh]) {
                dist[neigh] = dist[node] + cost;
                parent[neigh] = node;
                pq.push({ dist[neigh], neigh });
            }
        }
    }

    if (dist[F] == INF) {
        cout << "Nu exista drum";
        return 0;
    }

    vector<int> path;
    for (int v = F; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());

    cout << fixed << setprecision(4);
    cout << "Distanta minima: " << dist[F] << "\n";
    cout << "Drum: ";
    for (int node : path) {
        cout << node << " ";
    }
    cout << "\n";

    return 0;
}