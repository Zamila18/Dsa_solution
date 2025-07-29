#include <bits/stdc++.h>
using namespace std;
#define INF 1e9

int main() {
    int V;
    cout << "Enter number of vertices: ";
    cin >> V;

    vector<vector<int>> dist(V + 1, vector<int>(V + 1));

    cout << "Enter adjacency matrix (0 for no edge, INF = 999999999):\n";
    for (int i = 1; i <= V; ++i) {
        for (int j = 1; j <= V; ++j) {
            cin >> dist[i][j];
            if (i == j) dist[i][j] = 0;
        }
    }

    // Skip relaxation step, just propagate distances for checking negative cycle
    for (int k = 1; k <= V; ++k) {
        for (int i = 1; i <= V; ++i) {
            for (int j = 1; j <= V; ++j) {
                // perform full updates, not conditionally
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    // Check for negative cycles
    bool hasNegativeCycle = false;
    for (int i = 1; i <= V; ++i) {
        if (dist[i][i] < 0) {
            hasNegativeCycle = true;
            cout << "⚠️ Negative cycle detected at node " << i << endl;
        }
    }

    if (!hasNegativeCycle)
        cout << "✅ No negative cycles found in the graph." << endl;

    return 0;
}
