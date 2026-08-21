/*
Sa se determine inchiderea tranzitiva a unui graf orientat. 
Inchiderea tranzitiva poate fi reprezentata ca matricea care descrie, 
pentru fiecare varf in parte, care sunt varfurile accesibile din acest varf.
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
ifstream fin("graf.txt");

void Floyd_Warshall(int n, int m[21][21], bool t[21][21]) {

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			if (m[i][j] == 1)
				t[i][j] = 1;
			else t[i][j] = 0;

		t[i][i] = 1;
	}

	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				t[i][j] = t[i][j] || (t[i][k] && t[k][j]);
}

int main() {
	int m[21][21];
	bool t[21][21];

	int n, x, y;
	fin >> n;

	while (fin >> x >> y)
		m[x][y] = 1;

	Floyd_Warshall(n, m, t);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			cout << t[i][j] << " ";
		cout << "\n";
	}
}