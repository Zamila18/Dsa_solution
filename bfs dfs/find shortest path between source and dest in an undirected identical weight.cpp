#include <bits/stdc++.h>
using namespace std;

vector<int> adj[10001];  // Adjacency list for the graph
int dist[10001];  // Array to store the shortest distance from source
int parent[10001];  // To store the parent of each node in the path
bool visited[10001];  // To mark visited nodes

// BFS function to find the shortest path in an unweighted graph
void bfs(int source, int destination, int n) {
    queue<int> q;
    dist[source] = 0;  // Distance of source from itself is 0
    visited[source] = true;
    q.push(source);

    // Perform BFS
    while (!q.empty()) {
        int node = q.front();
        q.pop();

        // If we reach the destination, stop the BFS
        if (node == destination) break;

        // Explore all neighbors of the current node
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                dist[neighbor] = dist[node] + 1;  // Distance of neighbor is distance of current node + 1
                parent[neighbor] = node;  // Set the parent of the neighbor
                q.push(neighbor);
            }
        }
    }
}

// Function to print the path from source to destination using reverse()
void printPath(int destination) {
    vector<int> result;
    for (auto node = destination; node != -1; node = parent[node]) {  // Using 'auto' for node type
        result.push_back(node);  // Collect the nodes in the path
    }

    // Print the path in reverse order (from source to destination)
    reverse(result.begin(), result.end());  // Reverse the collected path
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i != result.size() - 1) {
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

    int source, destination;
    cout << "Enter the source and destination nodes: ";
    cin >> source >> destination;

    // Initialize arrays (reset visited nodes and distances)
    for (int i = 0; i < n; i++) {
        visited[i] = false;
        dist[i] = -1;  // -1 indicates that a node is not visited yet
        parent[i] = -1;  // -1 means no parent (not reachable)
    }

    // Run BFS from source to find the shortest path to destination
    bfs(source, destination, n);

    // Check if destination is reachable
    if (dist[destination] == -1) {
        cout << "No path from source to destination." << endl;
    } else {
        cout << "Shortest path distance: " << dist[destination] << endl;
        cout << "Path: ";
        printPath(destination);  // Print the path using reverse
    }

    return 0;
}
