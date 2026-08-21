
/*Problema 5. Pentru un graf dat sa se afiseze pe ecran varfurile descoperite de apelul
recursiv al procedurii dfs_visit(graf, nod).
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
ifstream fin("graf.txt");

void dfs_visit(vector<int> G[], int v, bool viz[]) {
	viz[v] = true;
	cout << v << " ";
	for (auto u : G[v])
		if (viz[u] == false)
			dfs_visit(G,u,viz);
}

int main() {
	vector<int> G[101];
	bool viz[101] = { false };
	int n, x, y;

	fin >> n;
	while (fin >> x >> y) {
		G[x].push_back(y);
		G[y].push_back(x);
	}

	for(int i = 1; i<=n; i++)
		if (viz[i] == false) {
			dfs_visit(G, i, viz);
			cout << "\n";
		}

	return 0;
}
