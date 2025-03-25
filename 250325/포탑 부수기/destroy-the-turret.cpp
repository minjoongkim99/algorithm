#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int n, m, k;
int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0};

int power[12][12];
int recent[12][12];
int visited[12][12];
int attacked[12][12];
int pre[12][12][2];

int ay, ax, ty, tx;

void showPower(){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cout << power[i][j] << '\t';
        }
        cout << '\n';
    }
    cout << "\n";
}

void showRecent(){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cout << recent[i][j] << '\t';
        }
        cout << '\n';
    }
    cout << "\n";
}

void showVisited(){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cout << visited[i][j] << '\t';
        }
        cout << '\n';
    }
    cout << "\n";
}

int canBreak(){
    int cnt = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            if(power[i][j] > 0)
                cnt++;
        }
    }   
    return cnt;
}

/*
1. 공격자 선정
가장 약한 포탑을 공격자로 선정하고, N + M 만큼 공격력 증가
선정기준1. 공격력이 가장 낮은 포탑
선정기준2. 공격력 낮은 포탑 2개 이상이면 가장 최근에 공격한 포탑
선정기준3. (행+열)큰
선정기준4. 열 큰*/

void findAttacker(int t){
    int ny = 0, nx = 0;
    int p = 100000000;
    int r = -1;

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            if(power[i][j] <= 0) continue;

            if(power[i][j] < p){
                p = power[i][j];
                r = recent[i][j];
                ny = i;
                nx = j;
            }
            else if(power[i][j] == p){
                if(recent[i][j] > r){
                    r = recent[i][j];
                    ny = i;
                    nx = j;
                }
                else if(recent[i][j] == r){
                    if(i + j > ny + nx){
                        r = recent[i][j];
                        ny = i;
                        nx = j;
                    }
                    else if(i + j == ny + nx){
                        if(j > nx){
                            r = recent[i][j];
                            ny = i;
                            nx = j;
                        }
                    }
                }
            }
        }
    }

    ay = ny;
    ax = nx;
    power[ay][ax] += (n + m);
    recent[ay][ax] = t;
}

/*
	2.피해자 선정(자신 제외)
	가장 강한 포탑 선정
	2개 이상이면 공격한지 가장 오래된 포탑.
	(행+열) 작
	열 작*/
void findTarget(){
    int ny = 0, nx = 0;
    int p = -1;
    int r = 100000000;

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            if(power[i][j] <= 0) continue;
            if(i == ay && j == ax) continue;

            if(power[i][j] > p){
                p = power[i][j];
                r = recent[i][j];
                ny = i;
                nx = j;
            }
            else if(power[i][j] == p){
                if(recent[i][j] < r){
                    r = recent[i][j];
                    ny = i;
                    nx = j;
                }
                else if(recent[i][j] == r){
                    if(i + j < ny + nx){
                        r = recent[i][j];
                        ny = i;
                        nx = j;
                    }
                    else if(i + j == ny + nx){
                        if(j < nx){
                            r = recent[i][j];
                            ny = i;
                            nx = j;
                        }
                    }
                }
            }
        }
    }

    ty = ny;
    tx = nx;
}

/*
    레이저 공격: 상하좌우 4방향 움직이고 부서진 포탑은 움직일 수 없음
	OOB는 반대편으로 나오게 할 수 있다.
	공격자의 위치에서 타겟까지 최단 경로로 이동 최단경로 없으면 포탄공격을 해야함
	최단경로에 우선순위는 우	하	좌	상이다.
	피해자는 공격자의 power만큼만 중간 경로는 공격자 공격력 절반만큼*/
void bfs(){
    fill(&visited[0][0], &visited[0][0] + 12 * 12, 0);
    fill(&pre[0][0][0], &pre[0][0][0] + 12 * 12 * 2, 0);

    queue<pair<int,int>> q;
    q.push({ay, ax});
    visited[ay][ax] = 1;    
    pre[ay][ax][0] = pre[ay][ax][1] = -1;

    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for(int dir = 0; dir < 4; ++dir){
            int yy = y + dy[dir];
            int xx = x + dx[dir];

            if(yy < 0)
                yy = n + yy;
            else if(yy >= n)
                yy = yy % n;
            if(xx < 0)
                xx = m + xx;
            else if(xx >= m)
                xx = xx % m;

            if(visited[yy][xx]) continue;
            if(power[yy][xx] <= 0) continue;
            q.push({yy, xx});
            visited[yy][xx] = visited[y][x] + 1;
            pre[yy][xx][0] = y;
            pre[yy][xx][1] = x;

        }
    }

}

void razer(){
    int damage = power[ay][ax];

    power[ty][tx] -= damage;
    attacked[ty][tx] = 1;
    attacked[ay][ax] = 1;                   //////////////////////////

    int cy = ty;
    int cx = tx;

    while(true){
        int ny = pre[cy][cx][0];
        int nx = pre[cy][cx][1];
        if(ny == ay && nx == ax) break;

        power[ny][nx] -= (damage / 2);
        attacked[ny][nx] = 1;

        cy = ny;
        cx = nx;
    }
}

void potan(){
    int ddy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int ddx[8] = {0, 1, 1, 1, 0, -1, -1, -1};

    int damage = power[ay][ax];
    power[ty][tx] -= damage;
    attacked[ty][tx] = 1;
    attacked[ay][ax] = 1;                   //////////////////////////

    for(int dir = 0; dir < 8; ++dir){
        int yy = ty + ddy[dir];
        int xx = tx + ddx[dir];

        if(yy < 0)
            yy = n + yy;
        else if(yy >= n)
            yy = yy % n;
        if(xx < 0)
            xx = m + xx;
        else if(xx >= m)
            xx = xx % m;
        
        if(yy == ay && xx == ax) continue;

        power[yy][xx] -= (damage / 2);
        attacked[yy][xx] = 1;
    }
}

void repair(){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            if(power[i][j] <= 0) continue;
            if(attacked[i][j] > 0) continue;
            power[i][j]++;
        }
    }
}

int main() {
    // Please write your code here.

    int T = 1;

    for(int test_case = 1; test_case <= T; ++test_case){
        // global_init();
        cin >> n >> m >> k;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                cin >> power[i][j];
        /*
	    N*M 격자위에 포탑이 존재
	    각 포탑은 공격력 존재.	증감이 있다. 공격력이 0이하면 부서진 포탑이므로 공격을 할 수 있다.
	    K번 4가지 액션 수행을 한다.	부서지지 않은 포탑이 1개가 되면 즉시 종료*/

        for(int run = 1; run <= k; ++run){
            //cout << "SIMU" << run << '\n';
            // local_init();

            fill(&attacked[0][0], &attacked[0][0] + 12 * 12, 0);
            ay = ax = ty = tx = 0;


            findAttacker(run);

            findTarget();

            //cout << "ATTACKER: " << ay << "," << ax << "\n";
            //cout << "TARGET: " << ty << "," << tx << "\n"; 

            bfs();
            //showVisited();
            if(visited[ty][tx] > 0){
                //cout << "RAZER\n";
                razer();
                //showPower();
            }
            else{
                //cout << "POTAN\n";
                potan();
                //showPower();
            }

            int flag = canBreak();
            if(flag < 2)
                break;

            repair();
            //cout << "REPAIR\n";
            //showPower();
        }


        int ans = 0;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                if(power[i][j] <= 0) continue;
                if(power[i][j] > ans)
                    ans = power[i][j];
            }
        }
        cout << ans <<'\n';


    }

    return 0;
}