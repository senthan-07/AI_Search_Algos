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
    unordered_map<char, vector<pair<char, int>>> &graph,
    unordered_map<char, int> &heuristic,
    char start, char goal)
{
    priority_queue<PQElement, vector<PQElement>, greater<PQElement>> pq;
    pq.push({heuristic[start], 0, start, {start}});

    unordered_set<char> visited;

    while (!pq.empty()) {
        PQElement current = pq.top();
        pq.pop();

        cout << "\nCurr node: " << current.node << endl;
        cout << "Path: ";
        for (char c : current.path) cout << c << " ";
        cout << "\nCurr g_cost: " << current.g_cost << ", f_cost: " << current.f_cost << endl;

        if (current.node == goal) {
            cout << "\nGoal found\n";
            return {current.path, current.g_cost};
        }

        if (visited.count(current.node)) {
            cout << "Node " << current.node << " already visited so skip.\n";
            continue;
        }

        visited.insert(current.node);

        for (auto &neighbor_pair : graph[current.node]) {
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
                cout << neighbor << " already visited so skip.\n";
            }
        }
    }

    cout << "No path found from " << start << " to " << goal << ".\n";
    return {{}, INT_MAX};
}

int main() {
    unordered_map<char, vector<pair<char, int>>> graph;
    graph['S'] = {{'A', 3}, {'B', 5}};
    graph['A'] = {{'D', 3}, {'B', 4}};
    graph['B'] = {{'A', 4}, {'C', 4}};
    graph['C'] = {{'E', 6}};
    graph['D'] = {{'A', 3}, {'G', 5}};
    graph['E'] = {{'C', 6}};
    graph['G'] = {{'D', 5}};

    unordered_map<char, int> heuristic = {
        {'S', 10}, {'A', 7}, {'B', 6}, {'C', 7}, {'D', 5}, {'E', 6}, {'G', 0}
    };

    char start_node = 'S';
    char goal_node = 'G';

    auto [path, cost] = aStarSearch(graph, heuristic, start_node, goal_node);

    if (!path.empty()) {
        cout << "\nPath from " << start_node << " to " << goal_node << ": ";
        for (char c : path) cout << c << " ";
        cout << "\nPath cost: " << cost << "\n";
    } else {
        cout << "\nNo valid path found.\n";
    }

    return 0;
}
