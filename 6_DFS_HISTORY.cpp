#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> ans; 

bool dfs(unordered_map<char, vector<char>> &graph,char curr, char goal,vector<char> &path,unordered_set<char> &vis,unordered_set<char> &deadEnd){
    if (deadEnd.count(curr)) {
        cout << "\n Skipping dead end node: " << curr << "\n";
        return false;
    }

    cout << "\n Curr node: " << curr <<endl;
    cout<<"\nPath: ";
    for (char c : path) cout << c << " ";
    cout << "\n";

    if (curr == goal) {
        cout << "\nGoal found add to ans\n";
        ans.push_back(path);
        return true; 
    }

    vector<char> neighbors = graph[curr];
    sort(neighbors.begin(), neighbors.end());

    bool found = false;
    for (char neigh : neighbors) {
        if (!vis.count(neigh)) {
            cout << "\nAdding new el: " << neigh;
            vis.insert(neigh);
            path.push_back(neigh);

            if (dfs(graph, neigh, goal, path, vis, deadEnd)) {
                found = true;
                break; 
            }

            path.pop_back();
            vis.erase(neigh);
        } else {
            cout << "\nAlready visiteed " << neigh << "\n";
        }
    }

    if (!found) {
        cout << "\n Mark as dead end: " << curr << "\n";
        deadEnd.insert(curr);
    }

    return found;
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
    unordered_set<char> vis, deadEnd;
    char start = 'S';
    char goal = 'G';

    vis.insert(start);
    path.push_back(start);

    cout << "\nSearch starts:\n";
    dfs(graph, start, goal, path, vis, deadEnd);

    cout << "\n---------------------------------";
    cout << "\nFinal answers:\n";
    for (auto &p : ans) {
        for (char c : p) cout << c << " ";
        cout << "\n";
    }
    cout << "---------------------------------\n";

    return 0;
}
