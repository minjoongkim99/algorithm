#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int n, m;

struct person{
    int cy, cx, ty, tx, died;
};
person P[32];

int dy[4] = {-1, 0, 0, 1};
int dx[4] = {0, -1, 1, 0};

int arr[17][17];
int visited[17][17];
int pre[17][17][2];     // [][][] 이유는
int t = 1;

void init(){
    fill(&visited[0][0], &visited[0][0] + 17 * 17, 0);
    fill(&pre[0][0][0], &pre[0][0][0] + 17 * 17 * 2, 0);
}

int checkFinsihed(){
    for(register int idx = 1; idx <= m; ++idx){
        if(P[idx].died == 0) return 0;
    }
    return 1;
}

int bfs(int cy, int cx, int ty, int tx){
    init();

    queue<pair<int,int>> q;
    q.push({cy,cx});
    visited[cy][cx] = 1;
    pre[cy][cx][0] = pre[cy][cx][1] = -1;

    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
        if(y == ty && x == tx)
            break;

        for(register int dir = 0; dir < 4; ++dir){
            int yy = y + dy[dir];
            int xx = x + dx[dir];
            if(yy < 1 || yy > n || xx < 1 || xx > n) continue;
            if(visited[yy][xx] || arr[yy][xx] == -1) continue;

            q.push({yy, xx});
            visited[yy][xx] = visited[y][x] + 1;
            pre[yy][xx][0] = y;
            pre[yy][xx][1] = x;
        }
    }

    return visited[ty][tx];
}

void movePerson(int idx){
    bfs(P[idx].cy, P[idx].cx, P[idx].ty, P[idx].tx);

    int cy = P[idx].ty, cx = P[idx].tx;
    
    while(true){
        int ny = pre[cy][cx][0];
        int nx = pre[cy][cx][1];
        if(ny == -1 && nx == -1) break;         ///////////
        if(ny == P[idx].cy && nx == P[idx].cx) break;
        cy = ny;
        cx = nx;
    }

    P[idx].cy = cy;
    P[idx].cx = cx;
}

void makeBlind(){
    for(register int idx = 1; idx <= m; ++idx){
        if(P[idx].died == 1) continue;
        if(P[idx].cy == P[idx].ty && P[idx].cx == P[idx].tx){
            P[idx].died = 1;
            arr[P[idx].cy][P[idx].cx] = -1;
        }
    }
}

void enterPerson(int idx){
    int cy = -1, cx = -1;
    int distance = 100000;

    for(register int i = 1; i <= n; ++i){
        for(register int j = 1; j <= n; ++j){
            if(arr[i][j] <= 0) continue;
            int d = bfs(i, j, P[idx].ty, P[idx].tx);
            if(d > 0 && distance > d){
                distance = d;
                cy = i;
                cx = j;
            }
        }
    }

    P[idx].cy = cy;
    P[idx].cx = cx;
    arr[P[idx].cy][P[idx].cx] = -1;
}

int main() {
    // Please write your code here.
    cin >> n >> m;
    for(register int i = 1; i <= n; ++i)
        for(register int j = 1; j <= n; ++j)
            cin >> arr[i][j];
    
    for(register int idx = 1; idx <= m; ++idx){
        cin >> P[idx].ty >> P[idx].tx;
        P[idx].cy = P[idx].cx = -1;
        P[idx].died = 0;
    }

    while(true){
        //cout << t << "!\n";
        int k = min(t, m + 1);
        for(register int idx = 1; idx < k; ++idx){
            if(P[idx].died == 1) continue;
            movePerson(idx);
            //cout << idx << "번 이동: " << P[idx].cy << " " << P[idx].cx << ".\n";
        }

        makeBlind();
        
        if(t <= m){
            enterPerson(t);
            //cout << t << "번 입장: "<< P[t].cy << " " << P[t].cx << "!\n";
        }

        int flag = checkFinsihed();
        if(flag == 1)
            break;

        t++;
    }

    cout << t << '\n';
    return 0;
}