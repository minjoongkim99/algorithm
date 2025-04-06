#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int n, m;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int arr[25][25];
int visited[25][25];

int ncnt, nred, ny, nx;

int point = 0;

void showArr(){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cout << arr[i][j] << '\t';
        }
        cout << '\n';
    }
    cout << '\n';
}

void redInit(){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(arr[i][j] == 0)
                visited[i][j] = 0;
        }
    }
}

pair<int,int> bfs(int i, int j){
    int cnt = 0, red = 0;

    queue<pair<int,int>> q;
    q.push({i, j});
    visited[i][j] = arr[i][j];
    cnt++;

    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for(int dir = 0; dir < 4; ++dir){
            int yy = y + dy[dir];
            int xx = x + dx[dir];

            if(yy < 0 | yy >= n || xx < 0 || xx >= n) continue;
            if(visited[yy][xx]) continue;

            if(arr[yy][xx] == arr[i][j]){
                q.push({yy, xx});
                visited[yy][xx] = arr[i][j];
                cnt++;
            }
            else if(arr[yy][xx] == 0){
                q.push({yy, xx});
                visited[yy][xx] = arr[i][j];
                cnt++;
                red++;
            }
        }
    }

    return{cnt, red};
}

void removeBomb(){
    int val = arr[ny][nx];
    queue<pair<int,int>> q;
    q.push({ny, nx});
    visited[ny][nx] = val;
    arr[ny][nx] = -2;
    int cnt = 1;

    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for(int dir = 0; dir < 4; ++dir){
            int yy = y + dy[dir];
            int xx = x + dx[dir];

            if(yy < 0 | yy >= n || xx < 0 || xx >= n) continue;
            if(visited[yy][xx]) continue;

            if(arr[yy][xx] == val){
                q.push({yy, xx});
                visited[yy][xx] = val;
                arr[yy][xx] = -2;
                cnt++;
            }
            else if(arr[yy][xx] == 0){
                q.push({yy, xx});
                visited[yy][xx] = val;
                arr[yy][xx] = -2;
                cnt++;
            }
        }
    }
    point += cnt * cnt;
}

/*
1. 가장 크기가 큰 폭탄묶음(2개 이상이며 모두 같은 색깔이거나 빨간색 폭탄 포함한 것)
폭탄묶음은 연결되어이있어야하고, 빨간색 폭탄으로만은 아님..
가장 큰 폭탄 묶음이며, 같다면 빨간색이 가장 적은 것
빨간색이 같다면, 기준점 행큰, 기준점 열 작*/
void findTarget(){
    ncnt = nred = ny = nx = 0;

    for(int i = n - 1; i >= 0; --i){
        for(int j = 0; j < n; ++j){
            if(arr[i][j] <= 0) continue;
            if(visited[i][j] > 0) continue;

            pair<int,int> val = bfs(i, j);
            if(val.first > ncnt){
                ncnt = val.first;
                nred = val.second;
                ny = i;
                nx = j;
            }
            else if(val.first == ncnt){
                if(val.second < nred){
                    nred = val.second;
                    ny = i;
                    nx = j;
                }
            }

            redInit();
        }
    }
}

void gravity(){

    for(int j = 0; j < n; ++j){
        for(int i = n - 1; i >= 0; --i){
            if(arr[i][j] != -2) continue;
            for(int k = i - 1; k >= 0; --k){
                if(arr[k][j] == -2){
                    continue;
                }
                else if(arr[k][j] == -1){
                    break;
                }
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
    int tmp[25][25];
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            tmp[i][j] = arr[i][j];
    
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            arr[i][j] = tmp[j][n - i - 1];
        }
    }
}

void input(){
    cin >> n >> m;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cin >> arr[i][j];
        }
    }
}

int main() {
    // Please write your code here.
    int T = 1;

    for(int tc = 1; tc <= T; ++tc){
        //global_init();
        input();
        int t = 1;
        while(true){
            ncnt = nred = ny = nx = 0;
            fill(&visited[0][0], &visited[0][0] + 25 * 25, 0);
            // local_init();
            // (ncnt 총합), (nred는 빨강만)

            // 1. 가장 크기가 큰 폭탄 묶음 찾기.
            findTarget();
            //cout << ncnt << " " << nred << " " << ny << " " << nx << "!\n";
            if(ncnt < 2)
                break;

            fill(&visited[0][0], &visited[0][0] + 25 * 25, 0);
            removeBomb();
            
            //showArr();

            // 2. 중력 작용.
            
            gravity();
            //cout << "GRAVITY1\n";
            //showArr();

            // 3. 반시계 방향 회전
            rotate_left();
            //cout << "ROTATE_LEFT\n";
            //showArr();

            // 4. 중력 작용
            gravity();
            //cout << "GRAVITY2\n";
            //showArr();
        
            t++;
        }

        cout << point << '\n';
    }
    return 0;
}

/*
격자 내 val -1, 0, 1 ~ m
-1: 검은색 돌, 0: 빨간색 돌, 1 ~ m 그 외 색
폭탄묶음이 더 없을 때까지 계속 반복.

1. 가장 크기가 큰 폭탄묶음(2개 이상이며 모두 같은 색깔이거나 빨간색 폭탄 포함한 것)
폭탄묶음은 연결되어이있어야하고, 빨간색 폭탄으로만은 아님..
가장 큰 폭탄 묶음이며, 같다면 빨간색이 가장 적은 것
빨간색이 같다면, 기준점 행큰, 기준점 열 작

2. 폭탄 제거. 중력 작용.
폭탄이 떨어지나, -1인 검은색 돌은 중력 작용 x.

3. 반시계 회전

4. 다시 중력 작용

이것을 round마다 반복한다.

총 점수 더이상 폭탄이 안 터질때까지...
*/