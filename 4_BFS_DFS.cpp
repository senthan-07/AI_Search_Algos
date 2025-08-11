#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> ans;

void dls(unordered_map<char, vector<char>> &graph, char curr, char goal, int limit, vector<char> &path, unordered_set<char> &vis) {
    cout << "\nChecking node: " << curr << endl;
    cout << "Path: ";
    for (char c : path) cout << c << " ";
    cout << "\n";

    if (curr == goal) {
        cout << "\nGoal found, add to ans\n";
        ans.push_back(path);
        return;
    }

    if (limit <= 0) return;

    vector<char> neighbors = graph[curr];
    sort(neighbors.begin(), neighbors.end());
    for (char neigh : neighbors) {
        if (!vis.count(neigh)) {
            cout << "\nAdding new element: " << neigh;
            vis.insert(neigh);
            path.push_back(neigh);
            dls(graph, neigh, goal, limit - 1, path, vis);
            path.pop_back();
            vis.erase(neigh);
        } else {
            cout << "\nAlready in path: " << neigh << endl;
        }
    }
}

void iddfs(unordered_map<char, vector<char>> &graph, char start, char goal) {
    int depth = 0;
    while (true) {
        vector<char> path = {start};
        unordered_set<char> vis = {start};

        cout << "\nTrying depth limit: " << depth << "\n";
        size_t before = ans.size();
        dls(graph, start, goal, depth, path, vis);

        if (!ans.empty()) break;
        depth++;
    }
}

int main() {
    unordered_map<char, vector<char>> graph;
    graph['S'] = {'A', 'B'};
    graph['A'] = {'D', 'B', 'S'};
    graph['B'] = {'A', 'C', 'S'};
    graph['C'] = {'E', 'B'};
    graph['D'] = {'A', 'G'};
    graph['E'] = {'C'};
    graph['G'] = {'D'};

    char start = 'S';
    char goal = 'G';

    cout << "\nSearch starts:\n";
    iddfs(graph, start, goal);

    cout << "\n---------------------------------";
    cout << "\nFinal answers:\n";
    for (auto &p : ans) {
        for (char c : p) cout << c << " ";
        cout << "\n";
    }
    cout << "---------------------------------\n";

    return 0;
}
