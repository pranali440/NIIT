#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

class Graph {

    int V;
    vector<vector<int> > adj;

public:

    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
    }

    // Add edge
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Parallel BFS
    void parallelBFS(int start) {

        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "Parallel BFS Traversal: ";

        while (!q.empty()) {

            int size = q.size();

            vector<int> currentLevel;

            // Store current level nodes
            while (size--) {

                int node = q.front();
                q.pop();

                currentLevel.push_back(node);

                cout << node << " ";
            }

            // Parallel traversal
            #pragma omp parallel for
            for (int i = 0; i < currentLevel.size(); i++) {

                int u = currentLevel[i];

                for (int j = 0; j < adj[u].size(); j++) {

                    int v = adj[u][j];

                    if (!visited[v]) {

                        #pragma omp critical
                        {
                            if (!visited[v]) {

                                visited[v] = true;

                                q.push(v);
                            }
                        }
                    }
                }
            }
        }

        cout << endl;
    }
};

int main() {

    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g(V);

    cout << "Enter number of edges: ";
    cin >> E;

    cout << "Enter edges (u v):" << endl;

    for (int i = 0; i < E; i++) {

        int u, v;

        cin >> u >> v;

        g.addEdge(u, v);
    }

    int start;

    cout << "Enter starting vertex: ";
    cin >> start;

    g.parallelBFS(start);

    return 0;
}
