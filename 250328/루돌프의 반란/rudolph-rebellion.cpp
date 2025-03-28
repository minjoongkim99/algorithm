#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int n, m, p, c, d;      // 격자크기, 턴 수, 산타 수, 루돌프 힘, 산타 힘

pair<int,int> monster;
int monsterDir = 0;

struct santa{
    int y, x, dir, point, died, stun;
};
santa S[32];
int arr[52][52];

int ddy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int ddx[8] = {0, 1, 1, 1, 0, -1, -1, -1};

void moveToArr(){
    for(int idx = 1; idx <= p; idx++){
        if(S[idx].died == 1) continue;
        arr[S[idx].y][S[idx].x] = idx;
    }
}

void moveToVec(){
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(arr[i][j] == 0) continue;
            S[arr[i][j]].y = i;
            S[arr[i][j]].x = j;
        }
    }
    fill(&arr[0][0], &arr[0][0] + 52 * 52, 0);
}

void monsterMove(){
    int distance = 1000000;
    int target = 0;
    for(int i = 1; i <= p; i++){
        if(S[i].died == 1) continue;
        int d = (monster.first - S[i].y) * (monster.first - S[i].y) + (monster.second - S[i].x) * (monster.second - S[i].x);
        if(distance > d){
            distance = d;
            target = i;
        }
        else if(distance == d){
            if(S[i].y > S[target].y){
                target = i;
            }
            else if(S[i].y == S[target].y){
                if(S[i].x > S[target].x){
                    target = i;
                }

            }
        }
    }

    distance = 1000000;
    int ny = 0, nx = 0, ndir = 0;
    for(int dir = 0; dir < 8; dir++){
        int yy = monster.first + ddy[dir];
        int xx = monster.second + ddx[dir];
        if(yy < 1 || yy > n || xx < 1 || xx > n) continue;

        int d = (yy - S[target].y) * (yy - S[target].y) + (xx - S[target].x) * (xx - S[target].x);
        if(distance > d){
            distance = d;
            ny = yy;
            nx = xx;
            ndir = dir;
        }
    }
    monster.first = ny;     monster.second = nx;    monsterDir = ndir;
}

bool isThere(int idx, int y, int x){
    for(int i = 1; i <= p; i++){
        if(S[i].died == 1) continue;
        if(i == idx) continue;
        if(S[i].y == y && S[i].x == x) return true;
    }
    return false;
}
void moveSanta(int idx){
    int distance = (monster.first - S[idx].y) * (monster.first - S[idx].y) + (monster.second - S[idx].x) * (monster.second - S[idx].x);
    int ny = S[idx].y, nx = S[idx].x, ndir = S[idx].dir;            //

    for(int dir = 0; dir < 8; dir = dir + 2){
        int yy = S[idx].y + ddy[dir];
        int xx = S[idx].x + ddx[dir];
        if(yy < 1 || yy > n || xx < 1 || xx > n) continue;
        if(isThere(idx, yy, xx)) continue;
        int d = (monster.first - yy) * (monster.first - yy) + (monster.second - xx) * (monster.second - xx);
        if(distance > d){
            distance = d;
            ny = yy;
            nx = xx;
            ndir = dir;
        }
    }
    S[idx].y = ny;  S[idx].x = nx;  S[idx].dir = ndir;
}

int checkConflict(){
    for(int idx = 1; idx <= p; idx++){
        if(S[idx].died == 1) continue;
        if(S[idx].y == monster.first && S[idx].x == monster.second) return idx;
    }
    return 0;
}

bool canEnd(){
    for(int i = 1; i <= p; i++)
        if(S[i].died == 0) return false;
    return true;
}

void interaction(int idx, int dir, int i, int j){
    int cy = i, cx = j;
    int val = arr[i][j];
    int next_val = 0;
    while(true){
        int ny = cy + ddy[dir];
        int nx = cx + ddx[dir];
        if(ny < 1 | ny > n || nx < 1 || nx > n){
            S[val].died = 1;
            break;
        }
        else if(arr[ny][nx] == 0){
            arr[ny][nx] = val;
            break;
        }
        else if(arr[ny][nx] > 0){
            next_val = arr[ny][nx];
            arr[ny][nx] = val;
        }
        cy = ny;
        cx = nx;
        val = next_val;
    }

    arr[i][j] = idx;
}

void conflict(int idx, int point, int dir){
    S[idx].point += point;
    
    int ny = S[idx].y + point * ddy[dir];
    int nx = S[idx].x + point * ddx[dir];
    if(ny < 1 || ny > n || nx < 1 || nx > n){
        S[idx].died = 1;
        arr[S[idx].y][S[idx].x] = 0;
        return;
    }
    else if(arr[ny][nx] == 0){
        arr[ny][nx] = idx;
        arr[S[idx].y][S[idx].x] = 0;
    }
    else if(arr[ny][nx] > 0){
        interaction(idx, dir, ny, nx);
        arr[S[idx].y][S[idx].x] = 0;
    }

    S[idx].stun = 2;
}

void decreaseStun(){
    for(int i = 1; i <= p; i++){
        if(S[i].died == 1) continue;
        if(S[i].stun > 0)
            S[i].stun--;
    }
}

void increasePoint(){
    for(int i = 1; i <= p; i++){
        if(S[i].died == 1) continue;
        S[i].point++;
    }
}

int main() {
    // 여기에 코드를 작성해주세요.

    cin >> n >> m >> p >> c >> d;           // 1 - indexed
    cin >> monster.first >> monster.second;
    for(int i = 1; i <= p; i++){    
        int idx;
        cin >> idx;
        cin >> S[idx].y >> S[idx].x;
    }

    for(int t = 1; t <= m; t++){
        monsterMove();

        int flag = checkConflict();
        if(flag > 0){
            moveToArr();
            conflict(flag, c, monsterDir);
            moveToVec();
        }
        for(int idx = 1; idx <= p; idx++){
            if(S[idx].died == 1) continue;
            if(S[idx].stun > 0) continue;
            moveSanta(idx);
            flag = checkConflict();
            if(flag > 0){
                moveToArr();
                conflict(flag, d, (S[idx].dir + 4) % 8);
                moveToVec();
            }
        }

        decreaseStun();

        if(canEnd())
            break;

        increasePoint();
    }

    for(int idx = 1; idx <= p; idx++){
        cout << S[idx].point << ' ';
    }
    return 0;
}
