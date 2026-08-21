#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;
	
struct Edge {
	int to, id;
};

int main(int argc, char* argv[]) {

	ifstream fin(argv[1]);
	ofstream fout(argv[2]);

	int V, E;
	fin >> V >> E;

	vector<vector<Edge>> adj(V);
	vector<bool> used(E, false);
	for (int i = 0; i < E; i++) {
		int x, y;
		fin >> x >> y;
		
		adj[x].push_back({ y, i});
		adj[y].push_back({ x, i });
	}

	vector<int> idx(V, 0);
	vector<int> ciclu;
	stack<int> st;

	int start = 0;
	while(start < V && adj[start].empty()) {
		start++;
	}

	st.push(start);
	while (!st.empty()) {
		int u = st.top();

		while (idx[u] < (int)adj[u].size() && used[adj[u][idx[u]].id]) {
			idx[u]++;
		}

		if (idx[u] == (int)adj[u].size()) {
			ciclu.push_back(u);
			st.pop();
		}
		else {
			Edge e = adj[u][idx[u]];
			used[e.id] = true;
			st.push(e.to);
		}
	}

	reverse(ciclu.begin(), ciclu.end());

	for (int x : ciclu) {
		fout << x << ' ';
	}

	fout.close();
	return 0;
}