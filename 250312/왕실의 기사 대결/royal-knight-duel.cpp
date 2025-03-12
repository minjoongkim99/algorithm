#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
int L, N, Q; // 주어진 조건

int knight[43][43];
int arr[43][43];
int visited[43][43];

struct rectangle{
    int r, c, h, w, k, s;
};
rectangle R[33];
int mov_idx[33];

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

void local_init(){
    fill(&mov_idx[0], &mov_idx[0] + 33, 0);

    for(register int i = 1; i <= L; ++i)
        for(register int j = 1; j <= L; ++j)
            knight[i][j] = visited[i][j] = 0;
}

void knightToArr(){
    for(register int idx = 1; idx <= N; ++idx){
        if(R[idx].k <= 0) continue;
        // 이중 포문 R[idx].r R[idx].c 부등호에 넣는 거 안한 실수.
        for(register int i = R[idx].r; i < R[idx].r + R[idx].h; ++i)
            for(register int j = R[idx].c; j < R[idx].c + R[idx].w; ++j)
                knight[i][j] = idx;
    }   
}

void push_knight(int idx, int dir){
    queue<pair<int,int>> q;
    for(register int i = 1; i <= L; ++i){
        for(register int j = 1; j <= L; ++j){
            if(knight[i][j] == idx){
                q.push({i, j});
                visited[i][j] = idx;
            }
        }
    }
    mov_idx[idx] = 1;

    while(!q.empty()){
        int r = q.front().first, c = q.front().second;
        q.pop();

        for(register int d = 0; d < 4; ++d){
            int rr = r + dr[d];
            int cc = c + dc[d];

            if(rr < 1 || rr > L || cc < 1 || cc > L) continue;
            if(visited[rr][cc]) continue;
            if(arr[rr][cc] == 2) continue;

            if(knight[rr][cc] == knight[r][c]){
                q.push({rr, cc});
                visited[rr][cc] = knight[rr][cc];
                mov_idx[knight[rr][cc]] = 1;
            }
            if(d == dir && knight[rr][cc] > 0){
                q.push({rr, cc});
                visited[rr][cc] = knight[rr][cc];
                mov_idx[knight[rr][cc]] = 1;
            }
        }
    }
}

bool canPush(int idx, int dir){
    for(register int i = 1; i <= L; ++i){
        for(register int j = 1; j <= L; ++j){
            if(visited[i][j] <= 0) continue;

            int rr = i + dr[dir];
            int cc = j + dc[dir];

            if(rr < 1 || rr > L || cc < 1 || cc > L) return false;
            if(arr[rr][cc] == 2)    return false;
        }
    }
    return true;
}

void push_start(int dir){
    for(register int idx = 1; idx <= N; ++idx){
        if(R[idx].k <= 0) continue;
        if(mov_idx[idx] > 0){
            R[idx].r += dr[dir];
            R[idx].c += dc[dir];
        }
    }
}

void calc_HP(int idx, int dir){
    for(register int k = 1; k <= N; ++k){
        if(R[k].k <= 0) continue;
        if(k == idx) continue;
        if(mov_idx[k] == 0) continue;

        for(register int i = R[k].r; i < R[k].r + R[k].h; ++i){
            for(register int j = R[k].c; j < R[k].c + R[k].w; ++j){
                if(arr[i][j] == 1){
                    R[k].k--;
                    R[k].s++;
                }
            }
        }
    }
}

int getScore(){
    int sum = 0;
    for(register int idx = 1; idx <= N; ++idx)
        if(R[idx].k > 0)
            sum += R[idx].s;

    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);  cin.tie(nullptr);

    int T = 1;
    for(register int tc = 1; tc <= T; ++tc){
        //global_init();

        cin >> L >> N >> Q;

        for(register int i = 1; i <= L; ++i)
            for(register int j = 1; j <= L; ++j)
                cin >> arr[i][j];
        
        for(register int idx = 1; idx <= N; ++idx){
            cin >> R[idx].r >> R[idx].c >> R[idx].h >> R[idx].w >> R[idx].k;
            R[idx].s = 0;
        }

        for(register int query = 1; query <= Q; ++query){
            local_init(); // 작성해야함

            int idx, dir;
            cin >> idx >> dir;

            if(R[idx].k <= 0) continue;

            knightToArr();

            push_knight(idx, dir);      // BFS 돌리기.

            if(canPush(idx, dir)){      // vistied[][] > 0 활용하여 OOB나 == 1 찾기.
                push_start(dir);        // 밀 수 있으면 진짜 밀기. struct || [][]

                calc_HP(idx, dir);
            }
        }
        cout << getScore() << '\n';
    }

    return 0;
}
