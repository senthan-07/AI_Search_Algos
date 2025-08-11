#include <bits/stdc++.h>
using namespace std;

vector<pair<vector<char>, int>> ans;

int britishMuseumRecursive(unordered_map<char, vector<pair<char, int>>> &graph, char curr, char goal, vector<char> &path, int cost) {
    if (curr == goal) {
        ans.push_back({path, cost});
        return cost;
    }

    int best_cost = INT_MAX;

    for (auto &neighbor_pair : graph[curr]) {
        char neigh = neighbor_pair.first;
        int edge_cost = neighbor_pair.second;
        if (find(path.begin(), path.end(), neigh) == path.end()) {
            path.push_back(neigh);
            int total_cost = britishMuseumRecursive(graph, neigh, goal, path, cost + edge_cost);
            best_cost = min(best_cost, total_cost);
            path.pop_back();
        }
    }

    return best_cost;
}

using PQElement = pair<int, pair<char, vector<char>>>;

int branchAndBoundSearch(unordered_map<char, vector<pair<char, int>>> &graph, char start, char goal, int cost_bound) {
    priority_queue<PQElement, vector<PQElement>, greater<PQElement>> pq;
    pq.push({0, {start, {start}}});

    unordered_set<char> visited;

    while (!pq.empty()) {
        auto [cost, nodePath] = pq.top();
        auto [curr, path] = nodePath;
        pq.pop();

        if (cost > cost_bound)
            return -1;

        if (curr == goal) {
            cout << "Path found: ";
            for (char node : path) cout << node << " ";
            cout << "with distance: " << cost << endl;
            return cost;
        }

        visited.insert(curr);

        for (auto &neighbor_pair : graph[curr]) {
            char neighbor = neighbor_pair.first;
            int edge_cost = neighbor_pair.second;
            if (!visited.count(neighbor)) {
                vector<char> new_path = path;
                new_path.push_back(neighbor);
                pq.push({cost + edge_cost, {neighbor, new_path}});
            }
        }
    }

    return -1;
}

int main() {
    unordered_map<char, vector<pair<char, int>>> graph;
    graph['S'] = {{'A', 3}, {'B', 5}};
    graph['A'] = {{'D', 3}, {'B', 4}, {'S', 3}};
    graph['B'] = {{'A', 4}, {'C', 4}, {'S', 5}};
    graph['C'] = {{'E', 6}, {'B', 6}};
    graph['D'] = {{'A', 3}, {'G', 5}};
    graph['E'] = {{'C', 6}};
    graph['G'] = {{'D', 5}};

    vector<char> path = {'S'};

    cout << "\nStarting British Museum Search (recursive):\n";
    int best_distance = britishMuseumRecursive(graph, 'S', 'G', path, 0);

    if (best_distance == INT_MAX) {
        cout << "Goal not reachable." << endl;
    } else {
        cout << "\nBest path cost found: " << best_distance << endl;
    }

    cout << "\n---------------------------------";
    cout << "\nAll found paths with costs:\n";
    for (auto &p : ans) {
        for (char c : p.first) cout << c << " ";
        cout << "and Cost: " << p.second << "\n";
    }
    cout << "---------------------------------\n";

    cout << "\n--- Branch and Bound Search ---\n";
    int result = branchAndBoundSearch(graph, 'S', 'G', best_distance);

    if (result == -1)
        cout << "Goal not reachable by Branch and Bound.\n";
    else
        cout << "Best path cost tru Branch and Bound (EL): " << result << endl;

    cout << "---------------------------------\n";

    return 0;
}
