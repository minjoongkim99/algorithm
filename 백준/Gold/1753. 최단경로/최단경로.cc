#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define INF 100000000

int v,e,start;
vector<pair<int,int>> adj[20002];
int d[20002];
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);  cout.tie(NULL);

    cin >> v >> e;
    cin >> start;
    fill(&d[0], &d[0] + 20002, INF);

    for(int i = 1; i <= e; i++){
        int a, b, c;
        cin >> a >> b >> c; // 시작점, 도착점, 가중치
        adj[a].push_back({c, b});
    }

    d[start] = 0;
    pq.push({0, start});

    while(!pq.empty()){
        int len = pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        if(d[cur] != len) {
            continue;
        }

        for(int i = 0; i < adj[cur].size(); i++) {
            int next = adj[cur][i].second;
            int nextDistance = adj[cur][i].first;

            if(d[next] > d[cur] + nextDistance){
                d[next] = d[cur] + nextDistance;
                pq.push({d[next], next});
            }
        }
    }

    for(int i = 1; i <= v; i++){
        if(d[i] != INF)
            cout << d[i] << "\n";
        else
            cout << "INF\n";
    }
    return 0;
}