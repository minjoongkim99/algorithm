#include <iostream>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;

int N, M;
int sy, sx, ey, ex;
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};

int arr[51][51];
int visited[51][51];
int stone[51][51];

int pre[51][51][2];
int nextStep[51][51][2];

struct knight{
    int y, x, dist, stop, died;
};
knight K[305];

int distSum, stoneCnt, attackCnt;

void showKnight(){
    for(int idx = 1; idx <= M; ++idx){
        if(K[idx].died == 1) cout << idx << ": DIED" << " DIST: " << K[idx].dist << " STOP:" << K[idx].stop <<  "\n";
        else cout << idx << ": " << K[idx].y << "," << K[idx].x << " DIST: " << K[idx].dist << " STOP:" << K[idx].stop << "\n";
    }
}

void showArr(){
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            cout << arr[i][j] << '\t';
        }
        cout << '\n';
    }
}

void showStone(){
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            cout << stone[i][j] << '\t';
        }
        cout << '\n';
    }
}

void local_init(){
    distSum = stoneCnt = attackCnt = 0;
    fill(&stone[0][0], &stone[0][0] + 51 * 51, 0);

    for(int idx = 1; idx <= M; ++idx){
        K[idx].dist = K[idx].stop = 0;
    }
}

void bfs(){
    queue<pair<int,int>> q;
    q.push({sy, sx});
    visited[sy][sx] = 1;
    pre[sy][sx][0] = pre[sy][sx][1] = -1;

    while(!q.empty()){
        int y = q.front().first, x = q.front().second;
        if(y == ey && x == ex) break;
        q.pop();

        for(int dir = 0; dir < 4; ++dir){
            int yy = y + dy[dir];
            int xx = x + dx[dir];
            if(yy < 0 || yy >= N || xx < 0 || xx >= N) continue;
            if(visited[yy][xx]) continue;
            if(arr[yy][xx] == 1) continue;
            q.push({yy, xx});
            visited[yy][xx] = visited[y][x] + 1;
            pre[yy][xx][0] = y;
            pre[yy][xx][1] = x; 
        }
    }
}

void medusaPath(){
    int cy = ey;
    int cx = ex;

    while(true){
        int ny = pre[cy][cx][0];
        int nx = pre[cy][cx][1];

        if(ny == -1 && nx == -1){
            break;
        }
        nextStep[ny][nx][0] = cy;
        nextStep[ny][nx][1] = cx;

        cy = ny;
        cx = nx;
    }
}

void moveM(){
    int ny = nextStep[sy][sx][0];
    int nx = nextStep[sy][sx][1];

    sy = ny;
    sx = nx;
}

void killKnight(){
    for(int idx = 1; idx <= M; ++idx){
        if(K[idx].died == 1) continue;
        if(K[idx].y == sy && K[idx].x == sx){
            K[idx].died =1;
        }
    }
}

void moveK(){
    for(int idx = 1; idx <= M; ++idx){
        if(K[idx].died == 1) continue;
        if(K[idx].stop > 0) continue;

        int ny = K[idx].y, nx = K[idx].x;
        int curDist = abs(sy - K[idx].y) + abs(sx - K[idx].x);

        for(int dir = 0; dir < 4; ++dir){
            int yy = K[idx].y + dy[dir];
            int xx = K[idx].x + dx[dir];

            if(yy < 0 || yy >= N || xx < 0 || xx >= N) continue;
            if(stone[yy][xx] > 0) continue;

            int nextDist = abs(sy - yy) + abs(sx - xx);
            if(nextDist < curDist){
                curDist = nextDist;
                ny = yy;
                nx = xx;
            }
        }

        if(ny != K[idx].y || nx != K[idx].x){
            distSum++;
            K[idx].dist++;
        }

        K[idx].y = ny;
        K[idx].x = nx;
        curDist = abs(sy - K[idx].y) + abs(sx - K[idx].x);

        if(sy == K[idx].y && sx == K[idx].x){
            attackCnt++;
            K[idx].died = 1;
            continue;
        }

        for(int dir = 2; dir < 6; ++dir){
            int d = dir % 4;
            int yy = K[idx].y + dy[d];
            int xx = K[idx].x + dx[d];

            if(yy < 0 || yy >= N || xx < 0 || xx >= N) continue;
            if(stone[yy][xx] > 0) continue;

            int nextDist = abs(sy - yy) + abs(sx - xx);
            if(nextDist < curDist){
                curDist = nextDist;
                ny = yy;
                nx = xx;
            }
        }

        if(ny != K[idx].y || nx != K[idx].x){
            distSum++;
            K[idx].dist++;
        }
        K[idx].y = ny;
        K[idx].x = nx;

        if(sy == K[idx].y && sx == K[idx].x){
            attackCnt++;
            K[idx].died = 1;
            continue;
        }
    }
}

void straight_stone(int dir, int val, int idx){
    int posY, posX;
    if(idx == 0){
        posY = sy;
        posX = sx;
    }
    else{
        posY = K[idx].y;
        posX = K[idx].x;
    }
    
    for(int i = 1; i <= N; ++i){
        int yy = posY + i * dy[dir];
        int xx = posX + i * dx[dir];
        if(yy < 0 || yy >= N || xx < 0 || xx >= N) continue;
        stone[yy][xx] = val; 
    }
}

void left_stone(int dir, int left, int val, int idx){
    int posY, posX;
    if(idx == 0){
        posY = sy;
        posX = sx;
    }
    else{
        posY = K[idx].y;
        posX = K[idx].x;
    }
    
    for(int i = 1; i <= N; ++i){
        int yy = posY + i * dy[dir];
        int xx = posX + i * dx[dir];
        if(yy < 0 || yy >= N || xx < 0 || xx >= N) break;
        for(int j = 1; j <= i; ++j){
            int yyy = yy + j * dy[left];
            int xxx = xx + j * dx[left];
            if(yyy < 0 || yyy >= N || xxx < 0 || xxx >= N) continue;
            if(idx > 0){
                //cout << idx << ":" << yyy << ".." << xxx << "\n";
            }
            stone[yyy][xxx] = val;
        }
    }
}

void right_stone(int dir, int right, int val, int idx){
    int posY, posX;
    if(idx == 0){
        posY = sy;
        posX = sx;
    }
    else{
        posY = K[idx].y;
        posX = K[idx].x;
    }
    
    for(int i = 1; i <= N; ++i){
        int yy = posY + i * dy[dir];
        int xx = posX + i * dx[dir];
        if(yy < 0 || yy >= N || xx < 0 || xx >= N) break;;
        for(int j = 1; j <= i; ++j){
            int yyy = yy + j * dy[right];
            int xxx = xx + j * dx[right];
            if(yyy < 0 || yyy >= N || xxx < 0 || xxx >= N) continue;
            if(idx > 0){
                //cout << idx << ":" << yyy << ".." << xxx << "\n";
            }
            stone[yyy][xxx] = val;
        }
    }
}


int makeStone(int dir){
    int cnt = 0;

    int left, right;
    if(dir == 0){
        left = 2;   right = 3;
    }
    else if(dir == 1){
        left = 3;   right = 2;
    }
    else if(dir == 2){
        left = 1;   right = 0;
    }
    else if(dir == 3){
        left = 0;   right = 1;
    }


    straight_stone(dir, 1 , 0);

    left_stone(dir, left, 2, 0);

    right_stone(dir, right, 3, 0);
    
    
    for(int idx = 1; idx <= M; ++idx){
        if(K[idx].died == 1) continue;

        if(stone[K[idx].y][K[idx].x] == 1){
            //cout << idx << "STRAIGHT\n";
            straight_stone(dir, 0, idx);
        }
        else if(stone[K[idx].y][K[idx].x] == 2){
            //cout << idx << "LEFT\n";
            straight_stone(dir, 0, idx);
            left_stone(dir, left, 0, idx);
        }
        else if(stone[K[idx].y][K[idx].x] == 3){
            //cout << idx << "RIGHT\n";
            straight_stone(dir, 0, idx);
            right_stone(dir, right, 0, idx);
        }
    }

    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            for(int idx = 1; idx <= M; ++idx){
                if(K[idx].died == 1) continue;
                if(stone[i][j] == 0) continue;
                else if(K[idx].y == i && K[idx].x == j){
                    cnt++;
                }
            }
        }
    }
    return cnt;
}

void medusaSight(){
    int stoneKnight = 0;
    int attackDir = 0;

    for(int dir = 0; dir < 4; ++dir){
        fill(&stone[0][0], &stone[0][0] + 51 * 51, 0);

        int stone = makeStone(dir);
        if(stone > stoneKnight){
            stoneKnight = stone;
            attackDir = dir;
        }

        //cout << dir << "DIR \n";
        //showStone();
        //cout << "\n";
    }

    fill(&stone[0][0], &stone[0][0] + 51 * 51, 0);
    makeStone(attackDir);
    //showStone();
    //cout << "\n";

    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            for(int idx = 1; idx <= M; ++idx){
                if(K[idx].died == 1) continue;
                if(stone[i][j] == 0) continue;
                else if(K[idx].y == i && K[idx].x == j){
                    K[idx].stop = 1;
                }
            }
        }
    }   

    stoneCnt = stoneKnight;
}



void input(){
    cin >> N >> M;
    cin >> sy >> sx >> ey >> ex;
    for(int i = 1; i <= M; ++i){
        cin >> K[i].y >> K[i].x;
        K[i].stop = K[i].dist = K[i].died = 0;
    }

    for(int i = 0; i < N; ++i)
        for(int j = 0; j < N; ++j)
            cin >> arr[i][j];   
}

int main() {
    // Please write your code here.

    int T = 1;
    for(int test_case = 1; test_case <= T; ++test_case){
        //global_init();

        input();

        int t = 0;

        bfs();
        if(visited[ey][ex] == 0){
            cout << -1 << '\n';
        }
        else{
            medusaPath();

            while(true){               ///////// true
                local_init();

                moveM();
                killKnight();

                //cout << "MEDUSA: " << sy << " and " << sx << "!\n";

                if(sy == ey && sx == ex){
                    cout << 0 << '\n';
                    break;
                }

                medusaSight();
                //showKnight();

                moveK();
                //showKnight();
            
                //cout << distSum << ' ' << stoneCnt << ' ' << attackCnt << '\n';
                /*
                for(int idx = 1; idx <= M; idx++){
                    if(K[idx].died == 1) continue;
                    distSum += K[idx].dist;
                }*/
                cout << distSum << ' ' << stoneCnt << ' ' << attackCnt << '\n';


                t++;
            }
        }
    }
    return 0;
}