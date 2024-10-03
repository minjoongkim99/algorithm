#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

vector<pair<int,int>> adj[20005];
int d[20005];
int visited[20005];
int solution(int n, vector<vector<int>> edge) {
    int answer = 0;

    for(auto e : edge){
        adj[e[0]].push_back({1, e[1]});
        adj[e[1]].push_back({1, e[0]});
    }
    fill(&d[0], &d[0] + n + 1, 1000000000);
    
    d[1] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({d[1], 1});
    
    while(!pq.empty()){
        pair<int,int> cur = pq.top();
        pq.pop();
        
        if(visited[cur.second]) continue;
        if(d[cur.second] != cur.first) continue;
        visited[cur.second] = 1;
        for(auto nxt : adj[cur.second]){
            if(d[nxt.second] < d[cur.second] + nxt.first){
                continue;
            }
            d[nxt.second] = d[cur.second] + nxt.first;
            pq.push({d[nxt.second], nxt.second});
        }
    }
    
    int mx = -1;
    for(int i = 1; i <= n; i++){
        if(mx < d[i])
            mx = d[i];
    }
    for(int i = 1; i <= n; i++){
        if(mx == d[i])
            answer++;
    }
    return answer;
}