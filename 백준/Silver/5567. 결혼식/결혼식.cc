#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m;
vector<int> adj[502];
int visited[502];
int ret = 0;

void bfs(int cur){
    queue<int> q;
    q.push(cur);
    visited[cur] = 1;

    while(!q.empty()){
        int x = q.front();
        q.pop();
        if(visited[x] == 3) continue;
        for(auto nxt : adj[x]){
            if(visited[nxt] > 0) continue;
            else{
                q.push(nxt);
                visited[nxt] = visited[x] + 1;
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

    for(int i = 2; i <= n; i++){
        if(visited[i] > 0)
            ret++;
    }

    cout << ret << "\n";
    return 0;
}