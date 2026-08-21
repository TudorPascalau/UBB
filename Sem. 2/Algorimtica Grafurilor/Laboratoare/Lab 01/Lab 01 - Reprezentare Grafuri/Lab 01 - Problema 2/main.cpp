#include <fstream>
#include <iostream>

using namespace std;
ifstream fin("in.txt");

void citire(int& n, int& m, int matrice_adiacenta[21][21])
{
	int x, y;
	fin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		fin >> x >> y;
		matrice_adiacenta[x][y] = 1;
		matrice_adiacenta[y][x] = 1;
	}
}

void calcul_grade(int n, int m, int matrice_adiacenta[21][21])
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (matrice_adiacenta[i][j] == 1) matrice_adiacenta[i][0]++;
}

void noduri_izolate(int n, int matrice_adiacenta[21][21])
{
	cout << "Noduri izolate: ";
	for (int i = 1; i <= n; i++)
		if (matrice_adiacenta[i][0] == 0) cout << i << " ";
	cout << "\n\n";
}	

void graf_regulat(int n, int m, int matrice_adiacenta[21][21])
{
	cout << "Este graful regulat?";
	for (int i = 2; i <= n; i++)
		if (matrice_adiacenta[i][0] != matrice_adiacenta[1][0])
		{
			cout << " Nu\n\n";
			return;
		}
	cout << " Da\n\n";
}

void dfs(int nod, int n, int matrice_adiacenta[21][21], int visited[21])
{
	visited[nod] = 1;
	for (int i = 1; i <= n; i++)
		if(matrice_adiacenta[nod][i] == 1 && visited[i] == 0) 
			dfs(i, n, matrice_adiacenta, visited);

}

void graf_conex(int n, int matrice_adiacenta[21][21])
{
	cout << "Verificam daca graful este conex ... ";
	int visited[21] = {0};

	dfs(1, n, matrice_adiacenta, visited);

	for(int i = 1; i<=n; i++)
		if (visited[i] == 0)
		{
			cout << " Nu\n\n";
			return;
		}
	cout << " Da\n\n";
}

void matricea_distantelor(int n, int matrice_adiacenta[21][21])
{
	int matrice_distante[21][21];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (matrice_adiacenta[i][j] == 1) matrice_distante[i][j] = 1;
			else if (i == j) matrice_distante[i][j] = 0;
			else matrice_distante[i][j] = 9999;

	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (matrice_distante[i][j] > matrice_distante[i][k] + matrice_distante[k][j])
					matrice_distante[i][j] = matrice_distante[i][k] + matrice_distante[k][j];

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			cout << matrice_distante[i][j] << " ";
		cout << "\n";
	}

}

int main()
{
	int n, m;
	int matrice_adiacenta[21][21] = {0};

	// Citire
	citire(n, m, matrice_adiacenta);

	// Calcul grade
	calcul_grade(n, m, matrice_adiacenta);

	/// Noduri izolate
	noduri_izolate(n, matrice_adiacenta);
	
	/// Graf regulat
	graf_regulat(n, m, matrice_adiacenta);

	/// Graf conex
	graf_conex(n, matrice_adiacenta);

	/// Matricea distantelor
	matricea_distantelor(n, matrice_adiacenta);

	return 0;
}