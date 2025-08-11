#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> ans;

bool dfs_hill(unordered_map<char, vector<pair<char, int>>> &graph,unordered_map<char, int> &heuristic,char curr, char goal,vector<char> &path,unordered_set<char> &vis) {
    cout << "\n Checking node: " << curr << endl;
    cout << "Path : ";
    for (char c : path) cout << c << " ";
    cout << "\n";

    if (curr == goal) {
        cout << "\nGoal found added to ans \n";
        ans.push_back(path);
        return true;
    }

    vector<pair<char, int>> neighbors = graph[curr];

    auto comp = [&heuristic](const pair<char, int> &a, const pair<char, int> &b) {
        return heuristic[a.first] < heuristic[b.first];
    };

    sort(neighbors.begin(), neighbors.end(), comp);

    for (auto &neigh_pair : neighbors) {
        char neigh = neigh_pair.first;
        cout<<"After sort add Heuristic of neigbour  "<<neigh<<" With value : "<<neigh_pair.second<<endl;
        if (!vis.count(neigh)) {
            cout << "\nAdding new element: " << neigh;
            vis.insert(neigh);
            path.push_back(neigh);
            if (dfs_hill(graph, heuristic, neigh, goal, path, vis)) return true;
            path.pop_back();
            vis.erase(neigh);
        } else {
            cout << "\nAlready in path: " << neigh << endl;
        }
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

    vector<char> path;
    unordered_set<char> vis;
    char start = 'S';
    char Goal = 'G';
    vis.insert(start);
    path.push_back(start);

    cout << "\nSearch starts:\n";
    dfs_hill(graph, heuristic, start, Goal, path, vis);

    cout << "\n---------------------------------";
    cout << "\nFinal answers:\n";
    for (auto &p : ans) {
        for (char c : p) cout << c << " ";
        cout << "\n";
    }
    cout << "---------------------------------\n";

    return 0;
}
