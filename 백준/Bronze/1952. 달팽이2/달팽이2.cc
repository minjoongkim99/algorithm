#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int arr[102][102];
int visited[102][102];

int n, m;

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0};
int ret = 0;
int main() {
    ios::sync_with_stdio(0);
    cout.tie(nullptr);				cin.tie(nullptr);

    cin >> n >> m;
    int curY = 0, curX = 0;
    int dir = 0;
    int t = 1;
    while(t < n * m){
        //cout << curY << " and " << curX << "\n";
        visited[curY][curX] = 1;
        int yy = curY + dy[dir];
        int xx = curX + dx[dir];

        if(yy < 0 || yy >= n || xx < 0 || xx >= m || visited[yy][xx] == 1){
            ret++;
            dir = (dir + 1) % 4;
            yy = curY + dy[dir];
            xx = curX + dx[dir];
        }

        curY = yy;
        curX = xx;
        t++;
    }
    cout << ret << '\n';
    return 0;
}