#include <iostream>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;

//  시험은 이렇게 각 단계로 나뉘어 있을까? SWEA 보자.

/* 메모장
    0-indexed, 0도로, 1은 도로아님
    메두사 좌표(,)  공원좌표(,) 항상 도로위에있음. 메두사는 공원까지 최단경로
    M명 전사들이 메두사 잡기 위해 마을 (ri, ci) 시작
    전사는 메두사 잡기 위한 최단 경로.

    바라보면서 돌로 만들어 멈춘다.

    1. 메두사 이동 상하좌우로 최단경로 (메두사 -> 공원까지 도달하는 경로 없음에 유의)

    2. 메두사의 시선은 (상하좌우 방향 중 하나 선택)
    예시를 보면서, 생각하고 90도 시야각
    시야각에 있으나, 다른 전사에 의해 가려지면 메두사에게 보이지 않음.
    8방향 중 바라본 방향은 이제 
    메두사에게 걸린 전사들은 현재 움직이지 못한다.
    각 칸에 전사들은 여러 명이 있을 수 있다.
    상,하,좌,우 순으로 최대한 전사 많이 보는 것 설정

    3. 첫번째에는 상하좌우 순으로 메두사와 가까워지는 방향이고, 메두사 시야 내에 범위와 OOB는 불가
       두번째에는 메두사와 가까워지는 방향으로 가고, 좌우상하 우선순위, 동일
       단, 전사들은 이동 중 같은 칸을 공격할 수 없다.
       최단 경로는 맨해튼 경로이다.
    
    4. 메두사와 같은 칸 도달 시 메두사를 공격하나 쓰러짐.

*/

int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};
int ddy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int ddx[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int N, M;
int sy, sx, ey, ex;

int arr[51][51];
int stone[51][51][4];       // 3d Matrix Thiking
struct fighter{
    int y, x, distance, died;
};
fighter F[301];
int mv[301];
int cnt = 0;
int sight = 0;

void showStone(int dir){
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            cout << stone[i][j][dir] << '\t';
        }
        cout << '\n';
    }
}

void moveMedusa(){
    int ny = sy, nx = sx;
    int dist = abs(sy - ey) + abs(sx - ex);

    for(int dir = 0; dir < 4; ++dir){
        int yy = sy + dy[dir];
        int xx = sx + dx[dir];
        if(yy < 0 || yy >= N || xx < 0 || xx >= N) continue;
        if(arr[yy][xx] == 1) continue;
        int next_dist = abs(yy - ey) + abs(xx - ex);
        if(dist > next_dist){
            dist = next_dist;
            ny = yy;
            nx = xx;
        }
    }

    sy = ny;
    sx = nx;
}

void attackFighter(){
    for(int idx = 1; idx <= M; ++idx){
        if(F[idx].died == 1) continue;
        if(F[idx].y == sy && F[idx].x == sx){
            F[idx].died = 1;
        }
    }
}

int makeStone(int see){

    int ddy[4] = {-1, 0, 1, 0};
    int ddx[4] = {0, 1, 0, -1};
    stone[sy][sx][see] = -1;
    queue<pair<int,int>> straight;
    queue<pair<int,int>> left;
    queue<pair<int,int>> right;

    for(int i = 1; i <= N; ++i){
        int yy = sy + i * ddy[see];
        int xx = sx + i * ddx[see];
        
        if(yy < 0 || yy >= N || xx < 0 || xx >= N) break;
        if(stone[yy][xx][see] > 0){
            cout << "STRIGHT: " << yy << "," << xx << "\n";
            straight.push({yy, xx});
        }
        stone[yy][xx][see] = -1;

        for(int j = 0; j <= i; ++j){
            int yyy = yy + j * ddy[(see + 3) % 4];
            int xxx = xx + j * ddx[(see + 3) % 4];
            if(yyy < 0 || yyy >= N || xxx < 0 || xxx >= N) continue;
            if(stone[yyy][xxx][see] > 0){
                cout << "LEFT: " << yyy << "," << xxx << "\n";
                left.push({yyy, xxx});
            }
            stone[yyy][xxx][see] = -1;
        }
        for(int j = 0; j <= i; ++j){
            int yyy = yy + j * ddy[(see + 1) % 4];
            int xxx = xx + j * ddx[(see + 1) % 4];
            if(yyy < 0 || yyy >= N || xxx < 0 || xxx >= N) continue;
            if(stone[yyy][xxx][see] > 0){
                cout << "RIGHTT: " << yyy << "," << xxx << "\n";
                right.push({yyy, xxx});
            }
            stone[yyy][xxx][see] = -1;
        }
    }
    
    return -1;
}

void seeMedusa(){
    int cnt = 0;

    for(int dir = 0; dir < 4; ++dir){

        for(int idx = 1; idx <= M; ++idx){
            if(F[idx].died == 1) continue;
            stone[F[idx].y][F[idx].x][dir] = idx;
        }

        int val = makeStone(dir);
        if(val > cnt){
            cnt = val;
            sight = dir;
        }
        cout << dir << "방향\n";
        showStone(dir);
        cout << "\n";
    }

    // sight 갱신하기.
}

void checkCanMove(int see){
    for(int idx = 1; idx <= M; ++idx){
        if(F[idx].died == 1) continue;
        if(stone[F[idx].y][F[idx].x][see] == -1){
            mv[idx] = idx;
        }
    }
}

/*
bool checkIn(int idx){
    for(int i = 1; i <= M; ++i){
        if(F[i].died == 1) continue;
        if(F[i].y == F[idx].y && F[i].x == F[idx].x) return false;
    }
    return true;
}*/

void moveFighter(int see){
    for(int idx = 1; idx <= M; ++idx){
        if(F[idx].died == 1) continue;
        if(mv[idx] > 0) continue;

        int ny = F[idx].y, nx = F[idx].x;
        int dist = abs(F[idx].y - sy) + abs(F[idx].x - sx);

        for(int dir = 0; dir < 4; ++dir){
            int yy = F[idx].y + dy[dir];
            int xx = F[idx].x + dx[dir];

            if(yy < 0 || yy >= N || xx < 0 || xx >= N) continue;
            if(stone[yy][xx][see] == -1) continue;
            //if(!checkIn(idx)) continue;

            int next_dist = abs(yy - sy) + abs(xx - sx);
            if(dist > next_dist){
                dist = next_dist;
                ny = yy;
                nx = xx;
            }
        }
        if(F[idx].y != ny || F[idx].x != nx)
            F[idx].distance++;
        F[idx].y = ny;
        F[idx].x = nx;

        ny = F[idx].y;
        nx = F[idx].x;
        dist = abs(F[idx].y - sy) + abs(F[idx].x - sx);

        for(int dir = 2; dir < 6; ++dir){
            int d = dir % 4;
            int yy = F[idx].y + dy[d];
            int xx = F[idx].x + dx[d];

            if(yy < 0 || yy >= N || xx < 0 || xx >= N) continue;
            if(stone[yy][xx][see] == -1) continue;
            // if(!checkIn(idx)) continue;

            int next_dist = abs(yy - sy) + abs(xx - sx);
            if(dist > next_dist){
                dist = next_dist;
                ny = yy;
                nx = xx;
            }
        }
        if(F[idx].y != ny || F[idx].x != nx)
            F[idx].distance++;
        F[idx].y = ny;
        F[idx].x = nx;

    }
}

void fighterAttack(){
    for(int idx = 1; idx <= M; ++idx){
        if(F[idx].died == 1) continue;
        if(F[idx].y == sy && F[idx].x == sx){
            cnt++;
            F[idx].died = 1;
        }
    }
}

int main() {
    // Please write your code here.
    int T = 1;

    for(int test_case = 1; test_case <= T; ++test_case){
        cin >> N >> M;
        cin >> sy >> sx >> ey >> ex;
        for(int i = 1; i <= M; ++i){
            cin >> F[i].y >> F[i].x;
            F[i].distance = F[i].died = 0;
        }
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j)
                cin >> arr[i][j];


        int t = 0;
        while(t < 3){
            cout << t << "시행\n";
            fill(&stone[0][0][0], &stone[0][0][0] + 51 * 51 * 4, 0);
            fill(&mv[0], &mv[0] + 301, 0);
            for(int i = 1; i <= M; ++i)
                F[i].distance = 0;

            cnt = 0;
            sight = 0;

            //if(못간다면) -1 출력 후 break;

            moveMedusa();

            attackFighter();

            seeMedusa();            // -> 쉬운 것부터 풀자!
            

            checkCanMove(sight);

            moveFighter(sight);         // 0바꿔야함.

            fighterAttack();


            if(sy == ey && sx == ex){
                cout << 0 << '\n';
                break;
            }
            
            cout << "\n";
            t++;        // erase
            // 모든 전사가 이동한 거리의 합, 메두사로 인해 돌이 된 전사의 수, 메두사를 공격한 전사의 수,
            // 공원 도착 시 0 출력, 공원으로 못간다면 -1 출력.
        }

    }
    return 0;
}