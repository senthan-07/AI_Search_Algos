#include <bits/stdc++.h>
using namespace std;

struct PQElement {
    int f_cost;
    int g_cost;
    char node;
    vector<char> path;
    bool operator>(const PQElement &other) const {
        return f_cost > other.f_cost;
    }
};

pair<vector<char>, int> aStarSearch(
    unordered_map<char, unordered_map<char, int>> &edges,
    unordered_map<char, int> &heuristic,
    char start, char goal)
{
    priority_queue<PQElement, vector<PQElement>, greater<PQElement>> pq;
    pq.push({heuristic[start], 0, start, {start}});

    unordered_set<char> visited;

    while (!pq.empty()) {
        PQElement current = pq.top();
        pq.pop();

        cout << "\n Curr node: " << current.node << endl;
        cout << "Path: ";
        for (char c : current.path) cout << c << " ";
        cout << "\n Curr g_cost: " << current.g_cost << ", f_cost: " << current.f_cost << endl;

        if (current.node == goal) {
            cout << "\n Goal found  \n";
            return {current.path, current.g_cost};
        }

        if (visited.count(current.node)) {
            cout << "Node " << current.node << " already visited so skip.\n";
            continue;
        }

        visited.insert(current.node);

        for (auto &neighbor_pair : edges[current.node]) {
            char neighbor = neighbor_pair.first;
            int edge_cost = neighbor_pair.second;

            if (!visited.count(neighbor)) {
                int new_g_cost = current.g_cost + edge_cost;
                int new_f_cost = new_g_cost + heuristic[neighbor];
                vector<char> new_path = current.path;
                new_path.push_back(neighbor);

                cout << "Adding neighbor: " << neighbor 
                     << " with edge cost: " << edge_cost
                     << ", new g_cost: " << new_g_cost 
                     << ", heuristic: " << heuristic[neighbor] 
                     << ", new f_cost: " << new_f_cost << endl;

                pq.push({new_f_cost, new_g_cost, neighbor, new_path});
            } else {
                cout  << neighbor << " already visited so skip.\n";
            }
        }
    }

    cout << "No path found from " << start << " to " << goal << ".\n";
    return {{}, INT_MAX};
}

int main() {
    unordered_map<char, unordered_map<char, int>> graph_edges = {
        {'A', {{'B', 1}, {'C', 4}}},
        {'B', {{'D', 2}, {'E', 5}}},
        {'C', {{'F', 1}}},
        {'D', {{'G', 3}}},
        {'E', {{'G', 1}}},
        {'F', {{'G', 2}}},
        {'G', {}}
    };

    unordered_map<char, int> heuristic = {
        {'A', 7}, {'B', 6}, {'C', 5}, {'D', 4},
        {'E', 2}, {'F', 3}, {'G', 0}
    };

    char start = 'A';
    char goal = 'G';

    auto [path, cost] = aStarSearch(graph_edges, heuristic, start, goal);

    if (!path.empty()) {
        cout << "\n Path from " << start << " to " << goal << ": ";
        for (char c : path) cout << c << " ";
        cout << "\n Path cost: " << cost << "\n";
    } else {
        cout << "\n No valid path found.\n";
    }

    return 0;
}
