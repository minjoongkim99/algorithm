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

void movePlayer(int idx){
    int nx = P[idx].x + dx[P[idx].d];
    int ny = P[idx].y + dy[P[idx].d];

    if(nx < 1 || nx > n || ny < 1 || ny > n)
        P[idx].d = (P[idx].d + 2) % 4;
    
    P[idx].x = P[idx].x + dx[P[idx].d];
    P[idx].y = P[idx].y + dy[P[idx].d];
}

int checkFight(int idx){
    for(int i = 1; i <= m; ++i){
        if(i == idx) continue;
        if(P[i].x == P[idx].x && P[i].y == P[idx].y){
            return i;
        }
    }
    return 0;
}

void getGun(int idx){
    if(pq[P[idx].x][P[idx].y].empty()) return;

    if(P[idx].gun < pq[P[idx].x][P[idx].y].top()){
        int tmp = P[idx].gun;
        P[idx].gun = pq[P[idx].x][P[idx].y].top();
        pq[P[idx].x][P[idx].y].pop();
        pq[P[idx].x][P[idx].y].push(tmp);
    }
}

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

bool isThere(int x, int y, int idx){
    for(int i = 1; i <= m; ++i){
        if(i == idx) continue;
        if(P[i].x == x && P[i].y == y)
            return true;
    }
    return false;
}

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