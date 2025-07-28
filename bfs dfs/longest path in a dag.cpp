#include <bits/stdc++.h>
using namespace std;

vector<int> adj[10001];  // Adjacency list for the graph
int dist[10001];  // Array to store the longest path distance
bool visited[10001];  // To mark visited nodes
vector<int> topoOrder;  // To store the topological order

// Function for DFS and storing the topological order
void dfs(int node) {
    visited[node] = true;
    // Explore all neighbors of the current node
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor);
        }
    }
    topoOrder.push_back(node);  // Add the node to the topological order
}

// Function to find the longest path length in a DAG
void findLongestPath(int source, int n) {
    // Perform DFS for all unvisited nodes to get the topological order
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    // Reverse the topological order since we need to process nodes in reverse postorder
    reverse(topoOrder.begin(), topoOrder.end());

    // Initialize the distance array with negative infinity manually
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MIN;  // Set all distances to -∞ (INT_MIN)
    }
    dist[source] = 0;  // Distance of source node is 0

    // Process nodes in topological order to compute the longest path
    for (int node : topoOrder) {
        // For each node, relax the edges of its neighbors
        for (int neighbor : adj[node]) {
            if (dist[neighbor] < dist[node] + 1) {
                dist[neighbor] = dist[node] + 1;  // Relax the edge
            }
        }
    }
}

// Function to print the length of the longest path from source to destination
void printLongestPathLength(int destination) {
    if (dist[destination] == INT_MIN) {
        cout << "No path to the destination" << endl;
    } else {
        cout << "Longest path length to node " << destination << ": " << dist[destination] << endl;
    }
}

int main() {
    int n, m;  // n = number of nodes, m = number of edges
    cout << "Enter the number of nodes and edges: ";
    cin >> n >> m;

    cout << "Enter the edges (u v) for the directed graph:" << endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);  // Add edge u -> v to the adjacency list
    }

    int source, destination;
    cout << "Enter the source node: ";
    cin >> source;
    cout << "Enter the destination node: ";
    cin >> destination;

    // Find the longest path from source to all other nodes
    findLongestPath(source, n);

    // Print the longest path length to the destination node
    printLongestPathLength(destination);

    return 0;
}
