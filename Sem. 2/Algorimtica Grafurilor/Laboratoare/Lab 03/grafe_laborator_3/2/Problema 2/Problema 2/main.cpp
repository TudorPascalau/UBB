#include <fstream>
#include <vector>
using std::vector;

#include <queue>
using std::priority_queue;

using std::pair;

class Edge {

public:
	int from;
	int to;
	int weight;
	Edge() : from(0), to(0), weight(0) {}
	Edge(int from, int to, int weight) : from(from), to(to), weight(weight) {}

};

int INF = 1e9;

int main(int argc, char* argv[]) 
{
	std::ifstream fin(argv[1]);
	std::ofstream fout(argv[2]);

	// Citire numar de noduri si numar de muchii
	int v, e;
	fin >> v >> e;

	// Initilizare distante noduri si super sursa
	vector<vector<int>> dist(v, vector<int>(v, INF));
	int superSource = v;

	// Citire arce si construire lista de adiacenta si vector de arce
	int from, to, weight;
	vector<Edge> edges(e);
	for(int i = 0; i < e; i++) {
		fin >> from >> to >> weight;
		edges[i] = Edge(from, to, weight);
	}

	for(int i = 0; i < v; i++) {
		edges.push_back(Edge(superSource, i, 0));
	}

	// Bellman-Ford de la super sursa
	int nrNodes = v + 1;
	vector<int> h(nrNodes, INF);
	h[superSource] = 0;

	for(int i=1; i<nrNodes; i++) {
		for (const auto& edge : edges) {
			// Relaxare - echivalent cu dist[edge.to] > dist[edge.from] + edge.weight
			if (h[edge.from] != INF && h[edge.to] > h[edge.from] + edge.weight) {
				h[edge.to] = h[edge.from] + edge.weight;
			}
		}
	}

	// Verificare ciclu negativ
	for (auto& edge : edges) {
		if (h[edge.from] != INF && h[edge.to] > h[edge.from] + edge.weight) {
			fout << "-1\n";
			fin.close();
			fout.close();
			return 0;
		}
	}

	// Reponderare arce
	edges.resize(e); // Eliminare arce super sursa

	for (auto& edge : edges) {
		edge.weight = edge.weight + h[edge.from] - h[edge.to];
	}

	// Creare lista de adiacenta reponderata pentru Dijkstra
	vector<vector<pair<int, int>>> adjList(v);
	for (const auto& edge : edges) {
		adjList[edge.from].push_back({edge.to, edge.weight});
	}

	// Dijkstra pentru fiecare nod
	for (int nod = 0; nod < v; nod++) {

		dist[nod][nod] = 0;

		priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> pq;
		pq.push({ 0, nod });

		while (!pq.empty()) {
			auto [currentDist, currentNode] = pq.top();
			pq.pop();

			// Daca distanta curenta este diferita de distanta stocata, inseamna ca am gasit o cale mai scurta intre timp, deci ignoram acest nod
			if (currentDist != dist[nod][currentNode])
				continue;

			for (auto& neighbor : adjList[currentNode]) {
				int nextNode = neighbor.first;
				int weight = neighbor.second;
				if (currentDist + weight < dist[nod][nextNode]) {
					dist[nod][nextNode] = currentDist + weight;
					pq.push({ dist[nod][nextNode], nextNode });
				}
			}
		}

		// Reponderare inversa pentru a obtine distantele reale
		for (int i = 0; i < v; i++) {
			if (dist[nod][i] != INF) {
				dist[nod][i] = dist[nod][i] - h[nod] + h[i];
			}
		}

	}

	// Afisare rezultate
	for (auto& edge : edges) {
		fout << edge.from << " " << edge.to << " " << edge.weight << "\n";
	}

	for(auto& nod: dist) {
		for(auto& d: nod) {
			if(d == INF) {
				fout << "INF ";
			} else {
				fout << d << " ";
			}
		}
		fout << "\n";
	}

	fin.close();
	fout.close();
	return 0;
}