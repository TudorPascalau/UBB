#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;
ifstream fin("graf.txt");

/*
* Problema 4. Pentru un graf dat sa se afiseze pe ecran varfurile descoperite de algoritmul
BFS si distanta fata de varful sursa
*/

void Moore(vector<int> lista_adiacenta[], int n, int s, vector<int>& p, vector<int>& l)
{
	queue<int> q;
	int x;

	p.assign(n + 1, -1);
	l.assign(n + 1, -1);

	l[s] = 0;
	q.push(s);

	while (!q.empty())
	{
		x = q.front();
		q.pop();

		for (int y : lista_adiacenta[x])
		{
			if (l[y] == -1)
			{
				l[y] = l[x] + 1;
				p[y] = x;
				q.push(y);
			}

		}
	}

}


int main()
{
	int n, x, y, s;
	vector<int> lista_adiacenta[101];
	vector<int> p, l;

	fin >> n;
	while (fin >> x >> y)
	{
		lista_adiacenta[x].push_back(y);
		lista_adiacenta[y].push_back(x);
	}
		

	cout << "Introduceti varful sursa: ";
	cin >> s;

	Moore(lista_adiacenta, n, s, p, l);

	cout << "\nVarfurile descoperite de BFS sunt:\n";
	for (int i = 1; i <= n; i++)
	{
		if (l[i] != -1)
		{
			cout << "Varf: " << i
				<< ", distanta: " << l[i]
				<< ", parinte: " << p[i] << '\n';
		}
	}

	return 0;
}