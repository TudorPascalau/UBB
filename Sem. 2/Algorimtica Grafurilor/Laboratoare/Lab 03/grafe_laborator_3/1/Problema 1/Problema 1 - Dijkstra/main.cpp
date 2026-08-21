#include <iostream>
#include <fstream>

#include <vector>
using std::vector;

#include <queue>
#include <unordered_set>

class Node {
	public:
	int id;
	int dist;
	int parent;
	Node() : id{ -1 }, dist{ 0 }, parent{ -1 } {}
	Node(int id, int dist, int parent) : id{id}, dist{dist}, parent{parent} {}

	// Priority queue will use this operator to compare nodes based on their distance
	bool operator<(const Node& other) const {
		return dist > other.dist; // We want the node with the smallest distance to have higher priority
	}
};

int INF = static_cast<int>(1e9);

int main() {

	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");

	// Read the number of vertices, edges, and the starting vertex from the input file
	int v, e, s;
	fin >> v >> e >> s;

	// Initialize the nodes
	vector<Node> nodes(v);
	for (int i = 0; i < v; i++)
		nodes[i] = { i, INF, -1 };
	nodes[s].dist = 0;

	// Create an adjacency list to store the graph
	int x, y, w;
	vector<vector<std::pair<int, int>>> graph(v);
	for(int i = 0; i < e; i++) {
		fin >> x >> y >> w;
		graph[x].push_back({y, w});
	}

	// Dijkstra's algorithm
	std::priority_queue<Node> pq;

	for(int i=0; i<v; i++)
		pq.push(nodes[i]);

	while(!pq.empty()) {
		Node current = pq.top();
		pq.pop();

		for(auto& neighbor : graph[current.id]) {
			int next_id = neighbor.first;
			int weight = neighbor.second;

			if(current.dist != INF && current.dist + weight < nodes[next_id].dist) {
				nodes[next_id].dist = current.dist + weight;
				nodes[next_id].parent = current.id;
				pq.push(nodes[next_id]);
			}
		}
	}

	for (int i = 0; i < v; i++)
		if (nodes[i].dist == INF)
			fout << "INF ";
		else fout << nodes[i].dist << " ";

	fin.close();
	fout.close();
	return 0;
}