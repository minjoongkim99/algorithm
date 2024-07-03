#include<vector>
#include<iostream>
#include<queue>
using namespace std;

int n, m;
int arr[102][102];
int visited[102][102];

int dy[] = {-1, 0, 1, 0};
int dx[] = {0, 1, 0, -1};

void bfs(int i, int j){
    queue<pair<int,int>> q;
    q.push({i, j});
    visited[i][j] = 1;
    
    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
        
        for(int dir = 0; dir < 4; dir++){
            int yy = y + dy[dir];
            int xx = x + dx[dir];
            if(yy < 0 || yy >= n || xx < 0 || xx >= m) continue;
            if(visited[yy][xx] != -1) continue;
            if(arr[yy][xx] != 1) continue;
            
            q.push({yy, xx});
            visited[yy][xx] = visited[y][x] + 1;
        }
    }
}

int solution(vector<vector<int>> maps){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   cout.tie(nullptr);
    
    n = maps.size();
    m = maps[0].size();
   
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            arr[i][j] = maps[i][j];
            visited[i][j] = -1;
        }
    }
    
    bfs(0, 0);
    
    return visited[n - 1][m - 1];
}