#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX  // Defining infinity as the maximum integer value

vector<pair<int, int>> adj[10001]; // Graph represented as adjacency list
int dist[10001]; // Stores the shortest distance from source to each node
int countPaths[10001]; // Stores the number of shortest paths to each node

void dijkstra(int source, int nodeCount) {
    // Initialize distance array and countPaths array
    for (int i = 1; i <= nodeCount; i++) {
        dist[i] = INF;
        countPaths[i] = 0;
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
                pq.push({dist[v], v});
            }
            // If another shortest path is found to v, add the number of paths
            else if (dist[v] == dist[u] + weight) {
                countPaths[v] += countPaths[u]; // Increment the number of paths
            }
        }
    }
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

    int source, destination;
    cout << "Enter the source node: ";
    cin >> source;
    cout << "Enter the destination node: ";
    cin >> destination;

    // Call Dijkstra's algorithm
    dijkstra(source, nodeCount);

    // Output the number of shortest paths for the destination node
    cout << "Number of shortest paths from node " << source << " to node " << destination << ": " << endl;
    if (dist[destination] == INF) {
        cout << "No path exists." << endl;
    } else {
        cout << "cost: " << dist[destination] << endl;
        cout << "The number of shortest paths: " << countPaths[destination] << endl;

    }

    return 0;
}
