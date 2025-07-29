#include <bits/stdc++.h>
using namespace std;
#define INF 1e9

void floydWarshall(vector<vector<int>> &dist, vector<vector<int>> &next, const set<int> &allowed) {
    int V = dist.size() - 1;
    for (int k = 1; k <= V; ++k) {
        if (!allowed.empty() && allowed.count(k) == 0) continue;
        for (int i = 1; i <= V; ++i) {
            if (!allowed.empty() && allowed.count(i) == 0) continue;
            for (int j = 1; j <= V; ++j) {
                if (!allowed.empty() && allowed.count(j) == 0) continue;
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

void printPath(int src, int dest, const vector<vector<int>> &dist, const vector<vector<int>> &next) {
    if (dist[src][dest] == INF) {
        cout << "No path exists from " << src << " to " << dest << endl;
    } else {
        cout << "Shortest distance from " << src << " to " << dest << ": " << dist[src][dest] << endl;
        cout << "Path: ";
        vector<int> path = getPath(src, dest, next);
        for (int i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i != path.size() - 1) cout << " => ";
        }
        cout << endl;
    }
}

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<vector<int>> dist(V + 1, vector<int>(V + 1, INF));
    vector<vector<int>> next(V + 1, vector<int>(V + 1, -1));

    for (int i = 1; i <= V; ++i) {
        dist[i][i] = 0;
        next[i][i] = i;
    }

    cout << "Enter " << E << " edges in format: u v w" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        dist[u][v] = w;
        dist[v][u] = w; // Undirected graph
        next[u][v] = v;
        next[v][u] = u;
    }

    int src, dest;
    cout << "Enter source node: ";
    cin >> src;
    cout << "Enter destination node: ";
    cin >> dest;

    // 1️⃣ Using all nodes
    vector<vector<int>> distAll = dist, nextAll = next;
    floydWarshall(distAll, nextAll, {});
    cout << "\n➡️ Shortest path using ALL nodes:\n";
    printPath(src, dest, distAll, nextAll);

    // 2️⃣ Using only active nodes
    int K;
    cout << "\nEnter number of active nodes: ";
    cin >> K;
    set<int> active;
    cout << "Enter active nodes: ";
    for (int i = 0; i < K; ++i) {
        int x;
        cin >> x;
        active.insert(x);
    }
    active.insert(src);
    active.insert(dest);

    vector<vector<int>> distActive = dist, nextActive = next;
    floydWarshall(distActive, nextActive, active);
    cout << "\n➡️ Shortest path using ONLY ACTIVE nodes:\n";
    printPath(src, dest, distActive, nextActive);

    return 0;
}
