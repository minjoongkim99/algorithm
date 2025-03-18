#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int R, C, K;        // 입력 상수들을 맨 위로 놓자

int dy[4] = {-1, 0, 1, 0};      // dy, dx 잘 안보니깐, 위에다가
int dx[4] = {0, 1, 0, -1};      // dy, dx 잘 안보니깐, 위에다가

int arr[75][75];                // use variables
int escape[75][75];             // use variables
int visited[75][75];            // use variables

struct ghost{
    int y, x, dir;
};
ghost G[1002];          // 구조체와 구조체 배열
int lastPos[1002][2];   // 구조체에 못 담은 정보(변수) 는 int 배열[idx 크기];

int sum = 0;            // output

bool canDown(int idx){
    int y1 = G[idx].y + 2, x1 = G[idx].x;
    int y2 = G[idx].y + 1, x2 = G[idx].x - 1;
    int y3 = G[idx].y + 1, x3 = G[idx].x + 1;

    if(arr[y1][x1] || arr[y2][x2] || arr[y3][x3]) return false;
    if(y1 > R || x1 < 1 || x1 > C) return false;
    if(y2 > R || x2 < 1 || x2 > C) return false;
    if(y3 > R || x3 < 1 || x3 > C) return false;

    return true;
}

void moveDown(int idx){
    G[idx].y++;
}

bool canLeft(int idx){
    int y1 = G[idx].y - 1, x1 = G[idx].x - 1;
    int y2 = G[idx].y, x2 = G[idx].x - 2;
    int y3 = G[idx].y + 1, x3 = G[idx].x - 1;
    int y4 = G[idx].y + 1, x4 = G[idx].x - 2;
    int y5 = G[idx].y + 2, x5 = G[idx].x - 1;

    if(arr[y1][x1] || arr[y2][x2] || arr[y3][x3] || arr[y4][x4] || arr[y5][x5]) return false;
    if(y1 > R || x1 < 1 || x1 > C) return false;
    if(y2 > R || x2 < 1 || x2 > C) return false;
    if(y3 > R || x3 < 1 || x3 > C) return false;
    if(y4 > R || x4 < 1 || x4 > C) return false;
    if(y5 > R || x5 < 1 || x5 > C) return false;

    return true;
}

void moveLeft(int idx){
    G[idx].y++;
    G[idx].x--;
    G[idx].dir = (G[idx].dir + 3) % 4;
}

bool canRight(int idx){
    int y1 = G[idx].y - 1, x1 = G[idx].x + 1;
    int y2 = G[idx].y, x2 = G[idx].x + 2;
    int y3 = G[idx].y + 1, x3 = G[idx].x + 1;
    int y4 = G[idx].y + 1, x4 = G[idx].x + 2;
    int y5 = G[idx].y + 2, x5 = G[idx].x + 1;

    if(arr[y1][x1] || arr[y2][x2] || arr[y3][x3] || arr[y4][x4] || arr[y5][x5]) return false;
    if(y1 > R || x1 < 1 || x1 > C) return false;
    if(y2 > R || x2 < 1 || x2 > C) return false;
    if(y3 > R || x3 < 1 || x3 > C) return false;
    if(y4 > R || x4 < 1 || x4 > C) return false;
    if(y5 > R || x5 < 1 || x5 > C) return false;

    return true;
}

void moveRight(int idx){
    G[idx].y++;
    G[idx].x++;
    G[idx].dir = (G[idx].dir + 1) % 4;
}

void moveGhost(int idx){
    int flag = 1;
    int t = 0;
    while(flag == 1){
        flag = 0;

        if(canDown(idx)){
            flag = 1;
            moveDown(idx);
        }
        else if(canLeft(idx)){
            flag = 1;
            moveLeft(idx);
        }
        else if(canRight(idx)){
            flag = 1;
            moveRight(idx);
        }
    }
}

void fillToArr(int idx){
    arr[G[idx].y][G[idx].x] = idx;
    for(int dir = 0; dir < 4; ++dir){
        arr[G[idx].y + dy[dir]][G[idx].x + dx[dir]] = idx;
    }
    escape[G[idx].y + dy[G[idx].dir]][G[idx].x + dx[G[idx].dir]] = idx;
}

void flushArr_Exit(){
    for(int i = 0; i <= R; ++i){
        for(int j = 0; j <= C; ++j){
            arr[i][j] = escape[i][j] = 0;
        }
    }
}

void bfs(int i, int j, int idx){
    fill(&visited[0][0], &visited[0][0] + 75 * 75, 0);

    queue<pair<int,int>> q;
    q.push({i, j});
    visited[i][j] = 1;
    int ny = i, nx = j;

    while(!q.empty()){
        int y = q.front().first, x = q.front().second;
        if(y == R) break;                   /// 크랙. 시간 줄이기....
        q.pop();

        for(int dir = 0; dir < 4; ++dir){
            int yy = y + dy[dir];
            int xx = x + dx[dir];
            if(yy < 1 || yy > R || xx < 1 || xx > C) continue;
            if(visited[yy][xx]) continue;
            if(arr[yy][xx] == 0) continue;      //

            if(arr[yy][xx] == arr[y][x]){
                q.push({yy, xx});
                visited[yy][xx] = 1;
                if(yy > ny){
                    ny = yy;
                    nx = xx;
                }
            }
            else if(escape[y][x] > 0){
                q.push({yy, xx});
                visited[yy][xx] = 1;
                if(ny > ny){
                    ny = yy;
                    nx = xx;
                }
            }
            
        }
    }

    lastPos[idx][0] = ny;
    lastPos[idx][1] = nx;
}

int main() {
    // Please write your code here.
    cin >> R >> C >> K;

    for(int run = 1; run <= K; ++run){
        int c, d;
        cin >> c >> d;
        G[run].y = -1;      G[run].x = c;       G[run].dir = d;

        moveGhost(run);

        if(G[run].y <= 1 || G[run].y >= R){
            flushArr_Exit();
            continue;
        }
        else{
            fillToArr(run);         //G[run].y x 같이고 4방향 fill.
            bfs(G[run].y, G[run].x, run);           // bfs() while(true) {break;} while 빠져나가는게 베스트.
        }
    }

    for(int i = 1; i <= K; ++i)
        sum += lastPos[i][0];
    
    cout << sum << '\n';
    return 0;
}