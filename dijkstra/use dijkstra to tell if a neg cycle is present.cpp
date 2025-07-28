#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> nodeVec[10001];
vector<pair<int, pair<int, int>>> allEdges;
int dist[10001];
int path[10001];
int nodeCount, edgeCount;
#define inf 1e9

// Bellman-Ford Algorithm to detect negative cycles
bool Bellman_Ford(int source, int nodeCount) {
    // Initialize distances
    for (int i = 1; i <= nodeCount; i++) {
        dist[i] = inf;
        path[i] = -1;
    }
    dist[source] = 0;

    // Relax all edges V-1 times
    for (int i = 1; i < nodeCount; i++) {
        for (auto e: allEdges) {
            int u = e.first;
            int v = e.second.first;
            int w = e.second.second;
            if (dist[u] != inf && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                path[v] = u;
            }
        }
    }

    // Check for negative weight cycles
    for (auto e: allEdges) {
        int u = e.first;
        int v = e.second.first;
        int w = e.second.second;
        if (dist[u] != inf && dist[v] > dist[u] + w) {
            return false;  // Negative cycle detected
        }
    }

    return true;
}

// Dijkstra's algorithm for finding the shortest paths from source to all other nodes
void Dijkstra(int source, int nodeCount) {
    // Initialize distances and priority queue
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (int i = 1; i <= nodeCount; i++) {
        dist[i] = inf;
        path[i] = -1;
    }
    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        // If the current distance is greater than the already found shortest distance, skip it
        if (d > dist[u]) continue;

        // Relax adjacent edges
        for (auto edge : nodeVec[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                path[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

// Print the path using the path[] array with arrows (->)
void printPath(int node) {
    vector<int> path1;
    int pred = node;
    while (pred != -1) {
        path1.push_back(pred);
        pred = path[pred];
    }

    for (int j = 0; j < path1.size(); j++) {
        cout << path1[j];
        if (j != path1.size() - 1) {
            cout << " -> ";  // Add arrow between nodes
        }
    }
    cout << endl;
}

int main() {
    cout << "Enter the number of nodes: ";
    cin >> nodeCount;
    cout << "Enter the number of edges: ";
    cin >> edgeCount;

    // Read the graph
    for (int i = 0; i < edgeCount; i++) {
        int nodeA, nodeB, weight;
        cin >> nodeA >> nodeB >> weight;
        allEdges.push_back({nodeA, {nodeB, weight}});
        nodeVec[nodeA].push_back({nodeB, weight});
    }

    int source;
    cout << "Enter the source node: ";
    cin >> source;

    // Step 1: Use Bellman-Ford to detect negative cycles
    bool isValid = Bellman_Ford(source, nodeCount);
    if (!isValid) {
        cout << "Negative Weight Cycle Detected." << endl;
        return 0;
    }

    // Step 2: If no negative cycle, apply Dijkstra's algorithm
    Dijkstra(source, nodeCount);

    // Print the shortest path and cost for each node
    for (int i = 1; i <= nodeCount; i++) {
        if (i == source) continue;

        cout << source << " --> " << i << ": ";
        if (dist[i] == inf) {
            cout << "cost: Infinite, path: None" << endl;
        } else {
            cout << "cost: " << dist[i] << ", path: ";
            printPath(i);
        }
        cout << endl;
    }

    return 0;
}

