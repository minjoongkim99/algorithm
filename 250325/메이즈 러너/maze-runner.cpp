#include <iostream>
#include <cmath>
#include <tuple>
using namespace std;

int arr[12][12];        // 1-indexed,  x-y
struct player{
    int x, y, dist, died;
};
player P[12];

int sum = 0;
int n, m, k;
int exitX, exitY;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, 1, -1};

bool isFinished(){
    for(int idx = 1; idx <= m; ++idx)
        if(P[idx].died == 0) return false;
    return true;
}

void findExit(){
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            if(arr[i][j] == -1){
                exitX = i;
                exitY = j;
                return;
            }
}

void moveAllPlayers(){
    for(int idx = 1; idx <= m; ++idx){
        if(P[idx].died == 1) continue;

        int curDist = abs(P[idx].x - exitX) + abs(P[idx].y - exitY);
        int nx = -1, ny = -1;

        for(int dir = 0; dir < 4; ++dir){
            int xx = P[idx].x + dx[dir];
            int yy = P[idx].y + dy[dir];
            if(xx < 1 || xx > n || yy < 1 || yy > n) continue;
            if(arr[xx][yy] > 0) continue;

            int nxtDist = abs(xx - exitX) + abs(yy - exitY);   
            if(nxtDist < curDist){
                nx = xx;
                ny = yy;
                curDist = nxtDist;
            }
        }

        if(nx == -1 && ny == -1) continue;
        else{
            P[idx].x = nx;
            P[idx].y = ny;
            P[idx].dist++;
        }

        if(P[idx].x == exitX && P[idx].y == exitY){
            P[idx].died = 1;
        }
    }
}

bool isIn(int x1, int y1, int x2, int y2){
    int flag1 = 0, flag2 = 0;

    for(int i = x1; i <= x2; ++i){
        for(int j = y1; j <= y2; ++j){
            if(arr[i][j] == -1)
                flag1 = 1;
            for(int idx = 1; idx <= m; ++idx){
                if(P[idx].died == 1) continue;

                if(P[idx].x == i && P[idx].y == j)
                    flag2 = 1;
            }
        }
    }

    return ((flag1 == 1) && (flag2 == 1));
}

tuple<int,int,int> findPos(){
    for(int len = 0; len < n; ++len){
        for(int i = 1; i < n; ++i){
            for(int j = 1; j < n; ++j){
                if(i + len > n || j + len > n) continue;

                if(isIn(i, j, i + len, j + len)){
                    return{i, j, len + 1};
                }
            }
        }
    }

    return {0, 0, 0};
}

void rotateRight(int x, int y, int len){
    int tmp[12][12];
    for(int i = 0; i <= n; ++i)
        for(int j = 0; j <= n; ++j)
            tmp[i][j] = arr[i][j];

    for(int i = 0; i < len; ++i){
        for(int j = 0; j < len; ++j){
            arr[x + i][y + j] = tmp[x + len - j - 1][y + i];
            if(arr[x + i][y + j] > 0)
                arr[x + i][y + j]--;
        }
    }
}

void rotatePerson(int x, int y, int len){
    for(int idx = 1; idx <= m; ++idx){
        if(P[idx].died == 1) continue;
        int flag = 0;

        for(int i = 0 ; i < len; ++i){
            for(int j = 0; j < len; ++j){
                if(P[idx].x == x + len - j - 1 && P[idx].y == y + i){
                    P[idx].x = x + i;
                    P[idx].y = y + j;
                    flag = 1;
                    break;
                }
            }
            if(flag == 1) 
                break;
        }
    }
}

int main() {
    // Please write your code here.

    cin >> n >> m >> k;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            cin >> arr[i][j];

    for(int idx = 1; idx <= m; ++idx){
        cin >> P[idx].x >> P[idx].y;
        P[idx].dist = P[idx].died = 0;
    }
    cin >> exitX >> exitY;
    arr[exitX][exitY] = -1;

    for(int run = 1; run <= k; ++run){
        if(isFinished())
            break;

        findExit();

        moveAllPlayers();

        int posX = 0, posY = 0, len = 0;
        tie(posX, posY, len) = findPos();

        rotateRight(posX, posY, len);

        rotatePerson(posX, posY, len);
    }
    findExit();

    for(int i = 1; i <= m; ++i)
        sum += P[i].dist;

    cout << sum << '\n' << exitX << ' ' << exitY << '\n';   // 모든 참가자들의 이동거리 합과 출구 좌표 출력하기.
    return 0;
}