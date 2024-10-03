#include<vector>
#include<algorithm>
#include<queue>
#include<iostream>
using namespace std;

int visited[102][102];
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int bfs(int i, int j, const vector<vector<int>> arr){
    int n = arr.size(), m = arr[0].size();
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
            if(visited[yy][xx] > 0) continue;
            if(arr[yy][xx] == 0) continue;
            q.push({yy, xx});
            visited[yy][xx] = visited[y][x] + 1;
        }
    }

    return visited[n - 1][m - 1];
}

int solution(vector<vector<int>> maps){
    int answer = 0;
    
    fill(&visited[0][0], &visited[0][0] + 102 * 102, -1);
    answer = bfs(0, 0, maps);
    return answer;
}