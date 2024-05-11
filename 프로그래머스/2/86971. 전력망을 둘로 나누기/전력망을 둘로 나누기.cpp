#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;
vector<int> adj[102];
int visited[102];
int n;

int dfs(int a){
    int cnt = 1;
    visited[a] = 1;
    for(int i = 0; i < adj[a].size(); i++){
        int nxt = adj[a][i];
        if(!visited[nxt]){
            cnt += dfs(nxt);
        }
    }
   
    return cnt; // ? cnt flowchart 생각.
}

int solution(int N, vector<vector<int>> wires) {
    int answer = 1000000000;
    n = N;
    
    for(auto v : wires){
        adj[v[0]].push_back(v[1]);
        adj[v[1]].push_back(v[0]);
    }
    
    for(auto wire: wires){
        fill(&visited[0], &visited[0] + 102, 0);
        int a = wire[0];    int b = wire[1];
        
        for(int i = 0; i < adj[a].size(); i++){
            if(adj[a][i] == b){
                adj[a].erase(adj[a].begin() + i);
                break;
            }
        }
        for(int i = 0; i < adj[b].size(); i++){
            if(adj[b][i] == a){
                adj[b].erase(adj[b].begin() + i);
                break;
            }
        }
        
        int x = dfs(a);     int y = n - x;
      
        if(answer > abs(x - y)){
            answer = abs(x - y);
        }
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    return answer;
}