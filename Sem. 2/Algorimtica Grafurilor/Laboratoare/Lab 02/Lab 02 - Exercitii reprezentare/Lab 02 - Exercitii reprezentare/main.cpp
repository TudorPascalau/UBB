#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;
ifstream fin("graf.txt");

/*
* 1. Implementați algoritmul lui Moore pentru un graf orientat neponderat (algoritm bazat pe breadth-first search). 
Datele sunt citite din fisierul graf.txt. Primul rând din graf.txt conține numărul vârfurilor, 
	iar următoarele rânduri conțin muchiile grafului. 
Programul trebuie să afiseze lanțul cel mai scurt dintr-un vârf (vârful sursa poate fi citit de la tastatura).
*/

void Moore(vector<int> lista_adiacenta[], int n, int s, vector<int>& p, vector<int>& l)
{
	queue<int> q;
	int x;

	p.assign(n + 1, -1);
	l.assign(n + 1, -1);

	l[s] = 0;
	q.push(s);

	while(!q.empty())
	{
		x = q.front();
		q.pop();

		for (int y: lista_adiacenta[x])
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

void afisare_drum(int s, int t, vector<int> &p)
{
	if (t == -1)
		return;

	if (t == s)
	{
		cout << s << " ";
		return;
	}


	afisare_drum(s, p[t], p);
	cout << t << " ";
		

}

int main()
{
	int n, x, y, s, t;
	vector<int> lista_adiacenta[101];
	vector<int> p, l;

	fin >> n;
	while (fin >> x >> y)
		lista_adiacenta[x].push_back(y);

	cout << "Introduceti varful sursa: ";
	cin >> s;

	Moore(lista_adiacenta, n, s, p, l);

	cout << "Introduceti varful destinatie: ";
	cin >> t;

	if (l[t] == -1)
		cout << "Nu exista drum";

	else
	{
		cout << l[t] << '\n';
		afisare_drum(s, t, p);
	}

	return 0;
}