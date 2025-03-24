#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;
int k, m;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int arr[5][5];
int test[5][5];
int visited[5][5];
queue<int> jewel;

int sum, rr, ry, rx = 0;

int point = 0;

void showTest(){
    cout << "TEST\n";
    for(int i = 0; i < 5; ++i){
        for(int j = 0; j < 5; ++j){
            cout << test[i][j] << '\t';
        }
        cout << '\n';
    }
}

void rotate(int r, int y, int x){
    int tmp[5][5];
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 5; ++j)
            tmp[i][j] = test[i][j] = arr[i][j];

    for(int rot = 1; rot <= r; ++rot){
        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                test[y + i][x + j] = tmp[y + 3 - j - 1][x + i];
            }
        }
        for(int i = 0; i < 5; ++i)
            for(int j = 0; j < 5; ++j)
                tmp[i][j] = test[i][j];
    }
}

int bfs(int i, int j){
    queue<pair<int,int>> q, q2;
    int cnt = 0;

    q.push({i, j});
    q2.push({i, j});
    visited[i][j] = 1;
    cnt++;

    while(!q.empty()){
        int y = q.front().first;    
        int x = q.front().second;
        q.pop();

        for(int dir = 0; dir < 4; ++dir){
            int yy = y + dy[dir];
            int xx = x + dx[dir];

            if(yy < 0 || yy >= 5 || xx < 0 || xx >= 5) continue;
            if(visited[yy][xx]) continue;
            if(test[yy][xx] == test[y][x]){
                q.push({yy, xx});
                q2.push({yy, xx});
                visited[yy][xx] = visited[y][x] + 1;
                cnt++;
            }
        }
    }
    if(cnt < 3) return 0;
    else{
        while(!q2.empty()){
            test[q2.front().first][q2.front().second] = 0;
            q2.pop();
        }
        return cnt;
    }
}

int explore(){
    fill(&visited[0][0], &visited[0][0] + 5 * 5, 0);
    int cnt = 0;
    for(int i = 0; i < 5; ++i){
        for(int j = 0; j < 5; ++j){
            if(visited[i][j]) continue;
            cnt += bfs(i, j);
        }
    }

    return cnt;
}

void findPos(){
    
    for(int r = 1; r < 4; ++r){
        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                rotate(r, i, j);
                //cout << r << "," << i << "," << j << "\n";
                //showTest();
                int val = explore();
                if(val > sum){
                    sum = val;
                    rr = r;
                    ry = i;
                    rx = j;
                }
            }
        }
    }
}

void insertJewel(){
    for(int j = 0; j < 5; ++j){
        for(int i = 4; i >= 0; --i){
            if(test[i][j] == 0){
                test[i][j] = jewel.front();
                jewel.pop();
            }
            else continue;
        }
    }
}

int main() {
    // Please write your code here.

    int T = 1;

    for(int test_case = 1; test_case <= T; ++test_case){
        //global_init();
        cin >> k >> m;
        for(int i = 0; i < 5; ++i)
            for(int j = 0; j < 5; ++j)
                cin >> arr[i][j];
        for(int i = 1; i <= m; ++i){
            int x;
            cin >> x;
            jewel.push(x);
        }

        for(int run = 1; run <= k; ++run){
            fill(&visited[0][0], &visited[0][0] + 5 * 5, 0);
            sum = rr = ry = rx = point = 0;

            // 3 * 3 격자 회전하는 것. 유물 1차 가치 극대화, 회전 작게, 열작, 행작
            // 회전 후 1차 가치 판단. 3개 이상 연결 된 경우 조각은 사라진다.
            findPos();
            
            //cout << "SUM" << sum << " Rot" << rr << " " << ry << "and" << rx << "\n";

            rotate(rr, ry, rx);
            fill(&visited[0][0], &visited[0][0] + 5 * 5, 0);
            point += explore();
            //showTest();

            // jewel로부터 열작 행큰 순으로 test[][]에 추가한다.
            insertJewel();
            //showTest();

            // 연쇄획득. 다시 test[][]를 찾는다. bfs하면서 3개이상 없을 때 까지 무한 반복.
            while(true){
                fill(&visited[0][0], &visited[0][0] + 5 * 5, 0);
                int cnt = explore();
                //cout << "WHILE\n";
                //showTest();
                if(cnt < 3)
                    break;
                point += cnt;
                insertJewel();
            }


            for(int i = 0; i < 5; ++i)
                for(int j = 0; j < 5; ++j)
                    arr[i][j] = test[i][j];
            if(point == 0)
                break;
            else cout << point << ' ';
        }


    }
    return 0;
}