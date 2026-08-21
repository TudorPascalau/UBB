#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
	ifstream fin("in.txt");

	// Matrice de adiacenta
	int n, m, i, j, x, y;
	int matrice_adiacenta[101][101] = {0};

	fin >> n >> m;
	for (i = 1; i <= m; i++)
	{
		fin>> x >> y;
		matrice_adiacenta[x][y] = 1;
		matrice_adiacenta[y][x] = 1;
	}

	cout << "Matricea de adicenta: \n";
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
			cout << matrice_adiacenta[i][j] << " ";
		cout << "\n";
	}

	fin.close();

	// Lista de adiacenta
	fin.open("in.txt");
	vector<int> lista_adiacenta[101];

	fin >> n >> m;
	for (i = 1; i <= m; i++)
	{
		fin >> x >> y;
		lista_adiacenta[x].push_back(y);
		lista_adiacenta[y].push_back(x);
	}
	cout <<"Lista de adiacenta : \n";
	for (i = 1; i <= n; i++)
	{
		cout << i << ": ";
		for(j = 0; j < lista_adiacenta[i].size(); j++)
			cout << lista_adiacenta[i][j] << " ";
		cout << "\n";
	}

	fin.close();

	// Matricea de incidenta
	fin.open("in.txt");
	int matrice_incidenta[101][101] = { 0 };

	fin >> n >> m;
	for (i = 1; i <= m; i++)
	{
		fin >> x >> y;
		matrice_incidenta[x][i] = 1;
		matrice_incidenta[y][i] = 1;
	}

	cout << "Matricea de incidenta: \n";
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
			cout << matrice_incidenta[i][j] << " ";
		cout << "\n";
	}
	fin.close();

	return 0;
}