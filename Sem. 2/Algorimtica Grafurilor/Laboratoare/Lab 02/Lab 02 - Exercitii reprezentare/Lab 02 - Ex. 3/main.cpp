/*
* Problema 3. Sa se scrie un program care gaseste o solutie pentru unul din urmatoarele
labirinturi: labirint_1.txt, labirint_2.txt, labirint_cuvinte.txt. 
Pentru labirintul 1 si 2 punctul de pornire este indicat de litera S si punctul de oprire este indicat de litera F. 
Pentru labirintul cu cuvinte nu exista o solutie unica
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;
ifstream fin("labirint_2.txt");

struct Punct {
	int x;
	int y;
};

int main() {
	vector<string> labirint;
	string linie;
	int i, j;

	/// Citire labirint
	while (getline(fin, linie))
		labirint.push_back(linie);

	fin.close();

	// Dimensiuni labirint
	int n = labirint.size();
	int m = labirint[0].size();

	// Stabilire puncte start si finish
	Punct start{ -1, -1 }, finish{ -1,-1 };
	for(i = 0; i<n; i++)
		for (j = 0; j < m; j++) {
			if (labirint[i][j] == 'S')
				start = { i, j };
			if (labirint[i][j] == 'F')
				finish = { i,j };
		}

	cout << "Start: (" << start.x << ", " << start.y << ")\n";
	cout << "Finish: (" << finish.x << ", " << finish.y << ")\n";

	// Pregatire distante
	int dx[] = { -1, 1, 0, 0 };
	int dy[] = { 0, 0, -1, 1 };

	vector<vector<int>> dist(n, vector<int>(m, -1));
	vector<vector<Punct>> parinte(n, vector<Punct>(m, { -1, -1 }));

	// Parcuregere Lee
	queue<Punct> q;
	q.push(start);
	dist[start.x][start.y] = 0;

	while (!q.empty()) {
		Punct curent = q.front();
		q.pop();

		for (int k = 0; k < 4; k++) {
			int nx = curent.x + dx[k];
			int ny = curent.y + dy[k];

			if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
				labirint[nx][ny] != '1' &&
				dist[nx][ny] == -1) {

				dist[nx][ny] = dist[curent.x][curent.y] + 1;
				parinte[nx][ny] = curent;
				q.push({ nx, ny });
			}
		}
	}

	// Verificare daca exista drum
	if (dist[finish.x][finish.y] == -1) {
		cout << "Nu exista drum de la S la F.\n";
	}
	else {
		cout << "Exista drum. Lungime minima = "
			<< dist[finish.x][finish.y] << "\n";
	}

	// Reconstruire drum
	vector<Punct> drum;
	Punct curent = finish;

	while (!(curent.x == -1 && curent.y == -1)) {
		drum.push_back(curent);
		if (curent.x == start.x && curent.y == start.y) {
			break;
		}
		curent = parinte[curent.x][curent.y];
	}

	reverse(drum.begin(), drum.end());

	// Marcam drumul in labirint
	for (const auto& p : drum) {
		if (labirint[p.x][p.y] == ' ') {
			labirint[p.x][p.y] = '*';
		}
	}

	// Afisam drumul in labirint
	for (const auto& row : labirint) {
		cout << row << '\n';
	}
}