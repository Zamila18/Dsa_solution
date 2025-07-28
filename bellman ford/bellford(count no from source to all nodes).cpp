#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> nodeVec[10001];
vector<pair<int, pair<int, int>>> allEdges;
int dist[10001];
int path[10001];
int countPaths[10001];  // Tracks number of shortest paths
int nodeCount, edgeCount;
#define inf 1e9

void Initialize_Single_Source(int source, int nodeCount) {
    for (int i = 1; i <= nodeCount; i++) {
        dist[i] = inf;
        path[i] = -1;
        countPaths[i] = 0;  // Reset count
    }
    dist[source] = 0;
    countPaths[source] = 1;  // There's one way to start at the source node
}

void Relax(int u, int v, int w) {
    if (dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
        path[v] = u;
        countPaths[v] = countPaths[u];  // Reset the number of paths
    }
    else if (dist[v] == dist[u] + w) {
        countPaths[v] += countPaths[u];  // Add the number of paths
    }
}

bool Bellman_Ford(int source, int nodeCount) {
    Initialize_Single_Source(source, nodeCount);

    for (int i = 1; i < nodeCount; i++) {
        for (auto e: allEdges) {
            int u = e.first;
            int v = e.second.first;
            int w = e.second.second;
            Relax(u, v, w);
        }
    }

    for (auto e: allEdges) {
        int u = e.first;
        int v = e.second.first;
        int w = e.second.second;
        if (dist[v] > dist[u] + w) {
            return false;  // Negative cycle detected
        }
    }

    return true;
}

int main() {
    cout << "Enter the number of nodes: ";
    cin >> nodeCount;
    cout << "Enter the number of edges: ";
    cin >> edgeCount;

    for (int i = 0; i < edgeCount; i++) {
        int nodeA, nodeB, weight;
        cin >> nodeA >> nodeB >> weight;
        allEdges.push_back({nodeA, {nodeB, weight}});
    }

    int source;
    cout << "Enter the source node: ";
    cin >> source;

    bool isValid = Bellman_Ford(source, nodeCount);
    if (!isValid) {
        cout << "Negative Weight Cycle Detected." << endl;
        return 0;
    }

    // Print number of shortest paths from source to all nodes
    for (int i = 1; i <= nodeCount; i++) {
        if (i == source) continue;
        cout << source << " --> " << i << endl;

        if (dist[i] == inf) {
            cout << "cost: Infinite" << endl;
            cout << "path count: 0" << endl;
        } else {
            cout << "cost: " << dist[i] << endl;
            cout << "path count: " << countPaths[i] << endl;
        }
        cout << endl;
    }

    return 0;
}
