#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

vector<vector<int>> tree;
int visited[1000];
vector<int> comp;
int n, answer = 0;

void dfs(vector<int> cur){
    int sheep = 0;
    int wolf = 0;
    
    for(int i = 0; i < cur.size(); i++){
        if(comp[cur[i]] == 0) 
            sheep++;
        else
            wolf++;
    }
    
    if(sheep <= wolf){
        //cout << "CUR :";
        //for(int i = 0; i < cur.size(); i++){
        //    cout << cur[i] << " ";
        //}
        // cout << "\n";
        return;
    }
    
    if(answer < sheep){
        answer = sheep;
    }
    
    for(int i = 0; i < cur.size(); i++){
        int idx = cur[i];
        
        for(int j = 0; j < tree[idx].size(); j++){
            if(visited[tree[idx][j]]) continue;
            
            visited[tree[idx][j]] = true;
            cur.push_back(tree[idx][j]);
            dfs(cur);
            cur.pop_back();
            visited[tree[idx][j]] = false;
        }
    }
}

int solution(vector<int> info, vector<vector<int>> edges) {
  
    n = info.size();
    tree.resize(n);
    //visited.resize(n, false);
    comp = info;
    
    for(int i = 0; i < edges.size(); i++){
        tree[edges[i][0]].push_back(edges[i][1]);
    }
    
    visited[0] = true;
    dfs({0});
    return answer;
}