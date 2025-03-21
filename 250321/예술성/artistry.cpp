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

// FloodFill용 BFS암
// 전형적인 bfs(i, j) 큐가 빌 때까지 4방향 탐색 후 (OOB, 이미 방문, 같은 그룹 아니면 Pass)
// 큐에 넣고 방문처리하기.          -> 여기까지가 전형적인 FloodFill BFS이다.
// 특수 조건이 있다. 각 그룹 번호에 대한 실제 value 값, 각 그룹에 대한 원소 개수를 구해야하므로 
// 전형 BFS 조건 밑에 코드를 삽입하여 원하는 조건을 처리해야한다. vistied[][] <-> arr[][]
// expolre()은 BFS에서 할 수 가 없다. 아직 FloodFill 완전히 안 끝나서 visited[][]가 완성이 안됐으므로.
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

// 각 2차원 visisted[i][j], 4방향 탐색하여, 자기 그룹이 아닌 것을 찾아야한다.
// 타당성을 생각해보자
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

    // 십자가 회전 == 중점 기준 절반 회전시키기 (신발 끈).       i,          n/2,        n-1-i
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

    // 배열회전(시계방향) 절반만 회전. 4개의 절반을 회전 시키고 평행이동 시켜야함.
    for(int i = 0; i < n / 2; ++i){
        for(int j = 0; j < n / 2; ++j){
            arr[i][j] = tmp[n / 2 - j - 1][i];
            arr[n / 2 + 1 + i][j] = tmp[n / 2 + 1 + n / 2 - j - 1][i];
            arr[i][n / 2 + 1 + j] = tmp[n / 2 - j - 1][n / 2 + 1 + i];
            arr[n / 2 + 1 + i][n / 2 + 1 + j] = tmp[n / 2 + 1 + n / 2 - j - 1][n / 2 + 1 + i];
        }
    }
}

// 수식은 질문에 있고, 질문에 맞게 수식화. 그리고 수식화 필요한 것들은 곧 변수가 됨.
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