#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;


int n, m, h, k; // 격자, 도망자 수, 나무 수, k 턴
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

struct runner{
    int x, y, dir, died;
};
runner R[10001];

int arr[101][101];
int tree[101][101];
int visited[101][101];

int sx = 0, sy = 0, sdir = 0;
int cur = 0, len = 1, change = 0;
int flag = 0;

int point = 0; // output

void showTree(){
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            cout << tree[i][j] << '\t';
        }
        cout << '\n';
    }
}

void showRunner(){
    for(int idx = 1; idx <= m; ++idx){
        if(R[idx].died == 1)
            cout << idx << " DIED\n";
        else cout << idx << ": " << R[idx].x << " " << R[idx].y << " DIR:" << R[idx].dir << '\n';
    }
}

void showS(){
    cout << sx << "," << sy << " DIR:" << sdir << "\n";
}

void moveR(){
    for(int idx = 1; idx <= m; ++idx){
        if(R[idx].died == 1) continue;

        int dist = abs(R[idx].x - sx) + abs(R[idx].y - sy);
        if(dist > 3) continue;

        int nx = R[idx].x + dx[R[idx].dir];
        int ny = R[idx].y + dy[R[idx].dir];

        if(nx < 1 || nx > n || ny < 1 || ny > n){
            R[idx].dir = (R[idx].dir + 2) % 4;
            nx = R[idx].x + dx[R[idx].dir];
            ny = R[idx].y + dy[R[idx].dir];
        }
        
        if(nx == sx && ny == sy) continue;

        R[idx].x = nx;
        R[idx].y = ny;
    }
}

// cur, len, change
void move1(){
    //cout << "FLAG1\n";
    sx = sx + dx[sdir];
    sy = sy + dy[sdir];

    cur++;

    if(cur == len){
        cur = 0;
        sdir = (sdir + 1) % 4;
        change++;
    }
    if(change == 2){
        len++;
        change = 0;
    }

    if(sx == 1 && sy == 1){
        fill(&visited[0][0], &visited[0][0] + 101 * 101, 0);
        sdir = 2;
        flag = 1;
    }
}

void move2(){
    //cout << "FLAG2\n";
    visited[sx][sy] = 1;
   

    int nx = sx + dx[sdir];
    int ny = sy + dy[sdir];
    
    sx = nx;
    sy = ny;

    nx = sx + dx[sdir];
    ny = sy + dy[sdir];

    if(nx < 1 || nx > n || ny < 1 || ny > n || visited[nx][ny] == 1){
        sdir = (sdir + 3) % 4;
    }


    if(sx == (n / 2) + 1 && sy == (n / 2) + 1){
        flag = 0;
        sdir = 0;
        len = 1;
        cur = 0;
        change = 0;
    }
}

void moveS(){
    if(flag == 0)
        move1();
    else
        move2();
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

// 1-indexed
int main() {
    // Please write your code here.
    int T = 1;
    for(int test_case = 1; test_case <= T; ++test_case){
        // global_init();

        cin >> n >> m >> h >> k;
        for(int i = 1; i <= m; ++i){
            cin >> R[i].x >> R[i].y >> R[i].dir;
        }
        for(int i = 1; i <= h; ++i){
            int x, y;
            cin >> x >> y;
            tree[x][y] = 1;
        }

        sx = sy = (n / 2) + 1; sdir = 0;
        flag = 0;

        for(int run = 1; run <= k; ++run){
            moveR();

            moveS();
            //showS();

            attack(run);

        }

        cout << point << '\n';
    }
    return 0;
}
