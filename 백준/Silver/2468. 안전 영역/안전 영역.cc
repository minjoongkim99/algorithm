#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int area[103][103], visited[103][103];
int dy[4] = {-1,0,1,0}, dx[4] = {0,-1,0,1};

int n, ret = 0;

void dfs(int y, int x, int k){
    visited[y][x] = 1;
    
    for(int i = 0 ; i < 4; i++){
        int yy = y + dy[i];
        int xx = x + dx[i];
        
        if(xx < 0 || xx >= n || yy < 0 || yy >= n) continue;
        if(visited[yy][xx]) continue;
        
        if(area[yy][xx] > k){
            dfs(yy,xx,k);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);  cout.tie(NULL);

    cin >> n;
    int limit = -1;
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> area[i][j];
            if(area[i][j] > limit)
                limit = area[i][j];
        }
    }

    for(int k = 0; k <= limit; k++){
        int cnt = 0;
        fill(&visited[0][0] , &visited[0][0] + 103 * 103, 0);

        for(int i = 0 ; i < n; i++){
            for(int j = 0; j < n; j++){
                if(!visited[i][j] && area[i][j] > k){
                    dfs(i,j,k);
                    cnt++;
                }
            }
        }
        
        if(ret < cnt)
            ret = cnt;
    }

    cout << ret;
    return 0;
}