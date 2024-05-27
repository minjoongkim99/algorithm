#include <iostream>
#include <string>
#include <vector>

using namespace std;

int n, m;
int st, en;
int d[1002];
vector<pair<int,int>> adj[1002];

void dfs(int cur, int par){
    if(cur == en){
        return;
    }

    for(auto e : adj[cur]){
        if(e.first == par) continue;

        //cout << cur << " :" << e.first << " " << e.second << "\n";
        d[e.first] += (d[cur] + e.second);

        dfs(e.first, cur);
    }

}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);      cout.tie(NULL);
    cin >> n >> m;
    
    for(int i = 1; i <= n - 1; i++){
        int a, b, w;
        cin >> a >>b >> w;
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }

    for(int i = 1; i <= m; i++){
        fill(&d[0], &d[0] + 1002, 0);
        cin >> st >> en;
        dfs(st, 0);
        cout << d[en] << "\n";
    }
    return 0;
}