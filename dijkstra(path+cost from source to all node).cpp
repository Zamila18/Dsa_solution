#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX  // Defining infinity as the maximum integer value

vector<pair<int, int>> adj[10001]; // Graph represented as adjacency list
int dist[10001]; // Stores the shortest distance from source to each node
int parent[10001]; // Stores the parent of each node for path reconstruction

void dijkstra(int source, int nodeCount) {
    // Initialize distance array and parent array
    for (int i = 1; i <= nodeCount; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[source] = 0;

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
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

// Function to get the path from source to a node
vector<int> getPath(int target) {
    vector<int> path;
    if (dist[target] == INF) {
        return path;  // Return an empty path if no path exists
    }

    // Traverse the parent array to reconstruct the path from target to source
    int node = target;
    while (node != -1) {
        path.push_back(node);
        node = parent[node];
    }

    reverse(path.begin(), path.end());  // Reverse to get the correct order (source to target)
    return path;
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

    // Output the shortest distances and paths for each node
    for (int i = 1; i <= nodeCount; i++) {
        if (i == source) continue;

        cout << source << " --> " << i << endl;
        if (dist[i] == INF) {
            cout << "cost: Infinite" << endl;
            cout << "path: None" << endl;
        } else {
            cout << "cost: " << dist[i] << endl;
            cout << "path: ";

            // Get the path from source to node i
            vector<int> path = getPath(i);

            // Print the path with arrows
            for (int j = 0; j < path.size(); j++) {
                cout << path[j];
                if (j != path.size() - 1) {
                    cout << " -> ";  // Add arrow between nodes
                }
            }
            cout << endl;
        }
    }

    return 0;
}
