#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int n;
int arr[31][31], visited[31][31]; // bfs니 바로.
int point = 0;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
int idx[901], idx_cnt[900];
int idx_near[901][901];

void init(){
    fill(&idx[0], &idx[0] + 901, 0);
    fill(&idx_cnt[0], &idx_cnt[0] + 901, 0);
    fill(&visited[0][0], &visited[0][0] + 31 * 31, 0);
    fill(&idx_near[0][0], &idx_near[0][0] + 901 * 901, 0);
}

void bfs(int i, int j, int val){
    queue<pair<int,int>> q;
    q.push({i, j});
    visited[i][j] = val;
    idx[val] = arr[i][j];               // KICK
    idx_cnt[val]++;                     // KICK

    while(!q.empty()){
        int y = q.front().first, x = q.front().second;
        q.pop();

        for(register int dir = 0; dir < 4; ++dir){
            int yy = y + dy[dir];
            int xx = x + dx[dir];
            if(yy < 0 || yy >= n || xx < 0 || xx >= n) continue;
            if(visited[yy][xx]) continue;

            if(arr[yy][xx] == arr[i][j]){
                q.push({yy, xx});
                visited[yy][xx] = val;
                idx_cnt[val]++;         // KICK
            }
        }
    }
}

int floodfill(){
    int cnt = 1;
    for(register int i = 0; i < n; ++i){
        for(register int j = 0; j < n; ++j){
            if(visited[i][j]) continue;
            else{
                bfs(i, j, cnt);     // cnt 추가해야하는 이유.
                cnt++;
            }
        }
    }
    return cnt;
}

void find_idx_near(){       // 변수의 의미에 대해서 visited[][], arr[][];
    for(register int i = 0; i < n; ++i){
        for(register int j = 0; j < n; ++j){
            for(register int dir = 0; dir < 4; ++dir){
                int yy = i + dy[dir];
                int xx = j + dx[dir];
                if(yy < 0 || yy >= n || xx < 0 || xx >= n) continue;
                if(visited[yy][xx] != visited[i][j]){
                    idx_near[visited[i][j]][visited[yy][xx]]++;
                }
            }
        }
    } // 여기서는 arr이 아닌 visited[][]를 봐야하는 이유를 바로 생각. 다른 변수로 놀 수 있음.
}

void getPoint(int cnt){
    for(register int i = 1; i < cnt; ++i){
        for(register int j = i + 1; j < cnt; ++j){
            point += (idx_cnt[i] + idx_cnt[j]) * idx[i] * idx[j] * idx_near[i][j];
        }
    }
}

void rotateCross(){
    int tmp[31][31];
    for(register int i = 0; i < n; ++i)
        for(register int j = 0; j < n; ++j)
            tmp[i][j] = arr[i][j];

    for(register int i = 0; i < n / 2; ++i){
        arr[i][n / 2] = tmp[n / 2][n - 1 - i];
        arr[n / 2][i] = tmp[i][n / 2];
        arr[n - i - 1][n / 2] = tmp[n / 2][i];
        arr[n / 2][n - 1 - i] = tmp[n - 1 - i][n / 2];
    }
}

void rotateRight(){
    int tmp[31][31];
    for(register int i = 0; i < n; ++i)
        for(register int j = 0; j < n; ++j)
            tmp[i][j] = arr[i][j];
    
    for(register int i = 0; i < n / 2; ++i){
        for(register int j = 0; j < n / 2; ++j){
            arr[i][j] = tmp[n / 2 - j - 1][i];
            arr[n / 2 + 1 + i][j] = tmp[n / 2 + 1 + n / 2 - j - 1][i];
            arr[i][j + n / 2 + 1] = tmp[n / 2 - j - 1][i + n / 2 + 1];
            arr[n / 2 + 1 + i][j + n / 2 + 1] = tmp[n / 2 + 1 + + n / 2 - j - 1][n / 2 + 1 + i];
        }
    }
}

int main() {
    cin >> n;
    for(register int i = 0; i < n; ++i)
        for(register int j = 0; j < n; ++j)
            cin >> arr[i][j];
    
    int T = 1;

    for(register int tc = 0; tc < T; ++tc){
        for(register int r = 0; r < 4; ++r){
            init();

            int cnt = floodfill();

            find_idx_near();

            getPoint(cnt);

            rotateCross();

            rotateRight();
        }
    }

    cout << point << '\n';
    return 0;
}