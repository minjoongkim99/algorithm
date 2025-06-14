#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

struct player {
	int x, y, d, s, gun, point;
};
player P[32];
int n, m, k;
vector<int> arr[22][22];

int loser, winner;

void showPlayerPos() {
	for (int i = 1; i <= m; ++i) {
		cout << i << "번 좌표:" << P[i].x << "," << P[i].y << "\n";
	}
}

void input() {
	cin >> n >> m >> k;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			int x;
			cin >> x;
			arr[i][j].push_back(x);
		}
	}
	for (int idx = 1; idx <= m; ++idx) {
		cin >> P[idx].x >> P[idx].y >> P[idx].d >> P[idx].s;
		P[idx].point = P[idx].gun = 0;
	}
}

void movePlayer(int idx) {
	int nx = P[idx].x + dx[P[idx].d];
	int ny = P[idx].y + dy[P[idx].d];

	if (nx < 1 || nx > n || ny < 1 || ny > n) {
		P[idx].d = (P[idx].d + 2) % 4;
	}
	P[idx].x = P[idx].x + dx[P[idx].d];
	P[idx].y = P[idx].y + dy[P[idx].d];
}

int check(int idx) {
	for (int i = 1; i <= m; ++i) {
		if (i == idx) continue;

		if (P[idx].x == P[i].x && P[idx].y == P[i].y)
			return i;
	}
	return 0;
}

void getGun(int idx) {
	int x = P[idx].x;
	int y = P[idx].y;
	sort(arr[x][y].begin(), arr[x][y].end(), greater<int>());

	if (P[idx].gun > arr[x][y][0]) return;
	else {
		int tmp = P[idx].gun;
		P[idx].gun = arr[x][y][0];
		arr[x][y].erase(arr[x][y].begin());
		arr[x][y].push_back(tmp);
	}
}

void battle(int a, int b) {
	int aPoint = P[a].gun + P[a].s;
	int bPoint = P[b].gun + P[b].s;

	if (aPoint > bPoint) {
		winner = a;
		loser = b;
	}
	else if (aPoint < bPoint) {
		winner = b;
		loser = a;
	}
	else {
		if (P[a].s > P[b].s) {
			winner = a;
			loser = b;
		}
		else {
			winner = b;
			loser = a;
		}
	}

	P[winner].point += abs(aPoint - bPoint);
}

bool isIn(int idx, int nx, int ny) {
	for (int i = 1; i <= m; ++i) {
		if (i == idx) continue;
		if (P[i].x == nx && P[i].y == ny)
			return true;
	}
	return false;
}

void loserMove() {
	int x = P[loser].x;
	int y = P[loser].y;
	arr[x][y].push_back(P[loser].gun);
	P[loser].gun = 0;

	for (int d = P[loser].d; d < P[loser].d + 4; ++d) {
		int dir = d % 4;

		int nx = P[loser].x + dx[dir];
		int ny = P[loser].y + dy[dir];

		if (nx < 1 || nx > n || ny < 1 || ny > n) continue;
		if (isIn(loser, nx, ny)) continue;
		else {
			P[loser].x = nx;
			P[loser].y = ny;
			P[loser].d = dir;
			getGun(loser);
			break;
		}
	}
}

void winnerMove() {
	getGun(winner);
}

int main() {
	int T = 1;

	for (int tc = 1; tc <= T; ++tc) {
		// init();
		input();

		for (int run = 1; run <= k; ++run) {

			for (int idx = 1; idx <= m; ++idx) {

				movePlayer(idx);

				int flag = check(idx);

				loser = winner = 0; // 초기화

				if (flag == 0) {
					getGun(idx);
				}
				else {
					battle(idx, flag);
					loserMove();
					winnerMove();
				}
			}
		}

		for (int i = 1; i <= m; ++i) {
			cout << P[i].point << ' ';
		}
		cout << '\n';
	}

	return 0;
}