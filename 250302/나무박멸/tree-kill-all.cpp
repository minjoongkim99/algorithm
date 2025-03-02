#include <iostream>
using namespace std;

int n, m, k, c;
int arr[21][21]; // == -1 벽, 0 빈칸.
int killer[21][21];
int tot = 0;

int ddy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int ddx[8] = {0, 1, 1, 1, 0, -1, -1, -1};

void showArr(){
    for(register int i = 0; i < n; ++i){
        for(register int j = 0; j < n; ++j){
            cout << arr[i][j] << '\t';
        }
        cout << '\n';
    }
}

void showKiller(){
    for(register int i = 0; i < n; ++i){
        for(register int j = 0; j < n; ++j){
            cout << killer[i][j] << '\t';
        }
        cout << '\n';
    }
}

void growth(){
    // 동시에 나무의 성장. 동시에 일어나는 함수란?
    for(register int i = 0; i < n; ++i){
        for(register int j = 0; j < n; ++j){
            if(arr[i][j] <= 0) continue;
            int cnt = 0;
            for(register int dir = 0; dir < 8; dir = dir + 2){
                int ny = i + ddy[dir];
                int nx = j + ddx[dir];

                if(ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
                if(arr[ny][nx] > 0)
                    cnt++;
            }
            arr[i][j] += cnt;
        }
    }
}

void makeNew(){
    int tmp[21][21];
    for(register int i = 0; i < n; ++i)
        for(register int j = 0; j < n; ++j)
            tmp[i][j] = arr[i][j];

    for(register int i = 0; i < n; ++i){
        for(register int j = 0; j < n; ++j){
            if(arr[i][j] <= 0) continue;
            if(killer[i][j] > 0) continue;      // 없어도 될듯

            int cnt = 0;
            for(register int dir = 0; dir < 8; dir = dir + 2){
                int ny = i + ddy[dir];
                int nx = j + ddx[dir];
                
                if(ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
                if(arr[ny][nx] != 0 || killer[ny][nx] > 0) continue;
                else cnt++;
            }
            if(cnt > 0){
                for(register int dir = 0; dir < 8; dir = dir + 2){
                    int ny = i + ddy[dir];
                    int nx = j + ddx[dir];
                    if(ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
                    if(killer[ny][nx] > 0) continue;
                    if(arr[ny][nx] == 0){
                        tmp[ny][nx] += (arr[i][j] / cnt); // +=
                    }                       /////
                }
            }
        }
    }
    for(register int i = 0; i < n; ++i)
        for(register int j = 0; j < n; ++j)
            arr[i][j] = tmp[i][j];
}

pair<int,int> findPos(){
    int ny = -1, nx = -1, sum = -1;

    for(register int i = 0; i < n; ++i){
        for(register int j = 0; j < n; ++j){
            if(arr[i][j] <= 0 || killer[i][j] > 0){
                if(sum < arr[i][j]){
                    ny = i;
                    nx = j;
                    sum = arr[i][k];
                }
            }
            else if(arr[i][j] > 0){
                int cnt = arr[i][j];

                for(register int dir = 1; dir < 8; dir = dir + 2){
                    for(register int len = 1; len <= k; ++len){
                        int yy = i + len * ddy[dir];
                        int xx = j + len * ddx[dir];
                        if(yy < 0 || yy >= n || xx < 0 || xx >= n) break;
                        if(arr[yy][xx] <= 0) break;
                        else cnt += arr[yy][xx];
                    }
                }

                if(sum < cnt){
                    ny = i;
                    nx = j;
                    sum = cnt;
                }
            }
        }
    }

    return {ny, nx};
}

void attack(int i, int j){
    killer[i][j] = c + 1;
    if(arr[i][j] <= 0)  return;

    tot += arr[i][j];
    arr[i][j] = 0;

    for(register int dir = 1; dir < 8; dir = dir + 2){
        for(register int len = 1; len <= k; ++len){
            int yy = i + len * ddy[dir];
            int xx = j + len * ddx[dir];
            if(yy < 0 || yy >= n || xx < 0 || xx >= n) break;
            if(arr[yy][xx] <= 0){
                killer[yy][xx] = c + 1;
                break;
            }
            else{
                tot += arr[yy][xx];
                killer[yy][xx] = c + 1;
                arr[yy][xx] = 0;
            }
        }
    }
}

void decreaseKiiler(){
    for(register int i = 0; i < n; ++i){
        for(register int j = 0; j < n; ++j)
            if(killer[i][j] > 0) 
                killer[i][j]--;
    }
}

int main() {
    // Please write your code here.
    cin >> n >> m >> k >> c;
    for(register int i = 0; i < n; ++i)
        for(register int j = 0; j < n; ++j)
            cin >> arr[i][j];

    int T = 1;

    for(register int tc = 1; tc <= T; ++tc){
        for(register int run = 1; run <= m; ++run){
            growth(); // 동시

            makeNew(); // 번식

            //showArr();

            pair<int,int> pos = findPos();  // 가장 많이 나오는 좌표 잡기.
            //cout << pos.first << " and " << pos.second << "\n";

            attack(pos.first, pos.second);

            decreaseKiiler();

            //cout << "공격 후\n";
            //showArr();

            //cout << "TOT : " << tot << "\n";
        }
    }

    cout << tot << '\n';
    return 0;
}