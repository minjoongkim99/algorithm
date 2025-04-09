#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int n, m;
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

int arr[25][25];
int visited[25][25];

int dice[7] = { 0, 1, 2, 3, 4, 5, 6 };
// up, front, right, left, behind, down

int diceY = 0, diceX = 0, diceDir = 1;

int point = 0;

void moveUp() {
	int tmp[7];
	for (int i = 0; i < 7; ++i) {
		tmp[i] = dice[i];
	}

	dice[5] = tmp[1];
	dice[1] = tmp[2];
	dice[2] = tmp[6];
	dice[6] = tmp[5];
}

void moveRight() {
	int tmp[7];
	for (int i = 0; i < 7; ++i) {
		tmp[i] = dice[i];
	}

	dice[3] = tmp[1];
	dice[1] = tmp[4];
	dice[4] = tmp[6];
	dice[6] = tmp[3];
}

void moveDown() {
	int tmp[7];
	for (int i = 0; i < 7; ++i) {
		tmp[i] = dice[i];
	}

	dice[1] = tmp[5];
	dice[5] = tmp[6];
	dice[6] = tmp[2];
	dice[2] = tmp[1];
}

void moveLeft() {
	int tmp[7];
	for (int i = 0; i < 7; ++i) {
		tmp[i] = dice[i];
	}

	dice[1] = tmp[3];
	dice[3] = tmp[6];
	dice[6] = tmp[4];
	dice[4] = tmp[1];
}

void moveDice() {
	if (diceDir == 0) {
		moveUp();
	}
	else if (diceDir == 1) {
		moveRight();
	}
	else if (diceDir == 2) {
		moveDown();
	}
	else if (diceDir == 3) {
		moveLeft();
	}

	diceY += dy[diceDir];
	diceX += dx[diceDir];
}

void bfs() {
	fill(&visited[0][0], &visited[0][0] + 25 * 25, 0);

	queue<pair<int, int>> q;
	q.push({ diceY, diceX });
	visited[diceY][diceX] = 1; 
	int cnt = 1;

	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;
		q.pop();

		for (int dir = 0; dir < 4; ++dir) {
			int yy = y + dy[dir];
			int xx = x + dx[dir];
			
			if (yy < 0 || yy >= n || xx < 0 || xx >= n) continue;

			if (visited[yy][xx]) continue;
			if (arr[yy][xx] == arr[y][x]) {
				q.push({ yy,xx });
				visited[yy][xx] = visited[y][x] + 1;
				cnt++;
			}
		}
	}

	point += arr[diceY][diceX] * cnt;
}

/*
* 주사위는 이동할 때마다 각 면의 pos가 바뀔 것이다.
* 이동 원칙
* 1. 주사위 아랫면이 격자 값보다 크면 90도 시계방향 회전하며 이동
* 2. 주사위 아랫면이 격자 값보다 작으면 90도 반시계방향 회전하며 이동
* 3. 동일하다면 현재 방향으로 지속적으로 이동함
* 주사위의 방향과 좌표들을 기록해야함.
* 만일 OOB이면 벽튕기기이다.
*/
void redirect() {
	if (dice[6] > arr[diceY][diceX]) {
		diceDir = (diceDir + 1) % 4;
	}
	else if (dice[6] < arr[diceY][diceX]) {
		diceDir = (diceDir + 3) % 4;
	}
	
	int ny = diceY + dy[diceDir];
	int nx = diceX + dx[diceDir];

	if (ny < 0 || ny >= n || nx < 0 || nx >= n) {
		diceDir = (diceDir + 2) % 4;
	}
}

int main() {

	int T = 1;
	//cin >> T;

	for (int tc = 1; tc <= T; ++tc) {
		//global_init();
		for (int i = 0; i < 7; ++i)
			dice[i] = i;
		point = 0;
		diceX = diceY = 0;
		diceDir = 1;

		cin >> n >> m;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				cin >> arr[i][j];

		for (int run = 1; run <= m; ++run) {

			moveDice();
			//cout << "AFTER MOVE\n";
			//cout << diceY << " AND " << diceX << " DIR:" << diceDir << '\n';

			bfs();

			redirect();
			//cout << "AFTER REDIERECT\n";
			//cout << diceY << " AND " << diceX << " DIR:" << diceDir << "\n\n";

		}

		cout << point << '\n';
	}
	return 0;
}
