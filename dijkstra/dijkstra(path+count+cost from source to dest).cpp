#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX  // Defining infinity as the maximum integer value

vector<pair<int, int>> adj[10001]; // Graph represented as adjacency list
int dist[10001]; // Stores the shortest distance from source to each node
int parent[10001]; // Stores the parent of each node for path reconstruction
int countPaths[10001]; // Stores the number of shortest paths to each node

void dijkstra(int source, int nodeCount) {
    // Initialize distance array, parent array, and countPaths array
    for (int i = 1; i <= nodeCount; i++) {
        dist[i] = INF;
        parent[i] = -1;
        countPaths[i] = 0;  // Initialize countPaths to 0
    }
    dist[source] = 0;
    countPaths[source] = 1;  // There's one way to start at the source

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // Explore all adjacent nodes of u
        for (auto edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight; // Update the shortest distance
                parent[v] = u; // Update the parent to construct the path
                countPaths[v] = countPaths[u]; // Reset the number of paths
                pq.push({dist[v], v});
            }
            // If another shortest path is found to v, increment countPaths[v]
            else if (dist[v] == dist[u] + weight) {
                countPaths[v] += countPaths[u];
            }
        }
    }
}

// Function to get all paths from source to destination
void getPaths(int target, vector<int>& path, vector<vector<int>>& allPaths) {
    // If the target is the source, return the path
    if (target == -1) {
        allPaths.push_back(path);
        return;
    }

    path.push_back(target);
    getPaths(parent[target], path, allPaths);
    path.pop_back();
}

int main() {
    int nodeCount, edgeCount;

    cout << "Enter the number of nodes: ";
    cin >> nodeCount;
    cout << "Enter the number of edges: ";
    cin >> edgeCount;

    // Read the edges and build the graph
    cout << "Enter the edges (node1 node2 weight):" << endl;
    for (int i = 0; i < edgeCount; i++) {
        int nodeA, nodeB, weight;
        cin >> nodeA >> nodeB >> weight;
        adj[nodeA].push_back({nodeB, weight});
        adj[nodeB].push_back({nodeA, weight}); // For undirected graph, add both directions
    }

    int source, destination;
    cout << "Enter the source node: ";
    cin >> source;
    cout << "Enter the destination node: ";
    cin >> destination;

    // Call Dijkstra's algorithm
    dijkstra(source, nodeCount);

    // Output the number of shortest paths and the corresponding paths for the destination node
    cout << "Shortest paths from node " << source << " to node " << destination << ":" << endl;
    if (dist[destination] == INF) {
        cout << "Cost: Infinite" << endl;
        cout << "Paths: None" << endl;
    } else {
        cout << "Cost: " << dist[destination] << endl;

        // Get all possible shortest paths
        vector<int> path;
        vector<vector<int>> allPaths;
        getPaths(destination, path, allPaths);

        // Print the number of shortest paths
        cout << "Number of shortest paths: " << countPaths[destination] << endl;

        // Print all shortest paths
        for (auto& p : allPaths) {
            cout << "Path: ";
            for (int i = 0; i < p.size(); i++) {
                cout << p[i];
                if (i != p.size() - 1) {
                    cout << " -> ";  // Add arrow between nodes
                }
            }
            cout << endl;
        }
    }

    return 0;
}
