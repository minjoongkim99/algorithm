#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

int n, m, k;
int arr[21][21];
int visited[21][21];
int point = 0;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

vector<pair<int,int>> team[7];  // 1번 ~ m번 팀;

int cnt = 1;                    // 그룹 번호 + 1 됨.

void showEachTeam(){
    for(register int idx = 1; idx < cnt; ++idx){
        for(register int i = 0; i < team[idx].size(); ++i){
            cout << team[idx][i].first << ',' << team[idx][i].second << " ";
        }
        cout << '\n';
    }
}

void bfs(int i, int j, int idx){
    queue<pair<int,int>> q;
    q.push({i, j});
    visited[i][j] = idx;
    team[idx].push_back({i, j});

    int lx, ly;
    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for(register int dir = 0; dir < 4; ++dir){
            int yy = y + dy[dir];
            int xx = x + dx[dir];
            
            if(yy < 0 || yy >= n || xx < 0 || xx >= n) continue;
            if(visited[yy][xx]) continue;
            if(arr[yy][xx] < 2 || arr[yy][xx] > 3) continue;

            if(arr[yy][xx] == 2){
                visited[yy][xx] = idx;
                q.push({yy, xx});
                team[idx].push_back({yy, xx});
            }
            if(arr[yy][xx] == 3){
                ly = yy;
                lx = xx;
            }
        }
    }
    team[idx].push_back({ly, lx});
}

void grouping(){
    for(register int i = 0; i < n; ++i){
        for(register int j = 0; j < n; ++j){
            if(visited[i][j]) continue;
            if(arr[i][j] != 1) continue;
            else{
                bfs(i, j, cnt++);
            }
        }
    }
}

void moveEachTeam(){

    for(register int idx = 1; idx < cnt; ++idx){
        int ny, nx;

        for(register int dir = 0; dir < 4; ++dir){
            int yy = team[idx][0].first + dy[dir];
            int xx = team[idx][0].second + dx[dir];

            if(yy < 0 || yy >= n || xx < 0 || xx >= n) continue;
            if(yy == team[idx][1].first && xx == team[idx][1].second) continue;
            if(arr[yy][xx] == 0) continue;

            ny = yy;
            nx = xx;
        }

        for(register int i = team[idx].size() - 1; i > 0; --i){
            team[idx][i].first = team[idx][i - 1].first;
            team[idx][i].second = team[idx][i - 1].second;
        }
        
        team[idx][0].first = ny;
        team[idx][0].second = nx;
    }
}

pair<int,int> isHit(int y, int x){
    for(register int idx = 1; idx < cnt; ++idx){
        for(register int i = 0; i < team[idx].size(); ++i){
            if(team[idx][i].first == y && team[idx][i].second == x){
                return{idx, i + 1};
            }
        }
    }

    return {-1, -1};
}

void throwBall(int t){
    int hold = (t / n) % 4;
    int pos = t % n;
    pair<int,int> val;

    if(hold == 0){
        for(register int j = 0; j < n; ++j){
            val = isHit(pos, j);
            if(val.first > 0) break;
        }
    }
    else if(hold == 1){
        for(register int i = n - 1; i >= 0; --i){
            val = isHit(i, pos);
            if(val.first > 0) break;
        }
    }
    else if(hold == 2){
        for(register int j = n - 1; j >= 0; --j){
            val = isHit(n - pos - 1, j);
            if(val.first > 0) break;
        }
    }
    else if(hold == 3){
        for(register int i = 0; i < n; ++i){
            val = isHit(i, n - pos - 1);
            if(val.first > 0) break;
        }
    }

    if(val.first > 0){
        point += val.second * val.second;
        reverse(team[val.first].begin(), team[val.first].end());
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);  cin.tie(nullptr);

    int T = 1;
    for(int tc = 1; tc <= T; ++tc){
        cin >> n >> m >> k;
        for(register int i = 0; i < n; ++i)
            for(register int j = 0; j < n; ++j)
                cin >> arr[i][j];

        grouping();

        for(register int run = 0; run < k; ++run){

            moveEachTeam();

            throwBall(run);
        }

        cout << point << '\n';
    }

    return 0;
}