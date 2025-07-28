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
        countPaths[i] = 0;
        parent[i] = -1;
    }
    dist[source] = 0;
    countPaths[source] = 1;  // There's one way to start at the source node

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // Explore all adjacent nodes of u
        for (auto edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            // If a shorter path to v is found, update the distance and path count
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight; // Update the shortest distance
                countPaths[v] = countPaths[u]; // Reset the number of paths
                parent[v] = u; // Set parent to reconstruct the path
                pq.push({dist[v], v});
            }
            // If another shortest path is found to v, increment countPaths[v]
            else if (dist[v] == dist[u] + weight) {
                countPaths[v] += countPaths[u]; // Add the number of paths
            }
        }
    }
}

// Function to get the path from source to a node
void getPath(int target, vector<int>& path) {
    // Traverse the parent array to reconstruct the path from target to source
    if (target == -1) return;
    getPath(parent[target], path);
    path.push_back(target);
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
        //adj[nodeB].push_back({nodeA, weight}); // For undirected graph, add both directions
    }

    int source;
    cout << "Enter the source node: ";
    cin >> source;

    // Call Dijkstra's algorithm
    dijkstra(source, nodeCount);

    // Output the shortest distances, paths, and number of shortest paths for all nodes
    for (int i = 1; i <= nodeCount; i++) {
        if (i == source) continue;  // Skip the source node

        cout << "Shortest path from node " << source << " to node " << i << ":" << endl;

        // Print the cost (shortest distance)
        if (dist[i] == INF) {
            cout << "cost: Infinite" << endl;
            cout << "path count: 0" << endl;
        } else {
            cout << "cost: " << dist[i] << endl;

            // Print the path
            vector<int> path;
            getPath(i, path);
            cout << "path: ";
            for (int j = 0; j < path.size(); j++) {
                cout << path[j];
                if (j != path.size() - 1) {
                    cout << " -> ";  // Add arrow between nodes
                }
            }
            cout << endl;

            // Print the number of shortest paths
            cout << "path count: " << countPaths[i] << endl;
        }
    }

    return 0;
}
