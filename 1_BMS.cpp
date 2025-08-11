#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> ans; 

struct comp {
    bool operator()(const pair<char, vector<char>> &a, const pair<char, vector<char>> &b) const {
        if (a.second.size() != b.second.size())
            return a.second.size() > b.second.size();
        return a.second > b.second;
    }
};

void britishMuseumSearch(unordered_map<char, vector<char>> &graph, char start, char goal) {
    priority_queue<pair<char, vector<char>>, vector<pair<char, vector<char>>>, comp> pq;

    pq.push({start, {start}});

    while (!pq.empty()) {
        auto [node, path] = pq.top();
        pq.pop();

        cout << "\n Curr node : " << node << " | path: ";
        for (char c : path) cout << c << " ";
        cout << "\n";

        if (node == goal) {
            ans.push_back(path); 
            cout << "Goal found! stored in ans.\n";
            continue;
        }

        vector<char> sorted_neigh = graph[node];
        sort(sorted_neigh.begin(), sorted_neigh.end());

        cout << "Sorted neigh of " << node << ": ";
        for (char n : sorted_neigh) cout << n << " ";
        cout << "\n";

        for (char neigh : sorted_neigh) {
            if (find(path.begin(), path.end(), neigh) == path.end()) {
                vector<char> new_path = path;
                new_path.push_back(neigh);
                pq.push({neigh, new_path});
                cout << "   add new neigh: " << neigh << "\n";
            } else {
                cout << "   check skips or not : " << neigh << "\n";
            }
        }
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

    britishMuseumSearch(graph, 'S', 'G');

    cout << "\n---------------------------------";
    cout << "\n Final answrs :\n";
    for (auto p : ans) {
        for (char c : p) cout << c << " ";
        cout << "\n";
    }
    cout << "\n---------------------------------";
}
