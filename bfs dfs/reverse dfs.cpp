#include <bits/stdc++.h>
using namespace std;

vector<int> adj[10001];  // Adjacency list for the graph
bool visited[10001];  // To mark visited nodes
vector<int> path;  // To store the DFS traversal nodes

// DFS function to store the traversal
void dfs(int node) {
    visited[node] = true;
    path.push_back(node);  // Store the node in the path vector

    // Explore all neighbors of the current node
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor);  // Recur for unvisited neighbors
        }
    }
}

// Function to print the reversed DFS traversal
void printReversedDFS() {
    // Print the DFS traversal in reverse order
    reverse(path.begin(), path.end());  // Reverse the collected DFS traversal
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i != path.size() - 1) {
            cout << " -> ";  // Add arrow between nodes
        }
    }
    cout << endl;
}

int main() {
    int n, m;  // n = number of nodes, m = number of edges
    cout << "Enter the number of nodes and edges: ";
    cin >> n >> m;

    cout << "Enter the edges (u v) for the undirected graph:" << endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);  // Add v to u's adjacency list
        adj[v].push_back(u);  // Add u to v's adjacency list (undirected)
    }

    int source;
    cout << "Enter the source node: ";
    cin >> source;

    // Initialize arrays (reset visited nodes)
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    // Run DFS from the source to store the traversal
    dfs(source);  // Start DFS from the source node

    // Print the reversed DFS traversal
    cout << "Reversed DFS Path: ";
    printReversedDFS();

    return 0;
}

