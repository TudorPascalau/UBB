// p2.cpp
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    int rev;
    int cap;
    int flow;
};

int V, E;
vector<vector<Edge>> adj;
vector<int> h, exces;
vector<bool> inQueue;
queue<int> q;

void addEdge(int u, int v, int cap) {
    Edge direct{ v, (int)adj[v].size(), cap, 0 };
    Edge invers{ u, (int)adj[u].size(), 0, 0 };

    adj[u].push_back(direct);
    adj[v].push_back(invers);
}

int capacitateReziduala(const Edge& e) {
    return e.cap - e.flow;
}

void adaugaActiv(int u, int s, int t) {
    if (u != s && u != t && exces[u] > 0 && !inQueue[u]) {
        q.push(u);
        inQueue[u] = true;
    }
}

void pompare(int u, int i, int s, int t) {
    Edge& e = adj[u][i];

    if (exces[u] <= 0) return;
    if (capacitateReziduala(e) <= 0) return;
    if (h[u] != h[e.to] + 1) return;

    int delta = min(exces[u], capacitateReziduala(e));

    e.flow += delta;
    adj[e.to][e.rev].flow -= delta;

    exces[u] -= delta;
    exces[e.to] += delta;

    adaugaActiv(e.to, s, t);
}

void inaltare(int u) {
    int minim = 1e9;

    for (const Edge& e : adj[u]) {
        if (capacitateReziduala(e) > 0) {
            minim = min(minim, h[e.to]);
        }
    }

    if (minim != 1e9) {
        h[u] = minim + 1;
    }
}

void descarca(int u, int s, int t) {
    while (exces[u] > 0) {
        bool amPompat = false;

        for (int i = 0; i < (int)adj[u].size() && exces[u] > 0; i++) {
            int vechi = exces[u];
            pompare(u, i, s, t);

            if (exces[u] < vechi) {
                amPompat = true;
            }
        }

        if (!amPompat) {
            inaltare(u);
        }
    }
}

void initializarePreflux(int s, int t) {
    h[s] = V;

    for (int i = 0; i < (int)adj[s].size(); i++) {
        Edge& e = adj[s][i];

        int delta = e.cap;
        e.flow += delta;
        adj[e.to][e.rev].flow -= delta;

        exces[s] -= delta;
        exces[e.to] += delta;

        adaugaActiv(e.to, s, t);
    }
}

int pomparePreflux(int s, int t) {
    initializarePreflux(s, t);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inQueue[u] = false;

        descarca(u, s, t);
    }

    return exces[t];
}

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    fin >> V >> E;

    adj.assign(V, {});
    h.assign(V, 0);
    exces.assign(V, 0);
    inQueue.assign(V, false);

    for (int i = 0; i < E; i++) {
        int x, y, c;
        fin >> x >> y >> c;
        addEdge(x, y, c);
    }

    int s = 0;
    int t = V - 1;

    fout << pomparePreflux(s, t);

    return 0;
}