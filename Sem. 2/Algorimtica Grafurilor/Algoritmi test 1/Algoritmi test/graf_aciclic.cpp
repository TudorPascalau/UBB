#include <fstream>
#include <vector>

using namespace std;

bool dfs(int node, int parent, const vector<vector<int>>& adj, vector<bool>& visited) {
    visited[node] = true;

    for (int neigh : adj[node]) {
        if (!visited[neigh]) {
            if (dfs(neigh, node, adj, visited)) {
                return true;
            }
        }
        else if (neigh != parent) {
            return true;
        }
    }

    return false;
}

int main(int argc, char* argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int n, m;
    fin >> n >> m;

    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int x, y;
        fin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<bool> visited(n + 1, false);
    bool hasCycle = false;

    for (int i = 1; i <= n && !hasCycle; i++) {
        if (!visited[i]) {
            if (dfs(i, 0, adj, visited)) {
                hasCycle = true;
            }
        }
    }

    if (hasCycle) {
        fout << "NU";
    }
    else {
        fout << "DA";
    }

    return 0;
}