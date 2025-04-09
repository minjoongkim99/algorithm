#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m, k;    // 격자 크기, 벽 개수, 사무실의 시원함 정도.
int arr[22][22];
int visited[22][22];
int temperature[22][22];
int wall[22][22][4];

int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};
int t = 0;

bool canEnd(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(arr[i][j] != 1) continue;
            if(temperature[i][j] < k) return false;
        }
    }
    return true;
}

void useAir(int i, int j, int d){
    fill(&visited[0][0], &visited[0][0] + 22 * 22 , 0);
    queue<pair<int,int>> q;

    int dir = d - 2;
    int tx = i + dx[dir],  ty = j + dy[dir];
    visited[tx][ty] = 5;
    q.push({tx, ty});
    
    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        if(visited[x][y] <= 1) continue;

        if(wall[x][y][dir] == 0){
            int xx = x + dx[dir];
            int yy = y + dy[dir];
            if(xx >= 0 && xx < n && yy >= 0 && yy < n){
                if(visited[xx][yy] == 0){
                    q.push({xx, yy});
                    visited[xx][yy] = visited[x][y] - 1;
                }
            }
        }
        if(wall[x][y][(dir + 1) % 4] == 0){
            int xx = x + dx[(dir + 1) % 4];
            int yy = y + dy[(dir + 1) % 4];

            if(xx >= 0 && xx < n && yy >= 0 && yy < n){
                if(wall[xx][yy][dir] == 0){
                    int xxx = xx + dx[dir];
                    int yyy = yy + dy[dir];

                    if(xxx >= 0 && xxx < n && yyy >= 0 && yyy < n){
                        if(visited[xxx][yyy] == 0){
                            q.push({xxx, yyy});
                            visited[xxx][yyy] = visited[x][y] - 1;
                        }
                    }
                }
            }
        }
        if(wall[x][y][(dir + 3) % 4] == 0){
            int xx = x + dx[(dir + 3) % 4];
            int yy = y + dy[(dir + 3) % 4];

            if(xx >= 0 && xx < n && yy >= 0 && yy < n){
                if(wall[xx][yy][dir] == 0){
                    int xxx = xx + dx[dir];
                    int yyy = yy + dy[dir];

                    if(xxx >= 0 && xxx < n && yyy >= 0 && yyy < n){
                        if(visited[xxx][yyy] == 0){
                            q.push({xxx, yyy});
                            visited[xxx][yyy] = visited[x][y] - 1;
                        }
                    }
                }
            }
        }

    }
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            temperature[i][j] += visited[i][j];
        }
    }
}

void mixing(){
    int tmp[22][22];
    fill(&tmp[0][0], &tmp[0][0] + 22 * 22, 0);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int dir = 0; dir < 4; dir++){
                int xx = i + dx[dir];
                int yy = j + dy[dir];
                if(xx < 0 || xx >= n || yy < 0 || yy >= n) continue;
                if(wall[i][j][dir] == 1) continue;

                if(temperature[i][j] > temperature[xx][yy]){
                    int diff = (temperature[i][j] - temperature[xx][yy]) / 4;
                    tmp[xx][yy] += diff;
                    tmp[i][j] -= diff;
                }
            }
        }
    }

    for(int i = 0; i < n ; i++){
        for(int j = 0; j < n; j++){
            temperature[i][j] += tmp[i][j];
        }
    }
}

void decreaseOne(){
    for(int j = 0; j < n; j++){
        if(temperature[0][j] > 0)
            temperature[0][j]--;
        if(temperature[n - 1][j] > 0)
            temperature[n - 1][j]--;
    }
    for(int i = 1; i < n - 1; i++){
        if(temperature[i][0] > 0)
            temperature[i][0]--;
        if(temperature[i][n - 1] > 0)
            temperature[i][n - 1]--;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   cout.tie(nullptr);

    cin >> n >> m >> k;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> arr[i][j];
        }
    }
    
    for(int i = 1; i <= m; i++){
        int x, y, s;
        cin >> x >> y >> s;
        if(s == 0){
            wall[x - 1][y - 1][1] = 1;
            wall[x - 2][y - 1][3] = 1;
        }
        else if(s == 1){
            wall[x - 1][y - 1][0] = 1;
            wall[x - 1][y - 2][2] = 1;
        }   
    }

    while(t <= 100){

        if(canEnd())
            break;
    
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(arr[i][j] >= 2){
                    useAir(i, j, arr[i][j]);
                }
                else continue;
            }
        }
        
        mixing();

        decreaseOne();

        t++;
    }

    // 모든 사무실의 시원함의 정도가 k이상이 되는 최소 시간을 출력. 100 넘으면 -1 출력.
    if(t > 100)
        cout << -1 << "\n";
    else cout << t << "\n";
    return 0;
}
