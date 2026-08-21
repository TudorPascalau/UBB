#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int x, y, cost;
};

int N, M;
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
    ifstream fin("apm.in");
    ofstream fout("apm.out");

    fin >> N >> M;

    vector<Edge> edges;

    for (int i = 0; i < M; i++) {
        int x, y, c;
        fin >> x >> y >> c;

        edges.push_back({ x, y, c });
    }

    // Problema are noduri indexate de la 1 la N.
    parent.resize(N + 1);
    rang.resize(N + 1, 0);

    for (int i = 1; i <= N; i++)
        parent[i] = i;

    // Dacă nodurile ar fi indexate de la 0:
    /*
    parent.resize(N);
    rang.resize(N, 0);

    for (int i = 0; i < N; i++)
        parent[i] = i;
    */

    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.cost < b.cost;
        });

    vector<Edge> mst;
    int totalCost = 0;

    for (const Edge& e : edges) {
        if (unionSet(e.x, e.y)) {
            mst.push_back(e);
            totalCost += e.cost;
        }
    }

    fout << totalCost << '\n';
    fout << mst.size() << '\n';

    for (const Edge& e : mst) {
        fout << e.x << " " << e.y << '\n';
    }

    return 0;
}