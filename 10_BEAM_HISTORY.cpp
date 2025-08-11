#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> ans;
unordered_set<char> visited;

bool beam_search(unordered_map<char, vector<pair<char, int>>> &graph,unordered_map<char, int> &heuristic,char start, char goal, size_t beam_width){
    auto cmp = [&](const pair<char, vector<char>> &a, const pair<char, vector<char>> &b) {
        return heuristic[a.first] > heuristic[b.first];
    };

    priority_queue<pair<char, vector<char>>, vector<pair<char, vector<char>>>, decltype(cmp)> curr_level(cmp);
    curr_level.push({start, {start}});
    visited.insert(start);

    while (!curr_level.empty()) {
        priority_queue<pair<char, vector<char>>, vector<pair<char, vector<char>>>, decltype(cmp)> next_level(cmp);

        while (!curr_level.empty()) {
            auto curr = curr_level.top();
            curr_level.pop();

            char curr_node = curr.first;
            vector<char> path = curr.second;

            cout << "\n Checking node: " << curr_node << endl;
            cout << "Current path: ";
            for (char c : path) cout << c << " ";
            cout << "\n";

            if (curr_node == goal) {
                cout << "\nGoal found add to ans \n";
                ans.push_back(path);
                return true;
            }

            for (auto &neighbor_pair : graph[curr_node]) {
                char neighbor = neighbor_pair.first;
                if (!visited.count(neighbor)) {
                    cout << "Adding neighbor: " << neighbor << " with heuristic: " << heuristic[neighbor] << endl;
                    vector<char> new_path = path;
                    new_path.push_back(neighbor);
                    next_level.push({neighbor, new_path});
                } else {
                    cout << "Already visited so skip : " << neighbor<<endl;
                }
            }
        }

        vector<pair<char, vector<char>>> pruned_nodes;
        while (!next_level.empty() && pruned_nodes.size() < beam_width) {
            auto node = next_level.top();
            next_level.pop();
            pruned_nodes.push_back(node);
            visited.insert(node.first);  
        }

        for (auto &node : pruned_nodes) {
            curr_level.push(node);
        }

        if (curr_level.empty()) break;
    }

    return false;
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

    size_t beam_width = 2;

    cout << "\nSearch starts:\n";
    if (!beam_search(graph, heuristic, 'S', 'G', beam_width)) {
        cout << "Goal not reachable." << endl;
    }

    cout << "\n---------------------------------";
    cout << "\nFinal answers:\n";
    for (auto &p : ans) {
        for (char c : p) cout << c << " ";
        cout << "\n";
    }
    cout << "---------------------------------\n";

    return 0;
}
