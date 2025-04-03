#include <iostream>
#include <algorithm>
using namespace std;

int n, m, p, c, d;
int ddy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int ddx[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int ry, rx, rdir;

struct santa{
    int y, x, dir, point, stop, died;
};
santa S[32];
int santa_map[55][55];

int getDistance(int y1, int x1, int y2, int x2){
    return (y1 - y2) * (y1 - y2) + (x1 - x2) * (x1 - x2);
}

bool canBreak(){
    for(int idx = 1; idx <= p; ++idx){
        if(S[idx].died == 0) return false;
    }
    return true;
}

int checkConflict(){
    for(int idx = 1; idx <= p; ++idx){
        if(S[idx].died == 1) continue;
        if(ry == S[idx].y && rx == S[idx].x)
            return idx;
    }
    return 0;
}

void rMove(){
    int ny = ry, nx = rx, ndir = rdir;
    int target = 0;
    int cur_dist = 100000000;
    
    for(int idx = 1; idx <= p; ++idx){
        if(S[idx].died == 1) continue;
        int next_dist = getDistance(ry, rx, S[idx].y, S[idx].x);
        if(cur_dist > next_dist){
            cur_dist = next_dist;
            target = idx;
            ny = S[idx].y;
            nx = S[idx].x;
        }
        else if(cur_dist == next_dist){
            if(S[idx].y > ny){
                target = idx;
                ny = S[idx].y;
                nx = S[idx].x;
            }
            else if(S[idx].y == ny){
                if(S[idx].x > nx){
                    target = idx;
                    ny = S[idx].y;
                    nx = S[idx].x;
                }
            }
        }
    }

    cur_dist = getDistance(ry, rx, S[target].y, S[target].x);

    for(int dir = 0; dir < 8; ++dir){
        int yy = ry + ddy[dir];
        int xx = rx + ddx[dir];
        if(yy < 1 || yy > n || xx < 1 || xx > n) continue;
        int next_dist = getDistance(yy, xx, S[target].y, S[target].x);
        if(cur_dist > next_dist){
            cur_dist = next_dist;
            ny = yy;
            nx = xx;
            ndir = dir;
        }
    }
    
    ry = ny, rx = nx, rdir = ndir;
}

void makeSantaMap(){
    fill(&santa_map[0][0], &santa_map[0][0] + 55 * 55, 0);
    for(int idx = 1; idx <= p; ++idx){
        if(S[idx].died == 1) continue;
        santa_map[S[idx].y][S[idx].x] = idx;
    }
}

void updateSantaPos(){
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            if(santa_map[i][j] > 0){
                S[santa_map[i][j]].y = i;
                S[santa_map[i][j]].x = j;
            } 
        }
    }
}

void interaction(int idx, int y, int x, int dir){
    int pre = idx;
    santa_map[ry][rx] = 0;
    
    for(int len = 0; len <= n; ++len){
        int yy = y + len * ddy[dir];
        int xx = x + len * ddx[dir];
        if(yy < 1 || yy > n || xx < 1 || xx > n){
            S[pre].died = 1;
            break;
        }
        ///////////////////////////////////////////////
        if(santa_map[yy][xx] == 0){
            santa_map[yy][xx] = pre;
            break;
        }
        ///////////////////////////////////////////////
        int nxt = santa_map[yy][xx];
        santa_map[yy][xx] = pre;
        pre = nxt;
    }
}

void conflict(int idx, int point, int dir){
    S[idx].point += point;

    makeSantaMap();

    int ny = S[idx].y + point * ddy[dir];
    int nx = S[idx].x + point * ddx[dir];
    if(ny < 1 || ny > n || nx < 1 || nx > n){
        S[idx].died = 1;
        return;
    }
    if(santa_map[ny][nx] == 0){
        santa_map[S[idx].y][S[idx].x] = 0;
        santa_map[ny][nx] = idx;
    }
    else if(santa_map[ny][nx] > 0){
        interaction(idx, ny, nx, dir);
    }

    S[idx].stop = 2;

    updateSantaPos();
}

bool isIn(int idx, int y, int x){
    for(int i = 1; i <= p; ++i){
        if(S[i].died == 1 || i == idx) continue;
        if(S[i].y == y && S[i].x == x){
            return true;
        }
    }
    return false;
}

void moveSanta(int idx){
    int ny = S[idx].y, nx = S[idx].x, ndir = S[idx].dir;
    int cur_dist = getDistance(ry, rx, S[idx].y, S[idx].x);

    for(int dir = 0; dir < 8; dir = dir + 2){
        int yy = S[idx].y + ddy[dir];
        int xx = S[idx].x + ddx[dir];
        if(yy < 1 || yy > n || xx < 1 || xx > n) continue;
        if(isIn(idx, yy, xx)) continue;

        int next_dist = getDistance(ry, rx, yy, xx);
        if(cur_dist > next_dist){
            cur_dist = next_dist;
            ny = yy;
            nx = xx;
            ndir = dir;
        }
    }

    S[idx].y = ny, S[idx].x = nx, S[idx].dir = ndir;
}

void moveSantas(){
    for(int idx = 1; idx <= p; ++idx){
        if(S[idx].died == 1 || S[idx].stop > 0) continue;
        moveSanta(idx);
        int flag = checkConflict();
        if(flag > 0){
            conflict(idx, d, (S[idx].dir + 4) % 8);
        }
    }
}

void decreaseStop(){
    for(int idx = 1; idx <= p; ++idx){
        if(S[idx].died == 1) continue;
        if(S[idx].stop > 0)
            S[idx].stop--;
    }
}

void increasePoint(){
    for(int idx = 1; idx <= p; ++idx){
        if(S[idx].died == 1) continue;
        S[idx].point++;
    }
}

void input(){
    cin >> n >> m >> p >> c >> d;
    cin >> ry >> rx;
    for(int i = 1; i <= p; ++i){
        int idx;
        cin >> idx;
        cin >> S[idx].y >> S[idx].x;
    }
}

int main() {
    // Please write your code here.

    int T = 1;
    for(int tc = 1; tc <= T; ++tc){
        // global_init();

        input();

        for(int run = 1; run <= m; ++run){

            if(canBreak())
                break;

            rMove();

            int flag = checkConflict();
            if(flag > 0){
                conflict(flag, c, rdir);
            }

            moveSantas();

            decreaseStop();

            increasePoint();
        }

        for(int idx = 1; idx <= p; ++idx){
            cout << S[idx].point << ' ';
        }

    }
    return 0;
}
