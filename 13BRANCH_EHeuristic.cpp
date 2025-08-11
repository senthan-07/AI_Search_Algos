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

int branchAndBoundWithHeuristic(unordered_map<char, vector<pair<char, int>>> &graph,unordered_map<char, int> &heuristic,char start, char goal, int cost_bound) {
    using Type= pair<pair<int, int>, pair<char, vector<char>>>; 
    // first pair<int,int> = {estimated_cost (f), cost_so_far (g)}
    // second pair<char, vector<char>> = {current_node, path_taken}

    priority_queue<Type, vector<Type>, greater<Type>> pq;

    int initial_estimate = heuristic[start];
    pq.push({{initial_estimate, 0}, {start, {start}}});

    unordered_set<char> visited;

    while (!pq.empty()) {
        auto [costs, nodePath] = pq.top();
        pq.pop();

        auto [est_cost, g_cost] = costs;
        auto [curr, path] = nodePath;

        if (g_cost > cost_bound)
            return -1;

        if (curr == goal) {
            cout << "Path found: ";
            for (char node : path) cout << node << " ";
            cout << "with Distance: " << g_cost << endl;
            return g_cost;
        }

        visited.insert(curr);

        for (auto &neighbor : graph[curr]) {
            if (!visited.count(neighbor.first)) {
                int new_g_cost = g_cost + neighbor.second;
                int new_est_cost = new_g_cost + heuristic[neighbor.first];
                vector<char> new_path = path;
                new_path.push_back(neighbor.first);

                pq.push({{new_est_cost, new_g_cost}, {neighbor.first, new_path}});
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

    unordered_map<char, int> heuristic = {
        {'S', 10}, {'A', 7}, {'B', 6}, {'C', 7}, {'D', 5}, {'E', 6}, {'G', 0}
    };

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

    cout << "\n--- Branch and Bound with Heuristic ---\n";
    int result = branchAndBoundWithHeuristic(graph, heuristic, 'S', 'G', best_distance);

    if (result == -1) {
        cout << "Goal not reachable by Branch and Bound.\n";
    } else {
        cout << "Best path cost thru Branch and Bound + Heuristic: " << result << endl;
    }

    return 0;
}
