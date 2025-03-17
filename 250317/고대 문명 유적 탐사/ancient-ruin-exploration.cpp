#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int K, M;   // 반복 횟수, 유물 조각 개수
int arr[5][5];
int test[5][5];
int visited[5][5];
queue<int> jewel;

int rr = 0, ry = 0, rx = 0;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};


void showPos(){
    cout << "회전:" << rr << " 좌표:" << ry << "," << rx << '\n';
}

void showArr(){
    for(int i = 0; i < 5; ++i){
        for(int j = 0; j < 5; ++j){
            cout << arr[i][j] << ' ';
        }
        cout << "\n";
    }
}

void arrToTest(){
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 5; ++j)
            test[i][j] = arr[i][j];
}
void TestToArr(){
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 5; ++j)
            arr[i][j] = test[i][j];
}




void rotate(int rot, int y, int x){
    int tmp[5][5];

    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 5; ++j)
            tmp[i][j] = test[i][j];

    for(int r = 1; r <= rot; ++r){

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
    queue<pair<int,int>> q;
    q.push({i, j});
    visited[i][j] = 1;
    int cnt = 1;

    while(!q.empty()){
        int y = q.front().first, x = q.front().second;
        q.pop();

        for(int dir = 0; dir < 4; ++dir){
            int yy = y + dy[dir];
            int xx = x + dx[dir];

            if(yy < 0 || yy >= 5 || xx < 0 || xx >= 5) continue;
            if(visited[yy][xx]) continue;
            if(test[yy][xx] == test[y][x]){
                q.push({yy, xx});
                visited[yy][xx] = 1;
                cnt++;
            }
        }
    }

    if(cnt < 3) return 0;
    else return cnt;
}

int bfs2(int i, int j){
    queue<pair<int,int>> q, q2;
    q.push({i, j});
    q2.push({i, j});
    visited[i][j] = 1;
    int cnt = 1;

    while(!q.empty()){
        int y = q.front().first, x = q.front().second;
        q.pop();

        for(int dir = 0; dir < 4; ++dir){
            int yy = y + dy[dir];
            int xx = x + dx[dir];

            if(yy < 0 || yy >= 5 || xx < 0 || xx >= 5) continue;
            if(visited[yy][xx]) continue;
            if(arr[yy][xx] == arr[y][x]){
                q.push({yy, xx});
                q2.push({yy, xx});
                visited[yy][xx] = 1;
                cnt++;
            }
        }
    }

    if(cnt < 3) return 0;
    else{
        while(!q2.empty()){
            int y = q2.front().first, x = q2.front().second;
            q2.pop();
            arr[y][x] = 0;
        }
        return cnt;
    }
}

int findCnt(){
    fill(&visited[0][0], &visited[0][0] + 5 * 5, 0);
    int sum = 0;

    for(int i = 0; i < 5; ++i){
        for(int j = 0; j < 5; ++j){
            if(visited[i][j] == 0)
                sum += bfs(i, j);
        }
    }

    return sum;
}

void find_RR_RY_RX(){
    int cnt = 0;
    int nr = 5, ny = 0, nx = 0;

    for(int r = 1; r < 4; ++r){
        for(int j = 0; j < 3; ++j){
            for(int i = 0; i < 3; ++i){
                arrToTest();

                rotate(r, i, j);

                int val = findCnt();
                if(val > cnt){
                    cnt = val;
                    nr = r;
                    ny = i;
                    nx = j;

                    //cout << val << " " << nr << " " << ny << " " << nx << "\n";
                }
            }
        }
    }

    rr = nr;
    ry = ny;
    rx = nx;
}

int deleteVal(){
    fill(&visited[0][0], &visited[0][0] + 5 * 5, 0);

    int val = 0;
    for(int i = 0; i < 5; ++i){
        for(int j = 0; j < 5; ++j){
            if(visited[i][j] == 0)
                val += bfs2(i, j);
        }
    }

    return val;
}

void pushNewItem(){
    for(int j = 0; j < 5; ++j){
        for(int i = 4; i >= 0; --i){
            if(arr[i][j] == 0){
                int x = jewel.front();
                arr[i][j] = x;
                jewel.pop();
            }
        }
    }
}

int main() {
    // Please write your code here.

    int T = 1;
    for(int tc = 1; tc <= T; ++tc){
        // global_init();

        cin >> K >> M;
        for(int i = 0; i < 5; ++i)
            for(int j = 0; j < 5; ++j)
                cin >> arr[i][j];
        for(int i = 1; i <= M; ++i){
            int x;
            cin >> x;
            jewel.push(x);
        }

        // input END

        int point = 0;
        for(int run = 1; run <= K; ++run){
            // local_init();
            point = rr = ry = rx = 0;
            arrToTest();

            find_RR_RY_RX();

            arrToTest();

            rotate(rr, ry, rx);

            TestToArr();

            //showPos();
            //showArr();

            while(true){
                int sum = deleteVal();
                if(sum <= 0) break;

                point += sum;
                pushNewItem();
            }
            if(point == 0) break;

            cout << point << ' ';
        }
    }
    return 0;
}