#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m;
vector<int> adj[20002];
int dist[20002];

void bfs(int idx){
    fill(&dist[0], &dist[0] + 20002, -1);
    queue<int> q;
    q.push(idx);
    dist[idx] = 0;

    while(!q.empty()){
        int cur = q.front();
        q.pop();
        for(auto nxt : adj[cur]){
            if(dist[nxt] >= 0) continue;
            else{
                q.push(nxt);
                dist[nxt] = dist[cur] + 1;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   cout.tie(nullptr);

    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    bfs(1);
    int mx = -1, idx = 0, cnt = 0;
    
    for(int i = 1; i <= n; i++){
        if(dist[i] > mx){
            mx = dist[i];
            idx = i;
        }
    }
    for(int i = 1; i <= n; i++){
        if(dist[i] == mx){
            cnt++;
        }
    }

    cout << idx << ' ' << mx << ' ' << cnt << "\n";
    return 0;
}