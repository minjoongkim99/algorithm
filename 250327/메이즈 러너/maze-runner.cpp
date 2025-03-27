#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int n, m, k;
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};

int arr[12][12]; // WALL, EXIT, EMPTY

struct player{
    int y, x, dist, died;
};
player P[12];

int len, ry, rx;
int ey, ex;

int point = 0;

bool canBreak(){
    for(int idx = 1; idx <= m; ++idx)
        if(P[idx].died == 0)
            return false;
    return true;
}

/*
    비교군 정하고 다음 좌표 탐색하기
    못갈수도 있으면 ny,nx는 현재 좌표로 처음에 초기화 해주기
    비교군보다 조건에 부합한다면
    비교값 갱신
    ny, nx 갱신
    ny, nx가 바뀐다면 무슨 일이 발생하는가?
    flag 변수.
*/
void moveRunner(){
    for(int idx = 1; idx <= m; ++idx){
        if(P[idx].died == 1) continue;

        int ny = P[idx].y;
        int nx = P[idx].x;
        int cur_dist = abs(ey - P[idx].y) + abs(ex - P[idx].x);
        int flag = 0;                           //

        for(int dir = 0; dir < 4; ++dir){
            int yy = P[idx].y + dy[dir];
            int xx = P[idx].x + dx[dir];
            if(yy < 1|| yy > n || xx < 1 || xx > n) continue;
            if(arr[yy][xx] > 0) continue;

            int next_dist = abs(ey - yy) + abs(ex - xx);
            if(cur_dist > next_dist){
                cur_dist = next_dist;
                ny = yy;
                nx = xx;
                flag = 1;
            }
        }

        if(flag == 1){
            P[idx].dist++;
        }

        P[idx].y = ny;
        P[idx].x = nx;
        if(P[idx].y == ey && P[idx].x == ex){
            P[idx].died = 1;
        }
    }
}

bool isIn(int y1, int x1, int y2, int x2){
    int flag1 = 0, flag2 = 0;
    if(y1 > n || x1 > n || y2 - 1 > n || x2 - 1 > n) return false;      /////////////////////
                            // y2 > n || x2 > n 이면 일부가 탐색이 안되는 이유를 생각해보자. y2 = n, x2 = n 을 못함
    for(int i = y1; i < y2; ++i){
        for(int j = x1; j < x2; ++j){
            if(arr[i][j] == -1)
                flag1 = 1;
            for(int idx = 1; idx <= m; ++idx){
                if(P[idx].died == 1) continue;
                else if(P[idx].y == i && P[idx].x == j){
                    flag2 = 1;
                }
            }
        }
    }
    
    if(flag1 == 1 && flag2 == 1) return true;
    else return false;
}

/*
    isIn(, , , )을 보면 i ~ i + 1이 아니다. j ~ j + 1이 아니다.
    탐색은 y1 <= y < y2이며, x1 <= x < x2이다.
    그런데 여기서 OOB 처리를 y2와 x2로 한다면,, 이건 문제다.
    findPos, isIn이 완점 탐색을 못하게 된다는 것임.
*/
void findPos(){
    for(int l = 1; l <= n + 1; ++l){
        for(int i = 1; i <= n; ++i){
            for(int j = 1; j <= n; ++j){
                if(isIn(i, j, i + l, j + l)){
                    len = l;
                    ry = i;
                    rx = j;
                    return;
                }
            }
        }
    }
}

/*
    tmp <- arr 때리고
    평행이동한 회전 (기준 좌표가 주어지는 회전임).
*/
void rotateArr(){
    int tmp[12][12];
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            tmp[i][j] = arr[i][j];

    for(int i = 0; i < len; ++i){
        for(int j = 0; j < len; ++j){
            arr[ry + i][rx + j] = tmp[ry + len - j - 1][rx + i];
            if(arr[ry + i][rx + j] > 0)     // 음수 절대 방지임. 음수면 안되는 이유는 벽을 -1로 설정했기 때문이다.
                arr[ry + i][rx + j]--;
        }
    }

    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            if(arr[i][j] == -1){
                ey = i;
                ex = j;
                return;
            }
        }
    }
}

/*
    배열 회전의 기본은
    for(int i = 0; i < m; ++i){
        for(int j = 0; j < m; ++j){
            arr[y + i][x + j] = tmp[y + m - j - 1][x + i];
        }
    }
    // tmp[][] 내용이 회전 이전의 좌표이고, arr[][]이 다음에 들어갈 곳이다.
        prev ->                     nxt
    즉, 관점을 보면 tmp[][]이전의 좌표를 다음 자리로 좌표이동을 시키는 것이다.
    구조체 관점에서 보자.
    구조체 좌표를 이동 시키려면 이전 좌표와 동일하다면
    다음 좌표로 이동을 시키는 것이다.
    단, 구조체 회전시에 모든 2중for문을 회전 탐색한다면
    IDX1이 (0, 0)에서 (2, 2)로 갔다가.
    (2, 2)탐색에서 다시 회전을 당해버린다. 회전은 이전 좌표로부터 한번만 당해야하는데, 여러번 당하는 경우가 생길 수 있다는 뜻이다.
*/
void rotatePerson(int idx){
    for(int i = 0; i < len; ++i){
        for(int j = 0; j < len; ++j){
            if(P[idx].y == ry + len - j - 1 && P[idx].x == rx + i){
                P[idx].y = ry + i;
                P[idx].x = rx + j;
                return;         // 회전은 한 번만 해야하는데, 특정 좌표에서 찾은 후 다음 좌표에서 탐색을 돌리는 것을 방지.
            }
        }
    }
}

/*
    처음에 player_map[][]을 만들어서, P[idx]들을 기입했다. (데이터 삽입)
    그런데, 이러면 왜 안되냐? 동시에 있을 수 있다.
    player_map[][]에 특정 좌표 여러 값을 담을 수가 없다. OverWrite 된다는 뜻.
    (2, 3)에서 idx = 1, idx = 5가 들어간다면 
    반복문에 의해 idx = 1의 좌표가 사라지게 되고, 이로 인해
    player_map[][] -> P[]시 정보가 누락된다.
 */
void rotatePeople(){
    for(int idx = 1; idx <= m; ++idx){
        if(P[idx].died == 1) continue;
        rotatePerson(idx);
    }
}

int main() {
    // Please write your code here.

    int T = 1;
    for(int test_case = 1; test_case <= T; ++test_case){
        // global_init();
        point = 0;
        cin >> n >> m >> k;
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j)
                cin >> arr[i][j];

        for(int idx = 1; idx <= m; ++idx){
            cin >> P[idx].y >> P[idx].x;
            P[idx].died = P[idx].dist = 0;
        }
        cin >> ey >> ex;
        arr[ey][ex] = -1;

        for(int run = 1; run <= k; ++run){
            //local_init();
            len = 0, ry = 0, rx = 0;

            moveRunner();

            if(canBreak()){
                break;
            }

            findPos();

            rotateArr();

            rotatePeople();
        }
        
        for(int idx = 1; idx <= m; ++idx)
            point += P[idx].dist;
        cout << point << '\n' << ey << ' ' << ex << '\n';
    }
    return 0;
}
