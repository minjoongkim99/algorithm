#include <iostream>
using namespace std;

int arr[75][75];
int escape[75][75];

struct ghost{
    int y, x, dir;
};
ghost G[1002];
int lastPos[1002][2];

int R, C, K;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

bool canDown(int idx){
    int y1 = G[idx].y + 2, x1 = G[idx].x;
    int y2 = G[idx].y + 1, x2 = G[idx].x - 1;
    int y3 = G[idx].y + 1, x3 = G[idx].x + 1;
    if(arr[y1][x1] || arr[y2][x2] || arr[y3][x3]) return false;
    if(y1 < 1 || y1 > n || x1 < 1 || x1 > n) return false;
    if(y2 < 1 || y2 > n || x2 < 1 || x2 > n) return false;
    if(y3 < 1 || y3 > n || x3 < 1 || x3 > n) return false;

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
    int y5 = G[idx].y + 2, x3 = G[idx].x - 1;

    if(arr[y1][x1] || arr[y2][x2] || arr[y3][x3] || arr[y4][x4] || arr[y5][x5]) return false;
    if(y1 < 1 || y1 > n || x1 < 1 || x1 > n) return false;
    if(y2 < 1 || y2 > n || x2 < 1 || x2 > n) return false;
    if(y3 < 1 || y3 > n || x3 < 1 || x3 > n) return false;
    if(y3 < 1 || y3 > n || x3 < 1 || x3 > n) return false;

    return true;
}

void moveLeft(int idx){
    G[idx].y++;
    G[idx].x--;
}

bool canRight(int idx){

}

void moveRight(int idx){
    G[idx].y++;
    G[idx].x++;
}

void moveGhost(int idx){
    int flag = 1;
    while(flag == 1){
        flag = 0;

        if(canDown()){
            flag = 1;
            moveDown();
        }
        else if(canLeft()){
            flag = 1;
            moveLeft();
        }
        else if(canRight()){
            flag = 1;
            moveRight();
        }
    }
}

void flushArr_Exit(){
    for(int i = 0; i <= R; ++i){
        for(int j = 0; j <= C; ++j){
            arr[i][j] = escape[i][j] = 0;
        }
    }
}

int main() {
    // Please write your code here.

    cin >> R >> C >> K;
    for(int idx = 1; idx <= K; ++idx){
        int c, d;
        cin >> c >> d;
        G[idx].y = -1;
        G[idx].x = c;
        G[idx].dir = d;
    }

    for(int run = 1; run <= K; ++run){
        //moveGhost(run);

        if(G[run].y <= 1 || G[run].y >= R){
            flushArr_Exit();
            continue;
        }
        else{
            // fillToArr(run); G[run].y x 같이고 4방향 fill.
            bfs(G[run].y, G[run].x);
        }

    }
    return 0;
}