#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <cmath>
using namespace std;
vector<pair<int,int>> v;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
int bfs(int a, int b, const vector<string> & place){
    int visited[5][5];
    fill(&visited[0][0], &visited[0][0] + 5 * 5, -1);
    queue<pair<int,int>> q;
    q.push({a, b});
    visited[a][b] = 0;
    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        
        q.pop();
        for(int i = 0; i < 4; i++){
            int yy = y + dy[i];
            int xx = x + dx[i];
            if(yy < 0 || yy >= 5 || xx < 0 || xx >= 5) continue;
            if(visited[yy][xx] != -1) continue;
            if(place[yy][xx] == 'X') continue;
            if(place[yy][xx] == 'P') return 0;
            visited[yy][xx] = visited[y][x] + 1;
            if(visited[yy][xx] < 2){
                q.push({yy, xx});
            }
        }
    }
    return 1;
}
vector<int> solution(vector<vector<string>> places) {    
    vector<int> answer;
    
    for(int k = 0; k < 5; k++){
        v.clear();
        int flag = 1;
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                if(places[k][i][j] == 'P'){
                   int a = bfs(i, j, places[k]);
                   if(a == 0){
                       flag = 0;
                   }
                }
            }
        }
        
        if(flag) answer.push_back(1);
        else answer.push_back(0);
      
    }
    
    return answer;
}