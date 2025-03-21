#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
int n;

int arr[31][31];
int visited[31][31];
int group_val[931];
int group_cnt[931];
int nearby[931][931];
int idx = 1;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int point = 0;

void bfs(int i, int j){
    queue<pair<int,int>> q;
    q.push({i, j});
    visited[i][j] = idx;

    group_val[idx] = arr[i][j];
    group_cnt[idx]++;

    while(!q.empty()){
        int y = q.front().first;
        int x=  q.front().second;
        q.pop();

        for(int dir = 0; dir < 4; ++dir){
            int yy = y + dy[dir];
            int xx = x + dx[dir];

            if(yy < 0 || yy >= n || xx < 0 || xx >= n) continue;
            if(visited[yy][xx]) continue;
            if(arr[yy][xx] != arr[y][x]) continue;

            q.push({yy, xx});
            visited[yy][xx] = idx;
            group_cnt[idx]++;
        }
    }
}

void floodFill(){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(visited[i][j] != 0) continue;
            bfs(i, j);
            idx++;
        }
    }
}

void explore(){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            
            for(int dir = 0; dir < 4; ++dir){
                int yy = i + dy[dir];
                int xx = j + dx[dir];
                if(yy < 0 || yy >= n || xx < 0 || xx >= n) continue;
                if(visited[yy][xx] != visited[i][j]){
                    nearby[visited[i][j]][visited[yy][xx]]++;
                }
            }
        }
    }
}

void rotateCross(){
    int tmp[31][31];
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            tmp[i][j] = arr[i][j];

    for(int i = 0; i < n / 2; ++i){
        arr[i][n / 2] = tmp[n / 2][n - 1 - i];
        arr[n / 2][n - 1 - i] = tmp[n - 1 - i][n / 2];
        arr[n - 1 - i][n / 2] = tmp[n / 2][i];
        arr[n / 2][i] = tmp[i][n / 2];
    }
}

void rotateRight(){
    int tmp[31][31];
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            tmp[i][j] = arr[i][j];    

    for(int i = 0; i < n / 2; ++i){
        for(int j = 0; j < n / 2; ++j){
            arr[i][j] = tmp[n / 2 - j - 1][i];
            arr[n / 2 + 1 + i][j] = tmp[n / 2 + 1 + n / 2 - j - 1][i];
            arr[i][n / 2 + 1 + j] = tmp[n / 2 - j - 1][n / 2 + 1 + i];
            arr[n / 2 + 1 + i][n / 2 + 1 + j] = tmp[n / 2 + 1 + n / 2 - j - 1][n / 2 + 1 + i];
        }
    }
}

void getPoint(){
    for(int i = 1; i < idx; ++i){
        for(int j = i + 1; j < idx; ++j){
            point += (group_cnt[i] + group_cnt[j]) * group_val[i] * group_val[j] * nearby[i][j];
        }
    }
}

int main() {
    // Please write your code here.
    int T = 1;
    
    for(int test_case = 1; test_case <= T; ++test_case){
        cin >> n;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                cin >> arr[i][j];


        for(int run = 0; run < 4; ++run){
            fill(&visited[0][0], &visited[0][0] + 31 * 31, 0);
            fill(&group_val[0], &group_val[0] + 931, 0);
            fill(&group_cnt[0], &group_cnt[0] + 931, 0);
            fill(&nearby[0][0], &nearby[0][0] + 931 * 931, 0);
            idx = 1;

            floodFill();

            explore();

            getPoint();

            rotateCross();

            rotateRight();
        }

        cout << point << '\n';
    }
    return 0;
}