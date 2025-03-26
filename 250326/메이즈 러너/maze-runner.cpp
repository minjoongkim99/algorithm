#include <iostream>
#include <cmath>
using namespace std;
int n, m, k;

int arr[12][12];
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, 1, -1};

struct player{
    int y, x, died, distance;
};
player P[12];

int ey, ex;

int len = 0, ry = 0, rx = 0;
int total_distance = 0;

void showArr(){
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            cout << arr[i][j] << " ";
        }
        cout << '\n';
    }
    cout << "\n";
}

void showPlayer(){
    for(int idx = 1; idx <= m; ++idx){
        if(P[idx].died == 1){
            cout << "IDX" << idx << " IS DIED\n"; 
        }
        else cout << "IDX" << idx << " " << P[idx].y << "," << P[idx].x << '\n';
    }
}

bool canBreak(){
    for(int idx = 1; idx <= m; ++idx)
        if(P[idx].died == 0) return false;
    return true;
}

void movePlayer(){
    for(int idx = 1; idx <= m; ++idx){
        if(P[idx].died == 1) continue;

        int flag = 0;
        int ny = P[idx].y;
        int nx = P[idx].x;
        int cur_distance = abs(ey - P[idx].y) + abs(ex - P[idx].x);

        for(int dir = 0; dir < 4; ++dir){
            int yy = P[idx].y + dy[dir];
            int xx = P[idx].x + dx[dir];

            if(yy < 1 || yy > n || xx < 1 || xx > n) continue;

            int next_distance = abs(ey - yy) + abs(ex - xx);
            if(arr[yy][xx] > 0) continue;

            if(cur_distance > next_distance){
                cur_distance = next_distance;
                ny = yy;
                nx = xx;
                flag = 1;
            }
        }
        if(flag == 1)
            P[idx].distance++;
        P[idx].y = ny;
        P[idx].x = nx;

        if(P[idx].y == ey && P[idx].x == ex){
            P[idx].died = 1;
        }
    }
}

bool isIn(int y1, int x1, int y2 ,int x2){
    if(y1 > n || x1 > n || y2 > n || x2 > n) return false;
    int flag1 = 0, flag2 = 0;
    for(int i = y1; i <= y2; ++i){
        for(int j = x1; j <= x2; ++j){
            if(arr[i][j] == -1)
                flag1 = 1;

            for(int idx = 1; idx <= m; ++idx){
                if(P[idx].died == 1) continue;
                if(P[idx].y == i && P[idx].x == j){
                    flag2 = 1;
                }
            }
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

void rotate(int len, int y, int x){          // parmater 뭐 들어갈지 생각해보면 좋을듯
    int tmp[12][12];
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            tmp[i][j] = arr[i][j];
        }
    }

    for(int i = 0; i < len; ++i){
        for(int j = 0; j < len; ++j){
            arr[y + i][x + j] = tmp[y + len - j - 1][x + i];
            if(arr[y + i][x + j] > 0){
                arr[y + i][x + j]--;
            }
        }
    }
}

void rotatePerson(int len, int y, int x){
    int tmp[12][12];
    int tmp2[12][12];
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            tmp2[i][j] = tmp[i][j] = 0;

    for(int idx = 1; idx <= m; ++idx){
        if(P[idx].died == 1) continue;
         tmp2[P[idx].y][P[idx].x] = tmp[P[idx].y][P[idx].x] = idx;
    }
    for(int i = 0; i < len; ++i){
        for(int j = 0; j < len; ++j){
            tmp[y + i][x + j] = tmp2[y + len - j - 1][x + i];
        }
    }

    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            if(tmp[i][j] > 0){
                P[tmp[i][j]].y = i;
                P[tmp[i][j]].x = j;
            }
        }
    }
}

void findEYEX(){
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

int getPoint(){
    for(int idx = 1; idx <= m; ++idx)
        total_distance += P[idx].distance;
}

int main() {
    // Please write your code here.
    int T = 1;

    for(int test_case = 1; test_case <= T; ++test_case){
        // global_init();

        cin >> n >> m >> k;
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j)
                cin >> arr[i][j];

        for(int i = 1; i <= m; ++i){
            cin >> P[i].y >> P[i].x;
            P[i].died = P[i].distance = 0;
        }
        cin >> ey >> ex;
        arr[ey][ex] = -1;

        //showArr();
        for(int run = 1; run <= k; ++run){
            // local_init();
            if(canBreak())
                break;
            len = 0;
            ry = rx = 0;

            //cout << "SIMU" << run << "\n";
            //showPlayer();
            movePlayer();
            //cout << "AFTER MOVE\n";
            //showPlayer();
            //checkIn();

            findPos();
            //cout << "LEN" << len << " " << "RY" << ry << " " << "RX" << rx << "!!\n";

            rotate(len + 1, ry, rx);
            rotatePerson(len + 1, ry, rx);
            //cout << "AFTER ROTATE\n";
            //showArr();

            findEYEX();
            //cout << "EXIT:" << ey << "," << ex << "\n";

        }

        for(int idx = 1; idx <= m; ++idx)
            total_distance += P[idx].distance;
        cout << total_distance << '\n' << ey << ' ' << ex << '\n';
        // 본질이 무엇인가.
    }
    return 0;
}