#include <bits/stdc++.h>
using namespace std;

vector<int> adj[100];  // Adjacency list for the tree
vector<int> ancestors[100];  // List of ancestors for each node
bool visited[100];  // To keep track of visited nodes

// DFS function to find all ancestors for each node
void dfs(int node, vector<int>& currentAncestors) {
    visited[node] = true;

    // Store the current ancestors of this node
    ancestors[node] = currentAncestors;

    // Traverse all the children of the node
    for (int child : adj[node]) {
        if (!visited[child]) {
            currentAncestors.push_back(node);  // Add current node to the ancestor list
            dfs(child, currentAncestors);  // Recur for the child
            currentAncestors.pop_back();  // Backtrack, remove current node from ancestors list
        }
    }
}

int main() {
    int n, m;  // n = number of nodes, m = number of edges
    cout << "Enter the number of nodes and edges: ";
    cin >> n >> m;

    cout << "Enter the edges (u v):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);  // Add edge u -> v
    }

    int root = 0;  // Assuming root is node 0 (can be changed)
    vector<int> currentAncestors;  // To store the ancestors for the current node

    // Perform DFS starting from the root node
    dfs(root, currentAncestors);

    // Print the ancestors for each node
    for (int i = 0; i < n; i++) {
        cout << "Ancestors of node " << i << ": ";
        for (int ancestor : ancestors[i]) {
            cout << ancestor << " ";
        }
        cout << endl;
    }

    return 0;
}
