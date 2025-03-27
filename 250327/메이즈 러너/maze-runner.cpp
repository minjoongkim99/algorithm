#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int n, m, k;
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};

int arr[12][12]; // WALL, EXIT, EMPTY
int player_map[12][12];

struct player{
    int y, x, dist, died;
};
player P[12];

int len, ry, rx;
int ey, ex;

int point = 0;
void showArr(){
    cout << "ARR\n";
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            cout << arr[i][j] << ' ';
        }
        cout << "\n";
    }
}

void showPlayer(){
    cout << "PLAYER_MAP\n";
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            cout << player_map[i][j] << ' ';
        }
        cout << "\n";
    }
}

bool canBreak(){
    for(int idx = 1; idx <= m; ++idx)
        if(P[idx].died == 0)
            return false;
    return true;
}

void moveRunner(){
    for(int idx = 1; idx <= m; ++idx){
        if(P[idx].died == 1) continue;

        int ny = P[idx].y;
        int nx = P[idx].x;
        int cur_dist = abs(ey - P[idx].y) + abs(ex - P[idx].x);
        int flag = 0;

        for(int dir = 0; dir < 4; ++dir){
            int yy = P[idx].y + dy[dir];
            int xx = P[idx].x + dx[dir];
            if(yy < 1|| yy > n || xx < 1 || xx > n) continue;
            if(arr[yy][xx] > 0) continue;

            int next_dist = abs(ey - yy) + abs(ex - xx);
            if(cur_dist > next_dist){
                cur_dist = next_dist;
                ny = yy;
                nx = xx;
                flag = 1;
            }
        }

        if(flag == 1){
            P[idx].dist++;
        }

        P[idx].y = ny;
        P[idx].x = nx;
        if(P[idx].y == ey && P[idx].x == ex){
            P[idx].died = 1;
        }
    }
}

void playerToArr(){
    fill(&player_map[0][0], &player_map[0][0] + 12 * 12, 0);
    for(int idx = 1; idx <= m; ++idx){
        if(P[idx].died == 1) continue;
        player_map[P[idx].y][P[idx].x] = idx;
    }
}

bool isIn(int y1, int x1, int y2, int x2){
    int flag1 = 0, flag2 = 0;

    for(int i = y1; i < y2; ++i){
        for(int j = x1; j < x2; ++j){
            if(arr[i][j] == -1)
                flag1 = 1;
            if(player_map[i][j] > 0)
                flag2 = 1;
        }
    }
    
    if(flag1 == 1 && flag2 == 1) return true;
    else return false;
}

void findPos(){
    for(int l = 1; l <= n; ++l){
        for(int i = 1; i <= n; ++i){
            for(int j = 1; j <= n; ++j){
                if(isIn(i, j, i + l, j + l)){
                    len = l;
                    ry = i;
                    rx = j;
                    return;
                }
            }
        }
    }
}

void rotateArr(){
    int tmp[12][12];
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            tmp[i][j] = arr[i][j];

    for(int i = 0; i < len; ++i){
        for(int j = 0; j < len; ++j){
            arr[ry + i][rx + j] = tmp[ry + len - j - 1][rx + i];
            if(arr[ry + i][rx + j] > 0)
                arr[ry + i][rx + j]--;
        }
    }

    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            if(arr[i][j] == -1){
                ey = i;
                ex = j;
                return;
            }
        }
    }
}

void rotatePlayerMap(){
    int tmp[12][12];
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            tmp[i][j] = player_map[i][j];

    for(int i = 0; i < len; ++i){
        for(int j = 0; j < len; ++j){
            player_map[ry + i][rx + j] = tmp[ry + len - j - 1][rx + i];
        }
    }

    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            if(player_map[i][j] > 0)
                P[player_map[i][j]].y = i;
                P[player_map[i][j]].x = j;
        }
    }

}

int main() {
    // Please write your code here.

    int T = 1;
    for(int test_case = 1; test_case <= T; ++test_case){
        // global_init();
        point = 0;
        cin >> n >> m >> k;
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j)
                cin >> arr[i][j];

        for(int idx = 1; idx <= m; ++idx){
            cin >> P[idx].y >> P[idx].x;
            P[idx].died = P[idx].dist = 0;
        }
        cin >> ey >> ex;
        arr[ey][ex] = -1;

        for(int run = 1; run <= k; ++run){
            //local_init();
            //cout << "SIMU" << run << '\n';

            moveRunner();

            playerToArr();

            if(canBreak())
                break;

            //cout << "AFTER RUNNER MOVE\n";
            //showArr();
            //showPlayer();

            len = 0, ry = 0, rx = 0;
            findPos();
            //cout << "LEN:" << len << " RY:" << ry << " RX:" << rx << "\n"; 

            rotateArr();
            //cout << "AFTER ROTATE\n";
            //showArr();


            rotatePlayerMap();
            //showPlayer();

            //cout << "================\n";
        }
        for(int idx = 1; idx <= m; ++idx){
            point += P[idx].dist;
        }
        cout << point << '\n' << ey << ' ' << ex << '\n';
    }
    return 0;
}