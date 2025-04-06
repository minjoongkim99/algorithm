#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int n, m;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int arr[25][25];
int visited[25][25];

int ncnt, nred, ny, nx;

int point = 0;

void redInit(){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(arr[i][j] == 0)
                visited[i][j] = 0;
        }
    }
}

pair<int,int> bfs(int i, int j){
    int cnt = 0, red = 0;

    queue<pair<int,int>> q;
    q.push({i, j});
    visited[i][j] = arr[i][j];
    cnt++;

    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for(int dir = 0; dir < 4; ++dir){
            int yy = y + dy[dir];
            int xx = x + dx[dir];

            if(yy < 0 | yy >= n || xx < 0 || xx >= n) continue;
            if(visited[yy][xx]) continue;

            if(arr[yy][xx] == arr[i][j]){
                q.push({yy, xx});
                visited[yy][xx] = arr[i][j];
                cnt++;
            }
            else if(arr[yy][xx] == 0){
                q.push({yy, xx});
                visited[yy][xx] = arr[i][j];
                cnt++;
                red++;
            }
        }
    }

    return{cnt, red};
}

void removeBomb(){
    int val = arr[ny][nx];
    queue<pair<int,int>> q;
    q.push({ny, nx});
    visited[ny][nx] = val;
    arr[ny][nx] = -2;
    int cnt = 1;

    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for(int dir = 0; dir < 4; ++dir){
            int yy = y + dy[dir];
            int xx = x + dx[dir];

            if(yy < 0 | yy >= n || xx < 0 || xx >= n) continue;
            if(visited[yy][xx]) continue;

            if(arr[yy][xx] == val){
                q.push({yy, xx});
                visited[yy][xx] = val;
                arr[yy][xx] = -2;
                cnt++;
            }
            else if(arr[yy][xx] == 0){
                q.push({yy, xx});
                visited[yy][xx] = val;
                arr[yy][xx] = -2;
                cnt++;
            }
        }
    }
    point += cnt * cnt;
}

/*
    총합 큰, 빨갱색 적은, 행 큰, 열 작 순으로
    행 큰, 열 작은 for문 조작으로 코드를 매우 간결하게 줄일 수 있음. (단, 행 + 열 이런건 안된다... 반례랑 이전 문제)
    반례: 포탑 부수기 문제.

    fill(&vistied[0][0], , 0);은 언제 해야하는가에 대해 항상 생각을 해야함.

    bfs()문에 다양한 format.
    bfs(i, j)로 param을 전달할 수 있고, (시작점을 전달한다는 의미임)
    bfs()가 void형이 아닌 int형이나 pair<int,int> 형 등 필요한 정보를 반환 받을 수 있게 해야함.
*/
void findTarget(){
    ncnt = nred = ny = nx = 0;

    for(int i = n - 1; i >= 0; --i){
        for(int j = 0; j < n; ++j){
            if(arr[i][j] <= 0) continue;
            if(visited[i][j] > 0) continue;

            pair<int,int> val = bfs(i, j);
            if(val.first > ncnt){
                ncnt = val.first;
                nred = val.second;
                ny = i;
                nx = j;
            }
            else if(val.first == ncnt){
                if(val.second < nred){
                    nred = val.second;
                    ny = i;
                    nx = j;
                }
            }

            redInit();
        }
    }
}

/*
    중력함수. 현재는 아랫방향으로 떨어진다.
    윗방향 우측방향 좌측방향에 대한 중력도 생각할 줄 알아야함.
    
    무조건적인 중력이 아님
    왜? 돌(-1)은 중력의 영향을 받지 않는다...

    중력 함수. for(j)   -> for(i) -> for(k 는 i 영향 받음)
    중력 조건을 받으려면 현재 탐색 구간[i][j]가 비어있어야한다. EMPTY 상태가 아니면 중력 불가 칸 (continue;)
    중력 조건을 받는 EMPTY라면 for(k 문으로) 탐색 시작.
    [k][j]가 EMPTY라면 중력으로 내릴게 없으므로 (continue);
    [k][j]가 제약조건(STOP)이라면 해당 [i][j]칸에 대한 추가적인 중력탐색이 필요가 없음. 떨어지지 않는다... break;
    [k][j]가 VALUE를 가지고 있다면, [i][j] <- [k][j] 처리하고, [k][j]를 EMPTY 상태로 만들어야한다.
*/
void gravity(){

    for(int j = 0; j < n; ++j){
        for(int i = n - 1; i >= 0; --i){
            if(arr[i][j] != -2) continue;

            for(int k = i - 1; k >= 0; --k){
                if(arr[k][j] == -2){
                    continue;
                }
                else if(arr[k][j] == -1){
                    break;
                }
                else{
                    arr[i][j] = arr[k][j];
                    arr[k][j] = -2;
                    break;
                }
            }
        }
    }
}

void rotate_left(){
    int tmp[25][25];
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            tmp[i][j] = arr[i][j];
    
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            arr[i][j] = tmp[j][n - i - 1];
        }
    }
}

void input(){
    cin >> n >> m;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cin >> arr[i][j];
        }
    }
}

int main() {
    // Please write your code here.
    int T = 1;

    for(int tc = 1; tc <= T; ++tc){
        //global_init();
        input();
        int t = 1;
        
        while(true){
            ncnt = nred = ny = nx = 0;
            fill(&visited[0][0], &visited[0][0] + 25 * 25, 0);
            // local_init();
            // (ncnt 총합), (nred는 빨강만)

            // 1. 가장 크기가 큰 폭탄 묶음 찾기.
            findTarget();

            if(ncnt < 2)
                break;

            fill(&visited[0][0], &visited[0][0] + 25 * 25, 0);
            removeBomb();

            // 2. 중력 작용.
            gravity();

            // 3. 반시계 방향 회전
            rotate_left();

            // 4. 중력 작용
            gravity();
        }

        cout << point << '\n';
    }
    return 0;
}

/*
격자 내 val -1, 0, 1 ~ m
-1: 검은색 돌, 0: 빨간색 돌, 1 ~ m 그 외 색
폭탄묶음이 더 없을 때까지 계속 반복.

1. 가장 크기가 큰 폭탄묶음(2개 이상이며 모두 같은 색깔이거나 빨간색 폭탄 포함한 것)
폭탄묶음은 연결되어이있어야하고, 빨간색 폭탄으로만은 아님..
가장 큰 폭탄 묶음이며, 같다면 빨간색이 가장 적은 것
빨간색이 같다면, 기준점 행큰, 기준점 열 작

2. 폭탄 제거. 중력 작용.
폭탄이 떨어지나, -1인 검은색 돌은 중력 작용 x.

3. 반시계 회전

4. 다시 중력 작용

이것을 round마다 반복한다.

총 점수 더이상 폭탄이 안 터질때까지...
*/