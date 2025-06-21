#include <iostream>
#include <algorithm>
using namespace std;

int n, m, k, c;

int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };
int ddy[4] = { -1, -1, 1, 1 };
int ddx[4] = { -1, 1, 1, -1 };

int arr[22][22];
int killer_map[22][22];

int ay, ax = 0;

int ans;

void showArr() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << arr[i][j] << '\t';
        }
        cout << '\n';
    }
}

void showKiller() {

    cout << "\nKiller Map\n";

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << killer_map[i][j] << '\t';
        }
        cout << '\n';
    }
}

void increase() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (arr[i][j] <= 0) continue;
            int cnt = 0;
            for (int dir = 0; dir < 4; ++dir) {
                int yy = i + dy[dir];
                int xx = j + dx[dir];
                if (yy < 0 || yy >= n || xx < 0 || xx >= n) continue;
                if (arr[yy][xx] <= 0) continue;
                cnt++;
            }
            arr[i][j] += cnt;
        }
    }
}

void born() {
    int tmp[22][22];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            tmp[i][j] = arr[i][j];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (arr[i][j] <= 0) continue;
            int cnt = 0;

            for (int dir = 0; dir < 4; ++dir) {
                int yy = i + dy[dir];
                int xx = j + dx[dir];

                if (yy < 0 || yy >= n || xx < 0 || xx >= n) continue;
                if (arr[yy][xx] != 0) continue;
                if (killer_map[yy][xx] > 0) continue;

                cnt++;
            }

            if (cnt == 0) continue;;
       

            for (int dir = 0; dir < 4; ++dir) {
                int yy = i + dy[dir];
                int xx = j + dx[dir];

                if (yy < 0 || yy >= n || xx < 0 || xx >= n) continue;
                if (arr[yy][xx] != 0) continue;
                if (killer_map[yy][xx] > 0) continue;

                tmp[yy][xx] += (arr[i][j] / cnt);
            }           
        }
    }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            arr[i][j] = tmp[i][j];
}

void findPos() {
    int mx = -1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int cnt = 0;
            if (arr[i][j] > 0) {
                cnt = arr[i][j];

                for (int dir = 0; dir < 4; ++dir) {
                    for (int len = 1; len <= k; ++len) {
                        int yy = i + len * ddy[dir];
                        int xx = j + len * ddx[dir];
                        
                        if (yy < 0 || yy >= n || xx < 0 || xx >= n) break;
                        if (arr[yy][xx] == -1) break;
                        if (killer_map[yy][xx] > 0) break;
                        cnt += arr[yy][xx];
                    }
                }
            }

            if (cnt > mx) {
                mx = cnt;
                ay = i;
                ax = j;
            }
        }
    }
}

void decrease() {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (killer_map[i][j] > 0)
                killer_map[i][j]--;
}

void attack() {
    if (arr[ay][ax] >= 0) {
        ans += arr[ay][ax];
        arr[ay][ax] = 0;
        killer_map[ay][ax] = c;
    }

    for (int dir = 0; dir < 4; ++dir) {
        for (int len = 1; len <= k; ++len) {
            int yy = ay + len * ddy[dir];
            int xx = ax + len * ddx[dir];

            if (yy < 0 || yy >= n || xx < 0 || xx >= n) break;
            if (arr[yy][xx] == -1) {
                killer_map[yy][xx] = c;
                break;
            }
            if (killer_map[yy][xx] > 0) {
                killer_map[yy][xx] = c;
                break;
            }
            ans += arr[yy][xx];
            arr[yy][xx] = 0;
            killer_map[yy][xx] = c;
          
        }
    }
}

void input() {
    cin >> n >> m >> k >> c;
   
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> arr[i][j];
}

int main() {
    // Please write your code here.

    int T = 1;

    for (int tc = 1; tc <= T; ++tc) {

        //global_init();

        input();
       
        for (int run = 1; run <= m; ++run) {
            increase();
            //cout << "증가 후\n";
            //showArr();

            born();
            //cout << "번식 후\n";
            //showArr();

            ay = 0; ax = 0;
            findPos();

            //cout << "POS: " << ay << " " << ax << "\n";

            decrease();

            attack();
            //cout << "공격 후\n";
            //showArr();
            //showKiller();
        }
        
        cout << ans << '\n';
    }
    return 0;
}