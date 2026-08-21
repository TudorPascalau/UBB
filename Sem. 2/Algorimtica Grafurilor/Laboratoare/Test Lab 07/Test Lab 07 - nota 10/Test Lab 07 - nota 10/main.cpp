#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
using namespace std;

ifstream fin("arb.in");
ofstream fout("arb.out");

const int INF = 1e9;

struct Edge {
    int x, y, cost;
};

int N, M;

int main() {
    fin >> N >> M;
    vector<Edge> edges_orig;
    edges_orig.reserve(M+1);
    for (int i = 1; i <= M; ++i) {
        int x, y, c;
        fin >> x >> y >> c;
        edges_orig.push_back({x, y, c});
    }

    vector<vector<pair<int,int>>> adj(N);
    for (int i = 0; i <= N-2; ++i) {
        int u = edges_orig[i].x;
        int v = edges_orig[i].y;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }

    vector<int> parent0(N, 0), depth(N, 0), parentEdgeIndex(N, -1);
    vector<int> st;
    st.reserve(N);
    st.push_back(0);
    parent0[0] = 0;
    depth[0] = 0;
    vector<int> itIdx(N, 0);
    while (!st.empty()) {
        int u = st.back();
        if (itIdx[u] < (int)adj[u].size()) {
            auto [v, ei] = adj[u][itIdx[u]++];
            if (v == parent0[u]) continue;
            parent0[v] = u;
            parentEdgeIndex[v] = ei;
            depth[v] = depth[u] + 1;
            st.push_back(v);
        } else {
            st.pop_back();
        }
    }

    int LOG = 1;
    while ((1<<LOG) <= N) ++LOG;
    vector<vector<int>> up(LOG, vector<int>(N));
    for (int v = 0; v < N; ++v) up[0][v] = parent0[v];
    for (int k = 1; k < LOG; ++k) {
        for (int v = 0; v < N; ++v) up[k][v] = up[k-1][ up[k-1][v] ];
    }
    auto lca = [&](int a, int b){
        if (depth[a] < depth[b]) swap(a,b);
        int d = depth[a] - depth[b];
        for (int k = 0; k < LOG; ++k) if (d & (1<<k)) a = up[k][a];
        if (a == b) return a;
        for (int k = LOG-1; k >= 0; --k) {
            if (up[k][a] != up[k][b]) {
                a = up[k][a];
                b = up[k][b];
            }
        }
        return up[0][a];
    };


    vector<int> jump(N);
    for (int i = 0; i < N; ++i) jump[i] = i;
    function<int(int)> findf = [&](int x) -> int {
        if (jump[x] == x) return x;
        return jump[x] = findf(jump[x]);
    };

    vector<int> ans(max(0, N-1), -1);

    struct NT { int u,v,w,idx; };
    vector<NT> nonTree;
    for (int i = N-1; i <= M-1; ++i) {
        auto &e = edges_orig[i];
        nonTree.push_back({e.x, e.y, e.cost, i});
    }
    sort(nonTree.begin(), nonTree.end(), [](const NT &a, const NT &b){ if (a.w!=b.w) return a.w < b.w; return a.idx < b.idx; });

    auto process_path = [&](int u, int anc, int edgeIdx){
        while (true) {
            int x = findf(u);
            if (depth[x] <= depth[anc]) break;
            int te = parentEdgeIndex[x];
            if (te >= 0 && ans[te] == -1) ans[te] = edgeIdx;
            jump[x] = findf(parent0[x]);
        }
    };

    for (auto &nt : nonTree) {
        int u = nt.u, v = nt.v, idx = nt.idx;
        int a = lca(u,v);
        process_path(u, a, idx);
        process_path(v, a, idx);
    }

    for (int i = 0; i <= N-2; ++i) {
        if (ans[i] == -1) fout << -1 << '\n';
        else fout << ans[i] << '\n';
    }

    return 0;
}