#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m;
vector<int> adj[10002];
vector<int> ans;
int cnt[10002];
int visited[10002];

void dfs(int cur){
    visited[cur] = 1;
    if(adj[cur].empty()) return;

    for(auto nxt : adj[cur]){
        if(visited[nxt] == 1) continue;
        dfs(nxt);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   cout.tie(nullptr);

    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int a, b;
        cin >> a >> b;
        adj[b].push_back(a);
    }

    int mx = -1;
    for(int i = 1; i <= n; i++){

        fill(&visited[0], & visited[0] + n + 1, 0);
        dfs(i);

        for(int k = 1; k <= n; k++){
            if(visited[k] == 1){
                cnt[i]++;
            }
        }
        if(cnt[i] > mx){
            mx = cnt[i];
        }
    }

    for(int i = 1; i <= n; i++){
        if(cnt[i] == mx){
            ans.push_back(i);
        }
    }

    for(auto e : ans){
        cout << e << " ";
    }
    cout << "\n";
    return 0;
}