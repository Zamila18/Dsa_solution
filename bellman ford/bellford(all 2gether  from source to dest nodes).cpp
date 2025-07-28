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
        countPaths[i] = 0;
    }
    dist[source] = 0;
    countPaths[source] = 1;
}

void Relax(int u, int v, int w) {
    if (dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
        path[v] = u;
        countPaths[v] = countPaths[u];
    } else if (dist[v] == dist[u] + w) {
        countPaths[v] += countPaths[u];
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

    int source, destination;
    cout << "Enter the source node: ";
    cin >> source;
    cout << "Enter the destination node: ";
    cin >> destination;

    bool isValid = Bellman_Ford(source, nodeCount);
    if (!isValid) {
        cout << "Negative Weight Cycle Detected." << endl;
        return 0;
    }

    cout << "Shortest path from " << source << " to " << destination << ":" << endl;
    if (dist[destination] == inf) {
        cout << "cost: Infinite" << endl;
        cout << "path: None" << endl;
        cout << "path count: 0" << endl;
    } else {
        cout << "cost: " << dist[destination] << endl;
        cout << "path count: " << countPaths[destination] << endl;

        // Path reconstruction
        cout << "path: ";
        vector<int> path1;
        int pred = destination;
        while (pred != -1) {
            path1.push_back(pred);
            pred = path[pred];
        }
        for (int i = 0; i < path1.size(); i++) {
            cout << path1[i];
            if (i != path1.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    }

    return 0;
}
