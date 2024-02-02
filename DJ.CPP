#include <iostream>
#include <vector>
#include <climits> // For INT_MAX
#include <set>
#include <cctype> // For isdigit() and toupper()

using namespace std;

int mapInputToIndex(char input) {
    if (isdigit(input)) {
        return input - '0'; // Convert char digit to int
    }
    input = toupper(input); // Convert to uppercase to standardize
    if (input >= 'A' && input <= 'E') {
        return input - 'A';
    }
    return -1; // Return -1 if the input is invalid
}

int findMinVertex(const vector<int>& distance, const set<int>& sptSet) {
    int min = INT_MAX, min_index = -1; 
    for (int v = 0; v < distance.size(); v++) {
        if (sptSet.find(v) == sptSet.end() && distance[v] < min) {
            min = distance[v], min_index = v;
        }
    }
    return min_index;
}

void printSolution(const vector<int>& distance, int n, const vector<int>& prev, int start, int end) {
    cout << "Vertex\t\tDistance from Source\tPath" << endl;
    int u = end;
    vector<int> path;
    while (prev[u] != -1) {
        path.insert(path.begin(), u);
        u = prev[u];
    }
    path.insert(path.begin(), start);
    cout << "Shortest path from " << start << " to " << end << ": ";
    for (size_t i = 0; i < path.size(); ++i) {
        if (i > 0) cout << " -> ";
        cout << path[i];
    }
    cout << "\nTotal distance: " << distance[end] << endl;
}

void dijkstra(const vector<vector<pair<int, int>>>& graph, int src, int end) {
    int V = graph.size();
    vector<int> distance(V, INT_MAX);
    vector<int> prev(V, -1);
    set<int> sptSet;

    distance[src] = 0;

    for (int count = 0; count < V; count++) {
        int u = findMinVertex(distance, sptSet);
        if (u == -1) break;

        sptSet.insert(u);

        for (auto& adj : graph[u]) {
            int v = adj.first;
            int weight = adj.second;
            if (sptSet.find(v) == sptSet.end() && distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                prev[v] = u;
                distance[v] = distance[u] + weight;
            }
        }
    }

    printSolution(distance, V, prev, src, end);
}

int main() {
    vector<vector<pair<int, int>>> graph = {
        {{1, 10}, {4, 3}},    // Adjacency list for vertex 0 (A)
        {{2, 2}, {0, 10}, {3, 4}, {4, 1}}, // Adjacency list for vertex 1 (B)
        {{1, 2}, {3, 9}, {4, 8}}, // Adjacency list for vertex 2 (C)
        {{1, 4}, {2, 9}, {4, 2}}, // Adjacency list for vertex 3 (D)
        {{0, 3}, {1, 1}, {2, 8}, {3, 2}}  // Adjacency list for vertex 4 (E)
    };

    string input;
    int start, end;

    cout << "Enter the starting node (A=0, B=1, C=2, D=3, E=4): ";
    cin >> input;
    start = mapInputToIndex(input[0]);

    cout << "Enter the ending node (A=0, B=1, C=2, D=3, E=4): ";
    cin >> input;
    end = mapInputToIndex(input[0]);

    if (start < 0 || end < 0 || start >= graph.size() || end >= graph.size()) {
        cout << "Invalid input. Please enter a value between A (or 0) and E (or 4)." << endl;
        return 1;
    }

    dijkstra(graph, start, end);

    return 0;
}
