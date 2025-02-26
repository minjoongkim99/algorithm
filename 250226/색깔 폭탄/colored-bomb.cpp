#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int n, m;
int arr[22][22];
int visited[22][22];
int point = 0;
int redCnt = 0, bombCnt = 0;
int ny = 0, nx = 0;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

void redInit(){
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            if(arr[i][j] == 0)
                visited[i][j] = 0;
}

pair<int,int> bfs(int i, int j){
    queue<pair<int,int>> q;
    q.push({i, j});
    visited[i][j] = 1;
    int bCnt = 1, rCnt = 0;

    while(!q.empty()){
        int y = q.front().first, x = q.front().second;
        q.pop();

        for(int dir = 0; dir < 4; ++dir){
            int yy = y + dy[dir], xx = x + dx[dir];

            if(yy < 0 || yy >= n || xx < 0 || xx >= n) continue;
            if(visited[yy][xx]) continue;           // 방문처리는 규격이다;

            if(arr[yy][xx] == arr[i][j]){
                bCnt++;
                visited[yy][xx] = 1;
                q.push({yy, xx});
            }
            if(arr[yy][xx] == 0){
                rCnt++;
                visited[yy][xx] = 1;
                q.push({yy, xx});
            }
        }
    }

    return {bCnt, rCnt};
}

void erasingAndPoint(int i, int j){
    fill(&visited[0][0], &visited[0][0] + 22 * 22, 0);
    int val = arr[i][j];

    //cout << i << " " << j << " " << val << "\n";
    queue<pair<int,int>> q;
    q.push({i, j});
    visited[i][j] = 1;
    arr[i][j] = -2;
    int cnt = 1;

    while(!q.empty()){
        int y = q.front().first, x = q.front().second;
        q.pop();

        for(int dir = 0; dir < 4; ++dir){
            int yy = y + dy[dir], xx = x + dx[dir];

            if(yy < 0 || yy >= n || xx < 0 || xx >= n) continue;
            if(visited[yy][xx]) continue;           // 방문처리는 규격이다;

            if(arr[yy][xx] == val || arr[yy][xx] == 0){
                cnt++;
                visited[yy][xx] = 1;
                q.push({yy, xx});
                arr[yy][xx] = -2;
            }
        }
    }

    point += cnt * cnt;
}

void rotate_left(){
    int tmp[22][22];

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            tmp[i][j] = arr[j][n - i - 1]; // 반시계 방향 정사각형 배열 회전
        }                                  // 시계방향은 당연히 알고, 직사각형 배열 회전 시 어떻게 되는가?
    }                                      // 직사각형 배열의 회전 구성도.

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            arr[i][j] = tmp[i][j];
        }
    }
}

void gravity(){
    // 빈칸:-2 검은돌:-1 빨강:0 그외:1~m
    for(int j = 0; j < n; ++j){             // 행과 열에 대하여.

        for(int i = n - 1; i > 0; --i){
            if(arr[i][j] != -2) continue;   // 빈칸이 아니라면 중력 작용 무의미.

            for(int k = i - 1; k >= 0; --k){ // 생각할 것.
                if(arr[k][j] == -1) break;
                if(arr[k][j] == -2) continue;
                if(arr[k][j] >= 0){
                    arr[i][j] = arr[k][j];
                    arr[k][j] = -2;
                    break;
                }
            }
        }
    } 
}

int main() {
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr); cin.tie(nullptr);
    cin >> n >> m;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cin >> arr[i][j];
        }
    }
    // 더 이상 폭탄 묶음이 없을 때까지 시뮬레이션을 진행한 최종 점수.
    // 더 이상 폭탄 묶음이 없으려면 시작 코드는 for문이어야 하는가. true여야 하는가.
    while(true){ // for test
        fill(&visited[0][0], &visited[0][0] + 22 * 22, 0);
        redCnt = bombCnt = 0;
        ny = -1, nx = -1;

        // 행큰 열작으로 탐색 순서가 정해져있음
        for(int i = n; i >= 0; --i){
            for(int j = 0; j < n; ++j){
                if(visited[i][j] || arr[i][j] <= 0) continue; // 코드 줄이기 ||
                
                // 빨강색 visited[][] 초기화를 해줘야함. 왜 여기서 하는가에 대해 생각.
                redInit();

                pair<int,int> ret = bfs(i, j);               // first = 빨강 이외, second = 빨강
               
                if((ret.first + ret.second) > (bombCnt + redCnt)){
                    bombCnt = ret.first;
                    redCnt = ret.second;
                    ny = i;
                    nx = j;
                }
                else if((ret.first + ret.second) == (bombCnt + redCnt)){
                    if(ret.second < redCnt){
                        bombCnt = ret.first;
                        redCnt = ret.second;
                        ny = i;
                        nx = j;
                    }
                }
            }
        }

        if((bombCnt + redCnt) < 2) break;
        if(ny == -1 || nx == -1) break;

        erasingAndPoint(ny, nx);

        gravity();

        rotate_left();

        gravity();
    }

    cout << point << '\n';
    return 0;
}