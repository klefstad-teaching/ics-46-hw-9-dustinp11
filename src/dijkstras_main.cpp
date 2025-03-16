#include "dijkstras.h"

int main() 
{
    Graph g; 
    string file_path = "small.txt";
    file_to_graph(file_path, g);
    int source = 0;
    vector<int> previous;

    vector<int> distances = dijkstra_shortest_path(g, source, previous);

    for (int i = 0; i < g.numVertices; ++i) {
        vector<int> path = extract_shortest_path(distances, previous, i);
        print_path(path, distances[i]);
    }

    return 0;
}
