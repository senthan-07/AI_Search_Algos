#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> ans; 

void bfs(unordered_map<char,vector<char>> &graph,char start,char goal){
    queue<pair<char,vector<char>>> q;
    q.push({start,{start}});
    bool found = false; 
    cout<<"\n Search starts : \n";
    while(!q.empty()){
        int qs = q.size(); 
        for (int i = 0; i < qs; i++) {
            auto [node, path] = q.front();
            q.pop();
            cout<<"\n checking node : "<<node<<endl;
            cout<<"Path of node : ";
            for(char ch : path) cout<<ch<<" "; 
            cout<<"\n";
            
            if (node == goal) {
                cout<<"\n G is found add to ans"<<endl;
                ans.push_back(path);
                found = true;
                continue;
            }
            
            if (!found) {
                for (char neigh : graph[node]) {
                    if (find(path.begin(), path.end(), neigh) == path.end()) {
                        vector<char> new_path = path;
                        cout<<"\n Adding new el : "<< neigh;
                        new_path.push_back(neigh);
                        q.push({neigh, new_path});
                    }
                    else{
                        cout<<"\n Alrdy in path : "<<neigh<<endl;
                    }
                }
            }
        }
    }
}

int main(){
    // unordered_map<char, vector<char>> graph;
    // graph['S'] = {'A', 'B'};
    // graph['A'] = {'D', 'B', 'S'};
    // graph['B'] = {'A', 'C', 'S'};
    // graph['C'] = {'E', 'B'};
    // graph['D'] = {'A', 'G'};
    // graph['E'] = {'C'};
    // graph['G'] = {'D'};

    unordered_map<char, vector<char>> graph;
    graph['S'] = {'A', 'B'};
    graph['A'] = {'S', 'C', 'G'}; // Added direct link A→G
    graph['B'] = {'S', 'D', 'G'}; // Added direct link B→G
    graph['C'] = {'A'};
    graph['D'] = {'B'};
    graph['G'] = {'A', 'B'};

    bfs(graph, 'S', 'G');
    cout << "\n---------------------------------";
    cout << "\n Final answrs :\n";
    for (auto &p : ans) {
        for (char c : p) cout << c << " ";
        cout << "\n";
    }
    cout << "\n---------------------------------";
    return 0;
}
