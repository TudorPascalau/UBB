#include <fstream>
#include <vector>
using std::vector;

#include <queue>
using std::queue;

#include <climits>

const int INF = 1e9;

struct Edge {
	int from;
	int to;
	int capacity;
	int flow;

	Edge(int from, int to, int capacity)
		: from(from), to(to), capacity(capacity), flow(0) {};
};

int residualCapacity(const Edge& edge) {
	return edge.capacity - edge.flow;
}

int main(int argc, char* argv[]) {

	std::ifstream fin(argv[1]);
	std::ofstream fout(argv[2]);

	int V, E;
	fin >> V >> E;

	vector<Edge> edges;
	vector<vector<int>> adj(V);

	for (int i = 0; i < E; i++) {
		int x, y, c;
		fin >> x >> y >> c;

		edges.emplace_back(x, y, c);
		adj[x].push_back(edges.size() - 1);

		edges.emplace_back(y, x, 0); 
		adj[y].push_back(edges.size() - 1);
	}

	int s = 0;
	int t = V - 1;

	int maxFlow = 0;

	while (true) {
		vector<int> parentEdge(V, -1);
        queue<int> q;

        q.push(s);
        parentEdge[s] = -2;

        while (!q.empty() && parentEdge[t] == -1) {
            int node = q.front();
            q.pop();

            for (int edgeIndex : adj[node]) {
                Edge& edge = edges[edgeIndex];

                if (parentEdge[edge.to] == -1 &&
                    residualCapacity(edge) > 0) {

                    parentEdge[edge.to] = edgeIndex;
                    q.push(edge.to);
                }
            }
        }

        if (parentEdge[t] == -1) {
            break;
        }

        int pathFlow = INT_MAX;

        for (int node = t; node != s; ) {
            int edgeIndex = parentEdge[node];
            Edge& edge = edges[edgeIndex];

            pathFlow = std::min(pathFlow, residualCapacity(edge));
            node = edge.from;
        }

        for (int node = t; node != s; ) {
            int edgeIndex = parentEdge[node];

            edges[edgeIndex].flow += pathFlow;
            edges[edgeIndex ^ 1].flow -= pathFlow;

            node = edges[edgeIndex].from;
        }

        maxFlow += pathFlow;
    } 

    fout << maxFlow;

    return 0;
}