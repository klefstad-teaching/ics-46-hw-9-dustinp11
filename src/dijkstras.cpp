#include "dijkstras.h"

struct EdgeComparison {
    bool operator()(const Edge& u, const Edge& v) { return u.weight > v.weight; }
};

using EdgeMinHeap = priority_queue<Edge, vector<Edge>, EdgeComparison>;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    int numVert = G.size();
    vector<int> distances(numVert, numeric_limits<int>::max()); // distances
    distances[source] = 0;
    previous.assign(numVert, -1); 
    vector<bool> visited(numVert, false); // boolean array, ith index true if ith vertex is visited

    EdgeMinHeap pq;
    pq.push(Edge(source, source, 0));

    while (!pq.empty()) {
        Edge e = pq.top();
        pq.pop();
        int u = e.dst;

        if (visited[u]) continue; // mark visited if visited
        visited[u] = true;

        for (const Edge& neighbor : G[u]) { // iterate through all neighbors and update distances
            int v = neighbor.dst, weight = neighbor.weight;

            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push(Edge(u, v, distances[v]));
            }
        }

    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination)
{
    stack<int> path;

    for (int curr = destination; curr != -1; curr = previous[curr]) path.push(curr);

    vector<int> res; 

    while (!path.empty()) { 
        int top = path.top();
        path.pop();
        res.push_back(top);
    }

    return res;
}

void print_path(const vector<int>& v, int total)
{
    for (int curr : v) {
        cout << curr << " "; 
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}


