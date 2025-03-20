#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int n, m, h, k; // 격자크기, 도망자 수, 나무 수, 턴

struct player{
    int x, y, dir, died;
};
player P[10000];

int tree[101][101]; // 1-indexed
int visited[101][101];
int attackerX, attackerY, attackerDir;
int point = 0;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int len = 1, cur = 0, s = 0, flag = 0;

void playerMove(){
    for(register int idx = 1; idx <= m; ++idx){
        if(P[idx].died == 1) continue;

        int distance = abs(attackerX - P[idx].x) + abs(attackerY - P[idx].y);
        if(distance > 3) continue;

        int nx = P[idx].x + dx[P[idx].dir];
        int ny = P[idx].y + dy[P[idx].dir];

        if(nx < 1 || nx > n || ny < 1 || ny > n){
            P[idx].dir = (P[idx].dir + 2) % 4;      ////
            nx = P[idx].x + dx[P[idx].dir];
            ny = P[idx].y + dy[P[idx].dir];
        }

        ////////////////////////
        if(nx == attackerX && ny == attackerY)  continue;
        
        P[idx].x = nx;
        P[idx].y = ny;
    }
}

void move1(){
    attackerX += dx[attackerDir];
    attackerY += dy[attackerDir];

    cur++;
    if(len == cur){
        s++;
        attackerDir = (attackerDir + 1) % 4;
        cur = 0;
    }
    if(s == 2){
        len++;
        s = 0;
    }

    if(attackerX == 1 && attackerY == 1){
        attackerDir = 2;
        fill(&visited[0][0], &visited[0][0] + 101 * 101, 0);
        flag = 1;
    }
}

void move2(){
    visited[attackerX][attackerY] = 1;

    attackerX += dx[attackerDir];
    attackerY += dy[attackerDir];

    int nx = attackerX + dx[attackerDir];
    int ny = attackerY + dy[attackerDir];

    if(nx < 1|| nx > n || ny < 1 || ny > n || visited[nx][ny] == 1){
        attackerDir = (attackerDir + 3) % 4;
    }

    if(attackerX == (n / 2) + 1 && attackerY == (n / 2) + 1){
        attackerDir = 0;
        len = 1, cur = 0, s = 0, flag = 0;
    }
}

void attackerMove(){
    if(flag == 0){
        move1();
    }
    else move2();
}

void getPoint(int t){
    int cnt = 0;

    for(register int len = 0; len < 3; ++len){
        int xx = attackerX + len * dx[attackerDir];
        int yy = attackerY + len * dy[attackerDir];

        if(xx < 1 || xx > n || yy < 1 || yy > n) continue;
        if(tree[xx][yy] == 1) continue;

        for(register int idx = 1; idx <= m; ++idx){
            if(P[idx].died == 1) continue;
            if(xx == P[idx].x && yy == P[idx].y){
                P[idx].died = 1;
                cnt++;
            }
        }
    }
    point += (t * cnt);
}

int main() {
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);  cin.tie(nullptr);

    int T = 1;
    for(register int tc = 1; tc <= T; ++tc){
        // init(); 테케마다 초기화할 것들 ex: tree, visited, attacker, died, point

        cin >> n >> m >> h >> k;

        attackerY = attackerX = (n / 2) + 1;
        attackerDir = 0;

        for(register int idx = 1; idx <= m; ++idx){
            cin >> P[idx].x >> P[idx].y >> P[idx].dir;
            P[idx].died = 0;
        }
        for(register int i = 1; i <= h; ++i){
            int x, y;
            cin >> x >> y;
            tree[x][y] = 1;
        }

        for(register int run = 1; run <= k; ++run){
            playerMove();

            attackerMove();

            getPoint(run);
        }

        cout << point << '\n';
    }

    return 0;
}
