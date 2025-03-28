#include <iostream>
#include <algorithm>
using namespace std;

int n, m, p, c, d;

int ddy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int ddx[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int ry, rx, rdir;
struct santa{
    int y, x, dir, stop, died, point;
};
santa S[32];
int arr[52][52];

void showR(){
    cout << ry << "and" << rx << " DIR:" << rdir << '\n';
}

void showSanta(){
    for(int idx = 1; idx <= p; ++idx){
        if(S[idx].died == 1) 
            cout << "IDX" << idx << " IS DIED\n";
        else cout << "IDX" << idx << " " << S[idx].y << "," << S[idx].x << "\n";
    }
}

void showArr(){
    cout << "This is SANTA MAP\n";
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            cout << arr[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

void santaToArr(){
    fill(&arr[0][0], &arr[0][0] + 52 * 52, 0);
    
    for(int idx = 1; idx <= p; ++idx){
        if(S[idx].died == 1) continue;
        arr[S[idx].y][S[idx].x] = idx;
    }
}

void arrToSanta(){
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            if(arr[i][j] > 0){
                S[arr[i][j]].y = i;
                S[arr[i][j]].x = j;
            }
        }
    }
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
        if(S[idx].y == ry && S[idx].x == rx)
            return idx;
    }

    return 0;
}

void rMove(){
    int ndir = rdir;
    int ny = ry, nx = rx;
    int target = 0;

    int cur_dist = 100000000;

    for(int dir = 0; dir < 8; ++dir){
        int yy = ry + ddy[dir];
        int xx = rx + ddx[dir];

        if(yy < 1 || yy > n || xx < 1 || xx > n) continue;

        for(int idx = 1; idx <= p; ++idx){
            if(S[idx].died == 1) continue;
            int next_dist = (S[idx].y - yy) * (S[idx].y - yy) + (S[idx].x - xx) * (S[idx].x - xx);

            if(cur_dist > next_dist){
                cur_dist = next_dist;
                ny = yy;
                nx = xx;
                ndir = dir;
                target = idx;
            }
            else if(cur_dist == next_dist){
                if(S[idx].y > S[target].y){
                    ny = yy;
                    nx = xx;
                    ndir = dir;
                    target = idx;
                }
                else if(S[idx].y == S[target].y){
                    if(S[idx].x > S[target].x){
                        ny = yy;
                        nx = xx;
                        ndir = dir;
                        target = idx;
                    }
                }
            }
        }
    }
    ry = ny;
    rx = nx;
    rdir = ndir;
}

bool isThere(int target, int y, int x){
    for(int idx = 1; idx <= p; ++idx){
        if(S[idx].died == 1) continue;
        if(idx == target) continue;
        if(S[idx].y == y && S[idx].x == x)
            return true;
    }
    return false;
}

void sMove(int idx){
    int ny = S[idx].y;
    int nx = S[idx].x;
    int ndir = S[idx].dir;
    int cur_dist = (ry - S[idx].y) * (ry - S[idx].y) + (rx - S[idx].x) * (rx - S[idx].x);
    
    for(int dir = 0; dir < 8; dir = dir + 2){
        int yy = S[idx].y + ddy[dir];
        int xx = S[idx].x + ddx[dir];

        if(yy < 1 || yy > n || xx < 1 || xx > n) continue;
        if(isThere(idx, yy, xx)) continue;

        int next_dist = (ry - yy) * (ry - yy) + (rx - xx) * (rx - xx);
        if(cur_dist > next_dist){
            cur_dist = next_dist;
            ny = yy;
            nx = xx;
            ndir = dir;
        }
    }
    S[idx].y = ny;
    S[idx].x = nx;
    S[idx].dir = ndir;
}



void interaction(int target, int y, int x, int dir){
    santaToArr();
    //cout << "상호작용 전\n";
    //showArr();

    arr[ry][rx] = 0;
    int pre = target;
    for(int len = 0; len < n; ++len){

        int yy = y + len * ddy[dir];
        int xx = x + len * ddx[dir];
        if(yy < 1 || yy > n || xx < 1 || xx > n){
            S[pre].died = 1;
            break;
        }
        if(arr[yy][xx] == 0){
            arr[yy][xx] = pre;
            break;
        }
        else{
            int next = arr[yy][xx];
            arr[yy][xx] = pre;
            pre = next;
        }

    }    
    arrToSanta();
    //cout << "상호작용 후\n";
    //showArr();
}

void conflict(int target, int point, int dir){
    //cout << "충돌\n";
    //showSanta();
    santaToArr();

    S[target].point += point;

    int yy = S[target].y + point * ddy[dir];
    int xx = S[target].x + point * ddx[dir];

    if(yy < 1 || yy > n || xx < 1 || xx > n){
        arr[S[target].y][S[target].x] = 0;
        S[target].died = 1;
        return;
    }

    if(isThere(target, yy, xx)){
        interaction(target, yy, xx, dir);
    }
    else{
        arr[S[target].y][S[target].x] = 0;
        S[target].y = yy;
        S[target].x = xx;
    }
    S[target].stop = 2;
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

int main() {
    // Please write your code here.

    int T = 1;
    for(int test_case = 1; test_case <= T; ++test_case){
        // global_init();

        cin >> n >> m >> p >> c >> d;
        cin >> ry >> rx;
        for(int i = 1; i <= p; ++i){
            int idx;
            cin >> idx;
            cin >> S[idx].y >> S[idx].x;
        }

        for(int run = 1; run <= m; ++run){

            santaToArr();
            //showArr();

            if(canBreak()){
                break;
            }

            rMove();
 
            int target = checkConflict();
            if(target > 0){
                conflict(target, c, rdir);
            }


            for(int idx = 1; idx <= p; ++idx){
                if(S[idx].died == 1) continue;
                if(S[idx].stop > 0) continue;

                sMove(idx);
                target = checkConflict();
                if(target > 0){
                    conflict(target, d, (S[target].dir + 4) % 8);
                }

            }

            decreaseStop();

            increasePoint();
            // 움직임 다 끝나고 받아와야할 듯?
        }

        for(int i = 1; i <= p; ++i){
            cout << S[i].point << ' ';
        }
        cout << '\n';
    }
    return 0;
}