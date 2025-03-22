#include <iostream>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;

int N, M;
int sy, sx, ey, ex;
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};

int arr[51][51];
int visited[51][51];
int pre[51][51][2];
int nextStep[51][51][2];

struct knight{
    int y, x, dist, stop, died;
};
knight K[305];

int distSum, stoneCnt, attackCnt;

void showKnight(){
    for(int idx = 1; idx <= M; ++idx){
        cout << idx << ": " << K[idx].y << "," << K[idx].x << "\n";
    }
}

void showArr(){
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            cout << arr[i][j] << '\t';
        }
        cout << '\n';
    }
}

void local_init(){
    distSum = stoneCnt = attackCnt = 0;
}

void bfs(){
    queue<pair<int,int>> q;
    q.push({sy, sx});
    visited[sy][sx] = 1;
    pre[sy][sx][0] = pre[sy][sx][1] = -1;

    while(!q.empty()){
        int y = q.front().first, x = q.front().second;
        if(y == ey && x == ex) break;
        q.pop();

        for(int dir = 0; dir < 4; ++dir){
            int yy = y + dy[dir];
            int xx = x + dx[dir];
            if(yy < 0 || yy >= N || xx < 0 || xx >= N) continue;
            if(visited[yy][xx]) continue;
            if(arr[yy][xx] == 1) continue;
            q.push({yy, xx});
            visited[yy][xx] = visited[y][x] + 1;
            pre[yy][xx][0] = y;
            pre[yy][xx][1] = x; 
        }
    }
}

void medusaPath(){
    int cy = ey;
    int cx = ex;

    while(true){
        int ny = pre[cy][cx][0];
        int nx = pre[cy][cx][1];

        if(ny == -1 && nx == -1){
            break;
        }
        nextStep[ny][nx][0] = cy;
        nextStep[ny][nx][1] = cx;

        cy = ny;
        cx = nx;
    }
}

void moveM(){
    int ny = nextStep[sy][sx][0];
    int nx = nextStep[sy][sx][1];

    sy = ny;
    sx = nx;
}

void killKnight(){
    for(int idx = 1; idx <= M; ++idx){
        if(K[idx].died == 1) continue;
        if(K[idx].y == sy && K[idx].x == sx){
            K[idx].died =1;
        }
    }
}

void moveK(){
    for(int i = 1; i <= M; ++i){
        if(K[i].died == 1) continue;

        int ny = K[idx].y, nx = K[idx].x;
        int curDist = abs(sy - K[idx].y) + abs(sx - K[idx].x);

        for(int dir = 0; dir < 4; ++dir){
            int yy = K[idx].y + dy[dir];
            int xx = K[idx].x + dx[dir];

            if(yy < 0 || yy >= N || xx < 0 || xx >= N) continue;


        }
    }
}

void medusaSight(){

}

void attackMedusa(){

}

void input(){
    cin >> N >> M;
    cin >> sy >> sx >> ey >> ex;
    for(int i = 1; i <= M; ++i){
        cin >> K[i].y >> K[i].x;
        K[i].stop = K[i].dist = K[i].died = 0;
    }

    for(int i = 0; i < N; ++i)
        for(int j = 0; j < N; ++j)
            cin >> arr[i][j];   
}

int main() {
    // Please write your code here.

    int T = 1;
    for(int test_case = 1; test_case <= T; ++test_case){
        //global_init();

        input();

        int t = 0;

        bfs();
        if(visited[ey][ex] == 0){
            cout << -1 << '\n';
        }
        else{
            medusaPath();

            while(t < 10){
                distSum = stoneCnt = attackCnt = 0;

                moveM();
                killKnight();

                cout << "MEDUSA: " << sy << " and " << sx << "!\n";

                if(sy == ey && sx == ex){
                    cout << 0 << '\n';
                    break;
                }

                medusaSight();

                moveK();

                attackMedusa();
            
                //cout << distSum << ' ' << stoneCnt << ' ' << attackCnt << '\n';
                t++;
            }
        }
    }
    return 0;
}