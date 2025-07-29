// ✅ Floyd-Warshall with all-pairs shortest path, negative cycle detection, and total shortest path count
#include <bits/stdc++.h>
using namespace std;
#define inf 1e9

int n, e;
vector<vector<int>> D, countPath;
vector<vector<int>> pred;

void Floyd_Warshall() {
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (D[i][k] < inf && D[k][j] < inf) {
                    if (D[i][j] > D[i][k] + D[k][j]) {
                        D[i][j] = D[i][k] + D[k][j];
                        pred[i][j] = pred[k][j];
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

void printPath(int i, int j) {
    if (i == j) cout << i;
    else if (pred[i][j] == -1) cout << "No path";
    else {
        printPath(i, pred[i][j]);
        cout << " -> " << j;
    }
}

int main() {
    cin >> n >> e;
    D.assign(n + 1, vector<int>(n + 1, inf));
    pred.assign(n + 1, vector<int>(n + 1, -1));
    countPath.assign(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; ++i) {
        D[i][i] = 0;
        countPath[i][i] = 1;
        pred[i][i] = i;
    }

    for (int i = 0; i < e; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        D[u][v] = w;
        pred[u][v] = u;
        countPath[u][v] = 1;
    }

    Floyd_Warshall();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j || D[i][j] == inf) continue;
            printPath(i, j);
            cout << " / total shortest paths = " << countPath[i][j] << endl;
        }
    }

    return 0;
}
