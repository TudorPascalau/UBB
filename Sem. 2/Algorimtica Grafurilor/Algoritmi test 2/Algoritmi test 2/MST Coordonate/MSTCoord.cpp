#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cfloat>
using namespace std;

struct Point {
    double x, y;
};

double distanceBetween(Point a, Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;

    return sqrt(dx * dx + dy * dy);
}

int main() {
    ifstream fin("input.in");
    ofstream fout("output.out");

    int N;
    fin >> N;

    // Orașe indexate de la 0 la N - 1.
    vector<Point> p(N);

    for (int i = 0; i < N; i++) {
        fin >> p[i].x >> p[i].y;
    }

    vector<double> key(N, DBL_MAX);
    vector<int> parent(N, -1);
    vector<bool> inMST(N, false);

    key[0] = 0;

    double totalCost = 0;

    for (int step = 0; step < N; step++) {
        int u = -1;

        for (int i = 0; i < N; i++) {
            if (!inMST[i] && (u == -1 || key[i] < key[u])) {
                u = i;
            }
        }

        inMST[u] = true;
        totalCost += key[u];

        for (int v = 0; v < N; v++) {
            if (!inMST[v]) {
                double cost = distanceBetween(p[u], p[v]);

                if (cost < key[v]) {
                    key[v] = cost;
                    parent[v] = u;
                }
            }
        }
    }

    fout << fixed << setprecision(3) << totalCost;

    return 0;
}