#include <string>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;
int startY, startX;
int endY, endX;
int leverY, leverX;
int visited[101][101];
int n, m;
int dy[] = {-1, 0, 1, 0};
int dx[] = {0, 1, 0, -1};
void bfs(const vector<string> &maps, int targetY, int targetX){
    fill(&visited[0][0], &visited[0][0] + 101 * 101, 0);
    
    queue<pair<int,int>> q;
    q.push({startY, startX});
    visited[startY][startX] = 1;
    
    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
        if(y == targetY && x == targetX) break;
        
        for(int i = 0; i < 4; i++){
            int yy = y + dy[i];
            int xx = x + dx[i];
            if(yy < 0 || yy >= n || xx < 0 || xx >= m) continue;
            if(visited[yy][xx]) continue;
            if(maps[yy][xx] == 'X') continue;
            else{
                q.push({yy, xx});
                visited[yy][xx] = visited[y][x] + 1;
            }
        }
    }
}
int solution(vector<string> maps) {
    int answer = 0;
    n = maps.size();    m = maps[0].size();
    
    for(int i = 0; i < maps.size(); i++){
        for(int j = 0; j < maps[i].size(); j++){
            if(maps[i][j] == 'S'){
                startY = i;
                startX = j;
            }
            if(maps[i][j] == 'E'){
                endY = i;
                endX = j;
            }
            if(maps[i][j] == 'L'){
                leverY = i;
                leverX = j;
            }
        }
    }
    
    bfs(maps, leverY, leverX);
    if(visited[leverY][leverX] == 0) return -1;
    else answer += visited[leverY][leverX] - 1;
    
    startY = leverY;    startX = leverX;
    bfs(maps, endY, endX);
    if(visited[endY][endX] == 0) return -1;
    else answer += visited[endY][endX] - 1;
    return answer;
}