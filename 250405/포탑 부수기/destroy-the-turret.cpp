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
int ans = 0;

int canBreak(){
    int cnt = 0;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            if(power[i][j] > 0)
                cnt++;
    return cnt;
}

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
            int yy = (y + dy[dir] + n) % n;
            int xx = (x + dx[dir] + m) % m;

            /*
            1 - indexed OOB를 격자내로 다시 들어오게.
            yy = (((y + dy[dir] + n) - 1) % n) + 1;
			xx = (((x + dx[dir] + m) - 1) % m) + 1;
            */

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
        int yy = (ty + ddy[dir] + n) % n;
        int xx = (tx + ddx[dir] + m) % m; 
        
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

void getAnswer(){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            if(power[i][j] <= 0) continue;
            if(power[i][j] > ans)
                ans = power[i][j];
        }
    }
}

 /*
            1 - indexed OOB를 격자내로 다시 들어오게.
            yy = (((y + dy[dir] + n) - 1) % n) + 1;
			xx = (((x + dx[dir] + m) - 1) % m) + 1;
*/
int main() {
    // Please write your code here.
    int T = 1;

    for(int test_case = 1; test_case <= T; ++test_case){
        // global_init();
        cin >> n >> m >> k;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                cin >> power[i][j];

        for(int run = 1; run <= k; ++run){
            // local_init();
            fill(&attacked[0][0], &attacked[0][0] + 12 * 12, 0);
            ans = ay = ax = ty = tx = 0;

            findAttacker(run);

            findTarget();

            bfs();

            if(visited[ty][tx] > 0){
                razer();
            }
            else{
                potan();
            }

            int flag = canBreak();
            if(flag < 2)
                break;

            repair();
        }
        
        getAnswer();
        cout << ans <<'\n';
    }

    return 0;
}
