#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int n;
vector<int> adj[101];
int ret[101][101];
int arr[101][101];
int visited[101];
int k = 0;

void dfs(int idx, int st){
    visited[idx] = 1;

    for(auto e : adj[idx]){
        if(e == st)
            k = 1;
        if(visited[e]) continue;
        else dfs(e, st);
    }
}

int main() {
    // 여기에 코드를 작성해주세요.
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);  cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
            if(arr[i][j] == 1)
                adj[i].push_back(j);
        }
    }

    for(int i = 0; i < n; i++){
        fill(&visited[0], &visited[0] + 101, 0);
        k = 0;

        dfs(i, i);
        if(k == 1)
            ret[i][i] = 1;
        for(int j = 0; j < n; j++){
            if(i == j) continue;
            if(visited[j]){
                ret[i][j] = 1;
            }
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << ret[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}