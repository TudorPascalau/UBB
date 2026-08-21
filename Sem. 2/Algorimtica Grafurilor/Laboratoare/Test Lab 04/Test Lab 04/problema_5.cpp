#include <iostream>
#include <fstream>
#include <vector>
using std::vector;

using std::ifstream;
using std::cout;

using std::pair;

int main() {

	ifstream fin("in.txt");

	int mat_ad[11][11];
	vector<pair<int, int>> lista_muchii;

	int n,i,j;
	fin >> n;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			fin >> mat_ad[i][j];

	for (i = 0; i < n; i++)
		for (j = 0; j < i; j++)
			if (mat_ad[i][j] == 1)
				lista_muchii.push_back({ j, i });

	for (auto& muchie : lista_muchii)
		cout << "(" << muchie.first << "," << muchie.second << ") ";
}