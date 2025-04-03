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

void showR(){
    cout << ry << "," << rx << " DIR:" << rdir << '\n';
}

void showSanta(){
    for(int idx = 1; idx <= p; ++idx){
        if(S[idx].died) cout << "IDX" << idx << " IS DIED\n";
        else cout << "IDX:" << idx << " " << S[idx].y << " " << S[idx].x << "\n";
    }
}

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

//루돌프의 움직임.
//거리 가장 가까운 산타(단 탈락하지 않은)
//거 같, 행큰, 열큰으로. 8방향으로 이동 가능하며, 우선순위가 높은 산타를 향해 가장 가까워지는 방향.
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

    //cout << "TAGET:" << target << '\n';
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
        int nxt = santa_map[yy][xx];
        santa_map[yy][xx] = pre;
        pre = nxt;
    }
}
/*
충돌.
산타와 루돌프가 같은 칸이면 충돌 발생
루돌프가 충돌을 일으키면 C만큼 산타가 점수를 얻고, C만큼 밀려남
산타가 충돌을 일으킨다면 D만큼 산타가 점수를 얻고, D만큼 반대방향으로 밀려남
포물선 충돌
OOB이면 탈락
밀려난 칸에 누가 있으면 상호작용 발생*/
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

/*
산타 움직임.
1~P. 순서대로 움직인다.
기절하거나 탈락하면 움직이지 않음.
루돌프에게 가장 가까워지는 방향으로 1칸 이동
다른 산타가 있거나, 게임판 밖으로는 이동이 불가하다.
움직일 수 없다면 움직이지 않는다.
루돌프와 가까워 지지않으면 움직이지 않는다.
산타는 4방향 dydx이고 상우하좌.*/
bool isIn(int idx, int y, int x){
    for(int i = 1; i <= p; ++i){
        if(S[i].died == 1 || i == idx) continue;
        if(S[i].y == y && S[i].x == x){
            //cout << "TTTTTTT\n";
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
    //cout << "IDX" << idx << " NEXT POS:" << S[idx].y << "," << S[idx].x << '\n';
}

void moveSantas(){
    for(int idx = 1; idx <= p; ++idx){
        if(S[idx].died == 1 || S[idx].stop > 0) continue;
        moveSanta(idx);
        int flag = checkConflict();
        if(flag > 0){
            //cout << flag << "BY 산타\n";
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
        //showSanta();
        for(int run = 1; run <= m; ++run){
            //cout << "RUN" << run << '\n';
            if(canBreak())
                break;

            rMove();
            //showR();

            int flag = checkConflict();
            if(flag > 0){
                //cout << flag << "BY 루돌프\n";
                conflict(flag, c, rdir);
            }

            moveSantas();
            //showSanta();

            decreaseStop();

            increasePoint();
        }

        for(int idx = 1; idx <= p; ++idx){
            cout << S[idx].point << ' ';
        }

    }
    return 0;
}

/*1~P번 산타 이동.
N*N 격자 1-indexed
M번 턴에 걸쳐 루돌프 한 번 움직이고 1~P 산타 순서대로 움직임. (단, 기절하거나 격자 밖으로 나간 산타 움직임 불가)
거리는 유클리드 거리로 계산

루돌프의 움직임.
거리 가장 가까운 산타(단 탈락하지 않은)
거 같, 행큰, 열큰으로. 8방향으로 이동 가능하며, 우선순위가 높은 산타를 향해 가장 가까워지는 방향.

산타 움직임.
1~P. 순서대로 움직인다.
기절하거나 탈락하면 움직이지 않음.
루돌프에게 가장 가까워지는 방향으로 1칸 이동
다른 산타가 있거나, 게임판 밖으로는 이동이 불가하다.
움직일 수 없다면 움직이지 않는다.
루돌프와 가까워 지지않으면 움직이지 않는다.
산타는 4방향 dydx이고 상우하좌.

충돌.
산타와 루돌프가 같은 칸이면 충돌 발생
루돌프가 충돌을 일으키면 C만큼 산타가 점수를 얻고, C만큼 밀려남
산타가 충돌을 일으킨다면 D만큼 산타가 점수를 얻고, D만큼 반대방향으로 밀려남
포물선 충돌
OOB이면 탈락
밀려난 칸에 누가 있으면 상호작용 발생

상호작용.
연쇄적으로 1칸씩 해당방향으로 밀리고
밖으로 밀려나는 산타는 탈락함

기절.
루돌프와 충돌한 산타는 k턴, k+1턴 기절, k+2면 정상
*/