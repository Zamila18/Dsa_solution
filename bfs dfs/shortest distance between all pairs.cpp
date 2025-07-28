//10.DFS Approach (Shortest Distance between All Pairs)
#include <iostream>
#include <vector>
#include <climits>
using namespace std;
void dfs(int node, int target, vector<vector<int>>& adj, vector<bool>& visited, vector<int>& dist, int current_dist) {
  visited[node] = true;
  // If the target node is reached, update the shortest distance
  if (node == target) {
  dist[target] = min(dist[target], current_dist);
  }
  // Visit all adjacent nodes (neighbors)
  for (int neighbor : adj[node]) {
  if (!visited[neighbor]) {
  dfs(neighbor, target, adj, visited, dist, current_dist + 1);
  }
  }
  visited[node] = false; // Backtrack
}
int main() {
  int n, e;
  cout << "Enter number of nodes and edges: ";
  cin >> n >> e;
  vector<vector<int>> adj(n);
  cout << "Enter edges (u v):\n";
  for (int i = 0; i < e; i++) {
  int u, v;
  cin >> u >> v;
  adj[u].push_back(v); // Add edge u -> v
  adj[v].push_back(u); // Add edge v -> u for undirected graph
  }
  vector<vector<int>> dist(n, vector<int>(n, INT_MAX)); // Distance matrix initialized to infinity
  // For each node, perform DFS to find the shortest path to every other node
  for (int i = 0; i < n; i++) {
  for (int j = 0; j < n; j++) {
  if (i != j) {
  vector<bool> visited(n, false); // Keep track of visited nodes
  dist[i][j] = INT_MAX;
  dfs(i, j, adj, visited, dist[i], 0);
  }
  }
  }
  // Print the shortest distance matrix
  cout << "Shortest distance between all pairs of nodes (DFS):\n";
  for (int i = 0; i < n; i++) {
  for (int j = 0; j < n; j++) {
  if (dist[i][j] == INT_MAX) {
  cout << "INF ";
  } else {
  cout << dist[i][j] << " ";
  }
  }
  cout << endl;
  }
  return 0;
}
9.BFS Approach (Shortest Distance between All Pairs)
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
void bfs(int start, vector<vector<int>>& adj, int n, vector<vector<int>>& dist) {
  vector<bool> visited(n, false);
  queue<int> q;
  visited[start] = true;
  dist[start][start] = 0;
  q.push(start);
  while (!q.empty()) {
  int node = q.front();
  q.pop();
  // Visit all the adjacent nodes (neighbors)
  for (int neighbor : adj[node]) {
  if (!visited[neighbor]) {
  visited[neighbor] = true;
  dist[start][neighbor] = dist[start][node] + 1;
  q.push(neighbor);
  }
  }
  }
}
int main() {
  int n, e;
  cout << "Enter number of nodes and edges: ";
  cin >> n >> e;
  vector<vector<int>> adj(n);
  cout << "Enter edges (u v):\n";
  for (int i = 0; i < e; i++) {
  int u, v;
  cin >> u >> v;
  adj[u].push_back(v); // Add edge u -> v
  adj[v].push_back(u); // Add edge v -> u for undirected graph
  }
  vector<vector<int>> dist(n, vector<int>(n, INT_MAX)); // Distance matrix initialized to infinity
  // Perform BFS from each node to calculate shortest distances
  for (int i = 0; i < n; i++) {
  bfs(i, adj, n, dist);
  }
  // Print the shortest distance matrix
  cout << "Shortest distance between all pairs of nodes:\n";
  for (int i = 0; i < n; i++) {
  for (int j = 0; j < n; j++) {
  if (dist[i][j] == INT_MAX) {
  cout << "INF ";
  } else {
  cout << dist[i][j] << " ";
  }
  }
  cout << endl;
  }
  return 0;
}
