#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

struct Edge {
    int src, dest, weight;
};

void bellmanFord(int V, int E, vector<Edge>& edges, int source) {
    // Step 1: Initialize distances from source to all vertices as infinite and distance to source itself as 0
    vector<int> distance(V, INT_MAX);
    distance[source] = 0;

    // Step 2: Relax all edges |V| - 1 times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
            }
        }
    }

    // Step 3: Check for negative-weight cycles
    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int weight = edges[j].weight;
        if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
            cout << "Graph contains negative weight cycle\n";
            return;
        }
    }

    // Print distances
    cout << "Vertex\tDistance from Source\n";
    for (int i = 0; i < V; i++) {
        cout << i << "\t\t" << distance[i] << "\n";
    }
}

int main() {
    int V, E, source;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<Edge> edges(E);
    cout << "Enter each edge as source, destination, and weight:\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }

    cout << "Enter the source vertex: ";
    cin >> source;

    bellmanFord(V, E, edges, source);

    return 0;
}
