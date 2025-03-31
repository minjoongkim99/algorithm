#include <iostream>
#include <cmath>
using namespace std;

/*
    자주 움직이는 것과 고정된 것을 구분하자. 나무는 고정되어있다 -> 독립된 2차원 배열
    구조체로 놓아야하는 것이 있다. (한 격자에 여러 개가 있을 수 있으면 무조건. 아니면 OverWrite된다.)
    따라서 이 문제는 겹쳐지는 것이 없으므로, 2차원 배열로 놓아도 되긴 한다.
    방향이 모두 있으므로, 구조체 멤버변수에는 dir이 들어가야한다. 놓쳤다면 당황하지 않고 int dir[10005];
    달팽이 회전과 역달팽이 회전
*/

int n, m, h, k; // 격자크기, 도망자 수, 나무 수, 턴. x - y.
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

struct runner{
    int x, y, dir, died;
};
runner R[10025];

int tree[105][105];
int visited[105][105];

int sx, sy, sdir;

int flag = 0;

int cur = 0, len = 1, change = 0;
int point = 0;

void showRunner(){
    for(int idx = 1; idx <= m; ++idx){
        if(R[idx].died == 1){
            cout << "IDX" << idx << " IS DIED\n";
        }
        else cout << "IDX" << idx << " " << R[idx].x << "," << R[idx].y << " DIR:" << R[idx].dir << '\n';
    }
}

void showS(){
    cout << "술래는 " << sx << "and" << sy << " DIR:" << sdir << '\n'; 
}

void movePlayer(int idx){
    int nx = R[idx].x + dx[R[idx].dir];
    int ny = R[idx].y + dy[R[idx].dir];

    if(nx < 1 || nx > n || ny < 1 || ny > n){
        R[idx].dir = (R[idx].dir + 2) % 4;
    }
    nx = R[idx].x + dx[R[idx].dir];
    ny = R[idx].y + dy[R[idx].dir];

    if(nx == sx && ny == sy) 
        return;
    R[idx].x = nx;
    R[idx].y = ny;
}

void movePlayers(){
    for(int idx = 1; idx <= m; ++idx){
        if(R[idx].died == 1) continue;
        if(abs(sx - R[idx].x) + abs(sy - R[idx].y) > 3) continue;
        movePlayer(idx);
    }
}

void mv1(){
    int nx = sx + dx[sdir];
    int ny = sy + dy[sdir];

    cur++;
    if(cur == len){
        sdir = (sdir + 1) % 4;
        change++;
        cur = 0;
    }
    if(change == 2){
        len++;
        change = 0;
    }

    sx = nx;
    sy = ny;

    if(sx == 1 && sy == 1){
        //cout << "LETS MV2\n";
        fill(&visited[0][0], &visited[0][0] + 105 * 105, 0);
        sdir = 2;
        flag = 1;
    }
}

void mv2(){
    visited[sx][sy] = 1;

    int nx = sx + dx[sdir];
    int ny = sy + dy[sdir];

    sx = nx;
    sy = ny;

    nx = sx + dx[sdir];
    ny = sy + dy[sdir];

    if(nx < 1 || nx > n || ny < 1 || ny > n){
        sdir = (sdir + 3) % 4;
    }
    else if(visited[nx][ny] == 1){
        sdir = (sdir + 3) % 4;
    }

    if(sx == (n / 2) + 1 && sy == (n / 2) + 1){
        len = 1;
        cur = 0;
        change = 0;
        sdir = 0;
        flag = 0;
    }
}

void moveS(){
    if(flag == 0)
        mv1();
    else mv2();
}

void attack(int t){
    int cnt = 0;
    for(int len = 0; len < 3; ++len){
        int xx = sx + len * dx[sdir];
        int yy = sy + len * dy[sdir];
        
        if(xx < 1 || xx > n || yy < 1 || yy > n) continue;
        if(tree[xx][yy] > 0) continue;

        for(int idx = 1; idx <= m; ++idx){
            if(R[idx].died == 1) continue;
            if(xx == R[idx].x && yy == R[idx].y){
                R[idx].died = 1;
                cnt++;
            }
        }
    }
    
    point += t * cnt;
}


int main() {
    // Please write your code here.

    int T = 1;
    for(int test_case = 1; test_case <= T; ++test_case){
        // global_init();

        cin >> n >> m >> h >> k;
        for(int idx = 1; idx <= m; ++idx){
            cin >> R[idx].x >> R[idx].y >> R[idx].dir;
        }
        for(int cnt = 1; cnt <= h; ++cnt){
            int x, y;
            cin >> x >> y;
            tree[x][y] = 1;
        }
        /////////////////////////////////
        sx = sy = (n / 2) + 1;
        sdir = 0;
        /////////////////////////////////

        for(int run = 1; run <= k; ++run){
            //cout << "SIMU " << run << "\n";

            movePlayers();
            //showRunner();

            moveS();
            //if(run > 30)
                //showS();

            attack(run);
        }

        cout << point << '\n';
    }

    return 0;
}