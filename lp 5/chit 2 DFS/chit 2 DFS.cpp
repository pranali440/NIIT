#include <iostream>
#include <vector>
#include <stack>
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
        adj[v].push_back(u); // Undirected graph
    }

    // Parallel DFS
    void parallelDFS(int start) {

        vector<bool> visited(V, false);

        stack<int> s;

        s.push(start);

        cout << "Parallel DFS Traversal: ";

        while (!s.empty()) {

            int node;

            #pragma omp critical
            {
                node = s.top();
                s.pop();
            }

            if (!visited[node]) {

                visited[node] = true;

                cout << node << " ";

                // Parallel traversal of neighbors
                #pragma omp parallel for
                for (int i = 0; i < adj[node].size(); i++) {

                    int v = adj[node][i];

                    if (!visited[v]) {

                        #pragma omp critical
                        {
                            s.push(v);
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

    cout << "Enter starting vertex for DFS: ";
    cin >> start;

    g.parallelDFS(start);

    return 0;
}
