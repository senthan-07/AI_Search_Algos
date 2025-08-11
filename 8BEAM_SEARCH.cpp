#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> ans;

bool beam_search(unordered_map<char, vector<pair<char, int>>> &g, unordered_map<char, int> &h, char st, char gl, size_t w) {

    auto cmp = [&](const pair<char, vector<char>> &a, const pair<char, vector<char>> &b) {
        return h[a.first] > h[b.first];
    };

    priority_queue<pair<char, vector<char>>, vector<pair<char, vector<char>>>, decltype(cmp)> cur_beam(cmp);
    cur_beam.push({st, {st}});

    while (!cur_beam.empty()) {
        priority_queue<pair<char, vector<char>>, vector<pair<char, vector<char>>>, decltype(cmp)> next_beam(cmp);

        while (!cur_beam.empty()) {
            auto cur = cur_beam.top();
            cur_beam.pop();

            char node = cur.first;
            vector<char> path = cur.second;

            cout << "\n Checking node: " << node << endl;
            cout << "Path : ";
            for (char c : path) cout << c << " ";
            cout << "\n";

            if (node == gl) {
                cout << "\nGoal found added to ans \n";
                ans.push_back(path);
                return true;
            }

            for (auto &nbr_p : g[node]) {
                char nbr = nbr_p.first;
                cout << "Adding neighbor: " << nbr << " with heuristic: " << h[nbr] << endl;

                vector<char> new_path = path;
                new_path.push_back(nbr);
                next_beam.push({nbr, new_path});
            }
        }

        vector<pair<char, vector<char>>> pruned;
        while (!next_beam.empty() && pruned.size() < w) {
            pruned.push_back(next_beam.top());
            next_beam.pop();
        }

        for (auto &p : pruned) {
            cur_beam.push(p);
        }

        if (cur_beam.empty()) break;
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
