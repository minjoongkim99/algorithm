#include <stdio.h>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N, M, K;    // N*M 직사각형, K 시뮬레이션

int arr[15][15];
int recent[15][15];
int visited[15][15];
int pre[15][15][2];
int attacked[15][15];


int ddy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int ddx[8] = {1, 1, 0, -1, -1, -1, 0, 1};

int ay = -1, ax = -1, ty = -1, tx = -1;

void printPos(){
    cout << "공격자: " << ay << "," << ax << " 피해자: " << ty << "," << tx << "\n";
}

void printArr(){
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            cout << arr[i][j] << '\t';
        }
        cout << '\n';
    }
}

void printVisited(){
    cout << "방문지도\n";
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            cout << visited[i][j] << '\t';
        }
        cout << '\n';
    }
}

int canEnd(){
    int cnt = 0;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            if(arr[i][j] > 0)
                cnt++;
        }
    }
    return cnt;
}

void local_init(){
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            attacked[i][j] = 0;
            visited[i][j] = 0;
        }
    }
}

void findAttacker(){
    int mn = 1000000;
    int ny = -1, nx = -1, nr = 0;

    for(int i = N - 1; i >= 0; --i){
        for(int j = M - 1; j >= 0; --j){
            if(arr[i][j] <= 0) continue;
            if(arr[i][j] < mn){
                mn = arr[i][j];
                nr = recent[i][j];
                ny = i;
                nx = j;
            }
            else if(arr[i][j] == mn){
                if(recent[i][j] > nr){
                    nr = recent[i][j];
                    ny = i;
                    nx = j;
                }
                else if(recent[i][j] == nr){
                    if(i + j > ny + nx){
                        nr = recent[i][j];
                        ny = i;
                        nx = j;
                    }
                }
            }
        }
    }

    ay = ny;
    ax = nx;
}

// recent 갱신해야함.
void findTarget(){
    int mx = 0;
    int ny = -1, nx = -1, nr = 100000;

    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            if(arr[i][j] <= 0) continue;
            if(arr[i][j] > mx){
                mx = arr[i][j];
                nr = recent[i][j];
                ny = i;
                nx = j;
            }
            else if(arr[i][j] == mx){
                if(recent[i][j] < nr){
                    nr = recent[i][j];
                    ny = i;
                    nx = j;
                }
                else if(recent[i][j] == nr){
                    if(i + j < ny + nx){
                        nr = recent[i][j];
                        ny = i;
                        nx = j;
                    }
                }
            }
        }
    }

    ty = ny;
    tx = nx;
}

void update(int t){
    arr[ay][ax] += (N + M);
    recent[ay][ax] = t;
}

void bfs(){
    fill(&visited[0][0], &visited[0][0] + 15 * 15, 0);
    fill(&pre[0][0][0], &pre[0][0][0] + 15 * 15 * 2, -1);

    queue<pair<int,int>> q;
    q.push({ay, ax});
    visited[ay][ax] = 1;

    while(!q.empty()){
        int y = q.front().first, x = q.front().second;
        q.pop();

        for(register int dir = 0; dir < 8; dir = dir + 2){
            int yy = y + ddy[dir];
            int xx = x + ddx[dir];

            if(yy < 0){
                yy = N + yy;
            }
            else if(yy >= N){
                yy = yy % N;
            }

            if(xx < 0){
                xx = M + xx;
            }
            else if(xx >= M){
                xx = xx % M;
            }

            if(arr[yy][xx] <= 0) continue;
            if(visited[yy][xx]) continue;

            q.push({yy, xx});
            visited[yy][xx] = visited[y][x] + 1;
            pre[yy][xx][0] = y;
            pre[yy][xx][1] = x;
        }
    }
}

void razer(){
    int cy = ty, cx = tx;

    int power = arr[ay][ax];
    arr[ty][tx] -= power;
    attacked[ty][tx] = 1;

    if(arr[ty][tx] < 0)
        arr[ty][tx] = 0;

    while(true){
        int ny = pre[cy][cx][0];
        int nx = pre[cy][cx][1];
        if(ny == ay && nx == ax) break;

        arr[ny][nx] -= (power / 2);
        if(arr[ny][nx] < 0)
            arr[ny][nx] = 0;

        attacked[ny][nx] = 1;


        cy = ny;
        cx = nx;
    }
}

void potan(){
    int power = arr[ay][ax];

    arr[ty][tx] -= power;
    attacked[ty][tx] = 1;
    if(arr[ty][tx] < 0)
        arr[ty][tx] = 0;
    
    for(int dir = 0; dir < 8; ++dir){
            int yy = ty + ddy[dir];
            int xx = tx + ddx[dir];

            if(yy < 0){
                yy = N + yy;
            }
            else if(yy >= N){
                yy = yy % N;
            }

            if(xx < 0){
                xx = M + xx;
            }
            else if(xx >= M){
                xx = xx % M;
            }

            if(arr[yy][xx] <= 0) continue;
            if(yy == ay && xx == ax) continue;

            arr[yy][xx] -= (power / 2);
            attacked[yy][xx] = 1;

            if(arr[yy][xx] < 0)
                arr[yy][xx] = 0;

    }
}

void repair(){
    attacked[ay][ax] = 1;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            if(arr[i][j] > 0 && attacked[i][j] == 0)
                arr[i][j]++;
        }
    }
}

int main() {
    // Please write your code here.
    int T = 1;

    for(register int tc = 1; tc <= T; ++tc){
        //global_init();

        cin >> N >> M >> K;
        for(register int i = 0; i < N; ++i)
            for(register int j = 0; j < M; ++j){
                cin >> arr[i][j];
                recent[i][j] = 0;
            }

        for(register int run = 1; run <= K; ++run){
            if(canEnd() < 2)
                break;

            local_init();

            findAttacker();

            findTarget();

            //printPos();

            update(run);

            //printArr();

            bfs();

            //printVisited();

            if(visited[ty][tx] > 0)
                razer();
            else 
                potan();

            repair();

            //cout << "회복 후\n";

            //printArr();
        }

        int val = 0;
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < M; ++j)
                if(arr[i][j] > val)
                    val = arr[i][j];
        }

        cout << val << '\n';
    }
    return 0;
}
