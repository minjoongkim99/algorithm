#include<vector>
#include<queue>
#include<iostream>
using namespace std;

int visited[102][102];
int dy[4] = {-1,0,1,0};
int dx[4] = {0,-1,0,1};

int solution(vector<vector<int> > maps)
{
    ios_base::sync_with_stdio(false);
    queue<pair<int,int>> q;
    
    q.push({0,0});
    visited[0][0] = 1;
    
    int L = maps.size(), R = maps[0].size();
    
    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        if(y == L - 1 && x == R - 1) break;
        q.pop();
        
        for(int i = 0 ; i < 4 ; i++){
            int yy = y + dy[i];
            int xx = x + dx[i];
            
            if(xx < 0 || yy < 0 || xx >= R || yy >= L)  continue;
            if(visited[yy][xx]) continue;
            if(!maps[yy][xx]) continue;
            visited[yy][xx] = visited[y][x] + 1;
            q.push({yy,xx});
        }
    }
    
    int answer = 0;
    if(visited[L - 1][R - 1] == 0)
        answer = -1;
    else
        answer = visited[L - 1][R - 1];
    return answer;
}