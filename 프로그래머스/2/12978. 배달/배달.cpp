#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int const INF = 1000000000;
vector<pair<int,int>> adj[52];
int d[52], visited[52];

int solution(int N, vector<vector<int> > road, int K) {
    ios_base::sync_with_stdio(false);
    int answer = 0;
    fill(&d[0], &d[0] + 52 , INF);
    
    for(int i = 0 ; i < road.size(); i++){
        adj[road[i][0]].push_back({road[i][2], road[i][1]});
        adj[road[i][1]].push_back({road[i][2], road[i][0]});
    }
    
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    
    d[1] = 0;
    pq.push({d[1], 1});
    
    while(!pq.empty()){
        pair<int,int> cur = pq.top();
        pq.pop();
        if(visited[cur.second]) continue;
        visited[cur.second] = 1;
        
        for(auto nxt : adj[cur.second]){
            if(d[nxt.second] > d[cur.second] + nxt.first){
                d[nxt.second] = d[cur.second] + nxt.first;
                pq.push({d[nxt.second], nxt.second});
            }
        }
    }
    
    for(int i = 1; i <= N; i++){
        if(d[i] <= K)
            answer++;
    }
    return answer;
}