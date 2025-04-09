#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, m;
int arr[17][17];
int visited[17][17];
int pre[17][17][2];

struct person{
    int cx, cy, tx, ty, died;
};
person P[32];
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};

int bfs(int cx, int cy, int tx, int ty){
    fill(&visited[0][0], &visited[0][0] + 17 * 17, 0);      ////
    fill(&pre[0][0][0], &pre[0][0][0] + 17 * 17 * 2, 0);    ////

    queue<pair<int,int>> q;
    q.push({cx, cy});
    visited[cx][cy] = 1;

    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        if(x == tx && y == ty) break;                       ////

        for(int dir = 0; dir < 4; dir++){
            int xx = x + dx[dir];
            int yy = y + dy[dir];
            if(xx < 1 || xx > n || yy < 1 || yy > n) continue;
            if(visited[xx][yy]) continue;
            if(arr[xx][yy] == -1) continue;                 ////
            
            q.push({xx, yy});
            visited[xx][yy] = visited[x][y] + 1;
            pre[xx][yy][0] = x;                             ////
            pre[xx][yy][1] = y;                             ////
        }
    }
    if(visited[tx][ty] == 0) return 10000001;               ////
    else return visited[tx][ty];
}

void movePerson(int idx){
    int ny = 0, nx = 0;
    int distance = bfs(P[idx].cx, P[idx].cy, P[idx].tx, P[idx].ty);
    int cx = P[idx].tx, cy = P[idx].ty;     // garbage value 보단 유용하게 초깃값 설정.

    while(true){
        nx = pre[cx][cy][0];
        ny = pre[cx][cy][1];
        if(nx == P[idx].cx && ny == P[idx].cy){
            break;
        }
        cx = nx;
        cy = ny;
    }
    P[idx].cx = cx;
    P[idx].cy = cy;
}

void makeBlind(){
    for(int idx = 1; idx <= m; idx++){
        if(P[idx].died == 1) continue;
        if(P[idx].cx == P[idx].tx && P[idx].cy == P[idx].ty){
            P[idx].died = 1;
            arr[P[idx].cx][P[idx].cy] = -1;
        }
    }
}

// 문제 순서대로 구현보다, 로직대로 구현하는 것이 낫다.
void entering(int idx){
    int distance = 10000000;
    int nx = 0, ny = 0;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(arr[i][j] != 1) continue;
            int d = bfs(i, j, P[idx].tx, P[idx].ty); 
            if(distance > d){                   // 좌표탐색 후 갱신하는 문제
                distance = d;
                nx = i;
                ny = j;
            }
        }
    }
    P[idx].cx = nx;
    P[idx].cy = ny;
    arr[nx][ny] = -1;
}

bool canEnd(){
    for(int idx = 1; idx <= m; idx++){
        if(P[idx].died == 0) return false;
    }
    return true;
}

int main() {
    // 여기에 코드를 작성해주세요.
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cin >> arr[i][j];       // 벽은 -1로 처리할 것이다.
        }
    }
    for(int idx = 1; idx <= m; idx++){
        cin >> P[idx].tx >> P[idx].ty;
        P[idx].died = P[idx].cx = P[idx].cy = 0;
    }

    int t = 1;              // t = 0 -> t++;로 while(true)문 테스트
    while(true){
        int nxt = min(t, m + 1);            //
        for(int idx = 1; idx < nxt; idx++){
            if(P[idx].died == 1) continue;
            else movePerson(idx);
        }

        makeBlind();

        if(t <= m)
            entering(t);

        if(canEnd())
            break;
        
        t++;
    }
    cout << t << "\n";
    return 0;
}
