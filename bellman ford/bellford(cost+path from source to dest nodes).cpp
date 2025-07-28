// Same code with minor modifications for destination node
#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> nodeVec[10001];
vector<pair<int, pair<int, int>>> allEdges;
int dist[10001];
int path[10001];
int nodeCount, edgeCount;
#define inf 1e9

void Initialize_Single_Source(int source, int nodeCount) {
    for (int i = 1; i <= nodeCount; i++) {
        dist[i] = inf;
        path[i] = -1;
    }
    dist[source] = 0;
}

void Relax(int u, int v, int w) {
    if (dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
        path[v] = u;
    }
}

bool Bellman_Ford(int source, int nodeCount) {
    Initialize_Single_Source(source, nodeCount);

    for (int i = 1; i < nodeCount; i++) {
        for (auto e: allEdges) {
            int u = e.first;
            int v = e.second.first;
            int w = e.second.second;
            Relax(u, v, w);
        }
    }

    for (auto e: allEdges) {
        int u = e.first;
        int v = e.second.first;
        int w = e.second.second;
        if (dist[v] > dist[u] + w) {
            return false;
        }
    }

    return true;
}

int main() {
    cout << "Enter the number of nodes: ";
    cin >> nodeCount;
    cout << "Enter the number of edges: ";
    cin >> edgeCount;

    for (int i = 0; i < edgeCount; i++) {
        int nodeA, nodeB, weight;
        cin >> nodeA >> nodeB >> weight;
        allEdges.push_back({nodeA, {nodeB, weight}});
        nodeVec[nodeA].push_back({nodeB, weight});
    }

    int source, destination;
    cout << "Enter the source node: ";
    cin >> source;
    cout << "Enter the destination node: ";
    cin >> destination;

    bool isValid = Bellman_Ford(source, nodeCount);
    if (!isValid) {
        cout << "Negative Weight Cycle Detected." << endl;
        return 0;
    }

    cout << source << " --> " << destination << endl;
    if (dist[destination] == inf) {
        cout << "cost: Infinite" << endl;
        cout << "path: None" << endl;
    } else {
        cout << "cost: " << dist[destination] << endl;
        cout << "path: ";
        vector<int> path1;
        int pred = destination;
        while (pred != -1) {
            path1.push_back(pred);
            pred = path[pred];
        }
        for (int j = 0; j < path1.size(); j++) {
            cout << path1[j];
            if (j != path1.size() - 1) {
                cout << " -> ";  // Add arrow between nodes
            }
        }
        cout << endl;
    }

    return 0;
}
