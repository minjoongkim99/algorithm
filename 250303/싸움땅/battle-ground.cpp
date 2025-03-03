#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, k;
vector<int> gun_map[23][23];

int point[32];              //
int gun[32];                //

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

struct person{
    int x, y, dir, s;
};
person P[32];

void printPos(){
    cout << "좌표\n";
    for(register int i = 1; i <= m; ++i){
        cout << P[i].x << ' ' << P[i].y << "\n";
    }
}
void printGun(){
    cout << "총: ";
    for(register int i = 1; i <= m; ++i){
        cout << gun[i] << " ";
    }
    cout << "\n";
}

void movePerson(int idx){
    int nx = P[idx].x + dx[P[idx].dir];
    int ny = P[idx].y + dy[P[idx].dir];
    if(nx < 1 || nx > n || ny < 1 || ny > n){
        P[idx].dir = (P[idx].dir + 2) % 4;
        nx = P[idx].x + dx[P[idx].dir];
        ny = P[idx].y + dy[P[idx].dir];
    }
    P[idx].x = nx;  P[idx].y = ny;
}

int checkConflict(int idx){
    for(register int i = 1; i <= m; ++i){
        if(i == idx) continue;
        if(P[i].x == P[idx].x && P[i].y == P[idx].y){
            return i;               //
        }       
    }
    return 0;
}

void changeGun(int idx){
    if(gun_map[P[idx].x][P[idx].y].size() > 0)
        sort(gun_map[P[idx].x][P[idx].y].begin(), gun_map[P[idx].x][P[idx].y].end(), greater<>());

    // sort( , ,) 유의사항 empty() 상태이면 안됨.
    if(gun_map[P[idx].x][P[idx].y][0] > gun[idx]){
        int tmp = gun[idx];
        gun[idx] = gun_map[P[idx].x][P[idx].y][0];
        gun_map[P[idx].x][P[idx].y][0] = tmp;
    }
}

pair<int,int> fight(int i, int j){
    int winner, loser;
    if(P[i].s + gun[i] > P[j].s + gun[j]){
        winner = i;
        loser = j;
    }
    else if(P[i].s + gun[i] < P[j].s + gun[j]){
        winner = j;
        loser = i;
    }
    else if(P[i].s + gun[i] == P[j].s + gun[j]){
        if(P[i].s > P[j].s){
            winner = i;
            loser = j;
        }
        else if(P[i].s < P[j].s){
            winner = j;
            loser = i;
        }
    }
    point[winner] += ((P[winner].s + gun[winner]) - (P[loser].s + gun[loser]));
    return {winner, loser};
}

void loserAction(int idx){
    if(gun[idx] > 0){
        gun_map[P[idx].x][P[idx].y].push_back(gun[idx]);
        gun[idx] = 0;
    }
    
    for(register int dir = 0; dir < 4; ++dir){
        int nx = P[idx].x + dx[(P[idx].dir + dir) % 4];
        int ny = P[idx].y + dy[(P[idx].dir + dir) % 4];
        if(nx < 1 || nx > n || ny < 1 || ny > n) continue;

        int flag = 0;
        for(register int i = 1; i <= m; ++i){
            if(i == idx) continue;
            if(P[i].x == nx && P[i].y == ny){
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            P[idx].x = nx;
            P[idx].y = ny;
            P[idx].dir = (P[idx].dir + dir) % 4;
            break;
        }
    }

    changeGun(idx);
}

void winnerAction(int idx){
    changeGun(idx);
}

int main() {
    // Please write your code here.
    cin >> n >> m >> k;

    for(register int i = 1; i <= n; ++i){
        for(register int j = 1; j <= n; ++j){
            int x;
            cin >> x;
            gun_map[i][j].push_back(x);
        }
    }
    for(register int i = 1; i <= m; ++i){
        int x, y, d, s;
        cin >> P[i].x >> P[i].y >> P[i].dir >> P[i].s;
    }


    for(register int run = 1; run <= k; ++run){
        
        for(register int idx = 1; idx <= m; ++idx){
            movePerson(idx);

            int flag = checkConflict(idx);

            if(flag == 0){
                changeGun(idx);
            }
            else{
                pair<int,int> ret = fight(idx, flag);
                //cout << "BATTLE " << ret.first << ' ' << ret.second << '\n';
                loserAction(ret.second);
                winnerAction(ret.first);
            }
        }
        //printGun();
        //printPos();
    }

    for(int i = 1; i <= m; ++i){
        cout << point[i] << ' ';
    }
    return 0;
}