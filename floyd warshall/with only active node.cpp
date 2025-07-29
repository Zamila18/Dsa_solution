#include <bits/stdc++.h>
using namespace std;
#define INF 1e9

int V;
vector<vector<vector<int>>> dist; // dist[i][j][k]: shortest distance from i to j using node ≤ k
vector<vector<vector<int>>> nxt;  // nxt[i][j][k]: next node from i to j using node ≤ k

void runFloydWarshallWith3D(const vector<vector<int>>& graph) {
    dist = vector<vector<vector<int>>>(V + 1, vector<vector<int>>(V + 1, vector<int>(V + 1, INF)));
    nxt = vector<vector<vector<int>>>(V + 1, vector<vector<int>>(V + 1, vector<int>(V + 1, -1)));

    // Base case (k = 0): Only direct edges
    for (int i = 1; i <= V; ++i) {
        for (int j = 1; j <= V; ++j) {
            if (i == j) {
                dist[i][j][0] = 0;
                nxt[i][j][0] = i;
            } else if (graph[i][j] != INF) {
                dist[i][j][0] = graph[i][j];
                nxt[i][j][0] = j;
            }
        }
    }

    // Build dist[i][j][k] from k = 1 to V
    for (int k = 1; k <= V; ++k) {
        for (int i = 1; i <= V; ++i) {
            for (int j = 1; j <= V; ++j) {
                int withoutK = dist[i][j][k - 1];
                int viaK = (dist[i][k][k - 1] != INF && dist[k][j][k - 1] != INF) ?
                           dist[i][k][k - 1] + dist[k][j][k - 1] : INF;

                if (viaK < withoutK) {
                    dist[i][j][k] = viaK;
                    nxt[i][j][k] = nxt[i][k][k - 1];
                } else {
                    dist[i][j][k] = withoutK;
                    nxt[i][j][k] = nxt[i][j][k - 1];
                }
            }
        }
    }
}

vector<int> getPath(int u, int v, int k) {
    if (nxt[u][v][k] == -1) return {};
    vector<int> path = {u};
    while (u != v) {
        u = nxt[u][v][k];
        if (u == -1) return {};
        path.push_back(u);
    }
    return path;
}

int main() {
    int E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    // Input graph as adjacency matrix
    vector<vector<int>> graph(V + 1, vector<int>(V + 1, INF));
    cout << "Enter edges (u v w):\n";
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u][v] = w;
        graph[v][u] = w; // Undirected
    }

    // 🔁 Run Floyd-Warshall with 3D matrix BEFORE any inputs
    runFloydWarshallWith3D(graph);

    // ✅ Now take input (after precomputation)
    int src, dest, activeCount;
    cout << "Enter source and destination: ";
    cin >> src >> dest;
    cout << "Enter number of active nodes (e.g., 3 means use node 1 to 3): ";
    cin >> activeCount;

    int cost = dist[src][dest][activeCount];
    if (cost == INF) {
        cout << "No path from " << src << " to " << dest << " using active nodes 1 to " << activeCount << endl;
    } else {
        cout << "Minimum cost: " << cost << endl;
        cout << "Path: ";
        vector<int> path = getPath(src, dest, activeCount);
        for (int i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i + 1 < path.size()) cout << " => ";
        }
        cout << endl;
    }

    return 0;
}
