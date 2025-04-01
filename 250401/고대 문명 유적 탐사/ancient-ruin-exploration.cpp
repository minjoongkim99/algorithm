#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

int k, m;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int arr[5][5];
int visited[5][5];
int test[5][5];

int rr = 0, ry = 0, rx = 0;
int nval = 0;

queue<int> wall;

int ans = 0;

void showTest(){
    for(int i = 0; i < 5; ++i){
        for(int j = 0; j < 5; ++j){
            cout << test[i][j] << ' ';
        }
        cout << '\n';
    }
}

void arrToTest(){
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 5; ++j)
            test[i][j] = arr[i][j];
}

void testToArr(){
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 5; ++j)
            arr[i][j] = test[i][j];
}

int bfs(int i, int j){
    queue<pair<int,int>> q;
    q.push({i, j});
    visited[i][j] = 1;
    int cnt = 1;

    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for(int dir = 0; dir < 4; ++dir){
            int yy = y + dy[dir];
            int xx = x + dx[dir];
            
            if(yy < 0 || yy >= 5 || xx < 0 || xx >= 5) continue;
            if(visited[yy][xx] > 0) continue;
            if(test[yy][xx] == test[y][x]){
                q.push({yy, xx});
                visited[yy][xx] = visited[y][x] + 1;
                cnt++;
            }
        }
    }
    if(cnt < 3) return 0;
    else return cnt;
}

int rotation(int rotate, int y, int x){
    int cnt = 0;
    int tmp[5][5];
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 5; ++j)
            tmp[i][j] = test[i][j];

    for(int r = 1; r <= rotate; ++r){
        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                test[y + i][x + j] = tmp[y + 3 - j - 1][x + i];
            }
        }

        for(int i = 0; i < 5; ++i)
            for(int j = 0; j < 5; ++j)
                tmp[i][j] = test[i][j];
    }

    fill(&visited[0][0], &visited[0][0] + 5 * 5, 0);
    for(int i = 0; i < 5; ++i){
        for(int j = 0; j < 5; ++j){
            if(visited[i][j] == 0)
                cnt += bfs(i, j);
        }
    }

    return cnt;
}   

//회전 목표: 1차가치 극대화, 각도 작, 열 작 행, 작
//유물 1차 획득: 서로 연결. 3개 이상 연결 되어 있으면 사라진다. 0이 된다
void findPos(){
   
    for(int rotate = 1; rotate <= 3; ++rotate){
        for(int j = 0; j < 3; ++j){
            for(int i = 0; i < 3; ++i){
                arrToTest();
                int val = rotation(rotate, i, j);
                if(val > nval){
                    nval = val;
                    rr = rotate;
                    ry = i;
                    rx = j;
                }
            }
        }
    }
}


void fillNewData(){
    for(int j = 0; j < 5; ++j){
        for(int i = 4; i >= 0; --i){
            if(test[i][j] == 0){
                test[i][j] = wall.front();
                wall.pop();
            }
            else continue;
        }
    }
}

int bfs2(int i, int j){
    queue<pair<int,int>> q, q2;
    q.push({i, j});
    q2.push({i, j});
    visited[i][j] = 1;
    int cnt = 1;

    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for(int dir = 0; dir < 4; ++dir){
            int yy = y + dy[dir];
            int xx = x + dx[dir];
            if(yy < 0 || yy >= 5 || xx < 0 || xx >= 5) continue;
            if(visited[yy][xx] > 0) continue;
            if(test[yy][xx] == test[y][x]){
                q.push({yy, xx});
                q2.push({yy, xx});
                visited[yy][xx] = visited[y][x] + 1;
                cnt++;
            }
        }
    }

    if(q2.size() < 3) return 0;
    else{
        int val = q2.size();

        while(!q2.empty()){
            int y = q2.front().first;
            int x = q2.front().second;
            test[y][x] = 0;
            q2.pop();
        }
        return val;
    }

}

int removeItem(){
    int sum = 0;
    fill(&visited[0][0], &visited[0][0] + 5 * 5, 0);
    for(int i = 0; i < 5; ++i){
        for(int j = 0; j < 5; ++j){
            if(visited[i][j] == 0)
                sum += bfs2(i, j);
        }
    }

    ans += sum;
    return sum;
}

int main() {

    /*
        5*5 격자 내에 3 * 3 배열 회전 arr[][] val은 7이하 자연수
        회전 목표: 1차가치 극대화, 각도 작, 열 작 행, 작

        유물 1차 획득: 서로 연결. 3개 이상 연결 되어 있으면 사라진다. 0이 된다

        벽면으로부터 숫자를 받아온다. 열 작 행 큰 순으로 채워진다.

        연쇄 획득: 채워지고 나서 3개 이상 일 수 있음. 없을 때까지 계속

        ---- 이게 1턴, k턴 반복. 없으면 즉시 종료

    */
    int T = 1;

    for(int test_case = 1; test_case <= T; ++test_case){
        // global_init();
        cin >> k >> m;
        for(int i = 0; i < 5; ++i)
            for(int j = 0; j < 5; ++j)
                cin >> arr[i][j];
        for(int i = 1; i <= m; ++i){
            int x;
            cin >> x;
            wall.push(x);
        }

        for(int run = 1; run <= k; ++run){
            // local_init();
            nval = ans = rr = ry = rx = 0;

            // test <- arr
            arrToTest();

            // 회전 목표에 부합하는 회전 개수와 좌표 찾기.
            findPos();
            //cout << "CNT:" << nval << " ROT" << rr << " " << ry << "," << rx << '\n';


            // 1차 획득 시키기.
            arrToTest();
            rotation(rr, ry, rx);

            int breakPoint = removeItem();
            if(breakPoint == 0)
                break;
            //showTest();
            //cout << "ANS " << ans << "\n";
            // 채우기
            fillNewData();
            //cout << "AFTER FILL\n";
            //showTest();

            // 연쇄 획득 여부 찾기
            while(true){
                fill(&visited[0][0], &visited[0][0] + 5 * 5, 0);
                int flag = removeItem();
                if(flag == 0) break;
                else fillNewData();
            }


            // arr <- test;
            testToArr();

            // 출력.
            cout << ans << ' ';
        }
    }
    return 0;
}