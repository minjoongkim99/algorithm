#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int n, m, point = 0;
int arr[22][22];
int visited[22][22];
int T = 1;

int diceY = 0, diceX = 0, diceDir = 0;
int dice[7] = {0,1,2,3,4,5,6};
int tmp[7] = {0,1,2,3,4,5,6};

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0};

void checkDir(){
    int ny = diceY + dy[diceDir];
    int nx = diceX + dx[diceDir];

    if(ny < 0 || ny >= n || nx < 0 || nx >= n)
        diceDir = (diceDir + 2) % 4;            // 2차원 배열[][] 튕겨내기의 특수성은 항상 만족하는가?
}

void moveRight(){
    tmp[3] = dice[1];   tmp[1] = dice[4];   tmp[4] = dice[6];   tmp[6] = dice[3];
    tmp[2] = dice[2];   tmp[5] = dice[5];
    for(int i = 0; i < 7; ++i)
        dice[i] = tmp[i];
}

void moveFront(){
    tmp[1] = dice[5];   tmp[5] = dice[6];   tmp[6] = dice[2];   tmp[2] = dice[1];
    tmp[4] = dice[4];   tmp[3] = dice[3];
    for(int i = 0; i < 7; ++i)
        dice[i] = tmp[i];
}

void moveLeft(){
    tmp[4] = dice[1];   tmp[1] = dice[3];   tmp[3] = dice[6];   tmp[6] = dice[4];
    tmp[2] = dice[2];   tmp[5] = dice[5];
    for(int i = 0; i < 7; ++i)
        dice[i] = tmp[i];
}

void moveBehind(){
    tmp[1] = dice[2];   tmp[2] = dice[6];   tmp[6] = dice[5];   tmp[5] = dice[1];
    tmp[3] = dice[3];   tmp[4] = dice[4];
    for(int i = 0; i < 7; ++i)
        dice[i] = tmp[i];
}

void moveDice(){
    if(diceDir == 0) moveRight();
    else if(diceDir == 1) moveFront();
    else if(diceDir == 2) moveLeft();
    else if(diceDir == 3) moveBehind();

    diceY = diceY + dy[diceDir];      // checkDir() -> OOB처리하고 다음 방향을 미리 변경했음.
    diceX = diceX + dx[diceDir];      // 이게 가능한 이유는? 이전에 OOB처리 후 DiceDir을 바꿨기에.
}

void bfs(int i, int j){
    int cnt = 0;
    queue<pair<int,int>> q;
    q.push({i, j});
    visited[i][j] = 1;
    ++cnt;

    while(!q.empty()){
        int y = q.front().first, x = q.front().second;
        q.pop();

        for(int dir = 0; dir < 4; dir++){
            int yy = y + dy[dir];
            int xx = x + dx[dir];

            if(yy < 0 || yy >= n || xx < 0 || xx >= n) continue;
            if(visited[yy][xx]) continue;

            if(arr[yy][xx] == arr[diceY][diceX]){
                q.push({yy, xx});
                visited[yy][xx] = 1;
                ++cnt;
            }
        }
    }

    point += cnt * arr[diceY][diceX];
}

void checkVal(){
    if(dice[6] > arr[diceY][diceX]){
        diceDir = (diceDir + 1) % 4;
    }
    else if(dice[6] <arr[diceY][diceX]){
        diceDir = (diceDir + 3) % 4;
    }
}

int main() {
    cin >> n >> m;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            cin >> arr[i][j];

    for(int tc = 1; tc <= T; ++tc){
        for(int p = 1; p <= m; ++p){

            checkDir();
            
            moveDice();

            fill(&visited[0][0], &visited[0][0] + 22 * 22, 0);
    
            bfs(diceY, diceX);      // 점수까지 비교하기

            checkVal();
        }
    }

    cout << point << '\n';
    return 0;
}

// 주사위 dice, 좌표, 방향에 대한 변수들 필요
// 구르는 방향 OOB이면 180도 방향 전환 후 한 칸 움직이기. 해당 코드는 어디에 위치해야하는가? 왜 그런가?
// 주사위 굴러간다. 각 인덱스는 val 값을 가지고 있음. tmp, dice overwrite 하면 됨
// 주사위 구르면 BFS하고 cnt 센 다음 점수 화
// 주사위와 arr[][]간 좌표 비교하여 방향 설정.
