// ✅ Floyd-Warshall with all-pairs shortest path, negative cycle detection, and total shortest path count
#include <bits/stdc++.h>
using namespace std;
#define inf 1e9

int n, e;
vector<vector<int>> D, countPath;

void Floyd_Warshall() {
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (D[i][k] < inf && D[k][j] < inf) {
                    if (D[i][j] > D[i][k] + D[k][j]) {
                        D[i][j] = D[i][k] + D[k][j];
                        countPath[i][j] = countPath[i][k] * countPath[k][j];
                    } else if (D[i][j] == D[i][k] + D[k][j]) {
                        countPath[i][j] += countPath[i][k] * countPath[k][j];
                    }
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (D[i][i] < 0) {
            cout << "Negative weight cycle detected at node " << i << endl;
            return;
        }
    }
}

int main() {
    cout << "Enter number of vertices and edges: ";
    cin >> n >> e;
    D.assign(n + 1, vector<int>(n + 1, inf));
    countPath.assign(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; ++i) {
        D[i][i] = 0;
        countPath[i][i] = 1;
    }

    cout << "Enter each edge in the format: from to weight\n";
    for (int i = 0; i < e; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        D[u][v] = w;
        countPath[u][v] = 1;
    }

    Floyd_Warshall();

    cout << "\nTotal Shortest Path Counts for All Pairs:\n";
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j || D[i][j] == inf) continue;
            cout << i << " => " << j << " / total shortest paths = " << countPath[i][j] << endl;
        }
    }

    return 0;
}
