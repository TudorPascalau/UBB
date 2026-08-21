#include <fstream>
#include <vector>
using std::vector;
#include <algorithm>
#include <set>
using std::set;

int main(int argc, char* argv[]) {

	std::ifstream fin(argv[1]);
	std::ofstream fout(argv[2]);

	int n;
	fin >> n;

	vector<int> parent(n);
	vector<int> degree(n, 0);
	int root = -1;

	for(int i=0; i<n; ++i) {
		fin >> parent[i];
		
		if (parent[i] == -1)
			root = i;
		else {
			degree[i]++;
			degree[parent[i]]++;
		}
	}

	set<int> leaves;
	for (int i = 0; i < n; i++) {
		if(degree[i] == 1 && i != root) {
			leaves.insert(i);
		}
	}

	vector<int> prufer_code;

	while ((int)prufer_code.size() < n - 1) {
		int leaf = *leaves.begin();
		leaves.erase(leaves.begin());

		int p = parent[leaf];
		prufer_code.push_back(p);

		degree[leaf]--;
		degree[p]--;

		if (degree[p] == 1 && p != root) {
			leaves.insert(p);
		}
	}

	fout << prufer_code.size() << "\n";
	for (int x : prufer_code) {
		fout << x << " ";
	}

	fout.close();
	return 0;
}