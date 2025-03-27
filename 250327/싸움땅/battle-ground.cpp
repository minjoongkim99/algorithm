#include <iostream>
#include <queue>
using namespace std;
int n, m, k;

priority_queue<int> pq[21][21];
struct player{
    int x, y, d, s, gun;
};
player P[32];

int point[32];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};


// 이 문제는 궁극적으로 격자 좌표내에 여러 플레이어들이 존재하려고 해도 할 수가 없다.

/*

*/
void movePlayer(int idx){
    int nx = P[idx].x + dx[P[idx].d];
    int ny = P[idx].y + dy[P[idx].d];

    if(nx < 1 || nx > n || ny < 1 || ny > n)
        P[idx].d = (P[idx].d + 2) % 4;
    
    P[idx].x = P[idx].x + dx[P[idx].d];
    P[idx].y = P[idx].y + dy[P[idx].d];
}

// index 반환할 때는 for(idx 1 ~ n) 
// 부한하는 거 있으면 return idx; 하면 더 간단해짐
int checkFight(int idx){
    for(int i = 1; i <= m; ++i){
        if(i == idx) continue;
        if(P[i].x == P[idx].x && P[i].y == P[idx].y){
            return i;
        }
    }
    return 0;
}

/* 
    내 총을 먼저 temp에 저장 안하면 Overwrite 문제가 생길 수도 있다!!
*/
void getGun(int idx){
    if(pq[P[idx].x][P[idx].y].empty()) return;          ////////////////////////////// KICK

    if(P[idx].gun < pq[P[idx].x][P[idx].y].top()){
        int tmp = P[idx].gun;
        P[idx].gun = pq[P[idx].x][P[idx].y].top();
        pq[P[idx].x][P[idx].y].pop();
        pq[P[idx].x][P[idx].y].push(tmp);
    }
}

/*
    비교군 정하기 문제. 비교군을 통해 ny, nx를 구하는게 매우 일반적인데
    여기서는 비교군을 통해 loser, winner를 정한다.
    loser,winner는 전역변수로 두어도 되나, 2개기에 pair<int,int> 형 함수 선언.
    (총 + 능력) > 이면 갱신 (총 + 능력) == 이면 (능력만으로 갱신하기.)
    비교군을 통하여 next_winner와 next_loser를 찾는 함수인 것이다.
*/
pair<int,int> fight(int a, int b){
    int loser = 0, winner = 0;

    if(P[a].s + P[a].gun > P[b].s + P[b].gun){
        winner = a;
        loser = b;
    }
    else if(P[a].s + P[a].gun < P[b].s + P[b].gun){
        winner = b;
        loser = a;
    }
    else if(P[a].s + P[a].gun == P[b].s + P[b].gun){
        if(P[a].s > P[b].s){
            winner = a;
            loser = b;
        }
        else if(P[a].s < P[b].s){
            winner = b;
            loser = a;
        }
    }

    point[winner] += (P[winner].s + P[winner].gun) - (P[loser].s + P[loser].gun); 
    return {winner, loser};
}


/*  isThere(int y, int x, int idx); 함수
    이 함수는 내가 가야할 좌표에 나를 제외한 다른 것이 있는지 판별하는 boolean()함수임.
    if(P[i].x == x && P[i].y == y) 이면 isThere(a,b,c)는 True()를 반환해야함
    즉, isThere() 함수가 참이면 실제로 나를 제외한 누군가가 있다는 뜻.
    이 함수는 왜 쓰냐? arr[][]이면 index에 대한 val 값 반환으로 확인하면되나, 여기는 구조체에 저장되어있음...
    */
bool isThere(int x, int y, int idx){
    for(int i = 1; i <= m; ++i){
        if(i == idx) continue;
        if(P[i].x == x && P[i].y == y)
            return true;
    }
    return false;
}

/*
    먼저 내 총을 격자에 내려놓기 pq[][].push();
    총을 내려놓으니 나의 건은 당연히 0이 되어여하므로 처리 해줌.
    현재 방향부터 4방향 탐색을 한다. 
    (dir = P[idx].d; dir < P[idx].d + 4; dir++) -> 이러면 dir값이 4이상일 수 있으므로 모듈러 연산을 해줘야함

    원하는 방향이 나오면 바로 이동한다. -> dir에 관한 for문에서 break;를 해줘야함.

    Loser는 총을 현 위치 격자에 내려놓고 원래 방향으로 가고자하나, 타 플레이어가 존재 또는 OOB이면 90도 시계방향 탐색 후
    있으면 바로 들어감(break)
    들어가서 총 가져오기.
*/
void moveLoser(int idx){
    pq[P[idx].x][P[idx].y].push(P[idx].gun);
    P[idx].gun = 0;

    for(int dir = P[idx].d; dir < P[idx].d + 4; ++dir){
        int d = dir % 4;

        int nx = P[idx].x + dx[d];
        int ny = P[idx].y + dy[d];
        if(nx < 1 || nx > n || ny < 1 || ny > n) continue;
        if(isThere(nx, ny, idx)) continue;

        P[idx].x = nx;
        P[idx].y = ny;              ////////////////////////
        P[idx].d = d;               ////////////////////////
                                    ////////////////////////
        break;
    }

    getGun(idx);
}

void moveWinner(int idx){
    getGun(idx);
}

int main() {

    int T = 1;

    for(int test_case = 1; test_case <= T; ++test_case){
        //global_init();
        cin >> n >> m >> k;

        // priority_queue empty() 상황 유의
        for(int i = 1; i <= n; ++i){
            for(int j = 1; j <= n; ++j){
                int x;
                cin >> x;
                pq[i][j].push(x);
            }
        }
        for(int idx = 1; idx <= m; ++idx){
            cin >> P[idx].x >> P[idx].y >> P[idx].d >> P[idx].s;
            P[idx].gun = 0;
        }

        for(int run = 1; run <=k; ++run){
            // local_init();
            
            for(int idx = 1; idx <= m; ++idx){
                movePlayer(idx);

                int val = checkFight(idx);
                if(val > 0){
                    pair<int,int> ret = fight(idx, val);

                    moveLoser(ret.second);
                    
                    moveWinner(ret.first);
                }
                else getGun(idx);
            }
        }

        for(int i = 1; i <= m; ++i){
            cout << point[i] << ' ';
        }
        cout << '\n';

    }
    return 0;
}