#include <string>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;
int r, c;
int startY, startX;
int leverY, leverX;
int targetY, targetX;
int visited[102][102];
vector<string> area;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
void bfsOne(int sy, int sx){
    queue<pair<int,int>> q;
    q.push({sy, sx});
    visited[sy][sx] = 1;
    
    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        if(y == leverY && x == leverX)break;
        q.pop();
        
        for(int i = 0; i < 4; i++){
            int yy = y + dy[i];
            int xx = x + dx[i];
            if(yy < 0 || yy >= r || xx < 0 || xx >= c) continue;
            if(visited[yy][xx]) continue;
            if(area[yy][xx] == 'X') continue;
            q.push({yy, xx});
            visited[yy][xx] = visited[y][x] + 1;
        }  
    }
}

void bfsTwo(int sy, int sx){
    queue<pair<int,int>> q;
    q.push({sy, sx});
    visited[sy][sx] = 1;
    
    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        if(y == targetY && x == targetX)break;
        q.pop();
        
        for(int i = 0; i < 4; i++){
            int yy = y + dy[i];
            int xx = x + dx[i];
            if(yy < 0 || yy >= r || xx < 0 || xx >= c) continue;
            if(visited[yy][xx]) continue;
            if(area[yy][xx] == 'X') continue;
            q.push({yy, xx});
            visited[yy][xx] = visited[y][x] + 1;
        }  
    }
}


int solution(vector<string> maps) {
    int answer = 0;
    area = maps;
    r = maps.size();
    c = maps[0].size();
    
    for(int i = 0; i < maps.size(); i++){
        for(int j = 0; j < maps[i].size(); j++){
            if(maps[i][j] == 'S'){
                startY = i; startX = j;
            }
            if(maps[i][j] == 'L'){
                leverY = i; leverX = j;
            }
            if(maps[i][j] == 'E'){
                targetY = i; targetX = j;
            }
        }
    }
   
    bfsOne(startY, startX);
    if(visited[leverY][leverX] == 0){
        answer = -1;
        return answer;
    }
    answer = visited[leverY][leverX] - 1;
    
    fill(&visited[0][0], &visited[0][0] + 102 * 102, 0);
    
    bfsTwo(leverY, leverX);
    if(visited[targetY][targetX] == 0){
        answer = -1;
        return answer;
    }
    answer += visited[targetY][targetX] - 1;
    return answer;
}