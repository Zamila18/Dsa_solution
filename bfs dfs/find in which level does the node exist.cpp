#include <bits/stdc++.h>
using namespace std;

vector<int> adj[10001];  // Adjacency list for the graph
int level[10001];  // Array to store the level (distance from source)
bool visited[10001];  // To mark visited nodes

// BFS function to find the level of each node from the source
void bfs(int source, int n) {
    queue<int> q;
    visited[source] = true;
    level[source] = 0;  // Starting level of source node is 0
    q.push(source);

    // Perform BFS
    while (!q.empty()) {
        int node = q.front();
        q.pop();

        // Explore all neighbors of the current node
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                level[neighbor] = level[node] + 1;  // Level of neighbor is one more than current node's level
                q.push(neighbor);
            }
        }
    }
}

// Function to print the level of the given node
void findLevel(int node) {
    if (level[node] != -1) {
        cout << "Node " << node << " is at level " << level[node] << endl;
    } else {
        cout << "Node " << node << " is not reachable from the source." << endl;
    }
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

    // Initialize arrays (reset visited nodes and distances)
    for (int i = 0; i < n; i++) {
        visited[i] = false;
        level[i] = -1;  // -1 indicates that a node is not visited yet
    }

    // Run BFS from source to find the level of each node
    bfs(source, n);

    int nodeToFind;
    cout << "Enter the node to find its level: ";
    cin >> nodeToFind;

    // Find and print the level of the node
    findLevel(nodeToFind);

    return 0;
}
//DFS
#include <bits/stdc++.h>
using namespace std;

vector<int> adj[10001];  // Adjacency list for the graph
int level[10001];  // Array to store the level (distance from source)
bool visited[10001];  // To mark visited nodes

// DFS function to find the level of each node
void dfs(int node, int currentLevel) {
    visited[node] = true;
    level[node] = currentLevel;  // Set the level of the current node

    // Explore all neighbors of the current node
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, currentLevel + 1);  // Recur for unvisited neighbors, incrementing the level
        }
    }
}

// Function to print the level of the given node
void findLevel(int node) {
    if (level[node] != -1) {
        cout << "Node " << node << " is at level " << level[node] << endl;
    } else {
        cout << "Node " << node << " is not reachable from the source." << endl;
    }
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

    // Initialize arrays (reset visited nodes and distances)
    for (int i = 0; i < n; i++) {
        visited[i] = false;
        level[i] = -1;  // -1 indicates that a node is not visited yet
    }

    // Run DFS from the source to find the level of each node
    dfs(source, 0);  // Start DFS from the source node, with level 0

    int nodeToFind;
    cout << "Enter the node to find its level: ";
    cin >> nodeToFind;

    // Find and print the level of the node
    findLevel(nodeToFind);

    return 0;
}

