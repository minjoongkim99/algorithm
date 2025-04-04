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

//func1()
/*
공격자의 선정
선정 문제는 비교군 잡고 다음 좌표나 특정 좌표 정하기 문제임.
비교군: Power, Recent 같은 조건들이나, 행작 열작 이런거
다른 문제에서 행작 열작 이런 것과 비교할 것들이 주어질 것이다. 이를 토대로 for문처리와 if else if문 처리

비교군을 통하여 if(>)else if(==){if (>) else if(==)}로 비교군을 지속적으로 비교하는 것이다.
행작 열작은 for문으로 처리하면 ifelseif 안해도 됨.
회작 행작 열작, 회 큰 열 큰 행 작 이런 것은 조건에 맞게 for문으로 처리하기
이 종류의 함수들의 목적은 다음(특정) 좌표를 선정하는 것.
마지막에 다음(특정)좌표로 이동을 시켜야하며, 처리해야할 것들을 마무리하며 함수를 종료해야함
좌표 찾기, 아외 갱신해야할 것 찾기
*/
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

//func2()
/*
피해자의 선정
선정 문제는 비교군 잡고 다음 좌표나 특정 좌표 정하기 문제임.
비교군: Power, Recent 같은 조건들이나, 행작 열작 이런거
다른 문제에서 행작 열작 이런 것과 비교할 것들이 주어질 것이다. 이를 토대로 for문처리와 if else if문 처리

비교군을 통하여 if(>)else if(==){if (>) else if(==)}로 비교군을 지속적으로 비교하는 것이다.
행작 열작은 for문으로 처리하면 ifelseif 안해도 됨.
회작 행작 열작, 회 큰 열 큰 행 작 이런 것은 조건에 맞게 for문으로 처리하기
이 종류의 함수들의 목적은 다음(특정) 좌표를 선정하는 것.
마지막에 다음(특정)좌표로 이동을 시켜야하며, 처리해야할 것들을 마무리하며 함수를 종료해야함
좌표 찾기, 아외 갱신해야할 것 찾기
*/
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

//func3()
/*
    bfs()함수 호출 시작하자마자 visited[][]와 pre[][][] 초기화를 했다. 이렇게 해도 되는 이유는?
    -> 각 시뮬레이션마다 bfs()는 한 번 실행되고, 특정지점에서 특정 지점으로 가는 것만 찾는 거기에
    floodFill 상황에서는 이러면 안된다. 왜? Grouping이 목표이기 때문에.

    최단경로 찾기는 pre[][][2]로 목표 지점에서 최단경로를 시작점까지 역추적하는 것이다.
    최단거리에서 목표점이 visited[ty][tx] = 0은 과연 무슨 의미인가?

    OOB일 때 격자 벗어나는 경우 다시 들어오는 것 구현 
    (yy >= n) 상황 (yy < 0) 상황 어떻게 처리?
*/
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

//func4()
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

//func5()
/*
    8방향은 ddy, ddx이다.
    8방향에서 삐져나오는 것이 다시 들어오는 것 처리는 똑같다.
    처리해야할 것은?
    제약조건 고려해야하기
*/
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

//func6()
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

void attack(){
    if(visited[ty][tx] > 0){
        razer();
    }
    else{
        potan();
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

        for(int run = 1; run <= k; ++run){
            // local_init();
            fill(&attacked[0][0], &attacked[0][0] + 12 * 12, 0);
            ans = ay = ax = ty = tx = 0;

            findAttacker(run);

            findTarget();

            bfs();

            attack();

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