#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int m, t;
int py, px;

int ddy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int ddx[8] = {0, -1, -1, -1, 0, 1, 1, 1};

int arr[7][7];
int died_map[7][7];

struct monster{
    int y, x, dir, died;
};

vector<monster> mon;
vector<monster> egg;

int ans = 0;

void showDiedMap(){
    cout << "DIED_MAP\n";
    for(int i = 1; i <= 4; ++i){
        for(int j = 1; j <= 4; ++j){
            cout << died_map[i][j] << '\t';
        }
        cout << "\n";
    }
}

void printMon(){
    cout << "MONSTER\n";
    for(int i = 0; i < mon.size(); ++i){
        if(mon[i].died == 1){
            cout << "IDX" << i << " IS DIED\n";
        }
        else cout << "IDX" << i << " POS:" << mon[i].y << "," << mon[i].x << " DIR:" << mon[i].dir << "\n"; 
    }
}
void printEgg(){
    cout << "EGG\n";
    for(int i = 0; i < egg.size(); ++i){
        if(egg[i].died == 1) continue;
        cout << "IDX" << i << " POS:" << egg[i].y << "," << egg[i].x << " DIR:" << egg[i].dir << "\n"; 
    }
}

void makeEgg(){
    for(int i = 0; i < mon.size(); ++i){
        if(mon[i].died == 1) continue;
        egg.push_back(mon[i]);
    }
}

void moveMonster(){
    for(int i = 0; i < mon.size(); ++i){
        if(mon[i].died == 1) continue;

        int ny = mon[i].y;
        int nx = mon[i].x;
        int ndir = mon[i].dir;

        for(int dir = mon[i].dir; dir < mon[i].dir + 8; ++dir){
            int d = dir % 8;

            int yy = mon[i].y + ddy[d];
            int xx = mon[i].x + ddx[d];

            if(yy < 1 || yy > 4 || xx < 1 || xx > 4) continue;
            if(yy == py && xx == px) continue;
            if(died_map[yy][xx] > 0) continue;

            ny = yy;     nx = xx;       ndir = d;
            break;
        }

        mon[i].y = ny;
        mon[i].x = nx;
        mon[i].dir = ndir;
    }
}

void decrease(){
    for(int i = 1; i <= 4; ++i){
        for(int j = 1; j <= 4; ++j){
            if(died_map[i][j] > 0)
                died_map[i][j]--;
        }
    }
}

int check(int y1, int x1, int y2, int x2, int y3, int x3){
    int cnt = 0;
    for(int i = 0; i < mon.size(); ++i){
        if(mon[i].died == 1) continue;
        if(mon[i].y == y1 && mon[i].x == x1){
            cnt++;
        }
        else if(mon[i].y == y2 && mon[i].x == x2){
            cnt++;
        }
        else if(mon[i].y == y3 && mon[i].x == x3){
            cnt++;
        }
    }
    return cnt;
}

void attack(int y1, int x1, int y2, int x2, int y3, int x3){
    int cnt = 0;
    for(int i = 0; i < mon.size(); ++i){
        if(mon[i].died == 1) continue;
        if(mon[i].y == y1 && mon[i].x == x1){
            died_map[y1][x1] = 2;
            mon[i].died = 1;
        }
        else if(mon[i].y == y2 && mon[i].x == x2){
            died_map[y2][x2] = 2;
            mon[i].died = 1;
        }
        else if(mon[i].y == y3 && mon[i].x == x3){
            died_map[y3][x3] = 2;
            mon[i].died = 1;
        }
    }
}
/*
    3.팩맨이동
    팩맨은 가장 많이 먹을 수 있는 방안을 찾는다. 총 3칸 움직이며 상좌하우의 우선순위를 가진다. OOB는 존재하지 않는다.
    팩맨은 알을 먹지 않고, 움직이기 전에 있던 몬스터 안먹음 이동하는 과정에서만 먹음
*/
void movePacman(){
    int ny1 = 0, nx1 = 0, ny2 = 0, nx2 = 0, ny3 = 0, nx3 = 0;
    int cnt = -1;

    for(int i = 0; i < 8; i = i + 2){
        int y1 = py + ddy[i];
        int x1 = px + ddx[i];
        if(y1 < 1 || y1 > 4 || x1 < 1 || x1 > 4) continue;

        for(int j = 0; j < 8; j = j + 2){
            int y2 = y1 + ddy[j];
            int x2 = x1 + ddx[j];
            if(y2 < 1 || y2 > 4 || x2 < 1 || x2 > 4) continue;

            for(int k = 0; k < 8; k = k + 2){
                int y3 = y2 + ddy[k];
                int x3 = x2 + ddx[k];
                if(y3 < 1 || y3 > 4 || x3 < 1 || x3 > 4) continue;

                int val = check(y1, x1, y2, x2, y3, x3);
                if(val > cnt){
                    cnt = val;
                    ny1 = y1, nx1 = x1;
                    ny2 = y2, nx2 = x2;
                    ny3 = y3, nx3 = x3;

                }
            }

        }
    }

    attack(ny1, nx1, ny2, nx2, ny3, nx3);
    py = ny3;
    px = nx3;
}

void eggToMon(){
    for(int i = 0; i < egg.size(); i++){
        mon.push_back(egg[i]);
    }
    egg.clear();
}

int main() {
    // Please write your code here.

    int T = 1;
    for(int test_case = 1; test_case <= T; ++test_case){
        // global_init();

        cin >> m >> t;
        cin >> py >> px;
        for(int i = 1; i <= m; ++i){
            int y, x, dir;
            cin >> y >> x >> dir;
            mon.push_back({y, x, dir - 1, 0});
        }

        for(int run = 1; run <= t; ++run){
            //local_init();
        
            makeEgg();
            //printMon();

            moveMonster();
            //printMon();

            decrease();

            movePacman();
            //printMon();

            eggToMon();

            //cout << "[------]\n";
        }

        for(int i = 0; i < mon.size(); ++i){
            if(mon[i].died == 0)
                ans++;
        }
        cout << ans << '\n';

    }
    return 0;
}