#include <bits/stdc++.h>
using namespace std;
#define INF 1e9

void floydWarshall(vector<vector<int>> &dist, vector<vector<int>> &next, const set<int> &allowed) {
    int V = dist.size() - 1;
    for (int k = 1; k <= V; ++k) {
        if (!allowed.count(k)) continue;
        for (int i = 1; i <= V; ++i) {
            if (!allowed.count(i)) continue;
            for (int j = 1; j <= V; ++j) {
                if (!allowed.count(j)) continue;
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

vector<int> getPath(int u, int v, const vector<vector<int>> &next) {
    if (next[u][v] == -1) return {};
    vector<int> path = {u};
    while (u != v) {
        u = next[u][v];
        path.push_back(u);
    }
    return path;
}

int main() {
    int edgeCount;
    cout << "Enter number of edges: ";
    cin >> edgeCount;

    int maxVertex = 0;
    vector<tuple<int, int, int>> edges;

    cout << "Enter edges in format: u v w\n";
    for (int i = 0; i < edgeCount; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
        maxVertex = max({maxVertex, u, v});
    }

    // Initialize adjacency matrix
    vector<vector<int>> dist(maxVertex + 1, vector<int>(maxVertex + 1, INF));
    vector<vector<int>> next(maxVertex + 1, vector<int>(maxVertex + 1, -1));

    for (int i = 1; i <= maxVertex; ++i) {
        dist[i][i] = 0;
        next[i][i] = i;
    }

    // Read forbidden nodes
    int forbiddenCount;
    cout << "Enter number of forbidden nodes: ";
    cin >> forbiddenCount;
    set<int> forbidden;
    cout << "Enter forbidden nodes: ";
    for (int i = 0; i < forbiddenCount; ++i) {
        int x;
        cin >> x;
        forbidden.insert(x);
    }

    // Read source and destination
    int src, dest;
    cout << "Enter source and destination: ";
    cin >> src >> dest;

    // Build graph without forbidden nodes
    set<int> active;
    for (auto &[u, v, w] : edges) {
        if (forbidden.count(u) || forbidden.count(v)) continue;
        dist[u][v] = w;
        dist[v][u] = w;
        next[u][v] = v;
        next[v][u] = u;
        active.insert(u);
        active.insert(v);
    }

    // Ensure src and dest are in active
    active.insert(src);
    active.insert(dest);

    // Run Floyd-Warshall
    floydWarshall(dist, next, active);

    // Print result
    if (dist[src][dest] == INF) {
        cout << "No path exists from " << src << " to " << dest << endl;
    } else {
        cout << "Shortest distance between vertex " << src << " and " << dest << " = " << dist[src][dest] << endl;
        cout << "Shortest path: ";
        vector<int> path = getPath(src, dest, next);
        for (int i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i != path.size() - 1) cout << " => ";
        }
        cout << endl;
    }

    return 0;
}
