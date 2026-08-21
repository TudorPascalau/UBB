#include <fstream>
#include <vector>
using std::vector;
#include <set>
using std::set;

int main(int argc, char* argv[]) {

	std::ifstream fin(argv[1]);
	std::ofstream fout(argv[2]);

	int m;
	fin >> m;

	int n = m + 1;

	vector<int> prufer_code(m);
	vector<int> freq(n, 0);

	for (int i = 0; i < m; i++) {
		fin >> prufer_code[i];
		freq[prufer_code[i]]++;
	}

	set<int> leaves;
	for (int i = 0; i < n; i++) {
		if (freq[i] == 0) {
			leaves.insert(i);
		}
	}

	vector<int> parent(n, -2);
	for (int i = 0; i < m; i++) {
		int x = prufer_code[i];

		int leaf = *leaves.begin();
		leaves.erase(leaves.begin());

		parent[leaf] = x;

		freq[x]--;

		if (freq[x] == 0) {
			leaves.insert(x);
		}
	}

	int root = *leaves.begin();
	parent[root] = -1;

	fout << n << "\n";
	for (int x : parent) {
		fout << x << " ";
	}

	return 0;
}