#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> ans; 

void bfsLevelGlobalVisited(unordered_map<char, vector<char>> &graph, char start, char goal) {
    queue<vector<char>> q; 
    unordered_set<char> visited; 

    cout << "\n Search starts : \n";
    q.push({start});
    visited.insert(start);

    while (!q.empty()) {
        int level_size = q.size();

        for (int i = 0; i < level_size; i++) {
            vector<char> path = q.front();
            q.pop();

            char node = path.back();
            cout << "\n Checking node: " << node<<endl;
            cout << "\nPath of node: ";
            for (char ch : path) cout << ch << " ";
            cout << "\n";

            if (node == goal) {
                cout << "\n Goal found add to ans\n";
                ans.push_back(path);
                return; 
            }

            for (char neigh : graph[node]) {
                if (!visited.count(neigh)) {
                    visited.insert(neigh);
                    vector<char> new_path = path;
                    cout << "\n Adding new el: " << neigh;
                    new_path.push_back(neigh);
                    q.push(new_path);
                } else {
                    cout << "\n Already visited: " << neigh << "\n";
                }
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

    bfsLevelGlobalVisited(graph, 'S', 'G');

    cout << "\n---------------------------------";
    cout << "\n Final answers:\n";
    for (auto &p : ans) {
        for (char c : p) cout << c << " ";
        cout << "\n";
    }
    cout << "---------------------------------\n";
}
