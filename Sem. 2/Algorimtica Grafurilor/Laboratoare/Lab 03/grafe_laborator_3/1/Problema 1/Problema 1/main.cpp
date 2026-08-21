#include <iostream>
#include <fstream>
#include <vector>
using std::vector;

struct vertex {
	int x;
	int y;
	int w;
};

int INF = 1e9;

int main(int argc, char* argv[]) {

	std::ifstream fin(argv[1]);
	std::ofstream fout(argv[2]);

	int v, e, s;
	int x, y, w, i, j;
	fin >> v >> e >> s;

	vector<vertex> graph(e);
	for (i = 0; i < e; i++) {
		fin >> x >> y >> w;
		graph[i] = { x, y, w };
	}

	vector<int> dist(v, INF);
	vector<int> parent(v, -1);
	dist[s] = 0;


	for(i=1; i<v; i++)
	{
		bool changed = false;
		for (j = 0; j < e; j++) {
			x = graph[j].x;
			y = graph[j].y;
			w = graph[j].w;

			if (dist[x] != INF && dist[y] > dist[x] + w) {
				dist[y] = dist[x] + w;
				parent[y] = x;
				changed = true;
			}
		}
		if (!changed) break;
	}

	for (j = 0; j < e; j++) {
		x = graph[j].x;
		y = graph[j].y;
		w = graph[j].w;

		if (dist[x]!= INF && dist[y] > dist[x] + w) {
			fout << "Negative cycle detected!";
			return 0;
		}
	}

	for (i = 0; i < v; i++)
		if (dist[i] == INF)
			fout << "INF ";
		else fout << dist[i] << " ";
			

	fin.close();
	fout.close();

	return 0;
}