#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int n, m;
int arr[21][21];
int tmp[21][21];
int visited[21][21];
int point = 0;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

pair<int,int> bfs(int i, int j){
    queue<pair<int,int>> q;
    q.push({i, j});
    visited[i][j] = 1;
    int cnt = 1, red = 0;

    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for(int dir = 0; dir < 4; dir++){
            int yy = y + dy[dir];
            int xx = x + dx[dir];
            if(yy < 0 || yy >= n || xx < 0 || xx >= n) continue;
            if(visited[yy][xx]) continue;
            if(arr[yy][xx] == -1) continue;
            if(arr[yy][xx] == arr[i][j]){
                q.push({yy, xx});
                visited[yy][xx] = visited[y][x] + 1;
                cnt++;
            }
            else if(arr[yy][xx] == 0){
                q.push({yy, xx});
                visited[yy][xx] = visited[y][x] + 1;
                red++;
            }
        }
    }

    return make_pair(cnt, red);
}

void clearRed(){
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(arr[i][j] == 0){
                visited[i][j] = 0;
            }
}

void erasing(int i, int j){
    queue<pair<int,int>> q;
    queue<pair<int,int>> q1;
    q.push({i, j});
    q1.push({i, j});
    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for(int dir = 0; dir < 4; dir++){
            int yy = y + dy[dir];
            int xx = x + dx[dir];
            if(yy < 0 || yy >= n || xx < 0 || xx >= n) continue;
            if(visited[yy][xx]) continue;
            if(arr[yy][xx] == -1) continue;
            if(arr[yy][xx] == arr[i][j]){
                q.push({yy, xx});
                q1.push({yy, xx});
                visited[yy][xx] = visited[y][x] + 1;
            }
            else if(arr[yy][xx] == 0){
                q.push({yy, xx});
                q1.push({yy, xx});
                visited[yy][xx] = visited[y][x] + 1;
            }
        }
    }
    while(!q1.empty()){
        arr[q1.front().first][q1.front().second] = -2;
        q1.pop();
    }
}

void gravity(){
    for(int j = 0; j < n; j++){
        for(int i = n - 1; i >= 0; i--){
            if(arr[i][j] != -2) continue;
            for(int k = i - 1; k >= 0; k--){
                if(arr[k][j] == -1) break;
                if(arr[k][j] == -2) continue;
                else{
                    arr[i][j] = arr[k][j];
                    arr[k][j] = -2;
                    break;
                }
            }
        }
    }
}

void rotate_left(){
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            tmp[i][j] = arr[i][j];

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            arr[i][j] = tmp[j][n - i - 1];
} 

int main() {
    // 여기에 코드를 작성해주세요.
    cin >> n >> m;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> arr[i][j];

    while(true){
        fill(&visited[0][0], &visited[0][0] + 21 * 21, 0);
        int tot = 1, red = 0, ny = -1, nx = -1;

        for(int i = n - 1; i >= 0; i--){
            for(int j = 0; j < n; j++){
                if(arr[i][j] <= 0) continue;
                if(visited[i][j] > 0) continue;
                pair<int, int> val = bfs(i, j);
                if(val.first + val.second > tot){
                    tot = val.first + val.second;
                    red = val.second;
                    ny = i;
                    nx = j;
                }
                else if(val.first + val.second == tot){
                    if(val.second < red){
                        red = val.second;
                        ny = i;
                        nx = j;
                    }
                }
                clearRed();
            }
        }

        if(tot < 2) break;
        
        point += tot * tot;             // 점수 측정.

        fill(&visited[0][0], &visited[0][0] + 21 * 21, 0);
        erasing(ny, nx);

        gravity();

        rotate_left();

        gravity();
        
    }
    cout << point << '\n';
    return 0;
}
