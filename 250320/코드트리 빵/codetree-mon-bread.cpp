#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int n, m;

int dy[4] = {-1, 0, 0, 1};
int dx[4] = {0, -1, 1, 0};

int arr[17][17];
int visited[17][17];
int pre[17][17][2];

struct player{
    int cy, cx, ey, ex, died;
};
player P[32];

void showArr(){
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            cout << arr[i][j] << '\t';
        }
        cout << '\n';
    }
}

void showPlayer(){
    for(int i = 1; i <= m; ++i){
        if(P[i].died == 1) cout << i << " DIED\n";
        else cout << i << ": "<< P[i].cy << "," << P[i].cx << "\n";
    }
}

bool canBreak(){
    for(int i = 1; i <= m; ++i){
        if(P[i].died == 0) return false;
    }
    return true;
}

int bfs(int cy, int cx, int ey, int ex){
    fill(&visited[0][0], &visited[0][0] + 17 * 17, 0);
    fill(&pre[0][0][0], &pre[0][0][0] + 17 * 17 * 2, 0);

    queue<pair<int,int>> q;
    q.push({cy, cx});
    visited[cy][cx] = 1;
    pre[cy][cx][0] = pre[cy][cx][1] = -1;

    while(!q.empty()){
        int y = q.front().first, x = q.front().second;
        if(y == ey && x == ex) break;
        q.pop();

        for(int dir = 0; dir < 4; ++dir){
            int yy = y + dy[dir];
            int xx = x + dx[dir];

            if(yy < 1 || yy > n || xx < 1 || xx > n) continue;
            if(visited[yy][xx]) continue;
            if(arr[yy][xx] == -1) continue;

            q.push({yy, xx});
            visited[yy][xx] = visited[y][x] + 1;
            pre[yy][xx][0] = y;
            pre[yy][xx][1] = x;
        }
    }

    return visited[ey][ex];
}

void nextStep(int idx){
    int cy = P[idx].ey;
    int cx = P[idx].ex;

    while(true){
        int ny = pre[cy][cx][0];
        int nx = pre[cy][cx][1];

        if(ny == P[idx].cy && nx == P[idx].cx){
            break;
        }

        cy = ny;
        cx = nx;
    }

    P[idx].cy = cy;
    P[idx].cx = cx;
}

void movePlayer(int t){

    for(int i = 1; i < t; ++i){
        if(P[i].died == 1) continue;

        bfs(P[i].cy, P[i].cx, P[i].ey, P[i].ex);

        nextStep(i);
    }
}

void makeBlind(){
    for(int i = 1; i <= m; ++i){
        if(P[i].died == 1) continue;
        if(P[i].cy == P[i].ey && P[i].cx == P[i].ex){
            P[i].died = 1;
            arr[P[i].cy][P[i].cx] = -1;
        }
    }
}

void entering(int idx){
    int posY = 0, posX = 0;
    int distance = 1000000;

    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            if(arr[i][j] <= 0) continue;
            int next_dist = bfs(i, j, P[idx].ey, P[idx].ex);
            if(next_dist == 0) continue;

            if(distance > next_dist){
                distance = next_dist;
                posY = i;
                posX = j;
            }
        }
    }

    arr[posY][posX] = -1;
    P[idx].cy = posY;
    P[idx].cx = posX;
}

int main() {
    // Please write your code here.
    
    //global_init()
    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            cin >> arr[i][j];

    for(int i = 1; i <= m; ++i){
        cin >> P[i].ey >> P[i].ex;
        P[i].cy = P[i].cx = P[i].died = 0;
    }

    int t = 1;

    while(true){          // 수정
        // 종료 조건.

        movePlayer(min(t, m + 1));
        //cout << "움직인 후\n";
        //showPlayer();

        makeBlind();

        if(t < m + 1)
            entering(t);
        //cout << "들어온 후\n";
        //showPlayer();

        if(canBreak())
            break;

        //showArr();

        //cout << "\n";

        t++;
    }
    cout << t << '\n';
    return 0;
}