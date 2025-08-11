#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> ans;

bool dfs(unordered_map<char, vector<char>> &graph, char curr, char goal, vector<char> &path, unordered_set<char> &vis) {
    cout << "\n Checking node: " << curr << endl;
    cout << "Path : ";
    for (char c : path) cout << c << " ";
    cout << "\n";

    if (curr == goal) {
        cout << "\nGoal found added to ans \n";
        ans.push_back(path);
        return true; 
    }

    vector<char> neighbors = graph[curr];
    sort(neighbors.begin(), neighbors.end());
    for (char neigh : neighbors) {
        if (!vis.count(neigh)) {
            cout << "\nAdding new element: " << neigh;
            vis.insert(neigh);
            path.push_back(neigh);
            if (dfs(graph, neigh, goal, path, vis)) return true; 
            path.pop_back();
            vis.erase(neigh);
        } else {
            cout << "\nAlready in path: " << neigh << endl;
        }
    }
    return false;
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

    vector<char> path;
    unordered_set<char> vis;
    char start = 'S';
    char Goal = 'G';
    vis.insert(start);
    path.push_back(start);
    cout << "\nSearch starts:\n";
    dfs(graph, start,Goal,path,vis);

    cout << "\n---------------------------------";
    cout << "\nFinal answers:\n";
    for (auto &p : ans) {
        for (char c : p) cout << c << " ";
        cout << "\n";
    }
    cout << "---------------------------------\n";

    return 0;
}
