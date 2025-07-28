#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> nodeVec[10001];
vector<pair<int, pair<int, int>>> allEdges;
int dist[10001];
int path[10001];
int nodeCount, edgeCount;
#define inf 1e9

// Initialize distances and path
void Initialize_Single_Source(int source, int nodeCount) {
    for (int i = 1; i <= nodeCount; i++) {
        dist[i] = inf;
        path[i] = -1;
    }
    dist[source] = 0;
}

// Relax the edges
void Relax(int u, int v, int w) {
    if (dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
        path[v] = u;
    }
}

// Function to detect negative cycle and print it
void Print_Negative_Cycle(int startNode) {
    // To find the cycle, backtrack from the startNode
    vector<int> cycle;
    int node = startNode;
    for (int i = 0; i < nodeCount; i++) {
        node = path[node];  // Move to the predecessor
    }

    // Backtrack from node to get the cycle
    int cycleStart = node;
    while (true) {
        cycle.push_back(node);
        node = path[node];
        if (node == cycleStart) {
            break;
        }
    }

    reverse(cycle.begin(), cycle.end());

    // Print the cycle
    cout << "Negative Weight Cycle: ";
    for (int i = 0; i < cycle.size(); i++) {
        cout << cycle[i];
        if (i != cycle.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
}

bool Bellman_Ford(int source, int nodeCount) {
    Initialize_Single_Source(source, nodeCount);

    // Relax all edges (V-1) times
    for (int i = 1; i < nodeCount; i++) {
        for (auto e: allEdges) {
            int u = e.first;
            int v = e.second.first;
            int w = e.second.second;
            Relax(u, v, w);
        }
    }

    // Check for negative weight cycles
    for (auto e: allEdges) {
        int u = e.first;
        int v = e.second.first;
        int w = e.second.second;
        if (dist[v] > dist[u] + w) {
            Print_Negative_Cycle(v);
            return false;  // Negative cycle detected
        }
    }

    return true; // No negative cycle
}

int main() {
    cout << "Enter the number of nodes: ";
    cin >> nodeCount;
    cout << "Enter the number of edges: ";
    cin >> edgeCount;

    // Read all edges
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

    // If no negative cycle is detected, print the shortest paths and their cost
    cout << "No Negative Weight Cycle" << endl;

    return 0;
}
