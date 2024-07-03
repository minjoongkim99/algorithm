#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<vector<int>> adj;
vector<int> visited;

void dfs(int idx){
    visited[idx] = true;
    
    for(int i = 0; i < adj[idx].size(); i++){
        int node = adj[idx][i];
        if(visited[node])
            continue;
        dfs(node);
    }
}

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    adj.resize(n);
    visited.resize(n, 0);
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == j) continue;
            if(computers[i][j] == 0) continue;
            adj[i].push_back(j);
        }
    }

    int cnt = 0;
    for(int i = 0; i < n; i++){
        if(visited[i])  continue;
        dfs(i);
        answer++;
    }
    //cout << cnt << "\n";
    return answer;
}