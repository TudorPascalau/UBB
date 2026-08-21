#include <iostream>
#include <vector>
using namespace std;

void dfs(int x, const vector<vector<int>>& adj, vector<bool>& viz) {
    viz[x] = true;
    cout << x << " ";

    for (int y : adj[x]) {
        if (!viz[y]) {
            dfs(y, adj, viz);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        // adj[y].push_back(x); // daca e neorientat
    }

    vector<bool> viz(n, false);

    for (int i = 0; i < n; i++) {
        if (!viz[i]) {
            dfs(i, adj, viz);
        }
    }
}