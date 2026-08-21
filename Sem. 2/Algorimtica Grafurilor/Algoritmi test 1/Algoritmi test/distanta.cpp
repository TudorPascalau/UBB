#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

double distEuclidiana(pair<int, int> a, pair<int, int> b) {
    double dx = a.first - b.first;
    double dy = a.second - b.second;
    return sqrt(dx * dx + dy * dy);
}

int main(int argc, char* argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int n, m;
    fin >> n >> m;

    vector<pair<int, int>> coord(n + 1);
    for (int i = 1; i <= n; i++) {
        fin >> coord[i].first >> coord[i].second;
    }

    vector<vector<pair<int, double>>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int x, y;
        fin >> x >> y;

        double cost = distEuclidiana(coord[x], coord[y]);
        adj[x].push_back({ y, cost });   // graf orientat
    }

    int S = 1;
    int F = n;

    const double INF = 1e18;
    vector<double> dist(n + 1, INF);
    vector<int> parent(n + 1, -1);

    priority_queue<pair<double, int>,
        vector<pair<double, int>>,
        greater<pair<double, int>>> pq;

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
        fout << "Nu exista drum";
        return 0;
    }

    vector<int> path;
    for (int v = F; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());

    fout << fixed << setprecision(6);
    fout << "Distanta minima: " << dist[F] << "\n";
    fout << "Drum: ";
    for (int node : path) {
        fout << node << " ";
    }
    fout << "\n";

    return 0;
}