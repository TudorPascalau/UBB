#include <iostream>
#include <fstream>
#include <vector>
using std::vector;
#include <queue>;
using std::priority_queue;
#include <utility>
using std::pair;

const int INF = 1e9;

struct Edge {
	int to;
	int weight;
};

int main(int argc, char* argv[]) {
	
	std::ifstream fin(argv[1]);
	std::ofstream fout(argv[2]);
	
	int V, E;
	fin >> V >> E;

	vector<vector<Edge>> adj(V);
	for(int i=0; i<E; i++) {
		int u, v, w;
		fin >> u >> v >> w;
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}

	vector<int> key(V, INF);
	vector<int> parent(V, -1);
	vector<bool> inMST(V, false);

	priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<>> pq;
	int root = 0;
	key[root] = 0;
	pq.push({ 0, root });

	long long totalCost = 0;
	vector<pair<int, int>> mstEdges;

	while (!pq.empty()) {
		auto [cost, node] = pq.top();
		pq.pop();

		if(inMST[node]) continue;

		inMST[node] = true;
		totalCost += cost;

		if (parent[node] != -1) {
			mstEdges.push_back({ parent[node], node });
		}

		for (const auto& edge : adj[node]) {
			int neighbor = edge.to;
			int weight = edge.weight;

			if (!inMST[neighbor] && weight < key[neighbor]) {
				key[neighbor] = weight;
				parent[neighbor] = node;
				pq.push({ key[neighbor], neighbor });
			}
		}
	}

	fout << totalCost << "\n";
	fout << mstEdges.size() << "\n";
	for (const auto& [u, v] : mstEdges) {
		fout << u << " " << v << "\n";
	}

	return 0;
}