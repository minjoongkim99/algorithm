#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
int n, m, h, k;             // 격자, 도망자 수, 나무 수, k 턴
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

bool canBreak(){
    for(int idx = 1; idx <= m; ++idx){
        if(R[idx].died == 0) return false;
    }
    return true;
}

void moveR(){
    for(int idx = 1; idx <= m; ++idx){
        if(R[idx].died == 1) continue;

        int dist = abs(R[idx].x - sx) + abs(R[idx].y - sy);
        if(dist > 3) continue;

        // 현재 구조체 배열 idx가 가지고 있는 방향으로 활용한다
        int nx = R[idx].x + dx[R[idx].dir];
        int ny = R[idx].y + dy[R[idx].dir];

        // OOB이면 방향을 틀고 다시 curX,curY로부터 방향벡터를 계산하면 nx, ny는 무엇이 되는가?
        if(nx < 1 || nx > n || ny < 1 || ny > n){
            R[idx].dir = (R[idx].dir + 2) % 4;
            nx = R[idx].x + dx[R[idx].dir];
            ny = R[idx].y + dy[R[idx].dir];
        }

        // OOB아니거나, OOB여도 방향 처리를 했으니 무조건 격자 내로 들어온다
        if(nx == sx && ny == sy) continue;

        R[idx].x = nx;
        R[idx].y = ny;
    }
}

void move1(){
    //전진 못하면 바로 방향 바꾸는게 아니라 확인하고 이후 바꾸는 것이라면? if(cur == len) if(change == 2)가 앞에 오면 됨.
    //현재 기준 방향벡터 활용하여 한 칸 전진
    sx += dx[sdir];
    sy += dy[sdir];
    
    // 한 칸 전진할 때마다 cur 증가
    cur++;

    // cur이 주어진 len만큼 갔으면, cur 초기화, 방향 변화, change 1 증가
    if(cur == len){
        cur = 0;
        sdir = (sdir + 1) % 4;
        change++;
    }
    // change == 2는 두 번 갔음. 이제 len을 증가시키고 변화를 0으로 만듬
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
    // 현 지점 방문 처리.
    visited[sx][sy] = 1;
   
    // 한 칸 전진.
    int nx = sx + dx[sdir];
    int ny = sy + dy[sdir];
    
    sx = nx;
    sy = ny;

    // 다음 칸을 미리 보고, OOB이거나 visited[][]라면 미리 방향을 선제적으로 전환
    nx = sx + dx[sdir];
    ny = sy + dy[sdir];

    if(nx < 1 || nx > n || ny < 1 || ny > n || visited[nx][ny] == 1){
        sdir = (sdir + 3) % 4;
    }

    if(sx == (n / 2) + 1 && sy == (n / 2) + 1){
        flag = 0;   sdir = 0;
        len = 1;    cur = 0;
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

    // 길이를 가진 방향 벡터. 특정 방향으로만 지속 전진한다.
    // 4방향을 길이만큼 탐색하려면 for(dir = 0 ~ 4) 가 어디에 위치해 있느냐에 따라 변화됨.
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
        for(int i = 1; i <= m; ++i){
            cin >> R[i].x >> R[i].y >> R[i].dir;
        }
        for(int i = 1; i <= h; ++i){
            int x, y;
            cin >> x >> y;
            tree[x][y] = 1;
        }

        sx = sy = (n / 2) + 1; sdir = 0;

        for(int run = 1; run <= k; ++run){ 
            if(canBreak())
                break;
            moveR();
            
            moveS();

            attack(run);
        }

        cout << point << '\n';
    }

    return 0;
}
