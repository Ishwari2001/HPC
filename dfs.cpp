#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

void dfsTraversal(vector<vector<int> >& graph, vector<bool>& visited, int startVertex) {
    stack<int> s;
    s.push(startVertex);
    visited[startVertex] = true;

    cout << "The DFS Traversal is: ";
    double start = omp_get_wtime();

    while (!s.empty()) {
        int currentVertex = s.top();
        s.pop();

        cout << currentVertex << " ";

        #pragma omp parallel for
        for (size_t i = 0; i < graph[currentVertex].size(); i++) {
            int neighbor = graph[currentVertex][i];
            if (!visited[neighbor]) {
                #pragma omp critical
                {
                    visited[neighbor] = true;
                    s.push(neighbor);
                }
            }
        }
    }

    double end = omp_get_wtime();
    double time = end - start;
    cout << "\n\nTime taken => " << time << endl;
}

int main() {
    omp_set_num_threads(4);
    int n, e;
    cout << "Consider first vertex => 0" << endl;
    cout << "\nEnter the number of vertices: ";
    cin >> n;
    cout << "\nEnter the number of edges: ";
    cin >> e;

    vector<bool> visited(n, false);
    vector<vector<int> > graph(n);

    cout << "\nEnter the edges with source and target vertex: " << endl;
    for (int i = 0; i < e; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a); // For undirected graph, add this line
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfsTraversal(graph, visited, i);
        }
    }

    return 0;
}

