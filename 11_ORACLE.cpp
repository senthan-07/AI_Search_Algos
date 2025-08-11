#include <bits/stdc++.h>
using namespace std;

vector<pair<vector<char>, int>> ans;

int britishMuseumRecursive(unordered_map<char, vector<pair<char, int>>> &graph, char curr, char goal,vector<char> &path, int cost){
    cout << "\n Curr node: " << curr <<endl;
    cout<< " Path: ";
    for (char c : path) cout << c << " ";
    cout << "\n Cost so far: " << cost << endl;

    if (curr == goal) {
        cout << "Found add to ans  "<<endl;
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

    return 0;
}
