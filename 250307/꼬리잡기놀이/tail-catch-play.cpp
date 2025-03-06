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

/*  BFS 기본 근간.
    큐 선언 -> 입력좌표 큐 삽입. 방문처리
    큐가 빌 때까지 좌표뽑고 pop() -> 4방향 돌면서 yy,xx 탐색하며 OOB와 방문여부 확인
    조건에 맞으면 큐 삽입 후 방문처리

    이 규격이다. 이제 여기서 문제에서 요구하는 특수조건들을 고려, 삽입하면 된다.

    해당 문제에서는 1. 큐에 넣을 때 team[idx]에도 좌표를 같이 삽입한다.
    2. arr[yy][xx] 2미만 3초과는 보지 않는다.
    3. arr[yy][xx] == 2인 경우와 arr[yy][xx] == 3인 경우 나누어 처리한다.
*/
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

/*  for(i = n - 1; i > 0; --i)      [0]은 대신 어떻게 해야할까에 대한 선처리가 필요함
        arr[i] = arr[i - 1];        // tmp 없이도 밀어내기가 가능한 기술
    Q:  for(int i = 0; i < n - 1; ++i)
            arr[i] = arr[i + 1]     이건 왜 안되는가?????       갱신이 앞에것이 된다.
    애매하면 tmp[];;;;;
    ny, nx이 대입 방식이 왜 필연적으로 되는지 정당성을 판단해야한다. 왜 ny, nx를 대입할 수 있을까?
*/
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

//  무엇을 반환해야하는가?
pair<int,int> isHit(int y, int x){
    for(register int idx = 1; idx < cnt; ++idx){
        for(register int i = 0; i < team[idx].size(); ++i){
            if(team[idx][i].first == y && team[idx][i].second == x){

                return{idx, i + 1};             //

            }
        }
    }

    return {-1, -1};                            // for debug
}

/*  사분면 공식 = (t / n) % 4;
    pos = t % n;          이해해보자. 1-indexed 이면 어려워지므로 0-indexed 화가 나을듯
*/
void throwBall(int t){
    int hold = (t / n) % 4;
    int pos = t % n;

    pair<int,int> val;

    if(hold == 0){              //      (pos, j)
        for(register int j = 0; j < n; ++j){        //
            val = isHit(pos, j);
            if(val.first > 0) break;
        }
    }
    else if(hold == 1){         //      (i, pos)
        for(register int i = n - 1; i >= 0; --i){   //
            val = isHit(i, pos);
            if(val.first > 0) break;
        }
    }
    else if(hold == 2){         //      (n - pos - 1, j)임에 유의
        for(register int j = n - 1; j >= 0; --j){   //
            val = isHit(n - pos - 1, j);
            if(val.first > 0) break;
        }
    }
    else if(hold == 3){         //      (i, n - pos - 1)임에 유의
        for(register int i = 0; i < n; ++i){        //
            val = isHit(i, n - pos - 1);
            if(val.first > 0) break;
        }
    }

    /*  vector 라이브러리 함수는 sort(), reverse() 등이 있다.
        알아두면 매우 유용할 것이다. 여기서 reverse()가 쓰이는 이유는?
    */
    if(val.first > 0){
        point += val.second * val.second;
        reverse(team[val.first].begin(), team[val.first].end());
    }
}

/*  해당 문제는 뱀과 같다. 뱀은 휘어져있다. (심지어 Cycle을 만들어내는 경우도 있다!)
    뱀과 같은 문제는 struct || pair<int,int>로 배열에 담아두는 것이 효율적일 수 있다.
    -> 미로타워 디펜스 문제 복기. 일직선에 있지 않고 꺾인 것들을 pair<int,int> [n]에 push_back()
    하여 일직선화 시키는 방안을 고려해야함
*/

int main() {
    int T = 1;
    for(int tc = 1; tc <= T; ++tc){
        // init_global();

        cin >> n >> m >> k;
        for(register int i = 0; i < n; ++i)
            for(register int j = 0; j < n; ++j)
                cin >> arr[i][j];

        /*  2차원 배열에서 분리되어있는 그룹들을 그룹 번호를 지정해줘야한다. 
            2중 for문 돌리며, 방문하지 않았다면 BFS(i, j, idx++||cnt++)
            다만, 여기 문제는 시작점이 특정 조건이어야한다. == 1에서만 해야 효율적임 왜일까?
        */
        grouping();

        for(register int run = 0; run < k; ++run){
            moveEachTeam();

            throwBall(run);
        }

        cout << point << '\n';
    }

    return 0;
}
