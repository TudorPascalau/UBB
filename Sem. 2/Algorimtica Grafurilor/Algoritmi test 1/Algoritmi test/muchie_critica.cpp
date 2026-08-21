#include <fstream>
#include <vector>
#include <queue>

using namespace std;

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

    int a, b;   // muchia care se elimina
    fin >> a >> b;

    vector<bool> viz(n + 1, false);
    queue<int> q;

    // Pornim din nodul 1 (sau orice alt nod existent)
    q.push(1);
    viz[1] = true;

    while (!q.empty()) {
        int x = q.front();
        q.pop();

        for (int y : adj[x]) {
            // ignoram muchia (a,b) si (b,a)
            if ((x == a && y == b) || (x == b && y == a)) {
                continue;
            }

            if (!viz[y]) {
                viz[y] = true;
                q.push(y);
            }
        }
    }

    bool conex = true;
    for (int i = 1; i <= n; i++) {
        if (!viz[i]) {
            conex = false;
            break;
        }
    }

    if (conex) {
        fout << "DA";
    }
    else {
        fout << "NU";
    }

    return 0;
}